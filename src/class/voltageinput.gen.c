/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/interfacekitdevice.h"
#include "device/temperaturesensordevice.h"
#include "device/phsensordevice.h"
#include "device/motorcontroldevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetVoltageInput_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetVoltageInput_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetVoltageInput_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetVoltageInput_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetVoltageInput_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetVoltageInput_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetVoltageInput_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetVoltageInput_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetVoltageInput_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetVoltageInput {
	struct _PhidgetChannel phid;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	Phidget_PowerSupply powerSupply;
	PhidgetVoltageInput_SensorType sensorType;
	Phidget_UnitInfo sensorUnit;
	uint8_t sensorUnitValid;
	double sensorValue;
	double sensorValueChangeTrigger;
	double voltage;
	double minVoltage;
	double maxVoltage;
	double voltageChangeTrigger;
	double minVoltageChangeTrigger;
	double maxVoltageChangeTrigger;
	PhidgetVoltageInput_VoltageRange voltageRange;
	PhidgetVoltageInput_OnSensorChangeCallback SensorChange;
	void *SensorChangeCtx;
	PhidgetVoltageInput_OnVoltageChangeCallback VoltageChange;
	void *VoltageChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetVoltageInputHandle ch;
	int nsversion;

	ch = (PhidgetVoltageInputHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 1) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 1 - functionality may be limited.", phid, nsversion);
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
	if (hasBridgePacketByName(bp, "powerSupply"))
		ch->powerSupply = getBridgePacketInt32ByName(bp, "powerSupply");
	if (hasBridgePacketByName(bp, "sensorType"))
		ch->sensorType = getBridgePacketInt32ByName(bp, "sensorType");
	if (hasBridgePacketByName(bp, "sensorValue"))
		ch->sensorValue = getBridgePacketDoubleByName(bp, "sensorValue");
	if (hasBridgePacketByName(bp, "sensorValueChangeTrigger"))
		ch->sensorValueChangeTrigger = getBridgePacketDoubleByName(bp, "sensorValueChangeTrigger");
	if (hasBridgePacketByName(bp, "voltage"))
		ch->voltage = getBridgePacketDoubleByName(bp, "voltage");
	if (hasBridgePacketByName(bp, "minVoltage"))
		ch->minVoltage = getBridgePacketDoubleByName(bp, "minVoltage");
	if (hasBridgePacketByName(bp, "maxVoltage"))
		ch->maxVoltage = getBridgePacketDoubleByName(bp, "maxVoltage");
	if (hasBridgePacketByName(bp, "voltageChangeTrigger"))
		ch->voltageChangeTrigger = getBridgePacketDoubleByName(bp, "voltageChangeTrigger");
	if (hasBridgePacketByName(bp, "minVoltageChangeTrigger"))
		ch->minVoltageChangeTrigger = getBridgePacketDoubleByName(bp, "minVoltageChangeTrigger");
	if (hasBridgePacketByName(bp, "maxVoltageChangeTrigger"))
		ch->maxVoltageChangeTrigger = getBridgePacketDoubleByName(bp, "maxVoltageChangeTrigger");
	if (hasBridgePacketByName(bp, "voltageRange"))
		ch->voltageRange = getBridgePacketInt32ByName(bp, "voltageRange");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetVoltageInputHandle ch;

	ch = (PhidgetVoltageInputHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 18, "_class_version_=%u"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",powerSupply=%d"
	  ",sensorType=%d"
	  ",sensorValue=%g"
	  ",sensorValueChangeTrigger=%g"
	  ",voltage=%g"
	  ",minVoltage=%g"
	  ",maxVoltage=%g"
	  ",voltageChangeTrigger=%g"
	  ",minVoltageChangeTrigger=%g"
	  ",maxVoltageChangeTrigger=%g"
	  ",voltageRange=%d"
	  ,1 /* class version */
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->powerSupply
	  ,ch->sensorType
	  ,ch->sensorValue
	  ,ch->sensorValueChangeTrigger
	  ,ch->voltage
	  ,ch->minVoltage
	  ,ch->maxVoltage
	  ,ch->voltageChangeTrigger
	  ,ch->minVoltageChangeTrigger
	  ,ch->maxVoltageChangeTrigger
	  ,ch->voltageRange
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetVoltageInputHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetVoltageInputHandle)phid;
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
	case BP_SETPOWERSUPPLY:
		if (!supportedPowerSupply(phid, (Phidget_PowerSupply)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified PowerSupply is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->powerSupply = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "PowerSupply");
		}
		break;
	case BP_SETSENSORTYPE:
		if (!supportedVoltageSensorType(phid, (PhidgetVoltageInput_SensorType)getBridgePacketInt32(bp,
		  0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified VoltageSensorType is unsupported by this device."));
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
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minVoltageChangeTrigger,
		  ch->maxVoltageChangeTrigger);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->voltageChangeTrigger = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "VoltageChangeTrigger");
		}
		break;
	case BP_SETVOLTAGERANGE:
		if (!supportedVoltageRange(phid, (PhidgetVoltageInput_VoltageRange)getBridgePacketInt32(bp,
		  0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified VoltageRange is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->voltageRange = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "VoltageRange");
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
	PhidgetTemperatureSensorDeviceHandle parentTemperatureSensor;
	PhidgetInterfaceKitDeviceHandle parentInterfaceKit;
	PhidgetMotorControlDeviceHandle parentMotorControl;
	PhidgetPHSensorDeviceHandle parentPHSensor;
	PhidgetVINTDeviceHandle parentVINT;
	PhidgetVoltageInputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetVoltageInputHandle)phid;

	ret = EPHIDGET_OK;

	parentTemperatureSensor = (PhidgetTemperatureSensorDeviceHandle)phid->parent;
	parentInterfaceKit = (PhidgetInterfaceKitDeviceHandle)phid->parent;
	parentMotorControl = (PhidgetMotorControlDeviceHandle)phid->parent;
	parentPHSensor = (PhidgetPHSensorDeviceHandle)phid->parent;
	parentVINT = (PhidgetVINTDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1011_VOLTAGEINPUT_000:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1013_VOLTAGEINPUT_000:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1018_VOLTAGEINPUT_821:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1018_VOLTAGEINPUT_900:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1018_VOLTAGEINPUT_1000:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5.456;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->minVoltage = -0.01001;
		ch->maxVoltage = 0.07741;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.08742;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentTemperatureSensor->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentTemperatureSensor->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->minVoltage = -0.01001;
		ch->maxVoltage = 0.07741;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.08742;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentTemperatureSensor->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentTemperatureSensor->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->minVoltage = -0.01001;
		ch->maxVoltage = 0.07741;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.08742;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentTemperatureSensor->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentTemperatureSensor->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->minVoltage = -0.01001;
		ch->maxVoltage = 0.07741;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.08742;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentTemperatureSensor->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentTemperatureSensor->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->minVoltage = -0.01001;
		ch->maxVoltage = 0.07741;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.08742;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentTemperatureSensor->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentTemperatureSensor->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 80;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 12.5;
		ch->minVoltage = -0.52711;
		ch->maxVoltage = 0.52687;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.1054;
		// Inputs, Settables
		ch->dataInterval = parentPHSensor->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentPHSensor->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentPHSensor->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1065_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentMotorControl->voltageSensorType[ch->phid.index];
		ch->voltage = parentMotorControl->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentMotorControl->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentMotorControl->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->minVoltage = 0;
		ch->maxVoltage = 80;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 80;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->voltageInputDataInterval[ch->phid.index];
		ch->voltage = parentMotorControl->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentMotorControl->voltageChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1202_VOLTAGEINPUT_000:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1202_VOLTAGEINPUT_120:
		// Constants
		ch->minDataInterval = 16;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 62.5;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1202_VOLTAGEINPUT_300:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 1000;
		ch->minDataRate = 1;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = parentInterfaceKit->voltageInputDataInterval[ch->phid.index];
		ch->sensorType = parentInterfaceKit->voltageSensorType[ch->phid.index];
		ch->voltage = parentInterfaceKit->voltage[ch->phid.index];
		ch->voltageChangeTrigger = parentInterfaceKit->voltageChangeTrigger[ch->phid.index];
		ch->sensorValueChangeTrigger = parentInterfaceKit->voltageSensorValueChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_HUB_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HUB_VOLTAGEINPUT_110:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5.25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HUB_VOLTAGEINPUT_200:
		// Constants
		ch->minDataInterval = 1;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 1000;
		ch->minVoltage = 0;
		ch->maxVoltage = 5.25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_ADP1000_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 50;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 20;
		ch->minVoltage = -2;
		ch->maxVoltage = 2;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 4;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->voltageRange = PUNK_ENUM;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_110:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = 0;
		ch->maxVoltage = 5.25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = 0;
		ch->maxVoltage = 5;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_120:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = 0;
		ch->maxVoltage = 5.25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_130:
		// Constants
		ch->minDataInterval = 10;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->minVoltage = 0;
		ch->maxVoltage = 5.25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 5;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->sensorType = PUNK_ENUM;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->sensorValueChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 10;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->minVoltage = 0;
		ch->maxVoltage = 50;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 25;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 10;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->minVoltage = 0;
		ch->maxVoltage = 50;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 25;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltage = 0;
		ch->maxVoltage = 40;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 32;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltage = 0;
		ch->maxVoltage = 40;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 32;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltage = 0;
		ch->maxVoltage = 40;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 20;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltage = 0;
		ch->maxVoltage = 40;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 20;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
		// Constants
		ch->minDataInterval = 10;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->minVoltage = 0;
		ch->maxVoltage = 40;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 20;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = -0.011;
		ch->maxVoltage = 0.079;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.09;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = -0.011;
		ch->maxVoltage = 0.079;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.09;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->minVoltage = -0.011;
		ch->maxVoltage = 0.08;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 0.09;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 80;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->minVoltage = PUNK_DBL;
		ch->maxVoltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->voltageRange = PUNK_ENUM;
		break;
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 40;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 80;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->minVoltage = PUNK_DBL;
		ch->maxVoltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->voltageRange = PUNK_ENUM;
		break;
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
		// Constants
		ch->minDataInterval = 12;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 83.33333333333333;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 80;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->minVoltage = PUNK_DBL;
		ch->maxVoltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->voltageRange = PUNK_ENUM;
		break;
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
		// Constants
		ch->minDataInterval = 40;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 25;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 2;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->minVoltage = PUNK_DBL;
		ch->maxVoltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->voltageRange = PUNK_ENUM;
		break;
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
		// Constants
		ch->minDataInterval = 12;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 83.33333333333333;
		ch->minVoltageChangeTrigger = 0;
		ch->maxVoltageChangeTrigger = 2;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->voltage = PUNK_DBL;
		ch->minVoltage = PUNK_DBL;
		ch->maxVoltage = PUNK_DBL;
		ch->voltageChangeTrigger = PUNK_DBL;
		ch->voltageRange = PUNK_ENUM;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetVoltageInputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetVoltageInputHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1011_VOLTAGEINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1013_VOLTAGEINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1018_VOLTAGEINPUT_821:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1018_VOLTAGEINPUT_900:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1018_VOLTAGEINPUT_1000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1065_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_VOLTAGEINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_VOLTAGEINPUT_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_VOLTAGEINPUT_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUB_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUB_VOLTAGEINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUB_VOLTAGEINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_ADP1000_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->voltageRange = VOLTAGE_RANGE_400mV;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d", ch->voltageRange);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_130:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 10;
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		ch->sensorType = SENSOR_TYPE_VOLTAGE;
		ch->voltageChangeTrigger = 0;
		ch->sensorValueChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORTYPE, NULL, NULL, 1, "%d", ch->sensorType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->sensorValueChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 100;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ch->voltageRange = VOLTAGE_RANGE_40V;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d", ch->voltageRange);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ch->voltageRange = VOLTAGE_RANGE_AUTO;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d", ch->voltageRange);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ch->voltageRange = VOLTAGE_RANGE_AUTO;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d", ch->voltageRange);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ch->voltageRange = VOLTAGE_RANGE_AUTO;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d", ch->voltageRange);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->voltageChangeTrigger = 0;
		ch->voltageRange = VOLTAGE_RANGE_AUTO;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->voltageChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d", ch->voltageRange);
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

	mos_free(*ch, sizeof (struct _PhidgetVoltageInput));
}

static PhidgetReturnCode CCONV
_create(PhidgetVoltageInputHandle *phidp) {

	CHANNELCREATE_BODY(VoltageInput, PHIDCHCLASS_VOLTAGEINPUT);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_delete(PhidgetVoltageInputHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetVoltageInput_setDataInterval(PhidgetVoltageInputHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetVoltageInput_getDataInterval(PhidgetVoltageInputHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMinDataInterval(PhidgetVoltageInputHandle ch, uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMaxDataInterval(PhidgetVoltageInputHandle ch, uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_setDataRate(PhidgetVoltageInputHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetVoltageInput_getDataRate(PhidgetVoltageInputHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMinDataRate(PhidgetVoltageInputHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMaxDataRate(PhidgetVoltageInputHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_setPowerSupply(PhidgetVoltageInputHandle ch, Phidget_PowerSupply powerSupply) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d",
	  powerSupply));
}

API_PRETURN
PhidgetVoltageInput_getPowerSupply(PhidgetVoltageInputHandle ch, Phidget_PowerSupply *powerSupply) {

	TESTPTR_PR(ch);
	TESTPTR_PR(powerSupply);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1011_VOLTAGEINPUT_000:
	case PHIDCHUID_1013_VOLTAGEINPUT_000:
	case PHIDCHUID_1018_VOLTAGEINPUT_821:
	case PHIDCHUID_1018_VOLTAGEINPUT_900:
	case PHIDCHUID_1018_VOLTAGEINPUT_1000:
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
	case PHIDCHUID_1202_VOLTAGEINPUT_000:
	case PHIDCHUID_1202_VOLTAGEINPUT_120:
	case PHIDCHUID_1202_VOLTAGEINPUT_300:
	case PHIDCHUID_HUB_VOLTAGEINPUT_100:
	case PHIDCHUID_HUB_VOLTAGEINPUT_110:
	case PHIDCHUID_HUB_VOLTAGEINPUT_200:
	case PHIDCHUID_ADP1000_VOLTAGEINPUT_100:
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_100:
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_110:
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*powerSupply = ch->powerSupply;
	if (ch->powerSupply == (Phidget_PowerSupply)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_setSensorType(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_SensorType sensorType) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSENSORTYPE, NULL, NULL, 1, "%d",
	  sensorType));
}

API_PRETURN
PhidgetVoltageInput_getSensorType(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_SensorType *sensorType) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorType);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*sensorType = ch->sensorType;
	if (ch->sensorType == (PhidgetVoltageInput_SensorType)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getSensorUnit(PhidgetVoltageInputHandle ch, Phidget_UnitInfo *sensorUnit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorUnit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
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
PhidgetVoltageInput_getSensorValue(PhidgetVoltageInputHandle ch, double *sensorValue) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorValue);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
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
PhidgetVoltageInput_setSensorValueChangeTrigger(PhidgetVoltageInputHandle ch,
  double sensorValueChangeTrigger) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSENSORVALUECHANGETRIGGER, NULL, NULL, 1,
	  "%g", sensorValueChangeTrigger));
}

API_PRETURN
PhidgetVoltageInput_getSensorValueChangeTrigger(PhidgetVoltageInputHandle ch,
  double *sensorValueChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(sensorValueChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
	case PHIDCHUID_VCP1000_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1001_VOLTAGEINPUT_110:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_100:
	case PHIDCHUID_VCP1002_VOLTAGEINPUT_110:
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
PhidgetVoltageInput_getVoltage(PhidgetVoltageInputHandle ch, double *voltage) {

	TESTPTR_PR(ch);
	TESTPTR_PR(voltage);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*voltage = ch->voltage;
	if (ch->voltage == (double)PUNK_DBL || isnan(ch->voltage))
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	if (ch->voltage > ch->maxVoltage)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALHIGH));
	if (ch->voltage < ch->minVoltage)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALLOW));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMinVoltage(PhidgetVoltageInputHandle ch, double *minVoltage) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minVoltage);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*minVoltage = ch->minVoltage;
	if (ch->minVoltage == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMaxVoltage(PhidgetVoltageInputHandle ch, double *maxVoltage) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxVoltage);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*maxVoltage = ch->maxVoltage;
	if (ch->maxVoltage == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_setVoltageChangeTrigger(PhidgetVoltageInputHandle ch, double voltageChangeTrigger) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
	  voltageChangeTrigger));
}

API_PRETURN
PhidgetVoltageInput_getVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double *voltageChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(voltageChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*voltageChangeTrigger = ch->voltageChangeTrigger;
	if (ch->voltageChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMinVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double *minVoltageChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minVoltageChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*minVoltageChangeTrigger = ch->minVoltageChangeTrigger;
	if (ch->minVoltageChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_getMaxVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double *maxVoltageChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxVoltageChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	*maxVoltageChangeTrigger = ch->maxVoltageChangeTrigger;
	if (ch->maxVoltageChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_setVoltageRange(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_VoltageRange voltageRange) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETVOLTAGERANGE, NULL, NULL, 1, "%d",
	  voltageRange));
}

API_PRETURN
PhidgetVoltageInput_getVoltageRange(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_VoltageRange *voltageRange) {

	TESTPTR_PR(ch);
	TESTPTR_PR(voltageRange);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1011_VOLTAGEINPUT_000:
	case PHIDCHUID_1013_VOLTAGEINPUT_000:
	case PHIDCHUID_1018_VOLTAGEINPUT_821:
	case PHIDCHUID_1018_VOLTAGEINPUT_900:
	case PHIDCHUID_1018_VOLTAGEINPUT_1000:
	case PHIDCHUID_1048_VOLTAGEINPUT_100:
	case PHIDCHUID_1048_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_200:
	case PHIDCHUID_1051_VOLTAGEINPUT_300:
	case PHIDCHUID_1051_VOLTAGEINPUT_400:
	case PHIDCHUID_1058_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_100:
	case PHIDCHUID_1065_VOLTAGEINPUT_SUPPLY_100:
	case PHIDCHUID_1202_VOLTAGEINPUT_000:
	case PHIDCHUID_1202_VOLTAGEINPUT_120:
	case PHIDCHUID_1202_VOLTAGEINPUT_300:
	case PHIDCHUID_HUB_VOLTAGEINPUT_100:
	case PHIDCHUID_HUB_VOLTAGEINPUT_110:
	case PHIDCHUID_HUB_VOLTAGEINPUT_200:
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_100:
	case PHIDCHUID_DAQ1000_VOLTAGEINPUT_110:
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_100:
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_120:
	case PHIDCHUID_DAQ1400_VOLTAGEINPUT_130:
	case PHIDCHUID_DCC1020_VOLTAGEINPUT_100:
	case PHIDCHUID_DCC1120_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_100:
	case PHIDCHUID_SAF1000_VOLTAGEINPUT_110:
	case PHIDCHUID_STC1003_VOLTAGEINPUT_200:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_100:
	case PHIDCHUID_STC1005_VOLTAGEINPUT_110:
	case PHIDCHUID_TMP1100_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_100:
	case PHIDCHUID_TMP1101_VOLTAGEINPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*voltageRange = ch->voltageRange;
	if (ch->voltageRange == (PhidgetVoltageInput_VoltageRange)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetVoltageInput_setOnSensorChangeHandler(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_OnSensorChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);

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
PhidgetVoltageInput_setOnVoltageChangeHandler(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_OnVoltageChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_VOLTAGEINPUT);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->VoltageChange = NULL;
		MEMORY_BARRIER();
		ch->VoltageChangeCtx = NULL;
	} else {
		ch->VoltageChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->VoltageChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
