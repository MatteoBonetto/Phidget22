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

#ifndef __CPHIDGETBRIDGEDEVICE
#define __CPHIDGETBRIDGEDEVICE

typedef struct _PhidgetBridgeDevice *PhidgetBridgeDeviceHandle;
PhidgetReturnCode PhidgetBridgeDevice_create(PhidgetBridgeDeviceHandle *phid);

struct _PhidgetBridgeDevice {
#undef devChannelCnts
#define devChannelCnts phid.deviceInfo.UDD->channelCnts.bridge
	PhidgetDevice phid;

	/* Public Members */

	uint8_t bridgeEnabled[BRIDGE_MAXVOLTAGERATIOINPUTS];
	PhidgetVoltageRatioInput_BridgeGain bridgeGain[BRIDGE_MAXVOLTAGERATIOINPUTS];
	double voltageRatioInputDataInterval[BRIDGE_MAXVOLTAGERATIOINPUTS];
	double voltageRatio[BRIDGE_MAXVOLTAGERATIOINPUTS];
	double voltageRatioChangeTrigger[BRIDGE_MAXVOLTAGERATIOINPUTS];

	/* Private Members */

	uint8_t enabledEcho[BRIDGE_MAXVOLTAGERATIOINPUTS];
	uint32_t dataRate;

	PhidgetVoltageRatioInput_BridgeGain gainEcho[BRIDGE_MAXVOLTAGERATIOINPUTS];
	double bridgeLastTrigger[BRIDGE_MAXVOLTAGERATIOINPUTS];

	uint32_t dataRateMin, dataRateMax, dataRateEcho;
	double bridgeMin[BRIDGE_MAXVOLTAGERATIOINPUTS], bridgeMax[BRIDGE_MAXVOLTAGERATIOINPUTS];

	uint8_t outOfRange[BRIDGE_MAXVOLTAGERATIOINPUTS];

	// Firmware bug handling
	uint8_t chEnabledBugNotValid[BRIDGE_MAXVOLTAGERATIOINPUTS];
	uint8_t ch0EnableOverride;
} typedef PhidgetBridgeDeviceInfo;

#endif
