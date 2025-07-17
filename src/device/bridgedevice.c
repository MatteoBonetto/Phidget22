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
#include "device/bridgedevice.h"

// === Internal Functions === //
static PhidgetReturnCode _sendpacket(mosiop_t iop, PhidgetBridgeDeviceHandle phid);
static void PhidgetBridgeDevice_updateBridgeIntervals(PhidgetChannelHandle ch, PhidgetBridgeDeviceHandle phid, BridgePacket *bp);

// initAfterOpen - sets up the initial state of an object, reading in packets from the device if needed
//				  used during attach initialization - on every attach
static PhidgetReturnCode CCONV
PhidgetBridgeDevice_initAfterOpen(PhidgetDeviceHandle device) {
	PhidgetBridgeDeviceHandle phid = (PhidgetBridgeDeviceHandle)device;
	uint8_t buffer[MAX_IN_PACKET_SIZE];
	PhidgetReturnCode ret;
	double interval;
	size_t len;
	int i;

	assert(phid);

	// Setup max/min values
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1046_GAINBUG:
	case PHIDUID_1046:
		phid->dataRateMin = 1000;
		phid->dataRateMax = 8;
		for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
			phid->bridgeMax[i] = 1.000;
			phid->bridgeMin[i] = -1.000;
		}
		break;
	case PHIDUID_1046_1:
		phid->dataRateMin = 1000;
		phid->dataRateMax = 1;
		for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
			phid->bridgeMax[i] = 1.000;
			phid->bridgeMin[i] = -1.000;
		}
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	// initialize triggers, set data arrays to unknown
	for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
		phid->bridgeEnabled[i] = PUNK_BOOL;
		phid->bridgeGain[i] = PUNK_ENUM;
		phid->voltageRatioInputDataInterval[i] = PUNK_DBL;
		phid->voltageRatio[i] = PUNK_DBL;
		phid->voltageRatioChangeTrigger[i] = 0;

		phid->enabledEcho[i] = PUNK_BOOL;
		phid->gainEcho[i] = PUNK_ENUM;
		phid->bridgeLastTrigger[i] = PUNK_DBL;
		phid->outOfRange[i] = PFALSE;
		phid->chEnabledBugNotValid[i] = PFALSE;
	}
	phid->ch0EnableOverride = 0;
	phid->dataRate = PUNK_UINT32;
	phid->dataRateEcho = PUNK_UINT32;

	// Read in device state
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1046_GAINBUG:
	case PHIDUID_1046:
		// issue one read
		waitForReads((PhidgetDeviceHandle)phid, 1, 100);
		for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
			phid->bridgeEnabled[i] = phid->enabledEcho[i];
			phid->bridgeGain[i] = phid->gainEcho[i];
			if (phid->dataRateEcho != PUNK_UINT32)
				phid->voltageRatioInputDataInterval[i] = phid->dataRateEcho;
		}
		phid->dataRate = phid->dataRateEcho;
		break;
	case PHIDUID_1046_1:
		len = (4 * phid->devChannelCnts.numVoltageRatioInputs) + 1;
		ret = PhidgetDevice_transferpacket(NULL, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_DEVICE_READ, 0, 0, buffer, &len, 100);
		if (ret != EPHIDGET_OK)
			return ret;
		for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
			phid->bridgeEnabled[i] = ((buffer[0] & (1 << i)) != 0);
			interval = unpackfloat(&buffer[(4 * i) + 1]);
			if (interval <= 60000)
				phid->voltageRatioInputDataInterval[i] = interval;
		}
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	return (EPHIDGET_OK);
}

// dataInput - parses device packets
static PhidgetReturnCode
_1046_1_dataInput(PhidgetBridgeDeviceHandle phid, uint8_t *buffer, size_t length) {
	PhidgetChannelHandle channel;
	int chIndex;

	chIndex = buffer[1];
	switch (buffer[0]) {
	case VINT_PACKET_TYPE_VOLTAGERATIOINPUT_VOLTAGERATIOCHANGE:
		phid->voltageRatio[chIndex] = unpackfloat(&buffer[2]);
		if ((channel = getChannel(phid, chIndex)) != NULL) {
			// Send out events
			if (length > 6) {
				switch (buffer[6]) {
				case VINT_PACKET_ERRORBYTE_OUTOFRANGEHIGH:
					PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGEHIGH, "The sensor reading is too high for the selected gain mode.");
					break;
				case VINT_PACKET_ERRORBYTE_OUTOFRANGELOW:
					PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGELOW, "The sensor reading is too low for the selected gain mode.");
					break;
				case VINT_PACKET_ERRORBYTE_OUTOFRANGE:
				default:
					PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGE, "Value is unknown");
					break;
				}
			}

			bridgeSendToChannel(channel, BP_VOLTAGERATIOCHANGE, 1, "%g", phid->voltageRatio[chIndex]);
			PhidgetRelease(&channel);
		}
		return (EPHIDGET_OK);
	case VINT_PACKET_TYPE_VOLTAGERATIOINPUT_SATURATION:
		if ((channel = getChannel(phid, chIndex)) != NULL) {
			// Send out events
			switch ((int8_t)buffer[2]) {
			case 1:
				PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGEHIGH, "The sensor reading is too high for the selected gain mode.");
				break;
			case -1:
				PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGELOW, "The sensor reading is too low for the selected gain mode.");
				break;
			default:
				PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_OUTOFRANGE, "Value is unknown");
				break;
			}
			PhidgetRelease(&channel);
		}
		return (EPHIDGET_OK);
	default:
		MOS_PANIC("Unexpected packet type");
	}
}

static PhidgetReturnCode CCONV
PhidgetBridgeDevice_dataInput(PhidgetDeviceHandle device, uint8_t *buffer, size_t length) {
	PhidgetBridgeDeviceHandle phid = (PhidgetBridgeDeviceHandle)device;
	double bridgeval[BRIDGE_MAXVOLTAGERATIOINPUTS];
	int gotdata[BRIDGE_MAXVOLTAGERATIOINPUTS] = {0};
	PhidgetChannelHandle channel;
	int dataRateRaw;
	int roundingFactor;
	int bridgeRawVal;
	double bridgeMax;
	double bridgeMin;
	uint8_t err;
	double gain;
	int i;

	assert(phid);
	assert(buffer);

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1046_1:
		return _1046_1_dataInput(phid, buffer, length);
	case PHIDUID_1046_GAINBUG:
	case PHIDUID_1046:
		// Output Data Rate (Hz) = dataRateRaw * 8
		dataRateRaw = ((buffer[4] & 0x03) << 8) + buffer[5];
		// in ms
		phid->dataRateEcho = dataRateRaw * 8;

		for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {

			// gain
			switch (buffer[(i / 2) + 2] >> ((i % 2) ? 0 : 4) & 0x0F) {
			default:
			case 0x00:
				phid->gainEcho[i] = BRIDGE_GAIN_1;
				gain = 1;
				roundingFactor = 9;
				break;
			case 0x03:
				phid->gainEcho[i] = BRIDGE_GAIN_8;
				gain = 8;
				roundingFactor = 10;
				break;
			case 0x04:
				phid->gainEcho[i] = BRIDGE_GAIN_16;
				gain = 16;
				roundingFactor = 11;
				break;
			case 0x05:
				phid->gainEcho[i] = BRIDGE_GAIN_32;
				gain = 32;
				roundingFactor = 11;
				break;
			case 0x06:
				phid->gainEcho[i] = BRIDGE_GAIN_64;
				gain = 64;
				roundingFactor = 11;
				break;
			case 0x07:
				phid->gainEcho[i] = BRIDGE_GAIN_128;
				gain = 128;
				roundingFactor = 12;
				break;
			}

			if (gain == 1) {
				bridgeMax = 1.000;
				bridgeMin = -1.000;
			} else {
				// with PGA, allow +-99.5%, because if doesn't clamp properly
				bridgeMax = 0.995 / gain;
				bridgeMin = -0.995 / gain;
			}

			phid->enabledEcho[i] = (buffer[0] & (0x01 << i)) ? PTRUE : PFALSE;
			// enabled and have data
			if (phid->bridgeEnabled[i] == PTRUE && phid->enabledEcho[i] && (buffer[0] & (0x10 << i))) {
				// Don't count data this time - wait for next event
				if (phid->chEnabledBugNotValid[i] == PTRUE) {
					bridgeval[i] = PUNK_DBL;
					phid->chEnabledBugNotValid[i] = PFALSE;
				} else {
					bridgeRawVal = (buffer[i * 3 + 6] << 16) + (buffer[i * 3 + 7] << 8) + buffer[i * 3 + 8];
					bridgeval[i] = round_double(((bridgeRawVal - 0x800000) / (double)0x800000) / (double)gain, roundingFactor);

					err = (buffer[1] & (0x01 << i)) ? PTRUE : PFALSE;

					if (err || bridgeval[i] > bridgeMax || bridgeval[i] < bridgeMin) {
						if ((channel = getChannel(phid, i)) != NULL) {
							if (bridgeval[i] > bridgeMax)
								PhidgetChannel_sendErrorEventThrottled(channel, EEPHIDGET_OUTOFRANGE, "Overrange condition detected on input, try lowering the gain.");
							else if (bridgeval[i] < bridgeMin)
								PhidgetChannel_sendErrorEventThrottled(channel, EEPHIDGET_OUTOFRANGE, "Underrange condition detected on input, try lowering the gain.");
							PhidgetRelease(&channel);
						}

						bridgeval[i] = PUNK_DBL;
					}
				}
				gotdata[i] = PTRUE;
			} else if (!phid->enabledEcho[i] || phid->bridgeEnabled[i] != PTRUE) {
				bridgeval[i] = PUNK_DBL;
				gotdata[i] = PTRUE;
			}

			// decrement until 0 - this is related to a firmware bug
			if (phid->ch0EnableOverride) {
				phid->ch0EnableOverride--;
				if (phid->ch0EnableOverride == 0)
					_sendpacket(NULL, phid);
			}
		}
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
		if (gotdata[i])
			phid->voltageRatio[i] = bridgeval[i];
	}

	for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
		if ((channel = getChannel(phid, i)) != NULL) {
			// Send out events
			if (gotdata[i] && phid->voltageRatio[i] != PUNK_DBL && (fabs(phid->voltageRatio[i] - phid->bridgeLastTrigger[i]) >= phid->voltageRatioChangeTrigger[i] || phid->bridgeLastTrigger[i] == PUNK_DBL)) {
				bridgeSendToChannel(channel, BP_VOLTAGERATIOCHANGE, 1, "%g", phid->voltageRatio[i]);
				phid->bridgeLastTrigger[i] = phid->voltageRatio[i];
			}
			PhidgetRelease(&channel);
		}
	}

	return (EPHIDGET_OK);
}

static PhidgetReturnCode
_1046_1_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetBridgeDeviceHandle phid = (PhidgetBridgeDeviceHandle)ch->parent;
	unsigned char buffer[MAX_OUT_PACKET_SIZE] = {0};
	PhidgetReturnCode ret;
	size_t len;

	switch (bp->vpkt) {
	case BP_SETENABLED:
		buffer[0] = (uint8_t)getBridgePacketInt32(bp, 0) ? 0xFF : 0x00;
		len = 1;
		ret = PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_VOLTAGERATIOINPUT_BRIDGEENABLED, ch->uniqueIndex, buffer, &len, 100);
		if (ret != EPHIDGET_OK)
			return ret;

		phid->bridgeEnabled[ch->index] = (buffer[0] != 0);
		PhidgetBridgeDevice_updateBridgeIntervals(ch, phid, bp);
		return EPHIDGET_OK;
	case BP_SETDATAINTERVAL:
		if (bp->entrycnt > 1)
			packfloat(buffer, getBridgePacketDouble(bp, 1));
		else
			packfloat(buffer, (float)getBridgePacketUInt32(bp, 0));
		len = 4;
		ret = (PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_SAMPLED_SETDATAINTERVAL, ch->uniqueIndex, buffer, &len, 100));
		if (ret != EPHIDGET_OK)
			return ret;

		len = 4;
		ret = (PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_READ, VINT_PACKET_TYPE_SAMPLED_SETDATAINTERVAL, ch->uniqueIndex, buffer, &len, 100));
		if (ret != EPHIDGET_OK)
			return ret;

		phid->voltageRatioInputDataInterval[ch->index] = unpackfloat(buffer);

		PhidgetBridgeDevice_updateBridgeIntervals(ch, phid, bp);
		return EPHIDGET_OK;
	case BP_SETCHANGETRIGGER:
		pack32(buffer, (uint32_t)(getBridgePacketDouble(bp, 0) * 0x80000000u));
		len = 4;
		return (PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_VOLTAGERATIOINPUT_SETVOLTAGERATIOCHANGETRIGGER, ch->uniqueIndex, buffer, &len, 100));
	case BP_SETBRIDGEGAIN:
		buffer[0] = getBridgePacketInt32(bp, 0);
		len = 1;
		return (PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_VOLTAGERATIOINPUT_BRIDGEGAIN, ch->uniqueIndex, buffer, &len, 100));
	case BP_OPENRESET:
	case BP_CLOSERESET:
		len = 0;
		phid->bridgeEnabled[ch->index] = 0;
		ret = PhidgetDevice_transferpacket(bp->iop, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_PHIDGET_RESET, ch->uniqueIndex, buffer, &len, 100);
		if (ret != EPHIDGET_OK)
			return ret;
		PhidgetBridgeDevice_updateBridgeIntervals(ch, phid, bp);
		return (EPHIDGET_OK);
	case BP_ENABLE:
		PhidgetBridgeDevice_updateBridgeIntervals(ch, phid, bp);
		return (EPHIDGET_OK);
	default:
		MOS_PANIC("Unexpected packet type");
	}
}

static PhidgetReturnCode CCONV
PhidgetBridgeDevice_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetBridgeDeviceHandle phid = (PhidgetBridgeDeviceHandle)ch->parent;
	PhidgetChannelHandle channel;
	PhidgetReturnCode ret;
	int i;

	assert(phid->phid.deviceInfo.class == PHIDCLASS_BRIDGE);
	assert(ch->class == PHIDCHCLASS_VOLTAGERATIOINPUT);
	assert(ch->index < phid->devChannelCnts.numVoltageRatioInputs);

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1046_1:
		return _1046_1_bridgeInput(ch, bp);
	case PHIDUID_1046_GAINBUG:
	case PHIDUID_1046:
		switch (bp->vpkt) {
		case BP_SETCHANGETRIGGER:
			phid->voltageRatioChangeTrigger[ch->index] = getBridgePacketDouble(bp, 0);
			return (EPHIDGET_OK);

		case BP_SETDATAINTERVAL:
			// XXX - figure out what firmware is doing and reflect the true rate back to the channel layer, and here.
			phid->voltageRatioInputDataInterval[ch->index] = getBridgePacketUInt32(bp, 0);
			phid->dataRate = phid->voltageRatioInputDataInterval[ch->index];
			ret = _sendpacket(bp->iop, phid);
			// Need to update the other channels because the data interval is board-wide
			for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
				if ((channel = getChannel(phid, i)) != NULL) {
					bridgeSendToChannel(channel, BP_DATAINTERVALCHANGE, 1, "%u", getBridgePacketUInt32(bp, 0));
					PhidgetRelease(&channel);
				}
			}
			return (ret);

		case BP_SETBRIDGEGAIN:
			switch ((PhidgetVoltageRatioInput_BridgeGain)getBridgePacketInt32(bp, 0)) {
			case BRIDGE_GAIN_1:
			case BRIDGE_GAIN_8:
			case BRIDGE_GAIN_16:
			case BRIDGE_GAIN_32:
			case BRIDGE_GAIN_64:
			case BRIDGE_GAIN_128:
				phid->bridgeGain[ch->index] = (PhidgetVoltageRatioInput_BridgeGain)getBridgePacketInt32(bp, 0);
				return (_sendpacket(bp->iop, phid));
			default:
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "Specified gain is not supported by this device."));
			}

		case BP_SETENABLED:
			phid->bridgeEnabled[ch->index] = (uint8_t)getBridgePacketInt32(bp, 0);
			return (_sendpacket(bp->iop, phid));

		case BP_OPENRESET:
		case BP_CLOSERESET:
			phid->bridgeGain[ch->index] = BRIDGE_GAIN_1;
			phid->bridgeEnabled[ch->index] = PFALSE;
			// NOTE: not resetting data interval because it affects multiple channels.
			return (_sendpacket(bp->iop, phid));

		case BP_ENABLE:
			return (EPHIDGET_OK);
		default:
			MOS_PANIC("Unexpected packet type");
		}
		break;
	default:
		MOS_PANIC("Unexpected device");
	}
}

static void PhidgetBridgeDevice_updateBridgeIntervals(PhidgetChannelHandle ch, PhidgetBridgeDeviceHandle phid, BridgePacket *bp) {
	uint8_t buffer[MAX_IN_PACKET_SIZE];
	PhidgetChannelHandle channel;
	PhidgetReturnCode ret;
	int integerInterval;
	double interval;
	size_t len;
	int i;

	len = (4 * phid->devChannelCnts.numVoltageRatioInputs) + 1;
	ret = PhidgetDevice_transferpacket(NULL, (PhidgetDeviceHandle)phid, PHIDGETUSB_REQ_DEVICE_READ, 0, 0, buffer, &len, 100);
	if (ret != EPHIDGET_OK)
		return;
	for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
		phid->bridgeEnabled[i] = ((buffer[0] & (1 << i)) != 0);
		interval = unpackfloat(&buffer[(4 * i) + 1]);
		if (interval <= 60000)
			phid->voltageRatioInputDataInterval[i] = interval;
		else
			phid->voltageRatioInputDataInterval[i] = PUNK_DBL;
	}

	for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
		interval = phid->voltageRatioInputDataInterval[i];

		if (interval == PUNK_DBL)
			continue;

		integerInterval = round((interval > 0) ? interval : 1);

		if (i == ch->index) {
			if (bp->vpkt == BP_CLOSERESET)
				continue;
			if (bp->vpkt != BP_SETDATAINTERVAL) {
				addBridgePacketDouble(bp, interval, "DataIntervalResp");
			} else {
				setBridgePacketUInt32(bp, integerInterval, 0);
				if (bp->entrycnt > 1)
					setBridgePacketDouble(bp, interval, 1);
				else
					addBridgePacketDouble(bp, interval, "");
			}
		}

		if ((channel = getChannel(phid, i)) != NULL) {
			bridgeSendToChannel(channel, BP_DATAINTERVALCHANGE, 2, "%u%g", integerInterval, interval);
			PhidgetRelease(&channel);
		}
	}
}

// makePacket - constructs a packet using current device state
static PhidgetReturnCode _sendpacket(mosiop_t iop, PhidgetBridgeDeviceHandle phid) {
	unsigned char buffer[MAX_OUT_PACKET_SIZE] = {0};
	int dataRateRaw;
	int gainRaw;
	int i;

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1046_GAINBUG:
	case PHIDUID_1046:
		// ms->raw
		if (phid->dataRate == PUNK_UINT32)
			dataRateRaw = 1;
		else
			dataRateRaw = phid->dataRate / 8;

		buffer[0] = 0;
		buffer[1] = 0;
		buffer[2] = 0;
		for (i = 0; i < phid->devChannelCnts.numVoltageRatioInputs; i++) {
			// Deal with some firmware bugs
			if (phid->phid.deviceInfo.UDD->uid == PHIDUID_1046_GAINBUG) {
				if (phid->bridgeGain[i] != phid->gainEcho[i] && (uint32_t)phid->bridgeGain[i] != PUNK_ENUM) {
					// anytime we change gain on any channel, we have to enable channel 0, and leave it enabled for at least 250ms
					phid->ch0EnableOverride = 256 / 8; // USB interval is 8ms, this is decremented by one each DATA packet until it gets back to 0.
				}

				if (phid->enabledEcho[i] == PFALSE && phid->bridgeEnabled[i] == PTRUE) {
					// 1st data after a channel is enabled can be bad, so we just ignore this.
					phid->chEnabledBugNotValid[i] = PTRUE;
				}
			}

			if (phid->bridgeEnabled[i] == PTRUE)
				buffer[0] |= (0x01 << i);

			if ((uint32_t)phid->bridgeGain[i] == PUNK_ENUM)
				phid->bridgeGain[i] = BRIDGE_GAIN_1;

			switch (phid->bridgeGain[i]) {
			case BRIDGE_GAIN_1:
				gainRaw = 0x00;
				break;
			case BRIDGE_GAIN_8:
				gainRaw = 0x03;
				break;
			case BRIDGE_GAIN_16:
				gainRaw = 0x04;
				break;
			case BRIDGE_GAIN_32:
				gainRaw = 0x05;
				break;
			case BRIDGE_GAIN_64:
				gainRaw = 0x06;
				break;
			case BRIDGE_GAIN_128:
				gainRaw = 0x07;
				break;
			default:
				MOS_PANIC("Unexpected Gain");
			}
			buffer[(i / 2) + 1] |= gainRaw << ((i % 2) ? 0 : 4);
		}

		// Deal with some firmware bugs
		if (phid->phid.deviceInfo.UDD->uid == PHIDUID_1046_GAINBUG && phid->ch0EnableOverride) {
			// override and enable ch0
			buffer[0] |= 0x01;
		}

		buffer[3] = dataRateRaw & 0xFF;
		buffer[4] = (dataRateRaw >> 8) & 0x03;
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	return (PhidgetDevice_sendpacket(iop, (PhidgetDeviceHandle)phid, buffer, getMaxOutPacketSize((PhidgetDeviceHandle)phid)));
}

static void CCONV
PhidgetBridgeDevice_free(PhidgetDeviceHandle *phid) {

	mos_free(*phid, sizeof(struct _PhidgetBridgeDevice));
	*phid = NULL;
}

PhidgetReturnCode
PhidgetBridgeDevice_create(PhidgetBridgeDeviceHandle *phidp) {
	DEVICECREATE_BODY(BridgeDevice, PHIDCLASS_BRIDGE);
	return (EPHIDGET_OK);
}
