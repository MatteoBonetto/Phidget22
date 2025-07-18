/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/interfacekitdevice.h"
#include "device/bridgedevice.h"
#include "device/motorcontroldevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetVoltageRatioInput_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetVoltageRatioInput_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetVoltageRatioInput_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetVoltageRatioInput_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetVoltageRatioInput_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetVoltageRatioInput_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetVoltageRatioInput_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetVoltageRatioInput_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetVoltageRatioInput_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetVoltageRatioInput {
	struct _PhidgetChannel phid;
	int bridgeEnabled;
	PhidgetVoltageRatioInput_BridgeGain bridgeGain;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	PhidgetVoltageRatioInput_SensorType sensorType;
	Phidget_UnitInfo sensorUnit;
	uint8_t sensorUnitValid;
	double sensorValue;
	double sensorValueChangeTrigger;
	double voltageRatio;
	double minVoltageRatio;
	double maxVoltageRatio;
	double voltageRatioChangeTrigger;
	double minVoltageRatioChangeTrigger;
	double maxVoltageRatioChangeTrigger;
	PhidgetVoltageRatioInput_OnSensorChangeCallback SensorChange;
	void *SensorChangeCtx;
	PhidgetVoltageRatioInput_OnVoltageRatioChangeCallback VoltageRatioChange;
	void *VoltageRatioChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetVoltageRatioInputHandle ch;
	int nsversion;

	ch = (PhidgetVoltageRatioInputHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 1) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 1 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "bridgeEnabled"))
		ch->bridgeEnabled = getBridgePacketInt32ByName(bp, "bridgeEnabled");
	if (hasBridgePacketByName(bp, "bridgeGain"))
		ch->bridgeGain = getBridgePacketInt32ByName(bp, "bridgeGain");
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
	if (hasBridgePacketByName(bp, "sensorType"))
		ch->sensorType = getBridgePacketInt32ByName(bp, "sensorType");
	if (hasBridgePacketByName(bp, "sensorValue"))
		ch->sensorValue = getBridgePacketDoubleByName(bp, "sensorValue");
	if (hasBridgePacketByName(bp, "sensorValueChangeTrigger"))
		ch->sensorValueChangeTrigger = getBridgePacketDoubleByName(bp, "sensorValueChangeTrigger");
	if (hasBridgePacketByName(bp, "voltageRatio"))
		ch->voltageRatio = getBridgePacketDoubleByName(bp, "voltageRatio");
	if (hasBridgePacketByName(bp, "minVoltageRatio"))
		ch->minVoltageRatio = getBridgePacketDoubleByName(bp, "minVoltageRatio");
	if (hasBridgePacketByName(bp, "maxVoltageRatio"))
		ch->maxVoltageRatio = getBridgePacketDoubleByName(bp, "maxVoltageRatio");
	if (hasBridgePacketByName(bp, "voltageRatioChangeTrigger"))
		ch->voltageRatioChangeTrigger = getBridgePacketDoubleByName(bp, "voltageRatioChangeTrigger");
	if (hasBridgePacketByName(bp, "minVoltageRatioChangeTrigger"))
		ch->minVoltageRatioChangeTrigger = getBridgePacketDoubleByName(bp,
	  "minVoltageRatioChangeTrigger");
	if (hasBridgePacketByName(bp, "maxVoltageRatioChangeTrigger"))
		ch->maxVoltageRatioChangeTrigger = getBridgePacketDoubleByName(bp,
	  "maxVoltageRatioChangeTrigger");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetVoltageRatioInputHandle ch;

	ch = (PhidgetVoltageRatioInputHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 18, "_class_version_=%u"
	  ",bridgeEnabled=%d"
	  ",bridgeGain=%d"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",sensorType=%d"
	  ",sensorValue=%g"
	  ",sensorValueChangeTrigger=%g"
	  ",voltageRatio=%g"
	  ",minVoltageRatio=%g"
	  ",maxVoltageRatio=%g"
	  ",voltageRatioChangeTrigger=%g"
	  ",minVoltageRatioChangeTrigger=%g"
	  ",maxVoltageRatioChangeTrigger=%g"
	  ,1 /* class version */
	  ,ch->bridgeEnabled
	  ,ch->bridgeGain
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->sensorType
	  ,ch->sensorValue
	  ,ch->sensorValueChangeTrigger
	  ,ch->voltageRatio
	  ,ch->minVoltageRatio
	  ,ch->maxVoltageRatio
	  ,ch->voltageRatioChangeTrigger
	  ,ch->minVoltageRatioChangeTrigger
	  ,ch->maxVoltageRatioChangeTrigger
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetVoltageRatioInputHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetVoltageRatioInputHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SETENABLED:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->bridgeEnabled = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "BridgeEnabled");
		}
		break;
	case BP_SETBRIDGEGAIN:
		if (!supportedBridgeGain(phid, (PhidgetVoltageRatioInput_BridgeGain)getBridgePacketInt32(bp,
		  0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified BridgeGain is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->bridgeGain = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "BridgeGain");
		}
		break;
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
	case BP_SETSENSORTYPE:
		if (!supportedVoltageRatioSensorType(phid,
		  (PhidgetVoltageRatioInput_SensorType)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified VoltageRatioSensorType is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->sensorType = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "SensorType");
		}
		break;
	case BP_SETSENSORVALUECHANGETRIGGER:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->sensorValueChangeTrigger = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "SensorValueChangeTrigger");
		}
		break;
	case BP_SETCHANGETRIGGER:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minVoltageRatioChangeTrigger,
		  ch->maxVoltageRatioChangeTrigger);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->voltageRatioChangeTrigger = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "VoltageRatioChangeTrigger");
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
	PhidgetInterfaceKitDeviceHandle parentInterfaceKit;
	PhidgetMotorControlDeviceHandle parentMotorControl;
	PhidgetBridgeDeviceHandle parentBridge;
	PhidgetVoltageRatioInputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetVoltageRatioInputHandle)phid;

	ret = EPHIDGET_OK;

	parentInterfaceKit = (PhidgetInterfaceKitDeviceHandle)phid->parent;
	parentMotorControl = (PhidgetMotorControlDeviceHandle)phid->parent;
	parentBridge = (PhidgetBridgeDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_ifkit488_VOLTAGERATIOINPUT_000:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1011_VOLTAGERATIOINPUT_000:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1013_VOLTAGERATIOINPUT_000:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_821:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_900:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_1000:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 125;
		ch->minVoltageRatio = -1;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->bridgeEnabled = parentBridge->bridgeEnabled[ch->phid.index];
		ch->bridgeGain = parentBridge->bridgeGain[ch->phid.index];
		ch->dataInterval = parentBridge->voltageRatioInputDataInterval[ch->phid.index];
		ch->voltageRatio = parentBridge->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentBridge->voltageRatioChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_102:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 125;
		ch->minVoltageRatio = -1;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->bridgeEnabled = parentBridge->bridgeEnabled[ch->phid.index];
		ch->bridgeGain = parentBridge->bridgeGain[ch->phid.index];
		ch->dataInterval = parentBridge->voltageRatioInputDataInterval[ch->phid.index];
		ch->voltageRatio = parentBridge->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentBridge->voltageRatioChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_200:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1200;
		ch->minVoltageRatio = -0.85;
		ch->maxVoltageRatio = 0.85;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 0.5;
		// Inputs, Settables
		ch->bridgeEnabled = parentBridge->bridgeEnabled[ch->phid.index];
		ch->bridgeGain = parentBridge->bridgeGain[ch->phid.index];
		ch->dataInterval = parentBridge->voltageRatioInputDataInterval[ch->phid.index];
		ch->voltageRatio = parentBridge->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentBridge->voltageRatioChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1065_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentMotorControl->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentMotorControl->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentMotorControl->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentMotorControl->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_000:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_120:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_300:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageRatioInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageRatioSensorType[ch->phid.index];
		ch->voltageRatio = parentInterfaceKit->voltageRatio[ch->phid.index];
		ch->voltageRatioChangeTrigger = parentInterfaceKit->voltageRatioChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageRatioSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_200:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_110:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1500_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltageRatio = -0.5;
		ch->maxVoltageRatio = 0.5;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 0.5;
		// Inputs, Settables
		ch->bridgeEnabled = PUNK_BOOL;
		ch->bridgeGain = PUNK_ENUM;
		ch->dataInterval = PUNK_UINT32;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_200:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_210:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 50;
		ch->minVoltageRatio = -1;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 2;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltageRatio = 0;
		ch->maxVoltageRatio = 1;
		ch->minVoltageRatioChangeTrigger = 0;
		ch->maxVoltageRatioChangeTrigger = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltageRatio = PUNK_DBL;
		ch->voltageRatioChangeTrigger = PUNK_DBL;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetVoltageRatioInputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetVoltageRatioInputHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_ifkit488_VOLTAGERATIOINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1011_VOLTAGERATIOINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1013_VOLTAGERATIOINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_821:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_900:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_1000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->bridgeEnabled = 1;
		ch->bridgeGain = BRIDGE_GAIN_128;
		ch->dataInterval = 256;
		ch->voltageRatioChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->bridgeEnabled);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRIDGEGAIN, NULL, NULL, 1, "%d", ch->bridgeGain);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_102:
		// Reset values
		// Must-set values
		// Default values
		ch->bridgeEnabled = 1;
		ch->bridgeGain = BRIDGE_GAIN_128;
		ch->dataInterval = 256;
		ch->voltageRatioChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->bridgeEnabled);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRIDGEGAIN, NULL, NULL, 1, "%d", ch->bridgeGain);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->bridgeEnabled = 1;
		ch->bridgeGain = BRIDGE_GAIN_128;
		ch->dataInterval = 250;
		ch->voltageRatioChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->bridgeEnabled);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRIDGEGAIN, NULL, NULL, 1, "%d", ch->bridgeGain);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
		  (uint32_t)round(ch->dataInterval), ch->dataInterval);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1065_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->voltageRatioChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1500_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->bridgeEnabled = 1;
		ch->bridgeGain = BRIDGE_GAIN_128;
		ch->dataInterval = 250;
		ch->voltageRatioChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->bridgeEnabled);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRIDGEGAIN, NULL, NULL, 1, "%d", ch->bridgeGain);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_100:
		// Reset values
		ch->voltageRatioChangeTrigger = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_200:
		// Reset values
		ch->voltageRatioChangeTrigger = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_210:
		// Reset values
		ch->voltageRatioChangeTrigger = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGERATIO;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 100;
		ch->voltageRatioChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 100;
		ch->voltageRatioChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageRatioChangeTrigger);
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

	mos_free(*ch, sizeof (struct _PhidgetVoltageRatioInput));
}

static PhidgetReturnCode CCONV
_create(PhidgetVoltageRatioInputHandle *phidp) {

	CHANNELCREATE_BODY(VoltageRatioInput, PHIDCHCLASS_VOLTAGERATIOINPUT);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_delete(PhidgetVoltageRatioInputHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetVoltageRatioInput_setBridgeEnabled(PhidgetVoltageRatioInputHandle ch, int bridgeEnabled) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETENABLED, NULL, NULL, 1, "%d",
	  bridgeEnabled));
}

API_PRETURN
PhidgetVoltageRatioInput_getBridgeEnabled(PhidgetVoltageRatioInputHandle ch, int *bridgeEnabled) {

	TESTPTR_PR(ch);
	TESTPTR_PR(bridgeEnabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1011_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1013_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_821:
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_900:
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_1000:
	case PHIDCHUID_1065_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_120:
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_300:
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_110:
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_210:
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*bridgeEnabled = ch->bridgeEnabled;
	if (ch->bridgeEnabled == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setBridgeGain(PhidgetVoltageRatioInputHandle ch,
  PhidgetVoltageRatioInput_BridgeGain bridgeGain) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETBRIDGEGAIN, NULL, NULL, 1, "%d",
	  bridgeGain));
}

API_PRETURN
PhidgetVoltageRatioInput_getBridgeGain(PhidgetVoltageRatioInputHandle ch,
  PhidgetVoltageRatioInput_BridgeGain *bridgeGain) {

	TESTPTR_PR(ch);
	TESTPTR_PR(bridgeGain);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1011_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1013_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_821:
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_900:
	case PHIDCHUID_1018_VOLTAGERATIOINPUT_1000:
	case PHIDCHUID_1065_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_000:
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_120:
	case PHIDCHUID_1202_VOLTAGERATIOINPUT_300:
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUB_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_DAQ1000_VOLTAGERATIOINPUT_110:
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DCC1000_VOLTAGERATIOINPUT_210:
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*bridgeGain = ch->bridgeGain;
	if (ch->bridgeGain == (PhidgetVoltageRatioInput_BridgeGain)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setDataInterval(PhidgetVoltageRatioInputHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetVoltageRatioInput_getDataInterval(PhidgetVoltageRatioInputHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMinDataInterval(PhidgetVoltageRatioInputHandle ch,
  uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMaxDataInterval(PhidgetVoltageRatioInputHandle ch,
  uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setDataRate(PhidgetVoltageRatioInputHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetVoltageRatioInput_getDataRate(PhidgetVoltageRatioInputHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMinDataRate(PhidgetVoltageRatioInputHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMaxDataRate(PhidgetVoltageRatioInputHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setSensorType(PhidgetVoltageRatioInputHandle ch,
  PhidgetVoltageRatioInput_SensorType sensorType) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSENSORTYPE, NULL, NULL, 1, "%d",
	  sensorType));
}

API_PRETURN
PhidgetVoltageRatioInput_getSensorType(PhidgetVoltageRatioInputHandle ch,
  PhidgetVoltageRatioInput_SensorType *sensorType) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorType);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_102:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DAQ1500_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*sensorType = ch->sensorType;
	if (ch->sensorType == (PhidgetVoltageRatioInput_SensorType)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getSensorUnit(PhidgetVoltageRatioInputHandle ch,
  Phidget_UnitInfo *sensorUnit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorUnit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_102:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DAQ1500_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*sensorUnit = ch->sensorUnit;
	if (ch->sensorUnitValid == PFALSE)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getSensorValue(PhidgetVoltageRatioInputHandle ch, double *sensorValue) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorValue);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_102:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DAQ1500_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*sensorValue = ch->sensorValue;
	if (ch->sensorValue == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setSensorValueChangeTrigger(PhidgetVoltageRatioInputHandle ch,
  double sensorValueChangeTrigger) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1,
	  "%g", sensorValueChangeTrigger));
}

API_PRETURN
PhidgetVoltageRatioInput_getSensorValueChangeTrigger(PhidgetVoltageRatioInputHandle ch,
  double *sensorValueChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorValueChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_102:
	case PHIDCHUID_1046_VOLTAGERATIOINPUT_200:
	case PHIDCHUID_DAQ1500_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HIN1100_VOLTAGERATIOINPUT_100:
	case PHIDCHUID_HUM1100_VOLTAGERATIOINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*sensorValueChangeTrigger = ch->sensorValueChangeTrigger;
	if (ch->sensorValueChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getVoltageRatio(PhidgetVoltageRatioInputHandle ch, double *voltageRatio) {

	TESTPTR_PR(ch);
	TESTPTR_PR(voltageRatio);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*voltageRatio = ch->voltageRatio;
	if (ch->voltageRatio == (double)PUNK_DBL || isnan(ch->voltageRatio))
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	if (ch->voltageRatio > ch->maxVoltageRatio)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALHIGH));
	if (ch->voltageRatio < ch->minVoltageRatio)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALLOW));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMinVoltageRatio(PhidgetVoltageRatioInputHandle ch,
  double *minVoltageRatio) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minVoltageRatio);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*minVoltageRatio = ch->minVoltageRatio;
	if (ch->minVoltageRatio == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMaxVoltageRatio(PhidgetVoltageRatioInputHandle ch,
  double *maxVoltageRatio) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxVoltageRatio);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*maxVoltageRatio = ch->maxVoltageRatio;
	if (ch->maxVoltageRatio == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setVoltageRatioChangeTrigger(PhidgetVoltageRatioInputHandle ch,
  double voltageRatioChangeTrigger) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
	  voltageRatioChangeTrigger));
}

API_PRETURN
PhidgetVoltageRatioInput_getVoltageRatioChangeTrigger(PhidgetVoltageRatioInputHandle ch,
  double *voltageRatioChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(voltageRatioChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*voltageRatioChangeTrigger = ch->voltageRatioChangeTrigger;
	if (ch->voltageRatioChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMinVoltageRatioChangeTrigger(PhidgetVoltageRatioInputHandle ch,
  double *minVoltageRatioChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minVoltageRatioChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*minVoltageRatioChangeTrigger = ch->minVoltageRatioChangeTrigger;
	if (ch->minVoltageRatioChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_getMaxVoltageRatioChangeTrigger(PhidgetVoltageRatioInputHandle ch,
  double *maxVoltageRatioChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxVoltageRatioChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);
	TESTATTACHED_PR(ch);

	*maxVoltageRatioChangeTrigger = ch->maxVoltageRatioChangeTrigger;
	if (ch->maxVoltageRatioChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setOnSensorChangeHandler(PhidgetVoltageRatioInputHandle ch,
  PhidgetVoltageRatioInput_OnSensorChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->SensorChange = NULL;
		MEMORY_BARRIER();
		ch->SensorChangeCtx = NULL;
	} else {
		ch->SensorChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->SensorChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(PhidgetVoltageRatioInputHandle ch,
  PhidgetVoltageRatioInput_OnVoltageRatioChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGERATIOINPUT);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->VoltageRatioChange = NULL;
		MEMORY_BARRIER();
		ch->VoltageRatioChangeCtx = NULL;
	} else {
		ch->VoltageRatioChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->VoltageRatioChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
