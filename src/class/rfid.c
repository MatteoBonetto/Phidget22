/* Generated: Wed Jan 27 2016 14:22:18 GMT-0700 (Mountain Standard Time) */
/* Will not be regenerated. */

#include "phidgetbase.h"
#include "class/rfid.gen.h"
#include "class/rfid.gen.c"

// Access the PhidgetRFIDSupport struct via the channel private pointer
#define RFID_SUPPORT(ch) ((PhidgetRFIDSupportHandle)(((PhidgetChannelHandle)(ch))->private))

static void
PhidgetRFID_errorHandler(PhidgetChannelHandle phid, Phidget_ErrorEventCode code) {}

static void CCONV
PhidgetRFID_free(PhidgetChannelHandle *ch) {
	if (ch && *ch)
		PhidgetRFIDSupport_free((PhidgetRFIDSupportHandle *)&(*ch)->private);
	_free(ch);
}

API_PRETURN
PhidgetRFID_create(PhidgetRFIDHandle *phidp) {
	PhidgetReturnCode res;

	res = _create(phidp);
	if (res == EPHIDGET_OK)
		res = PhidgetRFIDSupport_create((PhidgetRFIDSupportHandle *)&(*phidp)->phid.private);

	return (res);
}

static PhidgetReturnCode CCONV
PhidgetRFID_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	return (_setStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetRFID_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	return (_getStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetRFID_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetRFIDSupport_init(RFID_SUPPORT(phid));
	return (_initAfterOpen(phid));
}

static PhidgetReturnCode CCONV
PhidgetRFID_setDefaults(PhidgetChannelHandle phid) {
	return (_setDefaults(phid));
}

static PhidgetReturnCode
PhidgetRFID_verifyWritePacket(PhidgetChannelHandle phid, BridgePacket *bp, PhidgetRFID_Protocol proto, int lock, PhidgetRFID_Chipset chipset) {
	const char *tagString;
	uint64_t uniqueID;
	int i;

	if (!supportedRFIDProtocol(phid, proto))
		return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "Specified RFID protocol is not supported by this device or firmware revision."));

	if (!supportedRFIDChipset(phid, chipset))
		return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "Specified RFID chipset is not supported by this device or firmware revision."));
	TESTBOOL_IOP(bp->iop, lock); // lockTag

	// Verify the tag string is valid for the chosen protocol
	tagString = getBridgePacketString(bp, 0);
	switch (proto) {
	case PROTOCOL_EM4100:
		if (strlen(tagString) != 10)
			if (!(strlen(tagString) == 12 && tagString[0] == '0' && tagString[1] == 'x'))
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "EM4100 tag string must be specified as 'XXXXXXXXXX' or '0xXXXXXXXXXX' where 'X' is a hex digit."));
		for (i = 0; i < 10; i++) {
			char hexDigit = tagString[(strlen(tagString) - 1) - i];
			if ((hexDigit < '0' || hexDigit > '9') && (hexDigit < 'A' || hexDigit > 'F') && (hexDigit < 'a' || hexDigit > 'f'))
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "EM4100 tag string must be specified as 'XXXXXXXXXX' or '0xXXXXXXXXXX' where 'X' is a hex digit."));
		}
		break;
	case PROTOCOL_ISO11785_FDX_B:
		if (strlen(tagString) != 15)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "ISO11785_FDX_B tag must be specified as 15 decimal digits."));

		for (i = 0; i < 15; i++) {
			char digit = tagString[(strlen(tagString) - 1) - i];
			if (digit < '0' || digit > '9')
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "ISO11785_FDX_B tag must be a string of 15 decimal digits"));
		}

		// Get uniqueID
		uniqueID = (uint64_t)strtoll(tagString + 3, NULL, 10);
		// must be 38-bit or less
		if (uniqueID > 0x3FFFFFFFFFLL)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "ISO11785_FDX_B Unique ID (last 12 digits) must be <= 274877906943."));
		break;
	case PROTOCOL_PHIDGETS:
		if (strlen(tagString) > 24)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "PHIDGETS_TAG must be <= 24 characters."));
		break;
	case PROTOCOL_HID_H10301:
		if (chipset == CHIPSET_EM4305)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID H10301 protocol is not supported on EM4305 tags"));
		if (strlen(tagString) != 8)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID H10301 tag must be specified as 8 decimal digits."));

		for (i = 0; i < 8; i++) {
			char digit = tagString[(strlen(tagString) - 1) - i];
			if (digit < '0' || digit > '9')
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID H10301 tag must be a string of 8 decimal digits"));
		}
		// Get full tag number
		uniqueID = strtoll(tagString, NULL, 10);

		// Check Facility Code
		if ((uniqueID / 100000) > 0xFF)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID H10301 Facility Code (first 3 digits) must be <= 255."));

		// Check Card Number
		if ((uniqueID % 100000) > 0xFFFF)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID H10301 Card Number (last 5 digits) must be <= 65535."));
		break;
	case PROTOCOL_HID_GENERIC:
		if (chipset == CHIPSET_EM4305)
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID Generic protocol is not supported on EM4305 tags"));
		if (strlen(tagString) != 11)
			if (!(strlen(tagString) == 13 && tagString[0] == '0' && tagString[1] == 'x'))
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID Generic tag string must be specified as 'XXXXXXXXXXX' or '0xXXXXXXXXXXX' where 'X' is a hex digit."));
		for (i = 0; i < 10; i++) {
			char hexDigit = tagString[(strlen(tagString) - 1) - i];
			if ((hexDigit < '0' || hexDigit > '9') && (hexDigit < 'A' || hexDigit > 'F') && (hexDigit < 'a' || hexDigit > 'f'))
				return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG, "HID Generic tag string must be specified as 'XXXXXXXXXXX' or '0xXXXXXXXXXXX' where 'X' is a hex digit."));
		}
		break;
	}
	return EPHIDGET_OK;
}

static PhidgetReturnCode
PhidgetRFID_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRFIDHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetRFIDHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_WRITEWITHCHIPSET:
		res = PhidgetRFID_verifyWritePacket(phid, bp, (PhidgetRFID_Protocol)getBridgePacketInt32(bp, 1), getBridgePacketInt32(bp, 2), (PhidgetRFID_Chipset)getBridgePacketInt32(bp, 3));
		if (res)
			return res;
		res = _bridgeInput(phid, bp);
		break;
	case BP_WRITE:
		res = PhidgetRFID_verifyWritePacket(phid, bp, (PhidgetRFID_Protocol)getBridgePacketInt32(bp, 1), getBridgePacketInt32(bp, 2), CHIPSET_T5577);
		if (res)
			return res;
		res = _bridgeInput(phid, bp);
		break;
	case BP_TAG:
		PhidgetRunLock(ch);
		mos_strlcpy(ch->lastTagString, getBridgePacketString(bp, 0), RFIDDevice_MAX_TAG_STRING_LEN);
		ch->lastTagProtocol = (PhidgetRFID_Protocol)getBridgePacketInt32(bp, 1);
		ch->tagPresent = PTRUE;
		PhidgetRunUnlock(ch);
		FIRECH(ch, PhidgetRFID, Tag, getBridgePacketString(bp, 0), (PhidgetRFID_Protocol)getBridgePacketInt32(bp, 1));
		break;
	case BP_TAGLOST:
		ch->tagPresent = PFALSE;
		FIRECH(ch, PhidgetRFID, TagLost, getBridgePacketString(bp, 0), (PhidgetRFID_Protocol)getBridgePacketInt32(bp, 1));
		break;
	case BP_SETANTENNAON:
		res = _bridgeInput(phid, bp);
		if (res == EPHIDGET_OK) {
			if (ch->tagPresent == PUNK_BOOL)
				ch->tagPresent = PFALSE;
		}
		break;
	default:
		res = _bridgeInput(phid, bp);
		break;
	}

	return (res);
}

static void
PhidgetRFID_fireInitialEvents(PhidgetChannelHandle phid) {
	_fireInitialEvents(phid);
}

static int
PhidgetRFID_hasInitialState(PhidgetChannelHandle phid) {
	return (_hasInitialState(phid));
}

API_PRETURN
PhidgetRFID_getLastTag(PhidgetRFIDHandle ch, char *tagString, size_t tagStringLen, PhidgetRFID_Protocol *protocol) {
	size_t len;

	TESTPTR_PR(ch);
	TESTPTR_PR(tagString);
	TESTPTR_PR(protocol);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	PhidgetRunLock(ch);
	len = mos_strlen(ch->lastTagString);
	if (len > 0) {
		if (tagStringLen <= len) {
			PhidgetRunUnlock(ch);
			return (PHID_RETURN_ERRSTR(EPHIDGET_NOSPC, "tagString too short (%d / %d).", tagStringLen, len));
		}
		mos_strlcpy(tagString, ch->lastTagString, tagStringLen);
		*protocol = ch->lastTagProtocol;
		PhidgetRunUnlock(ch);
		return (EPHIDGET_OK);
	}
	PhidgetRunUnlock(ch);
	return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
}

#if PHIDUID_NFC0000_0_400_USB_SUPPORTED
API_PRETURN
PhidgetRFID_readNFCFull(PhidgetRFIDHandle ch, const char *uid, const char *password, uint8_t *recvData,
	size_t *recvDataLen) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	return bridgeSendToDeviceWithReply((PhidgetChannelHandle)ch, BP_READNFCFULL, NULL, NULL, recvData, (uint32_t*)recvDataLen, 2, "%s%s", uid,
		password);
}

API_PRETURN
PhidgetRFID_readNFCNDEF(PhidgetRFIDHandle ch, const char *uid, const char *password, uint8_t *recvData,
	size_t *recvDataLen) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	return bridgeSendToDeviceWithReply((PhidgetChannelHandle)ch, BP_READNFCNDEF, NULL, NULL, recvData, (uint32_t*)recvDataLen, 2, "%s%s", uid,
		password);
}

#endif

