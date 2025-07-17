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
#include "device/leddevice.h"

// === Internal Functions === //
static PhidgetReturnCode _sendpacket(mosiop_t iop, PhidgetLEDDeviceHandle phid, int Index);

// initAfterOpen - sets up the initial state of an object, reading in packets from the device if needed
//				  used during attach initialization - on every attach
static PhidgetReturnCode CCONV
PhidgetLEDDevice_initAfterOpen(PhidgetDeviceHandle device) {
	PhidgetLEDDeviceHandle phid = (PhidgetLEDDeviceHandle)device;
	int i = 0;

	assert(phid);

	// set data arrays to unknown
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1030:
		for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
			phid->changedDutyCycle[i] = PFALSE;
			phid->nextDutyCycle[i] = PUNK_DBL;
			phid->dutyCycle[i] = PUNK_DBL;
			phid->outputState[i] = PUNK_BOOL;
		}
		break;

	case PHIDUID_1031:
	case PHIDUID_1032:
		for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
			phid->changedDutyCycle[i] = PFALSE;
			phid->nextDutyCycle[i] = PUNK_DBL;
			phid->lastDutyCycle[i] = PUNK_DBL;
			phid->dutyCycle[i] = PUNK_DBL;
			phid->outputState[i] = PUNK_BOOL;
			phid->LEDCurrentLimit[i] = PUNK_DBL;
			phid->dutyCycleEcho[i] = PUNK_DBL;
			phid->LEDCurrentLimitEcho[i] = PUNK_DBL;
			phid->outputEnabledEcho[i] = PUNK_BOOL;
		}
		phid->LEDForwardVoltageDevProp = PUNK_ENUM;
		phid->LEDCurrentLimitDevProp = PUNK_DBL;
		phid->LEDForwardVoltageEchoDevProp = PUNK_ENUM;
		phid->LEDCurrentLimitEchoDevProp = PUNK_DBL;

		for (i = 0; i < 4; i++) {
			phid->TSDCount[i] = 0;
			phid->TSDClearCount[i] = 0;
			phid->TWarnCount[i] = 0;
			phid->TWarnClearCount[i] = 0;
		}
		phid->lastOutputPacket = 0;
		phid->lastControlPacketValid = PFALSE;
		break;

	default:
		MOS_PANIC("Unexpected device");
	}

	waitForReads((PhidgetDeviceHandle)phid, 1, 100);

	// issue a read - fill in data
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1031:
		// need two reads to get the full state
		if (waitForReads((PhidgetDeviceHandle)phid, 2, 100) == EPHIDGET_OK) {
			for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				if (phid->outputEnabledEcho[i] == PTRUE)
					phid->dutyCycle[i] = round_double(phid->dutyCycleEcho[i], 3);
				else
					phid->dutyCycle[i] = 0;

				if (phid->dutyCycle[i] != PUNK_DBL)
					phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;

				phid->lastDutyCycle[i] = round_double(phid->dutyCycleEcho[i], 3);
			}
			if (phid->LEDForwardVoltageEchoDevProp != PUNK_ENUM)
				phid->LEDForwardVoltageDevProp = phid->LEDForwardVoltageEchoDevProp;
			if (phid->LEDCurrentLimitEchoDevProp != PUNK_ENUM)
				phid->LEDCurrentLimitDevProp = phid->LEDCurrentLimitEchoDevProp;
		}
		break;
	case PHIDUID_1032:
		// need three reads to get the full state
		if (waitForReads((PhidgetDeviceHandle)phid, 3, 100) == EPHIDGET_OK) {
			for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				phid->dutyCycle[i] = round_double(phid->dutyCycleEcho[i], 5);
				if (phid->dutyCycle[i] != PUNK_DBL)
					phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;
				phid->LEDCurrentLimit[i] = round_double(phid->LEDCurrentLimitEcho[i], 4);
			}
			if (phid->LEDForwardVoltageEchoDevProp != PUNK_ENUM)
				phid->LEDForwardVoltageDevProp = phid->LEDForwardVoltageEchoDevProp;
		}
		break;
	}

	return (EPHIDGET_OK);
}

// dataInput - parses device packets
static PhidgetReturnCode CCONV
PhidgetLEDDevice_dataInput(PhidgetDeviceHandle device, uint8_t *buffer, size_t length) {
	PhidgetLEDDeviceHandle phid = (PhidgetLEDDeviceHandle)device;
	PhidgetChannelHandle channel;
	int ledOpenDetectCnt;
	int outputEnableEcho;
	int powerGoodEcho;
	int faultEcho;
	int i;
	int j;

	assert(phid);
	assert(buffer);

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1031:
		switch (buffer[0] & 0x80) {
		case LED64_IN_LOW_PACKET:
			// PowerGood
			if (buffer[0] & LED64_PGOOD_FLAG)
				powerGoodEcho = PTRUE;
			else
				powerGoodEcho = PFALSE;

			// all outputs enabled (power on/off)
			if (buffer[0] & LED64_OE_FLAG)
				outputEnableEcho = PTRUE;
			else
				outputEnableEcho = PFALSE;

			// fault
			if (buffer[0] & LED64_FAULT_FLAG)
				faultEcho = PTRUE;
			else
				faultEcho = PFALSE;

			// current limit
			if (buffer[0] & LED64_CURSELA_FLAG) {
				if (buffer[0] & LED64_CURSELB_FLAG)
					phid->LEDCurrentLimitEchoDevProp = 0.08; // 80mA
				else
					phid->LEDCurrentLimitEchoDevProp = 0.04; // 40mA
			} else if (buffer[0] & LED64_CURSELB_FLAG)
				phid->LEDCurrentLimitEchoDevProp = 0.06; // 60mA
			else
				phid->LEDCurrentLimitEchoDevProp = 0.02; // 20mA

			// voltage
			if (buffer[0] & LED64_PWRSELA_FLAG) {
				if (buffer[0] & LED64_PWRSELB_FLAG)
					phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_5_0V;
				else
					phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_2_75V;
			} else if (buffer[0] & LED64_PWRSELB_FLAG)
				phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_3_9V;
			else
				phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_1_7V;

			ledOpenDetectCnt = 0;
			for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				phid->outputEnabledEcho[i] = (buffer[(i / 8) + 1] & (1 << (i % 8))) ? 1 : 0;
				if (buffer[(i / 8) + 9] & (1 << (i % 8)))
					ledOpenDetectCnt++;
			}

			// 1st 24 LED powers
			for (i = 0; i < 24; i++) {
				double ledPowerTemp;
				ledPowerTemp = ((double)buffer[i + 17] / 127.0);
				phid->dutyCycleEcho[i] = ledPowerTemp;
			}

			// We can guess that the fault is a TSD if there is no LOD
			if (faultEcho) {
				phid->TSDCount[0]++;
				phid->TSDClearCount[0] = 30; // 500ms of no faults before we clear it

				if (ledOpenDetectCnt)
					phid->TSDCount[0] = 0;

				// send out some error events on faults
				// TODO: we could also send LED Open Detect?

				// we have counted three fault flags with no LODs - TSD
				// less then 3 counts, and it could be a false positive
				// if outputs are not enabled then the fault should be guaranteed as a TSD
				if (phid->TSDCount[0] >= 3 || (phid->TSDCount[0] < 3 && outputEnableEcho == PFALSE)) {
					phid->TSDCount[0] = 3;
					for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
						if ((channel = getChannel(phid, i)) != NULL) {
							PhidgetChannel_sendErrorEventThrottled(channel, EEPHIDGET_OVERTEMP, "Thermal Shutdown detected.");
							PhidgetRelease(&channel);
						}
					}
				}
			} else {
				if (phid->TSDClearCount[0] > 0)
					phid->TSDClearCount[0]--;
				else
					phid->TSDCount[0] = 0;
			}

			if (!powerGoodEcho) {
				for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
					if ((channel = getChannel(phid, i)) != NULL) {
						PhidgetChannel_sendErrorEventThrottled(channel, EEPHIDGET_BADPOWER, "Bad power supply detected.");
						PhidgetRelease(&channel);
					}
				}
			}
			break;
		case LED64_IN_HIGH_PACKET:
			// last 40 LED powers
			for (i = 24; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				double ledPowerTemp;
				ledPowerTemp = ((double)buffer[i - 23] / 127.0);
				phid->dutyCycleEcho[i] = ledPowerTemp;
			}
			break;
		}
		break;

	case PHIDUID_1032:
		switch (buffer[0] & 0x60) {
		case LED64_M3_IN_MISC_PACKET:
			// PowerGood
			if (buffer[0] & LED64_PGOOD_FLAG)
				powerGoodEcho = PTRUE;
			else
				powerGoodEcho = PFALSE;

			if (!powerGoodEcho) {
				for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
					if ((channel = getChannel(phid, i)) != NULL) {
						PhidgetChannel_sendErrorEventThrottled(channel, EEPHIDGET_BADPOWER, "Bad power supply detected.");
						PhidgetRelease(&channel);
					}
				}
			}

			// voltage
			if (buffer[0] & LED64_PWRSELA_FLAG) {
				if (buffer[0] & LED64_PWRSELB_FLAG)
					phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_5_0V;
				else
					phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_2_75V;
			} else if (buffer[0] & LED64_PWRSELB_FLAG)
				phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_3_9V;
			else
				phid->LEDForwardVoltageEchoDevProp = LED_FORWARD_VOLTAGE_1_7V;

			// Temperature Warnings
			for (i = 0; i < 4; i++) {
				if (buffer[1] & (0x01 << i)) {
					phid->TWarnCount[i]++;
					phid->TWarnClearCount[i] = 20; // 480ms of no faults before we clear it

					if (phid->TWarnCount[i] >= 10) { // 240 ms of fault before we call it
						for (j = 0; j < phid->devChannelCnts.numDigitalOutputs; j++) {
							if ((channel = getChannel(phid, j)) != NULL) {
								SEND_ERROR_EVENT_THROTTLED(channel, EEPHIDGET_OVERTEMP, "Temperature Warning detected on chip %d.", i);
								PhidgetRelease(&channel);
							}
						}
						phid->TWarnCount[i]--; // so we don't overflow the char
					}
				} else {
					if (phid->TWarnClearCount[i] > 0)
						phid->TWarnClearCount[i]--;
					else
						phid->TWarnCount[i] = 0;
				}
			}

			// Temperature Errors
			for (i = 0; i < 4; i++) {
				if (buffer[1] & (0x10 << i)) {
					phid->TSDCount[i]++;
					phid->TSDClearCount[i] = 20; // 480ms of no faults before we clear it

					if (phid->TSDCount[i] >= 10) // 240 ms of fault before we call it
					{
						for (j = 0; j < phid->devChannelCnts.numDigitalOutputs; j++) {
							if ((channel = getChannel(phid, j)) != NULL) {
								SEND_ERROR_EVENT_THROTTLED(channel, EEPHIDGET_OVERTEMP, "Temperature Error detected on chip %d.", i);
								PhidgetRelease(&channel);
							}
						}
						phid->TSDCount[i]--; // so we don't overflow the char
					}
				} else {
					if (phid->TSDClearCount[i] > 0)
						phid->TSDClearCount[i]--;
					else
						phid->TSDCount[i] = 0;
				}
			}

			// Current Limit
			for (i = 0; i < 64; i++) {
				int index = (i * 6) / 8 + 2;
				int currentLimitInt = 0;
				switch (i % 4) {
				case 0:
					currentLimitInt = buffer[index] & 0x3F;
					break;
				case 1:
					currentLimitInt = ((buffer[index] >> 6) & 0x03) + ((buffer[index + 1] << 2) & 0x3C);
					break;
				case 2:
					currentLimitInt = ((buffer[index] >> 4) & 0x0F) + ((buffer[index + 1] << 4) & 0x30);
					break;
				case 3:
					currentLimitInt = (buffer[index] >> 2) & 0x3F;
					break;
				}
				phid->LEDCurrentLimitEcho[i] = (currentLimitInt / 63.0) * LED64_CURRENTLIMIT;
			}

			break;
		case LED64_M3_IN_LOW_PACKET:
			for (i = 0; i < 32; i++) {
				int ledPowerInt;
				int index = (i * 12) / 8 + 9;

				if (i % 2 == 0)
					ledPowerInt = buffer[index] + ((buffer[index + 1] & 0x0F) << 8);
				else
					ledPowerInt = ((buffer[index] & 0xF0) >> 4) + (buffer[index + 1] << 4);

				phid->dutyCycleEcho[i] = (ledPowerInt / 4095.0);
			}
			break;
		case LED64_M3_IN_HIGH_PACKET:
			for (i = 0; i < 32; i++) {
				int ledPowerInt;
				int index = (i * 12) / 8 + 9;

				if (i % 2 == 0)
					ledPowerInt = buffer[index] + ((buffer[index + 1] & 0x0F) << 8);
				else
					ledPowerInt = ((buffer[index] & 0xF0) >> 4) + (buffer[index + 1] << 4);

				phid->dutyCycleEcho[i + 32] = (ledPowerInt / 4095.0);
			}
			break;
		}
		break;

	default:
		MOS_PANIC("Unexpected device");
	}

	return (EPHIDGET_OK);
}

static int
configured(PhidgetLEDDeviceHandle phid, int index) {
	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1030:
		return (PTRUE);
	case PHIDUID_1031:
		if (phid->LEDForwardVoltageDevProp == (PhidgetDigitalOutput_LEDForwardVoltage)PUNK_ENUM || phid->LEDCurrentLimitDevProp == PUNK_DBL)
			return (PFALSE);
		return (PTRUE);
	case PHIDUID_1032:
		if (phid->LEDForwardVoltageDevProp == (PhidgetDigitalOutput_LEDForwardVoltage)PUNK_ENUM || phid->LEDCurrentLimit[index] == PUNK_DBL)
			return (PFALSE);
		return (PTRUE);
	default:
		MOS_PANIC("Unexpected device");
	}
}

static PhidgetReturnCode CCONV
PhidgetLEDDevice_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetLEDDeviceHandle phid = (PhidgetLEDDeviceHandle)ch->parent;
	PhidgetReturnCode ret;

	assert(phid->phid.deviceInfo.class == PHIDCLASS_LED);
	assert(ch->class == PHIDCHCLASS_DIGITALOUTPUT);
	assert(ch->index < phid->devChannelCnts.numDigitalOutputs);

	switch (bp->vpkt) {
	case BP_SETSTATE:
		if (!configured(phid, ch->index))
			return (MOS_ERROR(bp->iop, EPHIDGET_NOTCONFIGURED, "Voltage and Current Limit must be configured before outputs can be enabled."));
		if ((double)getBridgePacketInt32(bp, 0) != phid->dutyCycle[ch->index]) {
			phid->changedDutyCycle[ch->index] = PTRUE;
			phid->nextDutyCycle[ch->index] = (double)getBridgePacketInt32(bp, 0);
			return (_sendpacket(bp->iop, phid, LED64_NORMAL_PACKET));
		}
		return (EPHIDGET_OK);

	case BP_SETDUTYCYCLE:
		if (!configured(phid, ch->index))
			return (MOS_ERROR(bp->iop, EPHIDGET_NOTCONFIGURED, "Voltage and Current Limit must be configured before outputs can be enabled."));
		if (getBridgePacketDouble(bp, 0) != phid->dutyCycle[ch->index]) {
			phid->changedDutyCycle[ch->index] = PTRUE;
			phid->nextDutyCycle[ch->index] = getBridgePacketDouble(bp, 0);
			return (_sendpacket(bp->iop, phid, LED64_NORMAL_PACKET));
		}
		return (EPHIDGET_OK);

	case BP_SETLEDFORWARDVOLTAGE:
		// Only send a packet if we changed the whole-board voltage
		if (phid->LEDForwardVoltageDevProp != getBridgePacketInt32(bp, 0)) {
			phid->LEDForwardVoltageDevProp = getBridgePacketInt32(bp, 0);
			ret = _sendpacket(bp->iop, phid, LED64_CONTROL_PACKET);
			// Need to update the other channels because forward voltage is board wide
			if (ret == EPHIDGET_OK)
				bridgeSendToChannelSiblings(ch, BP_LEDFORWARDVOLTAGECHANGE, 1, "%d", phid->LEDForwardVoltageDevProp);
			return (ret);
		}
		return EPHIDGET_OK;

	case BP_SETLEDCURRENTLIMIT:
		switch (phid->phid.deviceInfo.UDD->uid) {
		case PHIDUID_1031:
			if (phid->LEDCurrentLimitDevProp != getBridgePacketDouble(bp, 0)) {
				phid->LEDCurrentLimitDevProp = getBridgePacketDouble(bp, 0);
				return (_sendpacket(bp->iop, phid, LED64_CONTROL_PACKET));
			}
			return EPHIDGET_OK;
		case PHIDUID_1032:
			phid->LEDCurrentLimit[ch->index] = getBridgePacketDouble(bp, 0);
			return (_sendpacket(bp->iop, phid, LED64_CONTROL_PACKET));
		default:
			return (EPHIDGET_UNSUPPORTED);
		}

	case BP_OPENRESET:
	case BP_CLOSERESET:
		if (phid->dutyCycle[ch->index] != 0) {
			phid->changedDutyCycle[ch->index] = PTRUE;
			phid->nextDutyCycle[ch->index] = 0;
			return (_sendpacket(bp->iop, phid, LED64_NORMAL_PACKET));
		}
	case BP_ENABLE:
		return (EPHIDGET_OK);
	default:
		MOS_PANIC("Unexpected packet type");
	}
}

// getPacket - used by write thread to get the next packet to send to device
static PhidgetReturnCode _sendpacket(mosiop_t iop, PhidgetLEDDeviceHandle phid, int Index) {
	unsigned char buffer[MAX_OUT_PACKET_SIZE] = {0};
	int numLeds = 0;
	int i = 0;

	switch (phid->phid.deviceInfo.UDD->uid) {
	case PHIDUID_1030:
		// construct the packet, with up to 4 LED sets
		for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
			if (phid->changedDutyCycle[i] && numLeds < 4) {
				phid->dutyCycle[i] = phid->nextDutyCycle[i];
				phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;
				phid->changedDutyCycle[i] = PFALSE;
				phid->nextDutyCycle[i] = PUNK_DBL;
				buffer[numLeds * 2] = i;
				// 0-1 -> 0-63
				buffer[numLeds * 2 + 1] = (uint8_t)round((phid->dutyCycle[i]) * 63.0);
				numLeds++;
			}
		}

		assert(numLeds >= 1);

		// fill up any remaining bufferfer space with valid data - sending 0's will mess things up
		for (; numLeds < 4; numLeds++) {
			buffer[numLeds * 2] = buffer[(numLeds - 1) * 2];
			buffer[numLeds * 2 + 1] = buffer[(numLeds - 1) * 2 + 1];
		}
		break;
	case PHIDUID_1031:
		// control packet
		if (Index == LED64_CONTROL_PACKET) {

			buffer[0] = LED64_CONTROL_PACKET;

			buffer[1] = 0;
			if (phid->LEDCurrentLimitDevProp >= 0.080)
				buffer[1] |= (LED64_CURSELA_FLAG | LED64_CURSELB_FLAG);
			else if (phid->LEDCurrentLimitDevProp >= 0.060)
				buffer[1] |= LED64_CURSELB_FLAG;
			else if (phid->LEDCurrentLimitDevProp >= 0.040)
				buffer[1] |= LED64_CURSELA_FLAG;

			if (phid->LEDForwardVoltageDevProp != PUNK_ENUM) {
				switch (phid->LEDForwardVoltageDevProp) {
				case LED_FORWARD_VOLTAGE_1_7V:
					break;
				case LED_FORWARD_VOLTAGE_2_75V:
					buffer[1] |= LED64_PWRSELA_FLAG;
					break;
				case LED_FORWARD_VOLTAGE_3_9V:
					buffer[1] |= LED64_PWRSELB_FLAG;
					break;
				case LED_FORWARD_VOLTAGE_5_0V:
					buffer[1] |= (LED64_PWRSELA_FLAG | LED64_PWRSELB_FLAG);
					break;
				default:
					MOS_PANIC("Unexpected voltage");
				}
			}

			// Don't need to resend an identical packet
			if (phid->lastControlPacketValid) {
				if (!memcmp(phid->lastControlPacket, buffer, MAX_OUT_PACKET_SIZE))
					return (EPHIDGET_OK);
			}

			memcpy(phid->lastControlPacket, buffer, MAX_OUT_PACKET_SIZE);
			phid->lastControlPacketValid = PTRUE;
		}
		// LED packet
		else {
			int bright_packet = PFALSE;
			int output_upper = PFALSE;
			int output_lower = PFALSE;
			// decide if we need to use a normal brightness packet, or if we can use a high efficiency output packet
			for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				if (phid->changedDutyCycle[i]) {
					if ((phid->nextDutyCycle[i] != phid->lastDutyCycle[i]) && phid->nextDutyCycle[i] != 0)
						bright_packet = PTRUE;
					else {
						if (i < 32)
							output_lower = PTRUE;
						else
							output_upper = PTRUE;
					}
				}
			}

			// only sends brightness changes - not changes between 0 and a brightness
			if (bright_packet) {
				// construct the packet, with up to 4 LED sets
				for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
					if (phid->changedDutyCycle[i] && numLeds < 4 && phid->nextDutyCycle[i] != 0) {
						phid->dutyCycle[i] = phid->nextDutyCycle[i];
						phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;
						phid->lastDutyCycle[i] = phid->nextDutyCycle[i];
						phid->changedDutyCycle[i] = PFALSE;
						phid->nextDutyCycle[i] = PUNK_DBL;
						buffer[numLeds * 2] = i;
						// 0-1 -> 0-127
						buffer[numLeds * 2 + 1] = (uint8_t)round((phid->dutyCycle[i]) * 127.0);
						if (buffer[numLeds * 2 + 1])
							buffer[numLeds * 2 + 1] |= 0x80; // this turns the LED on when set brightness > 0;
						numLeds++;
					}
				}

				assert(numLeds >= 1);

				// fill up any remaining bufferfer space with valid data - sending 0's will mess things up
				// this just replicates data - doesn't send anything
				for (; numLeds < 4; numLeds++) {
					buffer[numLeds * 2] = buffer[(numLeds - 1) * 2];
					buffer[numLeds * 2 + 1] = buffer[(numLeds - 1) * 2 + 1];
				}
			} else {
				// send lower packet
				if ((phid->lastOutputPacket == 0 && output_lower) || (phid->lastOutputPacket != 0 && !output_upper)) {
					buffer[0] = LED64_OUTLOW_PACKET;
					for (i = 0; i < 32; i++) {
						if (phid->changedDutyCycle[i]) {
							phid->dutyCycle[i] = phid->nextDutyCycle[i];
							phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;
							phid->changedDutyCycle[i] = PFALSE;
							phid->nextDutyCycle[i] = PUNK_DBL;
						}
						if (phid->dutyCycle[i] > 0)
							buffer[i / 8 + 1] |= (1 << (i % 8));
					}
					phid->lastOutputPacket = 1;
				}
				// send upper packet
				else {
					buffer[0] = LED64_OUTHIGH_PACKET;
					for (i = 32; i < 64; i++) {
						if (phid->changedDutyCycle[i]) {
							phid->dutyCycle[i] = phid->nextDutyCycle[i];
							phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;
							phid->changedDutyCycle[i] = PFALSE;
							phid->nextDutyCycle[i] = PUNK_DBL;
						}
						if (phid->dutyCycle[i] > 0)
							buffer[i / 8 - 3] |= (1 << (i % 8));
					}
					phid->lastOutputPacket = 0;
				}
			}
		}
		break;
	case PHIDUID_1032:
		// control packet
		if (Index == LED64_CONTROL_PACKET) {
			buffer[0] = LED64_M3_CONTROL_PACKET;

			if (phid->LEDForwardVoltageDevProp == PUNK_ENUM) {
				buffer[0] |= LED64_PWRSELA_FLAG;
			} else {
				switch (phid->LEDForwardVoltageDevProp) {
				case LED_FORWARD_VOLTAGE_1_7V:
					break;
				case LED_FORWARD_VOLTAGE_2_75V:
					buffer[0] |= LED64_PWRSELA_FLAG;
					break;
				case LED_FORWARD_VOLTAGE_3_9V:
					buffer[0] |= LED64_PWRSELB_FLAG;
					break;
				case LED_FORWARD_VOLTAGE_5_0V:
					buffer[0] |= (LED64_PWRSELA_FLAG | LED64_PWRSELB_FLAG);
					break;
				default:
					MOS_PANIC("Unexpected voltage");
				}
			}

			for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				int value;
				int bufferIndex = (i * 6) / 8 + 1;

				// Default is 20 mA
				if (phid->LEDCurrentLimit[i] == PUNK_DBL)
					phid->LEDCurrentLimit[i] = 0.020;
				value = round((phid->LEDCurrentLimit[i] / LED64_CURRENTLIMIT) * 63.0);

				switch (i % 4) {
				case 0:
					buffer[bufferIndex] |= (value & 0x3F);
					break;
				case 1:
					buffer[bufferIndex] |= ((value << 6) & 0xC0);
					buffer[bufferIndex + 1] |= ((value >> 2) & 0x0F);
					break;
				case 2:
					buffer[bufferIndex] |= ((value << 4) & 0xF0);
					buffer[bufferIndex + 1] |= ((value >> 4) & 0x03);
					break;
				case 3:
					buffer[bufferIndex] |= ((value << 2) & 0xFC);
					break;
				}
			}

			// Don't need to resend an identical packet
			if (phid->lastControlPacketValid) {
				if (!memcmp(phid->lastControlPacket, buffer, MAX_OUT_PACKET_SIZE))
					return (EPHIDGET_OK);
			}

			memcpy(phid->lastControlPacket, buffer, MAX_OUT_PACKET_SIZE);
			phid->lastControlPacketValid = PTRUE;
		}
		// LED packet
		else {
			int output_upper = PFALSE;
			int output_lower = PFALSE;
			int startIndex;

			for (i = 0; i < phid->devChannelCnts.numDigitalOutputs; i++) {
				if (phid->changedDutyCycle[i]) {
					if (i < 32)
						output_lower = PTRUE;
					else
						output_upper = PTRUE;
				}
			}

			// send lower packet
			if ((phid->lastOutputPacket == 0 && output_lower) || (phid->lastOutputPacket != 0 && !output_upper)) {
				buffer[0] = LED64_M3_OUT_LOW_PACKET;
				startIndex = 0;
				phid->lastOutputPacket = 1;
			}
			// send upper packet
			else {
				buffer[0] = LED64_M3_OUT_HIGH_PACKET;
				startIndex = 32;
				phid->lastOutputPacket = 0;
			}

			for (i = startIndex; i < startIndex + 32; i++) {
				int value;
				int bufferIndex = ((i - startIndex) * 12) / 8 + 1;

				if (phid->changedDutyCycle[i]) {
					phid->dutyCycle[i] = phid->nextDutyCycle[i];
					phid->outputState[i] = phid->dutyCycle[i] ? PTRUE : PFALSE;
					phid->changedDutyCycle[i] = PFALSE;
					phid->nextDutyCycle[i] = PUNK_DBL;
				}

				// Default is 0 %
				if (phid->dutyCycle[i] == PUNK_DBL) {
					phid->dutyCycle[i] = 0;
					phid->outputState[i] = PFALSE;
				}
				value = round((phid->dutyCycle[i]) * 4095.0);

				if (i % 2 == 0) {
					buffer[bufferIndex] |= (value & 0xFF);
					buffer[bufferIndex + 1] |= ((value >> 8) & 0x0F);
				} else {
					buffer[bufferIndex] |= ((value << 4) & 0xF0);
					buffer[bufferIndex + 1] |= ((value >> 4) & 0xFF);
				}
			}
		}
		break;
	default:
		MOS_PANIC("Unexpected device");
	}

	return (PhidgetDevice_sendpacket(iop, (PhidgetDeviceHandle)phid, buffer, getMaxOutPacketSize((PhidgetDeviceHandle)phid)));
}

static void CCONV
PhidgetLEDDevice_free(PhidgetDeviceHandle *phid) {

	mos_free(*phid, sizeof(struct _PhidgetLEDDevice));
	*phid = NULL;
}

PhidgetReturnCode
PhidgetLEDDevice_create(PhidgetLEDDeviceHandle *phidp) {
	DEVICECREATE_BODY(LEDDevice, PHIDCLASS_LED);
	return (EPHIDGET_OK);
}