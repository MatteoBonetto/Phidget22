/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/rfiddevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetRFID_errorHandler(PhidgetChannelHandle ch, Phidget_ErrorEventCode code);
static void CCONV PhidgetRFID_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetRFID_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetRFID_setStatus(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetRFID_getStatus(PhidgetChannelHandle phid, BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetRFID_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetRFID_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetRFID_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetRFID_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetRFID {
	struct _PhidgetChannel phid;
	char lastTagString[25];
	PhidgetRFID_Protocol lastTagProtocol;
	int antennaEnabled;
	int tagPresent;
	PhidgetRFID_OnTagCallback Tag;
	void *TagCtx;
	PhidgetRFID_OnTagLostCallback TagLost;
	void *TagLostCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRFIDHandle ch;
	int nsversion;

	ch = (PhidgetRFIDHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 1) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 1 - functionality may be limited.", phid, nsversion);
	}

	if(hasBridgePacketByName(bp, "lastTagString"))
		memcpy(&ch->lastTagString, getBridgePacketUInt8ArrayByName(bp, "lastTagString"),
	  sizeof (char) * 25);
	if (hasBridgePacketByName(bp, "antennaEnabled"))
		ch->antennaEnabled = getBridgePacketInt32ByName(bp, "antennaEnabled");
	if (hasBridgePacketByName(bp, "tagPresent"))
		ch->tagPresent = getBridgePacketInt32ByName(bp, "tagPresent");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetRFIDHandle ch;

	ch = (PhidgetRFIDHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 4, "_class_version_=%u"
	  ",lastTagString=%25R"
	  ",antennaEnabled=%d"
	  ",tagPresent=%d"
	  ,1 /* class version */
	  ,ch->lastTagString
	  ,ch->antennaEnabled
	  ,ch->tagPresent
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRFIDHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetRFIDHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_WRITE:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_WRITEWITHCHIPSET:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_SETANTENNAON:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->antennaEnabled = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "AntennaEnabled");
		}
		break;
	default:
		logerr("%"PRIphid": unsupported bridge packet:0x%x", phid, bp->vpkt);
		res = EPHIDGET_UNSUPPORTED;
	}

	return (res);
}

static PhidgetReturnCode CCONV
_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetRFIDDeviceHandle parentRFID;
	PhidgetRFIDHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetRFIDHandle)phid;

	ret = EPHIDGET_OK;

	parentRFID = (PhidgetRFIDDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1023_RFID_000:
		// Constants
		ch->antennaEnabled = 1;
		// Inputs, Settables
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1023_RFID_104:
		// Constants
		ch->antennaEnabled = 1;
		// Inputs, Settables
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1023_RFID_200:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = parentRFID->antennaEnabled[ch->phid.index];
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1023_RFID_201:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = parentRFID->antennaEnabled[ch->phid.index];
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1024_RFID_100:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = parentRFID->antennaEnabled[ch->phid.index];
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1024_RFID_300_USB:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = parentRFID->antennaEnabled[ch->phid.index];
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1024_RFID_300_VINT:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = PUNK_BOOL;
		ch->tagPresent = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_RFID_310_USB:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = parentRFID->antennaEnabled[ch->phid.index];
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1024_RFID_310_VINT:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = PUNK_BOOL;
		ch->tagPresent = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_RFID_320_USB:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = parentRFID->antennaEnabled[ch->phid.index];
		ch->tagPresent = parentRFID->tagPresent[ch->phid.index];
		break;
	case PHIDCHUID_1024_RFID_320_VINT:
		// Constants
		// Inputs, Settables
		ch->antennaEnabled = PUNK_BOOL;
		ch->tagPresent = PUNK_BOOL;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	memset(ch->lastTagString, 0, sizeof (char) * 25);
	ch->lastTagProtocol = 0;

	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetRFIDHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetRFIDHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1023_RFID_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_RFID_104:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_RFID_200:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1023_RFID_201:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_100:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_300_USB:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_300_VINT:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_310_USB:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_310_VINT:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_320_USB:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1024_RFID_320_VINT:
		// Reset values
		// Must-set values
		// Default values
		ch->antennaEnabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETANTENNAON, NULL, NULL, 1, "%d", ch->antennaEnabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	return (ret);
}

static void CCONV
_fireInitialEvents(PhidgetChannelHandle phid) {

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetRFID));
}

static PhidgetReturnCode CCONV
_create(PhidgetRFIDHandle *phidp) {

	CHANNELCREATE_BODY(RFID, PHIDCHCLASS_RFID);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_delete(PhidgetRFIDHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetRFID_write(PhidgetRFIDHandle ch, const char *tagString, PhidgetRFID_Protocol protocol,
  int lockTag) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_WRITE, NULL, NULL, 3, "%s%d%d", tagString,
	  protocol, lockTag); 
}

API_PRETURN
PhidgetRFID_writeWithChipset(PhidgetRFIDHandle ch, const char *tagString, PhidgetRFID_Protocol protocol,
  int lockTag, PhidgetRFID_Chipset chipset) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_WRITEWITHCHIPSET, NULL, NULL, 4, "%s%d%d%d",
	  tagString, protocol, lockTag, chipset); 
}

API_PRETURN
PhidgetRFID_setAntennaEnabled(PhidgetRFIDHandle ch, int antennaEnabled) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETANTENNAON, NULL, NULL, 1, "%d",
	  antennaEnabled));
}

API_PRETURN
PhidgetRFID_getAntennaEnabled(PhidgetRFIDHandle ch, int *antennaEnabled) {

	TESTPTR_PR(ch);
	TESTPTR_PR(antennaEnabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	*antennaEnabled = ch->antennaEnabled;
	if (ch->antennaEnabled == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_getTagPresent(PhidgetRFIDHandle ch, int *tagPresent) {

	TESTPTR_PR(ch);
	TESTPTR_PR(tagPresent);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);
	TESTATTACHED_PR(ch);

	*tagPresent = ch->tagPresent;
	if (ch->tagPresent == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_setOnTagHandler(PhidgetRFIDHandle ch, PhidgetRFID_OnTagCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->Tag = NULL;
		MEMORY_BARRIER();
		ch->TagCtx = NULL;
	} else {
		ch->TagCtx = ctx;
		MEMORY_BARRIER();
		ch->Tag = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRFID_setOnTagLostHandler(PhidgetRFIDHandle ch, PhidgetRFID_OnTagLostCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RFID);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->TagLost = NULL;
		MEMORY_BARRIER();
		ch->TagLostCtx = NULL;
	} else {
		ch->TagLostCtx = ctx;
		MEMORY_BARRIER();
		ch->TagLost = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
