/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/firmwareupgradedevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetFirmwareUpgrade_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetFirmwareUpgrade_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetFirmwareUpgrade_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetFirmwareUpgrade_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetFirmwareUpgrade_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetFirmwareUpgrade_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetFirmwareUpgrade_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetFirmwareUpgrade_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetFirmwareUpgrade_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetFirmwareUpgrade {
	struct _PhidgetChannel phid;
	Phidget_DeviceID actualDeviceID;
	const char * actualDeviceName;
	const char * actualDeviceSKU;
	int actualDeviceVersion;
	uint32_t actualDeviceVINTID;
	double progress;
	PhidgetFirmwareUpgrade_OnProgressChangeCallback ProgressChange;
	void *ProgressChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetFirmwareUpgradeHandle ch;
	int nsversion;

	ch = (PhidgetFirmwareUpgradeHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 1) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 1 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "actualDeviceID"))
		ch->actualDeviceID = getBridgePacketInt32ByName(bp, "actualDeviceID");
	if (hasBridgePacketByName(bp, "actualDeviceName"))
		ch->actualDeviceName = getBridgePacketStringByName(bp, "actualDeviceName");
	if (hasBridgePacketByName(bp, "actualDeviceSKU"))
		ch->actualDeviceSKU = getBridgePacketStringByName(bp, "actualDeviceSKU");
	if (hasBridgePacketByName(bp, "actualDeviceVersion"))
		ch->actualDeviceVersion = getBridgePacketInt32ByName(bp, "actualDeviceVersion");
	if (hasBridgePacketByName(bp, "actualDeviceVINTID"))
		ch->actualDeviceVINTID = getBridgePacketUInt32ByName(bp, "actualDeviceVINTID");
	if (hasBridgePacketByName(bp, "progress"))
		ch->progress = getBridgePacketDoubleByName(bp, "progress");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetFirmwareUpgradeHandle ch;

	ch = (PhidgetFirmwareUpgradeHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 7, "_class_version_=%u"
	  ",actualDeviceID=%d"
	  ",actualDeviceName=%s"
	  ",actualDeviceSKU=%s"
	  ",actualDeviceVersion=%d"
	  ",actualDeviceVINTID=%u"
	  ",progress=%g"
	  ,1 /* class version */
	  ,ch->actualDeviceID
	  ,ch->actualDeviceName
	  ,ch->actualDeviceSKU
	  ,ch->actualDeviceVersion
	  ,ch->actualDeviceVINTID
	  ,ch->progress
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetFirmwareUpgradeHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetFirmwareUpgradeHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SENDFIRMWARE:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_PROGRESSCHANGE:
		ch->progress = getBridgePacketDouble(bp, 0);
		FIRECH(ch, PhidgetFirmwareUpgrade, ProgressChange, ch->progress);
		break;
	default:
		logerr("%"PRIphid": unsupported bridge packet:0x%x", phid, bp->vpkt);
		res = EPHIDGET_UNSUPPORTED;
	}

	return (res);
}

static PhidgetReturnCode CCONV
_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetFirmwareUpgradeHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetFirmwareUpgradeHandle)phid;

	ret = EPHIDGET_OK;


	switch (phid->UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		break;
	case PHIDCHUID_STM32F0_FIRMWARE_UPGRADE_100:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		ch->actualDeviceID = PUNK_ENUM;
		ch->actualDeviceVINTID = PUNK_UINT32;
		ch->actualDeviceSKU = NULL;
		ch->actualDeviceVersion = PUNK_INT32;
		ch->actualDeviceName = NULL;
		break;
	case PHIDCHUID_STM32G0_FIRMWARE_UPGRADE_110:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		ch->actualDeviceID = PUNK_ENUM;
		ch->actualDeviceVINTID = PUNK_UINT32;
		ch->actualDeviceSKU = NULL;
		ch->actualDeviceVersion = PUNK_INT32;
		ch->actualDeviceName = NULL;
		break;
	case PHIDCHUID_STM32G0_FIRMWARE_UPGRADE_114:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		ch->actualDeviceID = PUNK_ENUM;
		ch->actualDeviceVINTID = PUNK_UINT32;
		ch->actualDeviceSKU = NULL;
		ch->actualDeviceVersion = PUNK_INT32;
		ch->actualDeviceName = NULL;
		break;
	case PHIDCHUID_STM32F3_FIRMWARE_UPGRADE_120:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		ch->actualDeviceID = PUNK_ENUM;
		ch->actualDeviceVINTID = PUNK_UINT32;
		ch->actualDeviceSKU = NULL;
		ch->actualDeviceVersion = PUNK_INT32;
		ch->actualDeviceName = NULL;
		break;
	case PHIDCHUID_STM32F0_FIRMWARE_UPGRADE_400:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		ch->actualDeviceID = PUNK_ENUM;
		ch->actualDeviceVINTID = PUNK_UINT32;
		ch->actualDeviceSKU = NULL;
		ch->actualDeviceVersion = PUNK_INT32;
		ch->actualDeviceName = NULL;
		break;
	case PHIDCHUID_STM8S_FIRMWARE_UPGRADE_100:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		ch->actualDeviceID = PUNK_ENUM;
		ch->actualDeviceVINTID = PUNK_UINT32;
		ch->actualDeviceSKU = NULL;
		ch->actualDeviceVersion = PUNK_INT32;
		ch->actualDeviceName = NULL;
		break;
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		// Constants
		ch->progress = 0;
		// Inputs, Settables
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32F0_FIRMWARE_UPGRADE_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32G0_FIRMWARE_UPGRADE_110:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32G0_FIRMWARE_UPGRADE_114:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32F3_FIRMWARE_UPGRADE_120:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM32F0_FIRMWARE_UPGRADE_400:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_STM8S_FIRMWARE_UPGRADE_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	return (ret);
}

static void CCONV
_fireInitialEvents(PhidgetChannelHandle phid) {
	PhidgetFirmwareUpgradeHandle ch;

	ch = (PhidgetFirmwareUpgradeHandle)phid;

	if(ch->progress != PUNK_DBL)
		FIRECH(ch, PhidgetFirmwareUpgrade, ProgressChange, ch->progress);

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {
	PhidgetFirmwareUpgradeHandle ch;

	ch = (PhidgetFirmwareUpgradeHandle)phid;

	if(ch->progress == PUNK_DBL)
		return (PFALSE);

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetFirmwareUpgrade));
}

static PhidgetReturnCode CCONV
_create(PhidgetFirmwareUpgradeHandle *phidp) {

	CHANNELCREATE_BODY(FirmwareUpgrade, PHIDCHCLASS_FIRMWAREUPGRADE);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_delete(PhidgetFirmwareUpgradeHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetFirmwareUpgrade_getActualDeviceID(PhidgetFirmwareUpgradeHandle ch,
  Phidget_DeviceID *actualDeviceID) {

	TESTPTR_PR(ch);
	TESTPTR_PR(actualDeviceID);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*actualDeviceID = ch->actualDeviceID;
	if (ch->actualDeviceID == (Phidget_DeviceID)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_getActualDeviceName(PhidgetFirmwareUpgradeHandle ch,
  const char **actualDeviceName) {

	TESTPTR_PR(ch);
	TESTPTR_PR(actualDeviceName);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*actualDeviceName = ch->actualDeviceName;
	if (ch->actualDeviceName == (char *)NULL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_getActualDeviceSKU(PhidgetFirmwareUpgradeHandle ch,
  const char **actualDeviceSKU) {

	TESTPTR_PR(ch);
	TESTPTR_PR(actualDeviceSKU);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*actualDeviceSKU = ch->actualDeviceSKU;
	if (ch->actualDeviceSKU == (char *)NULL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_getActualDeviceVersion(PhidgetFirmwareUpgradeHandle ch,
  int *actualDeviceVersion) {

	TESTPTR_PR(ch);
	TESTPTR_PR(actualDeviceVersion);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*actualDeviceVersion = ch->actualDeviceVersion;
	if (ch->actualDeviceVersion == (int)PUNK_INT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_getActualDeviceVINTID(PhidgetFirmwareUpgradeHandle ch,
  uint32_t *actualDeviceVINTID) {

	TESTPTR_PR(ch);
	TESTPTR_PR(actualDeviceVINTID);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_M3_USB_FIRMWARE_UPGRADE_000:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_100:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_200:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_300:
	case PHIDCHUID_STM32_USB_FIRMWARE_UPGRADE_400:
	case PHIDCHUID_M3_SPI_FIRMWARE_UPGRADE_000:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*actualDeviceVINTID = ch->actualDeviceVINTID;
	if (ch->actualDeviceVINTID == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_getProgress(PhidgetFirmwareUpgradeHandle ch, double *progress) {

	TESTPTR_PR(ch);
	TESTPTR_PR(progress);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);
	TESTATTACHED_PR(ch);

	*progress = ch->progress;
	if (ch->progress == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFirmwareUpgrade_setOnProgressChangeHandler(PhidgetFirmwareUpgradeHandle ch,
  PhidgetFirmwareUpgrade_OnProgressChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FIRMWAREUPGRADE);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->ProgressChange = NULL;
		MEMORY_BARRIER();
		ch->ProgressChangeCtx = NULL;
	} else {
		ch->ProgressChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->ProgressChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
