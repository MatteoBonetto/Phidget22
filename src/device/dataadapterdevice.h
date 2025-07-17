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

#ifndef __CPHIDGETDATAADAPTERDEVICE
#define __CPHIDGETDATAADAPTERDEVICE

// DIGITAL OUTPUT IN
#define STATE_CHANGE				   0x0C
#define STATE_INVALID				   0x07

#define DATAADAPTER_PACKET_GETIOSTATUS 0

typedef struct _PhidgetDataAdapterDevice *PhidgetDataAdapterDeviceHandle;
PhidgetReturnCode PhidgetDataAdapterDevice_create(PhidgetDataAdapterDeviceHandle *phid);

#include "util/dataadaptersupport.h"

struct _PhidgetDataAdapterDevice {
#undef devChannelCnts
#define devChannelCnts phid.deviceInfo.UDD->channelCnts.dataadapter
	PhidgetDevice phid;

	/* Public Members */

	PhidgetDataAdapter_Frequency frequency[DATAADAPTER_MAXDATAADAPTERS];
	uint32_t dataBits[DATAADAPTER_MAXDATAADAPTERS];
	PhidgetDataAdapter_SPIMode SPIMode[DATAADAPTER_MAXDATAADAPTERS];
	PhidgetDataAdapter_SPIChipSelect SPIChipSelect[DATAADAPTER_MAXDATAADAPTERS];
	PhidgetDataAdapter_Endianness endianness[DATAADAPTER_MAXDATAADAPTERS];

	uint8_t inputState[DATAADAPTER_MAXDIGITALINPUTS];
	Phidget_InputMode inputMode[DATAADAPTER_MAXDIGITALINPUTS];

	double dutyCycle[DATAADAPTER_MAXDIGITALOUTPUTS];
	int outputState[DATAADAPTER_MAXDIGITALOUTPUTS];

	Phidget_DataAdapterVoltage dataAdapterVoltageDevProp;

	/* Private Members */

	uint8_t inputsEnabled;
	uint8_t outputsEnabled;

	double baudRate;

} typedef PhidgetDataAdapterDeviceInfo;

#endif
