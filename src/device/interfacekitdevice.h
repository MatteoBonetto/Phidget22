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

#ifndef __CPHIDGETINTERFACEKITDEVICE
#define __CPHIDGETINTERFACEKITDEVICE

typedef struct _PhidgetInterfaceKitDevice *PhidgetInterfaceKitDeviceHandle;
PhidgetReturnCode PhidgetInterfaceKitDevice_create(PhidgetInterfaceKitDeviceHandle *phid);

#define PACKET_OUTPUT_STATE_ECHO  1
#define PACKET_FAILSAFE_TRIGGERED 2

#define IFKIT_MAXSENSORCHANGE	  1000 // BL: Had to check for this, might as well use a define

// usually it is <=8, but could be bigger if a packet gets missed.
#define IFKIT_MAX_DATA_PER_PACKET 16
// in milliseconds - this is the fastest hardware rate of any device
#define IFKIT_MAX_DATA_RATE		  1
// 1 second is the longest between events that we support
#define IFKIT_MIN_DATA_RATE		  1000

struct _PhidgetInterfaceKitDevice {
#undef devChannelCnts
#define devChannelCnts phid.deviceInfo.UDD->channelCnts.interfacekit
	PhidgetDevice phid;

	/* Public Members */

	uint32_t capacitiveTouchDataInterval[INTERFACEKIT_MAXCAPACITIVETOUCHES];
	double touchValueChangeTrigger[INTERFACEKIT_MAXCAPACITIVETOUCHES];
	double touchValue[INTERFACEKIT_MAXCAPACITIVETOUCHES];
	int isTouched[INTERFACEKIT_MAXCAPACITIVETOUCHES];

	uint8_t inputState[INTERFACEKIT_MAXDIGITALINPUTS];

	double dutyCycle[INTERFACEKIT_MAXDIGITALOUTPUTS];
	uint8_t outputState[INTERFACEKIT_MAXDIGITALOUTPUTS];

	uint32_t voltageInputDataInterval[INTERFACEKIT_MAXVOLTAGEINPUTS];
	PhidgetVoltageInput_SensorType voltageSensorType[INTERFACEKIT_MAXVOLTAGEINPUTS];
	double voltage[INTERFACEKIT_MAXVOLTAGEINPUTS];
	double voltageChangeTrigger[INTERFACEKIT_MAXVOLTAGEINPUTS];
	double voltageSensorValueChangeTrigger[INTERFACEKIT_MAXVOLTAGEINPUTS];

	uint32_t voltageRatioInputDataInterval[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	PhidgetVoltageRatioInput_SensorType voltageRatioSensorType[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	double voltageRatio[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	double voltageRatioChangeTrigger[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	double voltageRatioSensorValueChangeTrigger[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];

	/* Private Members */

	double referenceVoltage;

	uint8_t ratiometric;
	uint8_t ratiometricEcho;
	uint8_t ratiometricSwitching;

	uint8_t _outputStateSet[INTERFACEKIT_MAXDIGITALOUTPUTS];
	uint8_t failsafeState[INTERFACEKIT_MAXDIGITALOUTPUTS];

	double sensorVoltageLastValue[INTERFACEKIT_MAXVOLTAGEINPUTS];
	double sensorVoltageAccumulator[INTERFACEKIT_MAXVOLTAGEINPUTS];
	int sensorVoltageAccumulatorCount[INTERFACEKIT_MAXVOLTAGEINPUTS];
	int sensorVoltageInterruptCount[INTERFACEKIT_MAXVOLTAGEINPUTS];

	double sensorRatioLastValue[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	double sensorRatioAccumulator[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	int sensorRatioAccumulatorCount[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	int sensorRatioInterruptCount[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	int gotSensorData[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];
	Phidget_EventMode eventMode[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];

	int proximity[INTERFACEKIT_MAXCAPACITIVETOUCHES];
	double touchInputLastValue[INTERFACEKIT_MAXCAPACITIVETOUCHES];

	// Shared between voltage input, ratio and cap touch
	uint32_t dataInterval[INTERFACEKIT_MAXVOLTAGERATIOINPUTS];

	uint32_t _interruptRate;
	uint32_t dataRateMax, dataRateMin;

	int32_t lastPacketCount;
	int maxDataPerPacket;

	int dataSinceAttach;
} typedef PhidgetInterfaceKitDeviceInfo;

#endif
