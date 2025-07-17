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

#ifndef __CPHIDGETPHSENSORDEVICE
#define __CPHIDGETPHSENSORDEVICE

typedef struct _PhidgetPHSensorDevice *PhidgetPHSensorDeviceHandle;
PhidgetReturnCode PhidgetPHSensorDevice_create(PhidgetPHSensorDeviceHandle *phid);

struct _PhidgetPHSensorDevice {
#undef devChannelCnts
#define devChannelCnts phid.deviceInfo.UDD->channelCnts.phsensor
	PhidgetDevice phid;

	/* Public Members */

	uint32_t PHSensorDataInterval[PHSENSOR_MAXPHSENSORS];
	double PH[PHSENSOR_MAXPHSENSORS];
	double PHChangeTrigger[PHSENSOR_MAXPHSENSORS];
	double correctionTemperature[PHSENSOR_MAXPHSENSORS];

	uint32_t voltageInputDataInterval[PHSENSOR_MAXVOLTAGEINPUTS];
	double voltage[PHSENSOR_MAXVOLTAGEINPUTS];
	double voltageChangeTrigger[PHSENSOR_MAXVOLTAGEINPUTS];

	/* Private Members */

	double potentialMax, potentialMin;
	double phMin, phMax;

	double lastVoltageTrigger[PHSENSOR_MAXVOLTAGEINPUTS];
	double lastPHTrigger[PHSENSOR_MAXPHSENSORS];

	uint32_t _interruptRate;
	mostime_t voltageDeadline[PHSENSOR_MAXVOLTAGEINPUTS];
	mostime_t phDeadline[PHSENSOR_MAXPHSENSORS];
	uint32_t _callcnt;

} typedef PhidgetPHSensorDeviceInfo;

#endif
