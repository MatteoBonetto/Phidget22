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
#include "util/rfidsupport.h"

// Access the PhidgetRFIDSupport struct via the channel private pointer
#define RFID_SUPPORT(ch) ((PhidgetRFIDSupportHandle)(((PhidgetChannelHandle)(ch))->private))

#if PHIDUID_NFC0000_0_400_USB_SUPPORTED
PhidgetReturnCode requestData(PhidgetChannelHandle ch, BridgePacket *bp);
#endif

/*
 * Public API
 */

const uint8_t PhidgetRFIDSupport_hexChar[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'};

PhidgetReturnCode
RFIDSupport_setLatestTagString(mosiop_t iop, PhidgetChannelHandle ch, const char *tagString) {

	PhidgetRFIDSupportHandle rfidSupport = RFID_SUPPORT(ch);

	mos_strncpy(rfidSupport->latestTagString, tagString, sizeof(rfidSupport->latestTagString) - 1);

	return EPHIDGET_OK;
}

PhidgetReturnCode
RFIDSupport_waitForTag(mosiop_t iop, PhidgetChannelHandle ch, const char *tagString, int timeout, mos_mutex_t *tagLock) {

	PhidgetRFIDSupportHandle rfidSupport = RFID_SUPPORT(ch);

	// Wait for this tag to show up
	while (timeout > 0) {
		if (tagLock == NULL)
			PhidgetLock(ch);
		else
			mos_mutex_lock(tagLock);

		if (!strncmp(rfidSupport->latestTagString, tagString, RFIDDevice_MAX_TAG_STRING_LEN)) {
			if (tagLock == NULL)
				PhidgetUnlock(ch);
			else
				mos_mutex_unlock(tagLock);
			return (EPHIDGET_OK);
		}
		if (tagLock == NULL)
			PhidgetUnlock(ch);
		else
			mos_mutex_unlock(tagLock);
		mos_usleep(50000);
		timeout -= 50;
	}

	return (MOS_ERROR(iop, EPHIDGET_TIMEOUT, "Timed out waiting for tag to appear after writing. Try again."));
}

void PhidgetRFIDSupport_free(PhidgetRFIDSupportHandle *arg) {

	if (arg == NULL || *arg == NULL)
		return;

	mos_free(*arg, sizeof(PhidgetRFIDSupport));
	*arg = NULL;
}

PhidgetReturnCode
PhidgetRFIDSupport_create(PhidgetRFIDSupportHandle *rfid) {

	TESTPTR_PR(rfid);
	*rfid = mos_zalloc(sizeof(PhidgetRFIDSupport));

	return (EPHIDGET_OK);
}

void PhidgetRFIDSupport_init(PhidgetRFIDSupportHandle rfid) {

	assert(rfid);
}

void PhidgetRFIDSupport_setExpectedTag(PhidgetRFID_Protocol protocol, const char *tagString, char *expectedTagString) {
	int oddParity = 0, evenParity = 1;
	uint64_t tagNumber = 0;
	uint32_t tagID;
	uint32_t tagFacilityID;
	int i, j;

	if (protocol == PROTOCOL_HID_GENERIC) {
		for (i = 0; (uint32_t)i < strlen(tagString); i++) {
			tagNumber <<= 4; // load the next hex-char at the end
			for (j = 0; j < 16; j++) {
				if (tagString[i] == PhidgetRFIDSupport_hexChar[j]) {
					tagNumber |= j;
					break;
				}
			}
		}

		for (i = 0; i <= 12; i++) {
			oddParity ^= (tagNumber >> i) & 1;
		}

		for (i = 13; i <= 25; i++) {
			evenParity ^= (tagNumber >> i) & 1;
		}

		// Check for H10301 pattern for additional decoding
		if (oddParity && evenParity && ((tagNumber & 0xFFFFC000000) == 0x02004000000)) {
			tagNumber >>= 1;
			tagID = tagNumber & 0xFFFF;
			tagFacilityID = (tagNumber >> 16) & 0xFF;

			expectedTagString[8] = 0; /* NUL trminator */
			// uint64_t decimalPlaceholder = 1;
			for (i = 7; i >= 3; i--) {
				expectedTagString[i] = (tagID % 10) + '0';
				tagID /= 10;
			}

			for (i = 2; i >= 0; i--) {
				expectedTagString[i] = (tagFacilityID % 10) + '0';
				tagFacilityID /= 10;
			}
			return;
		}
	}

	// copy tagString to expected string, including null terminator
	memcpy(expectedTagString, tagString, strlen(tagString) + 1);

	return;
}

#if PHIDUID_NFC0000_0_400_USB_SUPPORTED
PhidgetReturnCode CCONV
PhidgetRFIDSupport_bridgeInput(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetDeviceHandle device = (PhidgetDeviceHandle)ch->parent;
	unsigned char buffer[MAX_OUT_PACKET_SIZE] = { 0 };
	size_t len;

	switch (ch->UCD->uid) {
	case PHIDCHUID_NFC0000_RFID_400_USB:
		switch (ch->class) {
		case PHIDCHCLASS_RFID:
			assert(ch->index == 0);
			switch (bp->vpkt) {
			case BP_SETANTENNAON:
				len = 1;
				buffer[0] = getBridgePacketInt32(bp, 0) != 0;
				return PhidgetDevice_transferpacket(bp->iop, device, PHIDGETUSB_REQ_CHANNEL_WRITE, VINT_PACKET_TYPE_RFID_ANTENNA_ON, ch->uniqueIndex, buffer, &len, 100);

			case BP_READNFCFULL:
			case BP_READNFCNDEF:
				return requestData(ch, bp);

			case BP_OPENRESET:
			case BP_CLOSERESET:
			case BP_ENABLE:
				return EPHIDGET_OK;
			default:
				MOS_PANIC("Unexpected packet type");
			}
		default:
			MOS_PANIC("Unexpected channel class");
		}
	default:
		MOS_PANIC("Unexpected device");
	}
}

PhidgetReturnCode
hex2data(const uint8_t *hex, size_t hlen, uint8_t *data, size_t dlen) {
	uint8_t n;
	size_t i;
	size_t j;
	char h;

	for (i = 0, j = 0; i < hlen && j < dlen; i++) {
		h = hex[i];
		if (h >= '0' && h <= '9')
			n = h - '0';
		else if (h >= 'a' && h <= 'f')
			n = h - 'a' + 10;
		else if (h >= 'A' && h <= 'F')
			n = h - 'A' + 10;
		else
			n = 0;
		if (i % 2 == 0)
			data[j] = n << 4;
		else
			data[j++] |= n;
	}

	for (; j < dlen; j++) {
		data[j] = 0;
	}

	return EPHIDGET_OK;
}

static PhidgetReturnCode
processDataPackets(PhidgetChannelHandle ch, const uint8_t *buffer, size_t length) {
	PhidgetRFIDSupportHandle rfidSupport = RFID_SUPPORT(ch);
	uint16_t receivedPacketCount;

	size_t usedPacketLength = 0;
	int endPacket = 0;
	int error = 0;
	int packetOverhead = USB_IN_PACKET_OVERHEAD;
	PhidgetReturnCode errorCode = EPHIDGET_OK;
	int newResponsePacket = 0;
	uint16_t packetInfo;
	uint16_t packetID;

	switch (buffer[0]) {
	case VINT_PACKET_TYPE_RFID_NFC_PACKET_DATA_ERROR:
		error = 1; // we intend to fall through to the next here
		errorCode = buffer[5];
		packetOverhead++;
	case VINT_PACKET_TYPE_RFID_NFC_PACKET_DATA_END:
		endPacket = 1;
	case VINT_PACKET_TYPE_RFID_NFC_PACKET_DATA:
		// Verify the validity of the packet
		receivedPacketCount = unpack16(&buffer[1]);
		packetInfo = unpack16(&buffer[3]);
		packetID = packetInfo & 0x3FFF;
		newResponsePacket = ((packetInfo & NEW_PACKET_FLAG) != 0);

		if (rfidSupport->usbInPacketCount != receivedPacketCount || (newResponsePacket && (rfidSupport->storedPacketLength != 0))) {
			// Send old data to channel
			if (!newResponsePacket) { // we missed the start of this packet, it is in error
				error = 1;
				errorCode = PACKET_ERROR_CORRUPT;
			}
			rfidSupport->storedPacketLength = 0;
		}

		if (rfidSupport->rxPacketID == NEW_RX_READY) {
			rfidSupport->rxPacketID = packetID;
			rfidSupport->rxPacketError = 0;
		}

		rfidSupport->rxPacketError |= error;

		if (packetID != rfidSupport->rxPacketID && !newResponsePacket) {
			// MOS_PANIC("TODO: Something got out of sequence");
			// Send old data to channel with an error flag
			error = 1;
			errorCode = PACKET_ERROR_CORRUPT;
			rfidSupport->storedPacketLength = 0;
		}

		// handle the packet
		rfidSupport->usbInPacketCount = receivedPacketCount + 1;
		rfidSupport->lastDataLength = length - packetOverhead;
		memcpy(rfidSupport->lastData, buffer + packetOverhead, rfidSupport->lastDataLength);

		// Keep accumulating response data until the full response is received, or the maximum bridge packet length is reached
		if (rfidSupport->storedPacketLength + rfidSupport->lastDataLength <= RFID_MAX_PACKET_LENGTH) {
			memcpy(&rfidSupport->storedPacket[rfidSupport->storedPacketLength], rfidSupport->lastData, rfidSupport->lastDataLength);
			rfidSupport->storedPacketLength += (uint16_t)rfidSupport->lastDataLength;
			if ((endPacket == 0))
				return EPHIDGET_OK;
		} else {
			usedPacketLength = (RFID_MAX_PACKET_LENGTH - rfidSupport->storedPacketLength);
			memcpy(&rfidSupport->storedPacket[rfidSupport->storedPacketLength], rfidSupport->lastData, usedPacketLength);
			rfidSupport->storedPacketLength = RFID_MAX_PACKET_LENGTH;
		}
		// Release response data
		rfidSupport->responseLength = rfidSupport->storedPacketLength;
		memcpy(rfidSupport->responsePacket, rfidSupport->storedPacket, rfidSupport->storedPacketLength);
		rfidSupport->storedPacketLength = 0;
		rfidSupport->responseError = errorCode;

		rfidSupport->responsePacketID = rfidSupport->rxPacketID;
		rfidSupport->rxPacketID = NEW_RX_READY;
		return (EPHIDGET_OK);
	case VINT_PACKET_TYPE_RFID_NFC_PACKET_DROPPED:
		PhidgetLock(ch);
		rfidSupport->droppedPacketID = unpack16(&buffer[1]);
		rfidSupport->droppedPacketReason = buffer[3];
		PhidgetBroadcast(ch);
		PhidgetUnlock(ch);
		// Could add packet ID here for faster acknowledgement of rejection, but for now the corresponding send will time out.
		// PhidgetChannel_sendErrorEvent(ch, EEPHIDGET_PACKETLOST, "One or more of the transmitted packets were lost.");
		return (EPHIDGET_OK);
	case VINT_PACKET_TYPE_RFID_NFC_PACKET_ACK:
		PhidgetLock(ch);
		rfidSupport->ackID = (unpack16(&buffer[1])) & 0x3FFF;
		PhidgetBroadcast(ch);
		PhidgetUnlock(ch);
		return (EPHIDGET_OK);
	default:
		MOS_PANIC("Unexpected packet type");
	}
}

// dataInput - parses device packets
PhidgetReturnCode CCONV
PhidgetRFIDSupport_dataInput(PhidgetChannelHandle ch, const uint8_t *buffer, size_t length) {

	assert(ch);
	assert(buffer);

	// Parse device packets - store data locally
	switch (ch->UCD->uid) {
	case PHIDCHUID_NFC0000_RFID_400_USB:
		if (length > 0) {
			switch (buffer[0]) {
			default:
				return processDataPackets(ch, buffer, length);
			}
		}
		MOS_PANIC("Unexpected packet type");
	default:
		MOS_PANIC("Unexpected device");
	}
}

PhidgetReturnCode requestData(PhidgetChannelHandle ch, BridgePacket *bp) {
	PhidgetDeviceHandle device = (PhidgetDeviceHandle)ch->parent;
	PhidgetReturnCode ret;
	uint8_t outBuffer[64];
	int vintPacketType;
	size_t len;

	int packetID;

	const char* passwordString = getBridgePacketString(bp, 1);
	const char* uidString = getBridgePacketString(bp, 0);
	uint8_t passwordBytes[32];
	uint8_t uid[8];

	uint8_t passwordLen = (uint8_t)(strlen(passwordString) / 2);
	uint8_t uidLen = (uint8_t)(strlen(uidString) / 2);

	PhidgetRFIDSupportHandle rfidSupport = RFID_SUPPORT(ch);

	hex2data(passwordString, strlen(passwordString), passwordBytes, sizeof(passwordBytes));
	hex2data(uidString, strlen(uidString), uid, sizeof(uid));

	// Assign unique packet ID
	PhidgetLock(ch);
	rfidSupport->packetID++;
	rfidSupport->packetID &= 0x0F; // 4-bit packet ID
	if (rfidSupport->packetID == ANONYMOUS_PACKET_ID)
		rfidSupport->packetID = 0x0001;
	packetID = rfidSupport->packetID;
	PhidgetUnlock(ch);

	switch (bp->vpkt) {
	case BP_READNFCFULL:
		vintPacketType = VINT_PACKET_TYPE_RFID_NFC_READFULL;
		break;
	case BP_READNFCNDEF:
		vintPacketType = VINT_PACKET_TYPE_RFID_NFC_READNDEF;
		packetID |= RFID_NFC_NDEF_FLAG;
		break;
	default:
		MOS_PANIC("Unexpected packet type");
	}

	outBuffer[0] = packetID;
	outBuffer[1] = uidLen;
	memcpy(&outBuffer[2], uid, sizeof(uid));
	outBuffer[10] = passwordLen;
	memcpy(&outBuffer[11], passwordBytes, sizeof(passwordBytes));
	len = 3 + sizeof(uid) + sizeof(passwordBytes);

	ret = PhidgetDevice_transferpacket(bp->iop, device, PHIDGETUSB_REQ_DEVICE_WRITE, vintPacketType, 0, outBuffer, &len, 100);

	if (ret != EPHIDGET_OK)
		return ret;

	rfidSupport->rxPacketID = NEW_RX_READY;

	////Wait to see if the device accepted the packet, this makes the return code from sendPacket mean something
	// start = mos_gettime_usec();

	for (;;) {
		// Wait for acknowledgement that the packet finished transmitting, even if we're not reporting response data.
		// This helps keep the user's program in sync
		if (rfidSupport->responsePacketID == packetID) {
			// Bridge packet reply is entire response
			bp->reply_bpe = mos_malloc(sizeof(BridgePacketEntry));
			memset(bp->reply_bpe, 0, sizeof(BridgePacketEntry));

			bp->reply_bpe->type = BPE_UI8ARRAY;
			bp->reply_bpe->bpe_len = (uint16_t)(rfidSupport->responseLength+1); //leave room to null terminate
			bp->reply_bpe->bpe_ptr = mos_malloc(rfidSupport->responseLength+1);
			bp->reply_bpe->bpe_ui8array = bp->reply_bpe->bpe_ptr;
			bp->reply_bpe->bpe_cnt = (uint16_t)1;
			memcpy(bp->reply_bpe->bpe_ui8array, rfidSupport->responsePacket, rfidSupport->responseLength);
			bp->reply_bpe->bpe_ui8array[rfidSupport->responseLength] = 0; //null terminate
			rfidSupport->responseLength = 0;

			switch (rfidSupport->responseError) {
			case PACKET_ERROR_OK:
				return (EPHIDGET_OK);
			case PACKET_ERROR_TIMEOUT:
				rfidSupport->responseError = PACKET_ERROR_OK;
				return (MOS_ERROR(bp->iop, EPHIDGET_TIMEOUT, "Packet timed out"));
			case PACKET_ERROR_UNKNOWN:
			case PACKET_ERROR_FORMAT:
			case PACKET_ERROR_INVALID:
			case PACKET_ERROR_OVERRUN:
			case PACKET_ERROR_CORRUPT:
				rfidSupport->responseError = PACKET_ERROR_OK;
				return (MOS_ERROR(bp->iop, EPHIDGET_INTERRUPTED, "Something happened to corrupt the response data."));
			case PACKET_ERROR_NACK:
				rfidSupport->responseError = PACKET_ERROR_OK;
				return (MOS_ERROR(bp->iop, EPHIDGET_NACK, "Packet was NACKed by the external device"));
			default:
				rfidSupport->responseError = PACKET_ERROR_OK;
				return (MOS_ERROR(bp->iop, EPHIDGET_INTERRUPTED, "Something happened to corrupt the response data."));
			}
		}

		if (rfidSupport->droppedPacketID == packetID) {
//processReturnCode:
			rfidSupport->droppedPacketID = NO_ACTIVE_PACKET;
			//if (rfidSupport->droppedPacketReason == TX_DROPPED_TIMEOUT)
			//	return (MOS_ERROR(bp->iop, EPHIDGET_TIMEOUT, "The packet timed out while waiting to be transmitted. Check that your system can keep up with the data being sent."));
			//if (rfidSupport->droppedPacketReason == TX_DROPPED_TOOBIG)
			//	return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "The packet is too large to be accepted by the device"));
			return EPHIDGET_INTERRUPTED;
		}

		if (!(ISATTACHED(ch))) {
			return (EPHIDGET_CLOSED);
		}

		/*duration = (mos_gettime_usec() - start);
		if (duration >= maxDuration)
			return (EPHIDGET_TIMEOUT);
		PhidgetLock(ch);
		if (rfidSupport->baudRate != 0) {
			expectedDurationUS = ((len * 8) * 1000000) / rfidSupport->baudRate;
			if (expectedDurationUS > ((uint32_t)duration)) {
				if (waitResponse || (expectedDurationUS - ((uint32_t)duration)) > 20000)
					PhidgetTimedWait(ch, (expectedDurationUS - ((uint32_t)duration)) / 1000);
				else
					PhidgetTimedWait(ch, 1);
			}
		} else {
			PhidgetUnlock(ch);
			return (MOS_ERROR(bp->iop, EPHIDGET_NOTCONFIGURED, "Baud Rate Not Configured"));
		}
		PhidgetUnlock(ch);
		*/
	}

	return ret;
}

#endif
