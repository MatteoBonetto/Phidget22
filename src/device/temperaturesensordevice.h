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

#ifndef __CPHIDGETTEMPERATURESENSORDEVICE
#define __CPHIDGETTEMPERATURESENSORDEVICE

typedef struct _PhidgetTemperatureSensorDevice *PhidgetTemperatureSensorDeviceHandle;
PhidgetReturnCode PhidgetTemperatureSensorDevice_create(PhidgetTemperatureSensorDeviceHandle *phid);

#define TEMPSENSOR_AMBIENT_FILTER_COUNT 20

#define GAIN							85.0
#define OFFSET_200						-0.0065
#define OFFSET_300						((200.0 / 237.0) * 5.0)

#define PHIDID_1048_GAIN				((80 / 2.2) + 5)
// using 53.6K + 10K offset resistors: VOffset = (4.096Vref * 10K) / (10K + 53.6K)
#define PHIDID_1048_OFFSET				(4.096 / 6.36)

struct _PhidgetTemperatureSensorDevice {
#undef devChannelCnts
#define devChannelCnts phid.deviceInfo.UDD->channelCnts.temperaturesensor
	PhidgetDevice phid;

	/* Public Members */

	uint32_t temperatureSensorDataInterval[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	double temperature[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	double temperatureChangeTrigger[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	double maxTemperature[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	double minTemperature[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	PhidgetTemperatureSensor_ThermocoupleType thermocoupleType[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];

	uint32_t voltageInputDataInterval[TEMPERATURESENSOR_MAXVOLTAGEINPUTS];
	double voltage[TEMPERATURESENSOR_MAXVOLTAGEINPUTS];
	double voltageChangeTrigger[TEMPERATURESENSOR_MAXVOLTAGEINPUTS];

	/* Private Members */

	mostime_t temperatureDeadline[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	double lastTrigger[TEMPERATURESENSOR_MAXTEMPERATURESENSORS];
	double lastVoltageTrigger[TEMPERATURESENSOR_MAXVOLTAGEINPUTS];
	mostime_t voltageDeadline[TEMPERATURESENSOR_MAXVOLTAGEINPUTS];
	double lastAmbientTrigger;
	double potentialMax, potentialMin;
	uint32_t _callcnt;
	int _interruptRate;
	int ambientSensorIndex;

	double ambientTemperatureBuffer[TEMPSENSOR_AMBIENT_FILTER_COUNT];
	int32_t ambientTemperatureIndex;
	uint32_t ambientBufferFull;
} typedef PhidgetTemperatureSensorDeviceInfo;

#endif
