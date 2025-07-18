/*
 * This file is part of libphidget22
 *
 * Copyright (c) 2015-2022 Phidgets Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "phidgetbase.h"
#include "device/accelerometerdevice.h"

// === Internal Functions === //

// initAfterOpen - sets up the initial state of an object, reading in packets from the device if needed
//				  used during attach initialization - on every attach
static PhidgetReturnCode CCONV
PhidgetAccelerometerDevice_initAfterOpen(PhidgetDeviceHandle device) {
	PhidgetAccelerometerDeviceHandle phid = (PhidgetAccelerometerDeviceHandle)device;
	int i;

	assert(phid);

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1008:
		phid->_numAxes = 2;
		phid->_maxAcceleration = 2.0;
		phid->_minAcceleration = -2.0;
		phid->_interruptRate = 39; // NOTE: Interrupt rate is 16ms but ~41% are NAKed
		phid->accelerationChangeTrigger[0] = 0;
		phid->dataInterval[0] = phid->_interruptRate;
		break;
	case PHIDUID_1053:
		phid->_numAxes = 2;
		phid->_maxAcceleration = 5.0;
		phid->_minAcceleration = -5.0;
		phid->_interruptRate = 16;
		phid->accelerationChangeTrigger[0] = 0;
		phid->dataInterval[0] = phid->_interruptRate;
		break;
	case PHIDUID_1059:
		phid->_numAxes = 3;
		phid->_maxAcceleration = 3.0;
		phid->_minAcceleration = -3.0;
		phid->_interruptRate = 16;
		phid->accelerationChangeTrigger[0] = 0;
		phid->dataInterval[0] = phid->_interruptRate;
		break;
	case PHIDUID_MOT0100_USB:
		phid->_numAxes = 3;
		phid->_maxAcceleration = 8.0;
		phid->_minAcceleration = -8.0;
		phid->_interruptRate = 1;
		phid->accelerationChangeTrigger[0] = PUNK_DBL;
		phid->dataInterval[0] = 8;
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	// initialize triggers, set data arrays to unknown
	for (i = 0; i < phid->_numAxes; i++) {
		phid->_accelerationLastTrigger[i] = PUNK_DBL;
		phid->acceleration[0][i] = PUNK_DBL;
	}

	phid->timestamp[0] = 0;
	phid->_accelDeadline[0] = 0;

	phid->_callcnt = 0;

	// issue one read
	waitForReads((PhidgetDeviceHandle)phid, 1, 100);

	return (EPHIDGET_OK);
}

static PhidgetReturnCode
MOT0100_USB_dataInput(PhidgetAccelerometerDeviceHandle phid, uint8_t *buffer, size_t length) {
	double axis[ACCELEROMETER_MAXACCELEROMETERSAXES] = {0};
	PhidgetChannelHandle channel;
	size_t dataIndex = 0;
	int i;

	// this timestamp is for the latest data
	phid->timestamp[0] = unpack32(&buffer[0]);
	dataIndex += 4;

	// add data to data buffer
	for (i = 0; i < 3; i++) {
		axis[i] = unpackfloat(&buffer[dataIndex + (i * 4)]);
		if (!isnan(axis[i]))
			phid->acceleration[0][i] = round_double(axis[i], 6);
		else
			phid->acceleration[0][i] = axis[i];
	}
	dataIndex += 12;

	if ((channel = getChannel(phid, 0)) != NULL) {
		switch (channel->UCD->uid) {
		case PHIDCHUID_MOT0100_ACCELEROMETER_100_USB:
			if (length > dataIndex && buffer[dataIndex] & 0x0)
				PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGE, "One or more accelerometer readings is out of range");
			bridgeSendToChannel(channel, BP_ACCELERATIONCHANGE, 2, "%3G%g", phid->acceleration[0], phid->timestamp[0]);
			break;
		default:
			MOS_PANIC("Invalid Channel UID");
		}
	}

	return EPHIDGET_OK;
}

static PhidgetReturnCode CCONV
PhidgetAccelerometerDevice_dataInput(PhidgetDeviceHandle device, uint8_t *buffer, size_t length) {
	PhidgetAccelerometerDeviceHandle phid = (PhidgetAccelerometerDeviceHandle)device;
	double axis[ACCELEROMETER_MAXACCELEROMETERSAXES] = {0};
	PhidgetChannelHandle channel;
	int fireSaturation;
	int fireEvent;
	mostime_t tm;
	int data;
	int i;

	assert(phid);
	assert(buffer);

	// Parse device packets - store data locally
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1008:
		data = (int16_t)((uint16_t)buffer[0] + ((uint16_t)buffer[1] << 8));
		axis[0] = round_double((((double)data - 16384) / 2000), 4);
		data = (int16_t)((uint16_t)buffer[2] + ((uint16_t)buffer[3] << 8));
		axis[1] = round_double((((double)data - 16384) / 2000), 4);
		break;
	case PHIDUID_1053:
		data = ((uint16_t)buffer[0] + ((uint16_t)buffer[1] << 8));
		axis[0] = round_double((((double)(data - 32768)) / 4000), 5);
		data = ((uint16_t)buffer[2] + ((uint16_t)buffer[3] << 8));
		axis[1] = round_double((((double)(data - 32768)) / 4000), 5);
		break;
	case PHIDUID_1059:
		data = ((uint16_t)buffer[0] + ((uint16_t)buffer[1] << 8));
		axis[0] = round_double((((double)(data - 32768)) / 6553.6), 5);
		data = ((uint16_t)buffer[2] + ((uint16_t)buffer[3] << 8));
		axis[1] = round_double((((double)(data - 32768)) / 6553.6), 5);
		data = ((uint16_t)buffer[4] + ((uint16_t)buffer[5] << 8));
		axis[2] = round_double((((double)(data - 32768)) / 6553.6), 5);
		break;
	case PHIDUID_MOT0100_USB:
		return MOT0100_USB_dataInput(phid, buffer, length);
	default:
		MOS_PANIC("Unexpected device");
	}

	phid->timestamp[0] += phid->_interruptRate;

	// Make sure values are within defined range, and store to structure
	for (i = 0; i < phid->_numAxes; i++) {
		if (axis[i] > phid->_maxAcceleration)
			axis[i] = PUNK_DBL;
		if (axis[i] < phid->_minAcceleration)
			axis[i] = PUNK_DBL;

		phid->acceleration[0][i] = axis[i];
	}

	phid->_callcnt++;
	tm = CALLTM(phid);

	if (tm < phid->_accelDeadline[0])
		return (EPHIDGET_OK);

	// Now, notify any channels
	channel = getChannel(phid, 0);
	if (channel == NULL)
		return (EPHIDGET_OK);

	fireSaturation = PFALSE;
	fireEvent = PFALSE;
	for (i = 0; i < phid->_numAxes; i++) {
		phid->acceleration[0][i] = axis[i];
		if (phid->acceleration[0][i] == PUNK_DBL) {
			fireSaturation = PTRUE;
		} else if (fabs(phid->acceleration[0][i] - phid->_accelerationLastTrigger[i]) >= phid->accelerationChangeTrigger[0] || phid->_accelerationLastTrigger[i] == PUNK_DBL) {
			fireEvent = PTRUE;
		}
	}

	if (fireSaturation) {
		PhidgetChannel_sendErrorEventThrottled(channel, EEPHIDGET_SATURATION, "Saturation Detected.");
	} else if (fireEvent) {
		bridgeSendToChannel(channel, BP_ACCELERATIONCHANGE, 2, "%3G%g", phid->acceleration[0], phid->timestamp[0]);
		for (i = 0; i < phid->_numAxes; i++)
			phid->_accelerationLastTrigger[i] = phid->acceleration[0][i];
		phid->_accelDeadline[0] = tm + phid->dataInterval[0];
	}

	PhidgetRelease(&channel);

	return (EPHIDGET_OK);
}

static PhidgetReturnCode
MOT0100_USB_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetAccelerometerDeviceHandle phid = (PhidgetAccelerometerDeviceHandle)ch->parent;
	uint8_t buf[25];
	size_t len;

	switch (ch->UCD->uid) {
	case PHIDCHUID_MOT0100_ACCELEROMETER_100_USB:
		switch (bp->vpkt) {
		case BP_SETDATAINTERVAL:
			phid->dataInterval[ch->index] = HANDLE_DATAINTERVAL_PKT(bp, 1);
			pack16(buf, phid->dataInterval[ch->index]);
			len = 2;
			return PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_SAMPLED_SETDATAINTERVAL, ch->uniqueIndex, buf, &len, 100);
		case BP_SETCHANGETRIGGER:
			phid->accelerationChangeTrigger[ch->index] = getBridgePacketDouble(bp, 0);
			packfloat(buf, (float)phid->accelerationChangeTrigger[ch->index]);
			len = 4;
			return PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_AXES_SETAXISCHANGETRIGGER, ch->uniqueIndex, buf, &len, 100);
		case BP_OPENRESET:
		case BP_CLOSERESET:
			len = 0;
			return PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_PHIDGET_RESET, ch->uniqueIndex, NULL, &len, 100);
		case BP_ENABLE:
			len = 0;
			return PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_PHIDGET_ENABLE, ch->uniqueIndex, NULL, &len, 100);
		default:
			MOS_PANIC("Unexpected packet type");
		}
	default:
		MOS_PANIC("Invalid Channel UID");
	}
}

static PhidgetReturnCode CCONV
PhidgetAccelerometerDevice_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetAccelerometerDeviceHandle phid = (PhidgetAccelerometerDeviceHandle)ch->parent;

	assert(phid->phid.deviceInfo.class == PHIDCLASS_ACCELEROMETER);
	assert(ch->class == PHIDCHCLASS_ACCELEROMETER);
	assert(ch->index == 0);

	switch (phid->phid.deviceInfo.UDD->uid) {
	default:
		switch (bp->vpkt) {
		case BP_SETDATAINTERVAL:
			phid->dataInterval[ch->index] = HANDLE_DATAINTERVAL_PKT(bp, phid->_interruptRate);
			phid->_accelDeadline[ch->index] = 0;
			return (EPHIDGET_OK);
		case BP_SETCHANGETRIGGER:
			phid->accelerationChangeTrigger[ch->index] = getBridgePacketDouble(bp, 0);
			return (EPHIDGET_OK);
		case BP_OPENRESET:
		case BP_CLOSERESET:
		case BP_ENABLE:
			return (EPHIDGET_OK);
		default:
			MOS_PANIC("Unexpected packet type");
		}
		break;
	case PHIDUID_MOT0100_USB:
		return MOT0100_USB_bridgeInput(ch, bp);
	}
}

static void CCONV
PhidgetAccelerometerDevice_free(PhidgetDeviceHandle *phid) {
	mos_free(*phid, sizeof(struct _PhidgetAccelerometerDevice));
	*phid = NULL;
}

PhidgetReturnCode
PhidgetAccelerometerDevice_create(PhidgetAccelerometerDeviceHandle *phidp) {
	DEVICECREATE_BODY(AccelerometerDevice, PHIDCLASS_ACCELEROMETER);
	return (EPHIDGET_OK);
}
