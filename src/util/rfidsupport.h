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

#ifndef __RFIDSUPPORT
#define __RFIDSUPPORT

#define RFIDDevice_MAX_TAG_STRING_LEN 25

#if PHIDUID_NFC0000_0_400_USB_SUPPORTED
#define RFID_MAX_PACKET_LENGTH 4096
#define RFID_NFC_NDEF_FLAG		0x80

typedef enum RFID_TXDroppedReason {
	RFID_TX_DROPPED_UNKNOWN = 0,
	RFID_TX_DROPPED_TIMEOUT = 1,
	RFID_TX_DROPPED_CORRUPT = 2,
	RFID_TX_DROPPED_BUSY = 3,
	RFID_TX_DROPPED_NOT_CONFIGURED = 4,
	RFID_TX_DROPPED_TOOBIG = 5
} RFID_TXDroppedReason;

#define USB_OUT_PACKET_OVERHEAD		  5
#define USB_IN_PACKET_OVERHEAD		  5
#define NEW_PACKET_FLAG				  0x8000
#define WAIT_RESP_FLAG				  0x4000

#define NEW_RX_READY				  0xFFFF
#define NO_ACTIVE_PACKET			  0xFFFF
#define ANONYMOUS_PACKET_ID			  0x0000
#endif

PhidgetReturnCode RFIDSupport_waitForTag(mosiop_t iop, PhidgetChannelHandle ch, const char *tagString, int timeout, mos_mutex_t *tagLock);
PhidgetReturnCode RFIDSupport_setLatestTagString(mosiop_t iop, PhidgetChannelHandle ch, const char *tagString);

#if PHIDUID_NFC0000_0_400_USB_SUPPORTED
PhidgetReturnCode CCONV PhidgetRFIDSupport_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp);
PhidgetReturnCode CCONV PhidgetRFIDSupport_dataInput(PhidgetChannelHandle ch, const uint8_t *buffer, size_t length);
#endif

typedef struct {

	char latestTagString[RFIDDevice_MAX_TAG_STRING_LEN];

#if PHIDUID_NFC0000_0_400_USB_SUPPORTED
	uint16_t usbInPacketCount;
	uint16_t packetID;
	uint16_t rxPacketID;

	uint16_t responsePacketID;

	uint8_t lastData[RFID_MAX_PACKET_LENGTH];
	size_t lastDataLength;

	uint16_t ackID;

	uint16_t rxPacketError;

	uint16_t droppedPacketID;
	RFID_TXDroppedReason droppedPacketReason;

	uint8_t storedPacket[RFID_MAX_PACKET_LENGTH];
	size_t storedPacketLength;

	uint8_t responsePacket[RFID_MAX_PACKET_LENGTH];
	size_t responseLength;
	PhidgetDataAdapter_PacketErrorCode responseError;

#endif //PHIDUID_NFC0000_0_400_USB_SUPPORTED

} PhidgetRFIDSupport, *PhidgetRFIDSupportHandle;

void PhidgetRFIDSupport_free(PhidgetRFIDSupportHandle *arg);
PhidgetReturnCode PhidgetRFIDSupport_create(PhidgetRFIDSupportHandle *ir);
void PhidgetRFIDSupport_init(PhidgetRFIDSupportHandle ir);

void PhidgetRFIDSupport_setExpectedTag(PhidgetRFID_Protocol protocol, const char *tagString, char *expectedTagString);

#endif
