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

#ifndef _PHIDGET_DICTIONARYDEVICE_H_
#define _PHIDGET_DICTIONARYDEVICE_H_

typedef union {
	const char *ckey;
	char *key;
} tkey_t;

typedef struct _dictent {
#define de_key key.key
	tkey_t key;
	char *de_val;
	RB_ENTRY(_dictent)
	de_link;
} dictent_t;

int dictent_compare(dictent_t *a, dictent_t *b);

typedef RB_HEAD(dictionary, _dictent) dictionary_t;
RB_PROTOTYPE(dictionary, _dictent, de_link, dictent_compare)

typedef struct _PhidgetDictionaryDevice *PhidgetDictionaryDeviceHandle;
PhidgetReturnCode PhidgetDictionaryDevice_create(PhidgetDictionaryDeviceHandle *phid);

struct _PhidgetDictionaryDevice {
	PhidgetDevice phid;

	/* Public Members */

	/* Private Members */

	int initialized;
	dictionary_t dict;
	uint32_t cnt;
} typedef PhidgetDictionaryDeviceInfo;

#endif /* _PHIDGET_DICTIONARYDEVICE_H_ */
