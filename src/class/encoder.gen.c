/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/encoderdevice.h"
#include "device/motorcontroldevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetEncoder_errorHandler(PhidgetChannelHandle ch, Phidget_ErrorEventCode code);
static void CCONV PhidgetEncoder_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetEncoder_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetEncoder_setStatus(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetEncoder_getStatus(PhidgetChannelHandle phid, BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetEncoder_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetEncoder_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetEncoder_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetEncoder_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetEncoder {
	struct _PhidgetChannel phid;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	int enabled;
	int64_t indexPosition;
	Phidget_EncoderIOMode IOMode;
	int64_t position;
	uint32_t positionChangeTrigger;
	uint32_t minPositionChangeTrigger;
	uint32_t maxPositionChangeTrigger;
	PhidgetEncoder_OnPositionChangeCallback PositionChange;
	void *PositionChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetEncoderHandle ch;
	int nsversion;

	ch = (PhidgetEncoderHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 2) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 2 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "minDataInterval"))
		ch->minDataInterval = getBridgePacketUInt32ByName(bp, "minDataInterval");
	if (hasBridgePacketByName(bp, "maxDataInterval"))
		ch->maxDataInterval = getBridgePacketUInt32ByName(bp, "maxDataInterval");
	if (hasBridgePacketByName(bp, "dataIntervalDbl"))
		ch->dataInterval = getBridgePacketDoubleByName(bp, "dataIntervalDbl");
	else if(hasBridgePacketByName(bp, "dataInterval"))
		ch->dataInterval = (double)getBridgePacketUInt32ByName(bp, "dataInterval");
	if (hasBridgePacketByName(bp, "minDataRate"))
		ch->minDataRate = getBridgePacketDoubleByName(bp, "minDataRate");
	else if(hasBridgePacketByName(bp, "maxDataInterval"))
		ch->minDataRate = (double)(1000.0 / getBridgePacketUInt32ByName(bp, "maxDataInterval"));
	if (hasBridgePacketByName(bp, "maxDataRate"))
		ch->maxDataRate = getBridgePacketDoubleByName(bp, "maxDataRate");
	else if(hasBridgePacketByName(bp, "minDataInterval"))
		ch->maxDataRate = (double)(1000.0 / getBridgePacketUInt32ByName(bp, "minDataInterval"));
	if (hasBridgePacketByName(bp, "enabled"))
		ch->enabled = getBridgePacketInt32ByName(bp, "enabled");
	if (hasBridgePacketByName(bp, "indexPosition"))
		ch->indexPosition = getBridgePacketInt64ByName(bp, "indexPosition");
	if (hasBridgePacketByName(bp, "IOMode"))
		ch->IOMode = getBridgePacketInt32ByName(bp, "IOMode");
	if (hasBridgePacketByName(bp, "position"))
		ch->position = getBridgePacketInt64ByName(bp, "position");
	if (hasBridgePacketByName(bp, "positionChangeTrigger"))
		ch->positionChangeTrigger = getBridgePacketUInt32ByName(bp, "positionChangeTrigger");
	if (hasBridgePacketByName(bp, "minPositionChangeTrigger"))
		ch->minPositionChangeTrigger = getBridgePacketUInt32ByName(bp, "minPositionChangeTrigger");
	if (hasBridgePacketByName(bp, "maxPositionChangeTrigger"))
		ch->maxPositionChangeTrigger = getBridgePacketUInt32ByName(bp, "maxPositionChangeTrigger");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetEncoderHandle ch;

	ch = (PhidgetEncoderHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 14, "_class_version_=%u"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",enabled=%d"
	  ",indexPosition=%l"
	  ",IOMode=%d"
	  ",position=%l"
	  ",positionChangeTrigger=%u"
	  ",minPositionChangeTrigger=%u"
	  ",maxPositionChangeTrigger=%u"
	  ,2 /* class version */
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->enabled
	  ,ch->indexPosition
	  ,ch->IOMode
	  ,ch->position
	  ,ch->positionChangeTrigger
	  ,ch->minPositionChangeTrigger
	  ,ch->maxPositionChangeTrigger
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetEncoderHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetEncoderHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SETDATAINTERVAL:
		if (bp->entrycnt > 1)
			TESTRANGE_IOP(bp->iop, "%lf", round_double((1000.0 / getBridgePacketDouble(bp, 1)), 4),
			  ch->minDataRate, ch->maxDataRate);
		else
			TESTRANGE_IOP(bp->iop, "%"PRIu32, getBridgePacketUInt32(bp, 0), ch->minDataInterval,
			  ch->maxDataInterval);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		if (bp->entrycnt > 1)
			ch->dataInterval = getBridgePacketDouble(bp, 1);
		else
			ch->dataInterval = (double)getBridgePacketUInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "DataInterval");
			FIRE_PROPERTYCHANGE(ch, "DataRate");
		}
		break;
	case BP_SETENABLED:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->enabled = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Enabled");
		}
		break;
	case BP_SETIOMODE:
		if (!supportedEncoderIOMode(phid, (Phidget_EncoderIOMode)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified EncoderIOMode is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->IOMode = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "IOMode");
		}
		break;
	case BP_SETCHANGETRIGGER:
		TESTRANGE_IOP(bp->iop, "%"PRIu32, getBridgePacketUInt32(bp, 0), ch->minPositionChangeTrigger,
		  ch->maxPositionChangeTrigger);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->positionChangeTrigger = getBridgePacketUInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "PositionChangeTrigger");
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
	PhidgetMotorControlDeviceHandle parentMotorControl;
	PhidgetEncoderDeviceHandle parentEncoder;
	PhidgetEncoderHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetEncoderHandle)phid;

	ret = EPHIDGET_OK;

	parentMotorControl = (PhidgetMotorControlDeviceHandle)phid->parent;
	parentEncoder = (PhidgetEncoderDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1047_ENCODER_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		ch->enabled = parentEncoder->enabled[ch->phid.index];
		break;
	case PHIDCHUID_1047_ENCODER_200:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		ch->enabled = parentEncoder->enabled[ch->phid.index];
		break;
	case PHIDCHUID_1047_ENCODER_300:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		ch->enabled = parentEncoder->enabled[ch->phid.index];
		break;
	case PHIDCHUID_1052_ENCODER_000:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1052_ENCODER_101:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1052_ENCODER_110:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1057_ENCODER_300:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 125;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1057_ENCODER_400:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 125;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = parentEncoder->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentEncoder->encoderChangeTrigger[ch->phid.index];
		ch->enabled = parentEncoder->enabled[ch->phid.index];
		ch->IOMode = parentEncoder->IOMode[ch->phid.index];
		break;
	case PHIDCHUID_1065_ENCODER_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 125;
		ch->maxPositionChangeTrigger = 10000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->encoderDataInterval[ch->phid.index];
		ch->position = 0;
		ch->positionChangeTrigger = parentMotorControl->encoderChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_DCC1000_ENCODER_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		ch->IOMode = PUNK_ENUM;
		break;
	case PHIDCHUID_DCC1000_ENCODER_200:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		ch->IOMode = PUNK_ENUM;
		break;
	case PHIDCHUID_DCC1000_ENCODER_210:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		ch->IOMode = PUNK_ENUM;
		break;
	case PHIDCHUID_DCC1020_ENCODER_100:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		break;
	case PHIDCHUID_DCC1001_ENCODER_100:
		// Constants
		ch->minDataInterval = 50;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 20;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		break;
	case PHIDCHUID_DCC1001_ENCODER_120:
		// Constants
		ch->minDataInterval = 50;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 20;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		break;
	case PHIDCHUID_DCC1002_ENCODER_100:
		// Constants
		ch->minDataInterval = 50;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 20;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		break;
	case PHIDCHUID_DCC1002_ENCODER_110:
		// Constants
		ch->minDataInterval = 50;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 20;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		break;
	case PHIDCHUID_DCC1120_ENCODER_100:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		break;
	case PHIDCHUID_ENC1000_ENCODER_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 50;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		ch->enabled = PUNK_BOOL;
		ch->IOMode = PUNK_ENUM;
		break;
	case PHIDCHUID_ENC1001_ENCODER_100:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		ch->indexPosition = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		ch->enabled = PUNK_BOOL;
		break;
	case PHIDCHUID_HIN1101_ENCODER_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 50;
		ch->maxPositionChangeTrigger = 60000000;
		ch->minPositionChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->position = 0;
		ch->positionChangeTrigger = PUNK_UINT32;
		ch->enabled = PUNK_BOOL;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetEncoderHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetEncoderHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1047_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1047_ENCODER_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1047_ENCODER_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1052_ENCODER_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 16;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1052_ENCODER_101:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 16;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1052_ENCODER_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 16;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1057_ENCODER_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 8;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1057_ENCODER_400:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ch->IOMode = ENCODER_IO_MODE_PUSH_PULL;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETIOMODE, NULL, NULL, 1, "%d", ch->IOMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1065_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_ENCODER_100:
		// Reset values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ch->IOMode = ENCODER_IO_MODE_PUSH_PULL;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DCC1000_ENCODER_200:
		// Reset values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ch->IOMode = ENCODER_IO_MODE_PUSH_PULL;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DCC1000_ENCODER_210:
		// Reset values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ch->IOMode = ENCODER_IO_MODE_PUSH_PULL;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DCC1020_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 20;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1001_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1001_ENCODER_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1002_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1002_ENCODER_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1120_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 20;
		ch->positionChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_ENC1000_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ch->IOMode = ENCODER_IO_MODE_PUSH_PULL;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETIOMODE, NULL, NULL, 1, "%d", ch->IOMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_ENC1001_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 10;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HIN1101_ENCODER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->positionChangeTrigger = 0;
		ch->enabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
		  ch->positionChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
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

	mos_free(*ch, sizeof (struct _PhidgetEncoder));
}

static PhidgetReturnCode CCONV
_create(PhidgetEncoderHandle *phidp) {

	CHANNELCREATE_BODY(Encoder, PHIDCHCLASS_ENCODER);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_delete(PhidgetEncoderHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetEncoder_setDataInterval(PhidgetEncoderHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetEncoder_getDataInterval(PhidgetEncoderHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getMinDataInterval(PhidgetEncoderHandle ch, uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getMaxDataInterval(PhidgetEncoderHandle ch, uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_setDataRate(PhidgetEncoderHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetEncoder_getDataRate(PhidgetEncoderHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getMinDataRate(PhidgetEncoderHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getMaxDataRate(PhidgetEncoderHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_setEnabled(PhidgetEncoderHandle ch, int enabled) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETENABLED, NULL, NULL, 1, "%d", enabled));
}

API_PRETURN
PhidgetEncoder_getEnabled(PhidgetEncoderHandle ch, int *enabled) {

	TESTPTR_PR(ch);
	TESTPTR_PR(enabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_DCC1020_ENCODER_100:
	case PHIDCHUID_DCC1120_ENCODER_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*enabled = ch->enabled;
	if (ch->enabled == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getIndexPosition(PhidgetEncoderHandle ch, int64_t *indexPosition) {

	TESTPTR_PR(ch);
	TESTPTR_PR(indexPosition);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1052_ENCODER_000:
	case PHIDCHUID_1052_ENCODER_101:
	case PHIDCHUID_1052_ENCODER_110:
	case PHIDCHUID_1057_ENCODER_300:
	case PHIDCHUID_HIN1101_ENCODER_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*indexPosition = ch->indexPosition;
	if (ch->indexPosition == (int64_t)PUNK_INT64)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_setIOMode(PhidgetEncoderHandle ch, Phidget_EncoderIOMode IOMode) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETIOMODE, NULL, NULL, 1, "%d", IOMode));
}

API_PRETURN
PhidgetEncoder_getIOMode(PhidgetEncoderHandle ch, Phidget_EncoderIOMode *IOMode) {

	TESTPTR_PR(ch);
	TESTPTR_PR(IOMode);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1047_ENCODER_100:
	case PHIDCHUID_1047_ENCODER_200:
	case PHIDCHUID_1047_ENCODER_300:
	case PHIDCHUID_1052_ENCODER_000:
	case PHIDCHUID_1052_ENCODER_101:
	case PHIDCHUID_1052_ENCODER_110:
	case PHIDCHUID_1057_ENCODER_300:
	case PHIDCHUID_1065_ENCODER_100:
	case PHIDCHUID_DCC1020_ENCODER_100:
	case PHIDCHUID_DCC1001_ENCODER_100:
	case PHIDCHUID_DCC1001_ENCODER_120:
	case PHIDCHUID_DCC1002_ENCODER_100:
	case PHIDCHUID_DCC1002_ENCODER_110:
	case PHIDCHUID_DCC1120_ENCODER_100:
	case PHIDCHUID_ENC1001_ENCODER_100:
	case PHIDCHUID_HIN1101_ENCODER_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*IOMode = ch->IOMode;
	if (ch->IOMode == (Phidget_EncoderIOMode)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getPosition(PhidgetEncoderHandle ch, int64_t *position) {

	TESTPTR_PR(ch);
	TESTPTR_PR(position);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*position = ch->position;
	if (ch->position == (int64_t)PUNK_INT64)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_setPositionChangeTrigger(PhidgetEncoderHandle ch, uint32_t positionChangeTrigger) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%u",
	  positionChangeTrigger));
}

API_PRETURN
PhidgetEncoder_getPositionChangeTrigger(PhidgetEncoderHandle ch, uint32_t *positionChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(positionChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*positionChangeTrigger = ch->positionChangeTrigger;
	if (ch->positionChangeTrigger == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getMinPositionChangeTrigger(PhidgetEncoderHandle ch,
  uint32_t *minPositionChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minPositionChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*minPositionChangeTrigger = ch->minPositionChangeTrigger;
	if (ch->minPositionChangeTrigger == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_getMaxPositionChangeTrigger(PhidgetEncoderHandle ch,
  uint32_t *maxPositionChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxPositionChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);
	TESTATTACHED_PR(ch);

	*maxPositionChangeTrigger = ch->maxPositionChangeTrigger;
	if (ch->maxPositionChangeTrigger == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetEncoder_setOnPositionChangeHandler(PhidgetEncoderHandle ch,
  PhidgetEncoder_OnPositionChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_ENCODER);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->PositionChange = NULL;
		MEMORY_BARRIER();
		ch->PositionChangeCtx = NULL;
	} else {
		ch->PositionChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->PositionChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
