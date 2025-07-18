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
#include "device/frequencycounterdevice.h"

// === Internal Functions === //
static PhidgetReturnCode _sendpacket(mosiop_t iop, PhidgetFrequencyCounterDeviceHandle phid);

// initAfterOpen - sets up the initial state of an object, reading in packets from the device if needed
//				  used during attach initialization - on every attach
static PhidgetReturnCode CCONV
PhidgetFrequencyCounterDevice_initAfterOpen(PhidgetDeviceHandle device) {
	PhidgetFrequencyCounterDeviceHandle phid = (PhidgetFrequencyCounterDeviceHandle)device;
	int i;

	assert(phid);

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1054:
		phid->_interruptRate = 32;
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	// initialize triggers, set data arrays to unknown
	for (i = 0; i < phid->devChannelCnts.numFrequencyCounters; i++) {
		phid->filterType[i] = PUNK_ENUM;
		phid->filterTypeEcho[i] = PUNK_ENUM;
		phid->enabled[i] = PUNK_BOOL;
		phid->enabledEcho[i] = PUNK_BOOL;

		phid->frequencyCounterDataInterval[i] = phid->_interruptRate;
	}

	// issue one read
	waitForReads((PhidgetDeviceHandle)phid, 1, 100);

	// fill in enabledState and filterType, set other things to 0
	for (i = 0; i < phid->devChannelCnts.numFrequencyCounters; i++) {
		phid->filterType[i] = phid->filterTypeEcho[i];
		phid->enabled[i] = phid->enabledEcho[i];

		phid->countsAcc[i] = 0;
		phid->ticksAtLastCountAcc[i] = 0;
		phid->ticksAcc[i] = 0;
		phid->_frequencycounterDeadline[i] = 0;
	}
	phid->lastPacketCount = PUNK_INT32;
	phid->_callcnt = 0;

	return (EPHIDGET_OK);
}

// dataInput - parses device packets
static PhidgetReturnCode CCONV
PhidgetFrequencyCounterDevice_dataInput(PhidgetDeviceHandle device, uint8_t *buffer, size_t length) {
	PhidgetFrequencyCounterDeviceHandle phid = (PhidgetFrequencyCounterDeviceHandle)device;
	uint32_t ticksAtLastCount[FREQUENCYCOUNTER_MAXFREQUENCYCOUNTERS];
	uint32_t counts[FREQUENCYCOUNTER_MAXFREQUENCYCOUNTERS];
	PhidgetChannelHandle channel;
	int packetCount;
	mostime_t tm;
	uint32_t ticks;
	int i;

	// Setup max/min values
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1054:
		ticks = buffer[0] + (buffer[1] << 8);

		counts[0] = buffer[2] + (buffer[3] << 8) + (buffer[4] << 16);
		ticksAtLastCount[0] = buffer[5] + (buffer[6] << 8);

		counts[1] = buffer[7] + (buffer[8] << 8) + (buffer[9] << 16);
		ticksAtLastCount[1] = buffer[10] + (buffer[11] << 8);

		// Filter type echo
		if (buffer[12] & FREQCOUNTER_FLAG_CH0_LOGIC)
			phid->filterTypeEcho[0] = FILTER_TYPE_LOGIC_LEVEL;
		else
			phid->filterTypeEcho[0] = FILTER_TYPE_ZERO_CROSSING;
		if (buffer[12] & FREQCOUNTER_FLAG_CH1_LOGIC)
			phid->filterTypeEcho[1] = FILTER_TYPE_LOGIC_LEVEL;
		else
			phid->filterTypeEcho[1] = FILTER_TYPE_ZERO_CROSSING;

		// Enabled state echo
		if (buffer[12] & FREQCOUNTER_FLAG_CH0_ENABLE)
			phid->enabledEcho[0] = PTRUE;
		else
			phid->enabledEcho[0] = PFALSE;
		if (buffer[12] & FREQCOUNTER_FLAG_CH1_ENABLE)
			phid->enabledEcho[1] = PTRUE;
		else
			phid->enabledEcho[1] = PFALSE;

		packetCount = (buffer[12] & 0xF0) >> 4;
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	if ((phid->lastPacketCount != PUNK_INT32) && ((phid->lastPacketCount + 1) & 0x0F) != packetCount) {
		for (i = 0; i < phid->devChannelCnts.numFrequencyCounters; i++) {
			if ((channel = getChannel(phid, i)) != NULL) {
				PhidgetChannel_sendErrorEvent(channel, EEPHIDGET_PACKETLOST, "One or more data packets were lost");
				PhidgetRelease(&channel);
			}
		}
	}
	phid->lastPacketCount = packetCount;

	phid->_callcnt++;
	tm = CALLTM(phid);

	for (i = 0; i < phid->devChannelCnts.numFrequencyCounters; i++) {
		if (phid->enabledEcho[i] != PTRUE || phid->enabled[i] != PTRUE)
			continue;

		phid->countsAcc[i] += counts[i];
		phid->ticksAtLastCountAcc[i] = phid->ticksAcc[i] + ticksAtLastCount[i]; /* previously accumulated ticks plus current ticksAtLastCount */
		phid->ticksAcc[i] += ticks;

		if (tm < phid->_frequencycounterDeadline[i])
			continue;

		channel = getChannel(phid, i);
		if (channel == NULL)
			continue;

		bridgeSendToChannel(channel, BP_FREQUENCYDATA, 3, "%g%u%g", phid->ticksAcc[i] * FREQCOUNTER_MS_PER_TICK, phid->countsAcc[i], phid->ticksAtLastCountAcc[i] * FREQCOUNTER_MS_PER_TICK);
		PhidgetRelease(&channel);

		phid->countsAcc[i] = 0;
		phid->ticksAtLastCountAcc[i] = 0;
		phid->ticksAcc[i] = 0;

		phid->_frequencycounterDeadline[i] = tm + phid->frequencyCounterDataInterval[i];
	}
	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
PhidgetFrequencyCounterDevice_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetFrequencyCounterDeviceHandle phid = (PhidgetFrequencyCounterDeviceHandle)ch->parent;
	PhidgetReturnCode ret;

	assert(phid->phid.deviceInfo.class == PHIDCLASS_FREQUENCYCOUNTER);
	assert(ch->class == PHIDCHCLASS_FREQUENCYCOUNTER);
	assert(ch->index < phid->devChannelCnts.numFrequencyCounters);

	switch (bp->vpkt) {
	case BP_SETENABLED:
		phid->enabled[ch->index] = getBridgePacketInt32(bp, 0);
		return (_sendpacket(bp->iop, phid));
	case BP_SETDATAINTERVAL:
		phid->frequencyCounterDataInterval[ch->index] = HANDLE_DATAINTERVAL_PKT(bp, phid->_interruptRate);
		phid->_frequencycounterDeadline[ch->index] = 0;
		return (EPHIDGET_OK);
	case BP_SETFILTERTYPE:
		phid->filterType[ch->index] = (PhidgetFrequencyCounter_FilterType)getBridgePacketInt32(bp, 0);
		return (_sendpacket(bp->iop, phid));
	case BP_OPENRESET:
		// NOTE: These is a firmware bug in 1054 where at least one enableTrue,zeroCrossing packet MUST be sent to initialize a channel properly
		phid->filterType[ch->index] = FILTER_TYPE_ZERO_CROSSING;
		phid->enabled[ch->index] = PTRUE;
		ret = _sendpacket(bp->iop, phid);
		if (ret != EPHIDGET_OK)
			return (ret);
		// Reset state should be disabled
		phid->enabled[ch->index] = PFALSE;
		return (_sendpacket(bp->iop, phid));
	case BP_CLOSERESET:
		phid->enabled[ch->index] = PFALSE;
		phid->filterType[ch->index] = FILTER_TYPE_ZERO_CROSSING;
		return (_sendpacket(bp->iop, phid));
	case BP_ENABLE:
		return (EPHIDGET_OK);
	default:
		MOS_PANIC("Unexpected packet type");
	}
}

// makePacket - constructs a packet using current device state
static PhidgetReturnCode _sendpacket(mosiop_t iop, PhidgetFrequencyCounterDeviceHandle phid) {
	unsigned char buffer[MAX_OUT_PACKET_SIZE] = {0};

	// Setup max/min values
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1054:
		buffer[0] = 0;
		if (phid->enabled[0] == PTRUE)
			buffer[0] |= FREQCOUNTER_FLAG_CH0_ENABLE;
		if (phid->filterType[0] == FILTER_TYPE_LOGIC_LEVEL)
			buffer[0] |= FREQCOUNTER_FLAG_CH0_LOGIC;

		if (phid->enabled[1] == PTRUE)
			buffer[0] |= FREQCOUNTER_FLAG_CH1_ENABLE;
		if (phid->filterType[1] == FILTER_TYPE_LOGIC_LEVEL)
			buffer[0] |= FREQCOUNTER_FLAG_CH1_LOGIC;
		break;

	default:
		MOS_PANIC("Unexpected device");
	}

	return (PhidgetDevice_sendpacket(iop, (PhidgetDeviceHandle)phid, buffer, getMaxOutPacketSize((PhidgetDeviceHandle)phid)));
}

static void CCONV
PhidgetFrequencyCounterDevice_free(PhidgetDeviceHandle *phid) {

	mos_free(*phid, sizeof(struct _PhidgetFrequencyCounterDevice));
	*phid = NULL;
}

PhidgetReturnCode
PhidgetFrequencyCounterDevice_create(PhidgetFrequencyCounterDeviceHandle *phidp) {
	DEVICECREATE_BODY(FrequencyCounterDevice, PHIDCLASS_FREQUENCYCOUNTER);
	return (EPHIDGET_OK);
}
