/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/temperaturesensordevice.h"
#include "device/vintdevice.h"
#include "device/spatialdevice.h"
static void CCONV PhidgetTemperatureSensor_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetTemperatureSensor_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetTemperatureSensor_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetTemperatureSensor_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetTemperatureSensor_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetTemperatureSensor_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetTemperatureSensor_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetTemperatureSensor_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetTemperatureSensor_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetTemperatureSensor {
	struct _PhidgetChannel phid;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	PhidgetTemperatureSensor_RTDType RTDType;
	Phidget_RTDWireSetup RTDWireSetup;
	double temperature;
	double minTemperature;
	double maxTemperature;
	double temperatureChangeTrigger;
	double minTemperatureChangeTrigger;
	double maxTemperatureChangeTrigger;
	PhidgetTemperatureSensor_ThermocoupleType thermocoupleType;
	PhidgetTemperatureSensor_OnTemperatureChangeCallback TemperatureChange;
	void *TemperatureChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetTemperatureSensorHandle ch;
	int nsversion;

	ch = (PhidgetTemperatureSensorHandle)phid;

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
	if (hasBridgePacketByName(bp, "RTDType"))
		ch->RTDType = getBridgePacketInt32ByName(bp, "RTDType");
	if (hasBridgePacketByName(bp, "RTDWireSetup"))
		ch->RTDWireSetup = getBridgePacketInt32ByName(bp, "RTDWireSetup");
	if (hasBridgePacketByName(bp, "temperature"))
		ch->temperature = getBridgePacketDoubleByName(bp, "temperature");
	if (hasBridgePacketByName(bp, "minTemperature"))
		ch->minTemperature = getBridgePacketDoubleByName(bp, "minTemperature");
	if (hasBridgePacketByName(bp, "maxTemperature"))
		ch->maxTemperature = getBridgePacketDoubleByName(bp, "maxTemperature");
	if (hasBridgePacketByName(bp, "temperatureChangeTrigger"))
		ch->temperatureChangeTrigger = getBridgePacketDoubleByName(bp, "temperatureChangeTrigger");
	if (hasBridgePacketByName(bp, "minTemperatureChangeTrigger"))
		ch->minTemperatureChangeTrigger = getBridgePacketDoubleByName(bp, "minTemperatureChangeTrigger");
	if (hasBridgePacketByName(bp, "maxTemperatureChangeTrigger"))
		ch->maxTemperatureChangeTrigger = getBridgePacketDoubleByName(bp, "maxTemperatureChangeTrigger");
	if (hasBridgePacketByName(bp, "thermocoupleType"))
		ch->thermocoupleType = getBridgePacketInt32ByName(bp, "thermocoupleType");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetTemperatureSensorHandle ch;

	ch = (PhidgetTemperatureSensorHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 16, "_class_version_=%u"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",RTDType=%d"
	  ",RTDWireSetup=%d"
	  ",temperature=%g"
	  ",minTemperature=%g"
	  ",maxTemperature=%g"
	  ",temperatureChangeTrigger=%g"
	  ",minTemperatureChangeTrigger=%g"
	  ",maxTemperatureChangeTrigger=%g"
	  ",thermocoupleType=%d"
	  ,1 /* class version */
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->RTDType
	  ,ch->RTDWireSetup
	  ,ch->temperature
	  ,ch->minTemperature
	  ,ch->maxTemperature
	  ,ch->temperatureChangeTrigger
	  ,ch->minTemperatureChangeTrigger
	  ,ch->maxTemperatureChangeTrigger
	  ,ch->thermocoupleType
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetTemperatureSensorHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetTemperatureSensorHandle)phid;
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
	case BP_SETRTDTYPE:
		if (!supportedRTDType(phid, (PhidgetTemperatureSensor_RTDType)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified RTDType is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->RTDType = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "RTDType");
		}
		break;
	case BP_SETRTDWIRESETUP:
		if (!supportedRTDWireSetup(phid, (Phidget_RTDWireSetup)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified RTDWireSetup is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->RTDWireSetup = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "RTDWireSetup");
		}
		break;
	case BP_SETCHANGETRIGGER:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minTemperatureChangeTrigger,
		  ch->maxTemperatureChangeTrigger);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->temperatureChangeTrigger = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "TemperatureChangeTrigger");
		}
		break;
	case BP_SETTHERMOCOUPLETYPE:
		if (!supportedThermocoupleType(phid,
		  (PhidgetTemperatureSensor_ThermocoupleType)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified ThermocoupleType is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->thermocoupleType = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "ThermocoupleType");
		}
		break;
	case BP_TEMPERATURECHANGE:
		ch->temperature = getBridgePacketDouble(bp, 0);
		FIRECH(ch, PhidgetTemperatureSensor, TemperatureChange, ch->temperature);
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
	PhidgetSpatialDeviceHandle parentSpatial;
	PhidgetVINTDeviceHandle parentVINT;
	PhidgetTemperatureSensorHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetTemperatureSensorHandle)phid;

	ret = EPHIDGET_OK;

	parentTemperatureSensor = (PhidgetTemperatureSensorDeviceHandle)phid->parent;
	parentSpatial = (PhidgetSpatialDeviceHandle)phid->parent;
	parentVINT = (PhidgetVINTDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1045_TEMPERATURESENSOR_IR_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 380;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperature = -70;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1045_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->maxTemperature = parentTemperatureSensor->maxTemperature[ch->phid.index];
		ch->minTemperature = parentTemperatureSensor->minTemperature[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		ch->thermocoupleType = parentTemperatureSensor->thermocoupleType[ch->phid.index];
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 150;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -55;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->maxTemperature = parentTemperatureSensor->maxTemperature[ch->phid.index];
		ch->minTemperature = parentTemperatureSensor->minTemperature[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		ch->thermocoupleType = parentTemperatureSensor->thermocoupleType[ch->phid.index];
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 150;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -55;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_000:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->maxTemperature = parentTemperatureSensor->maxTemperature[ch->phid.index];
		ch->minTemperature = parentTemperatureSensor->minTemperature[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_000:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 150;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -55;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->maxTemperature = parentTemperatureSensor->maxTemperature[ch->phid.index];
		ch->minTemperature = parentTemperatureSensor->minTemperature[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		ch->thermocoupleType = parentTemperatureSensor->thermocoupleType[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 150;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -55;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_300:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->maxTemperature = parentTemperatureSensor->maxTemperature[ch->phid.index];
		ch->minTemperature = parentTemperatureSensor->minTemperature[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		ch->thermocoupleType = parentTemperatureSensor->thermocoupleType[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_300:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 150;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -55;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_400:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperatureChangeTrigger = 1000;
		ch->minDataInterval = 32;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->maxTemperature = parentTemperatureSensor->maxTemperature[ch->phid.index];
		ch->minTemperature = parentTemperatureSensor->minTemperature[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		ch->thermocoupleType = parentTemperatureSensor->thermocoupleType[ch->phid.index];
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_400:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxTemperature = 150;
		ch->maxTemperatureChangeTrigger = 100;
		ch->minDataInterval = 32;
		ch->minTemperature = -55;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentTemperatureSensor->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentTemperatureSensor->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentTemperatureSensor->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 2;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 500;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 2;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 500;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_210:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 2;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 500;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1020_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 10;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 100;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_120:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 100;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1120_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 10;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HUM1000_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 2;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 500;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_HUM1001_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 20;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 50;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_MOT0109_TEMPERATURESENSOR_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 250;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 4;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentSpatial->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentSpatial->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentSpatial->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_USB:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 8;
		ch->minDataInterval = 10;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = parentSpatial->temperatureSensorDataInterval[ch->phid.index];
		ch->temperature = parentSpatial->temperature[ch->phid.index];
		ch->temperatureChangeTrigger = parentSpatial->temperatureChangeTrigger[ch->phid.index];
		break;
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_VINT:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 10;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 100;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_110:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxTemperature = 125;
		ch->maxTemperatureChangeTrigger = 165;
		ch->minDataInterval = 100;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1000_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 2;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 500;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_THERMOCOUPLE_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->maxTemperature = 1370;
		ch->maxTemperatureChangeTrigger = 1640;
		ch->minDataInterval = 20;
		ch->minTemperature = -270;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		ch->thermocoupleType = PUNK_ENUM;
		break;
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 3.3333333333333335;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 300;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->maxTemperature = 1370;
		ch->maxTemperatureChangeTrigger = 1640;
		ch->minDataInterval = 20;
		ch->minTemperature = -270;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		ch->thermocoupleType = PUNK_ENUM;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 3.3333333333333335;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 300;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->maxTemperature = 1370;
		ch->maxTemperatureChangeTrigger = 1640;
		ch->minDataInterval = 20;
		ch->minTemperature = -270;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		ch->thermocoupleType = PUNK_ENUM;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_200:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 3.3333333333333335;
		ch->maxTemperature = 85;
		ch->maxTemperatureChangeTrigger = 125;
		ch->minDataInterval = 300;
		ch->minTemperature = -40;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		break;
	case PHIDCHUID_TMP1200_TEMPERATURESENSOR_RTD_100:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 4;
		ch->maxTemperature = 850;
		ch->maxTemperatureChangeTrigger = 1050;
		ch->minDataInterval = 250;
		ch->minTemperature = -200;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		ch->RTDType = PUNK_ENUM;
		ch->RTDWireSetup = parentVINT->RTDWireSetupDevProp;
		break;
	case PHIDCHUID_TMP1200_TEMPERATURESENSOR_RTD_300:
		// Constants
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 3.003003003003003;
		ch->maxTemperature = 850;
		ch->maxTemperatureChangeTrigger = 1050;
		ch->minDataInterval = 333;
		ch->minTemperature = -200;
		ch->minTemperatureChangeTrigger = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->temperature = PUNK_DBL;
		ch->temperatureChangeTrigger = PUNK_DBL;
		ch->RTDType = PUNK_ENUM;
		ch->RTDWireSetup = parentVINT->RTDWireSetupDevProp;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetTemperatureSensorHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetTemperatureSensorHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1045_TEMPERATURESENSOR_IR_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1045_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_400:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_400:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_100:
		// Reset values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_200:
		// Reset values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_210:
		// Reset values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DCC1020_TEMPERATURESENSOR_IC_100:
		// Reset values
		ch->temperatureChangeTrigger = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 100;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1120_TEMPERATURESENSOR_IC_100:
		// Reset values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_HUM1000_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HUM1001_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_MOT0109_TEMPERATURESENSOR_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_USB:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_VINT:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1000_TEMPERATURESENSOR_IC_100:
		// Reset values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_THERMOCOUPLE_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ch->thermocoupleType = THERMOCOUPLE_TYPE_K;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
		  ch->thermocoupleType);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_200:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 500;
		ch->temperatureChangeTrigger = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1200_TEMPERATURESENSOR_RTD_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->temperatureChangeTrigger = 0;
		ch->RTDType = RTD_TYPE_PT1000_3850;
		// (Device Property - check if already set)
		if (ch->RTDWireSetup == PUNK_ENUM)
			ch->RTDWireSetup = RTD_WIRE_SETUP_4WIRE;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETRTDTYPE, NULL, NULL, 1, "%d", ch->RTDType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETRTDWIRESETUP, NULL, NULL, 1, "%d", ch->RTDWireSetup);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_TMP1200_TEMPERATURESENSOR_RTD_300:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 333;
		ch->temperatureChangeTrigger = 0;
		ch->RTDType = RTD_TYPE_PT1000_3850;
		// (Device Property - check if already set)
		if (ch->RTDWireSetup == PUNK_ENUM)
			ch->RTDWireSetup = RTD_WIRE_SETUP_4WIRE;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
		  ch->temperatureChangeTrigger);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETRTDTYPE, NULL, NULL, 1, "%d", ch->RTDType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETRTDWIRESETUP, NULL, NULL, 1, "%d", ch->RTDWireSetup);
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
	PhidgetTemperatureSensorHandle ch;

	ch = (PhidgetTemperatureSensorHandle)phid;

	if(ch->temperature != PUNK_DBL)
		FIRECH(ch, PhidgetTemperatureSensor, TemperatureChange, ch->temperature);

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {
	PhidgetTemperatureSensorHandle ch;

	ch = (PhidgetTemperatureSensorHandle)phid;

	if(ch->temperature == PUNK_DBL)
		return (PFALSE);

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetTemperatureSensor));
}

static PhidgetReturnCode CCONV
_create(PhidgetTemperatureSensorHandle *phidp) {

	CHANNELCREATE_BODY(TemperatureSensor, PHIDCHCLASS_TEMPERATURESENSOR);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_delete(PhidgetTemperatureSensorHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetTemperatureSensor_setDataInterval(PhidgetTemperatureSensorHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetTemperatureSensor_getDataInterval(PhidgetTemperatureSensorHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMinDataInterval(PhidgetTemperatureSensorHandle ch,
  uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMaxDataInterval(PhidgetTemperatureSensorHandle ch,
  uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_setDataRate(PhidgetTemperatureSensorHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetTemperatureSensor_getDataRate(PhidgetTemperatureSensorHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMinDataRate(PhidgetTemperatureSensorHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMaxDataRate(PhidgetTemperatureSensorHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_setRTDType(PhidgetTemperatureSensorHandle ch,
  PhidgetTemperatureSensor_RTDType RTDType) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETRTDTYPE, NULL, NULL, 1, "%d", RTDType));
}

API_PRETURN
PhidgetTemperatureSensor_getRTDType(PhidgetTemperatureSensorHandle ch,
  PhidgetTemperatureSensor_RTDType *RTDType) {

	TESTPTR_PR(ch);
	TESTPTR_PR(RTDType);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1045_TEMPERATURESENSOR_IR_100:
	case PHIDCHUID_1045_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_200:
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_000:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_000:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_300:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_300:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_400:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_400:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_210:
	case PHIDCHUID_DCC1020_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_120:
	case PHIDCHUID_DCC1120_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_HUM1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_HUM1001_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_MOT0109_TEMPERATURESENSOR_100:
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_USB:
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_VINT:
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_110:
	case PHIDCHUID_TMP1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_THERMOCOUPLE_100:
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_200:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*RTDType = ch->RTDType;
	if (ch->RTDType == (PhidgetTemperatureSensor_RTDType)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_setRTDWireSetup(PhidgetTemperatureSensorHandle ch,
  Phidget_RTDWireSetup RTDWireSetup) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETRTDWIRESETUP, NULL, NULL, 1, "%d",
	  RTDWireSetup));
}

API_PRETURN
PhidgetTemperatureSensor_getRTDWireSetup(PhidgetTemperatureSensorHandle ch,
  Phidget_RTDWireSetup *RTDWireSetup) {

	TESTPTR_PR(ch);
	TESTPTR_PR(RTDWireSetup);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1045_TEMPERATURESENSOR_IR_100:
	case PHIDCHUID_1045_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_THERMOCOUPLE_200:
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_000:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_000:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_300:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_300:
	case PHIDCHUID_1051_TEMPERATURESENSOR_THERMOCOUPLE_400:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_400:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_210:
	case PHIDCHUID_DCC1020_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_120:
	case PHIDCHUID_DCC1120_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_HUM1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_HUM1001_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_MOT0109_TEMPERATURESENSOR_100:
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_USB:
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_VINT:
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_110:
	case PHIDCHUID_TMP1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_THERMOCOUPLE_100:
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_THERMOCOUPLE_200:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*RTDWireSetup = ch->RTDWireSetup;
	if (ch->RTDWireSetup == (Phidget_RTDWireSetup)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getTemperature(PhidgetTemperatureSensorHandle ch, double *temperature) {

	TESTPTR_PR(ch);
	TESTPTR_PR(temperature);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*temperature = ch->temperature;
	if (ch->temperature == (double)PUNK_DBL || isnan(ch->temperature))
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	if (ch->temperature > ch->maxTemperature)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALHIGH));
	if (ch->temperature < ch->minTemperature)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALLOW));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMinTemperature(PhidgetTemperatureSensorHandle ch, double *minTemperature) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minTemperature);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*minTemperature = ch->minTemperature;
	if (ch->minTemperature == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMaxTemperature(PhidgetTemperatureSensorHandle ch, double *maxTemperature) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxTemperature);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*maxTemperature = ch->maxTemperature;
	if (ch->maxTemperature == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_setTemperatureChangeTrigger(PhidgetTemperatureSensorHandle ch,
  double temperatureChangeTrigger) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETCHANGETRIGGER, NULL, NULL, 1, "%g",
	  temperatureChangeTrigger));
}

API_PRETURN
PhidgetTemperatureSensor_getTemperatureChangeTrigger(PhidgetTemperatureSensorHandle ch,
  double *temperatureChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(temperatureChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*temperatureChangeTrigger = ch->temperatureChangeTrigger;
	if (ch->temperatureChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMinTemperatureChangeTrigger(PhidgetTemperatureSensorHandle ch,
  double *minTemperatureChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minTemperatureChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*minTemperatureChangeTrigger = ch->minTemperatureChangeTrigger;
	if (ch->minTemperatureChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_getMaxTemperatureChangeTrigger(PhidgetTemperatureSensorHandle ch,
  double *maxTemperatureChangeTrigger) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxTemperatureChangeTrigger);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	*maxTemperatureChangeTrigger = ch->maxTemperatureChangeTrigger;
	if (ch->maxTemperatureChangeTrigger == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_setThermocoupleType(PhidgetTemperatureSensorHandle ch,
  PhidgetTemperatureSensor_ThermocoupleType thermocoupleType) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETTHERMOCOUPLETYPE, NULL, NULL, 1, "%d",
	  thermocoupleType));
}

API_PRETURN
PhidgetTemperatureSensor_getThermocoupleType(PhidgetTemperatureSensorHandle ch,
  PhidgetTemperatureSensor_ThermocoupleType *thermocoupleType) {

	TESTPTR_PR(ch);
	TESTPTR_PR(thermocoupleType);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1045_TEMPERATURESENSOR_IR_100:
	case PHIDCHUID_1045_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_1048_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_000:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_300:
	case PHIDCHUID_1051_TEMPERATURESENSOR_IC_400:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_DCC1000_TEMPERATURESENSOR_IC_210:
	case PHIDCHUID_DCC1020_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_DCC1100_TEMPERATURESENSOR_IC_120:
	case PHIDCHUID_DCC1120_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_HUM1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_HUM1001_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_MOT0109_TEMPERATURESENSOR_100:
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_USB:
	case PHIDCHUID_MOT0110_TEMPERATURESENSOR_100_VINT:
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_SAF1000_TEMPERATURESENSOR_IC_110:
	case PHIDCHUID_TMP1000_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1100_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_100:
	case PHIDCHUID_TMP1101_TEMPERATURESENSOR_IC_200:
	case PHIDCHUID_TMP1200_TEMPERATURESENSOR_RTD_100:
	case PHIDCHUID_TMP1200_TEMPERATURESENSOR_RTD_300:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*thermocoupleType = ch->thermocoupleType;
	if (ch->thermocoupleType == (PhidgetTemperatureSensor_ThermocoupleType)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetTemperatureSensor_setOnTemperatureChangeHandler(PhidgetTemperatureSensorHandle ch,
  PhidgetTemperatureSensor_OnTemperatureChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_TEMPERATURESENSOR);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->TemperatureChange = NULL;
		MEMORY_BARRIER();
		ch->TemperatureChangeCtx = NULL;
	} else {
		ch->TemperatureChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->TemperatureChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
