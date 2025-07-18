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

#ifndef __CPHIDGETLEDARRAYDEVICE
#define __CPHIDGETLEDARRAYDEVICE

// DIGITAL OUTPUT IN
#define STATE_CHANGE  0x0C
#define STATE_INVALID 0x07

typedef struct _PhidgetLEDArrayDevice *PhidgetLEDArrayDeviceHandle;
PhidgetReturnCode PhidgetLEDArrayDevice_create(PhidgetLEDArrayDeviceHandle *phid);

#include "util/ledarraysupport.h"

struct _PhidgetLEDArrayDevice {
#undef devChannelCnts
#define devChannelCnts phid.deviceInfo.UDD->channelCnts.ledarray
	PhidgetDevice phid;

	/* Public Members */

	int powerEnabled[LEDARRAY_MAXLEDARRAYS];
	PhidgetLEDArray_ColorOrder colorOrder[LEDARRAY_MAXLEDARRAYS];
	double gamma[LEDARRAY_MAXLEDARRAYS];
	double brightness[LEDARRAY_MAXLEDARRAYS];

	/* Private Members */

	uint8_t inputsEnabled;
	uint8_t outputsEnabled;

} typedef PhidgetLEDArrayDeviceInfo;

#endif
