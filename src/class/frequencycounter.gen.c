/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/frequencycounterdevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetFrequencyCounter_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetFrequencyCounter_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetFrequencyCounter_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetFrequencyCounter_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetFrequencyCounter_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetFrequencyCounter_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetFrequencyCounter_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetFrequencyCounter_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetFrequencyCounter_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetFrequencyCounter {
	struct _PhidgetChannel phid;
	double totalTicksSinceLastCount;
	uint32_t frequencyPrecision;
	uint64_t count;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	int enabled;
	PhidgetFrequencyCounter_FilterType filterType;
	double frequency;
	double maxFrequency;
	double frequencyCutoff;
	double minFrequencyCutoff;
	double maxFrequencyCutoff;
	Phidget_InputMode inputMode;
	Phidget_PowerSupply powerSupply;
	double timeElapsed;
	PhidgetFrequencyCounter_OnCountChangeCallback CountChange;
	void *CountChangeCtx;
	PhidgetFrequencyCounter_OnFrequencyChangeCallback FrequencyChange;
	void *FrequencyChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetFrequencyCounterHandle ch;
	int nsversion;

	ch = (PhidgetFrequencyCounterHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 3) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 3 - functionality may be limited.", phid, nsversion);
	}

	if(hasBridgePacketByName(bp, "totalTicksSinceLastCount"))
		ch->totalTicksSinceLastCount = getBridgePacketDoubleByName(bp, "totalTicksSinceLastCount");
	if(hasBridgePacketByName(bp, "frequencyPrecision"))
		ch->frequencyPrecision = getBridgePacketUInt32ByName(bp, "frequencyPrecision");
	if (hasBridgePacketByName(bp, "count"))
		ch->count = getBridgePacketUInt64ByName(bp, "count");
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
	if (hasBridgePacketByName(bp, "filterType"))
		ch->filterType = getBridgePacketInt32ByName(bp, "filterType");
	if (hasBridgePacketByName(bp, "frequency"))
		ch->frequency = getBridgePacketDoubleByName(bp, "frequency");
	if (hasBridgePacketByName(bp, "maxFrequency"))
		ch->maxFrequency = getBridgePacketDoubleByName(bp, "maxFrequency");
	if (hasBridgePacketByName(bp, "frequencyCutoff"))
		ch->frequencyCutoff = getBridgePacketDoubleByName(bp, "frequencyCutoff");
	if (hasBridgePacketByName(bp, "minFrequencyCutoff"))
		ch->minFrequencyCutoff = getBridgePacketDoubleByName(bp, "minFrequencyCutoff");
	if (hasBridgePacketByName(bp, "maxFrequencyCutoff"))
		ch->maxFrequencyCutoff = getBridgePacketDoubleByName(bp, "maxFrequencyCutoff");
	if (hasBridgePacketByName(bp, "inputMode"))
		ch->inputMode = getBridgePacketInt32ByName(bp, "inputMode");
	if (hasBridgePacketByName(bp, "powerSupply"))
		ch->powerSupply = getBridgePacketInt32ByName(bp, "powerSupply");
	if (hasBridgePacketByName(bp, "timeElapsed"))
		ch->timeElapsed = getBridgePacketDoubleByName(bp, "timeElapsed");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetFrequencyCounterHandle ch;

	ch = (PhidgetFrequencyCounterHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 20, "_class_version_=%u"
	  ",totalTicksSinceLastCount=%g"
	  ",frequencyPrecision=%u"
	  ",count=%ul"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",enabled=%d"
	  ",filterType=%d"
	  ",frequency=%g"
	  ",maxFrequency=%g"
	  ",frequencyCutoff=%g"
	  ",minFrequencyCutoff=%g"
	  ",maxFrequencyCutoff=%g"
	  ",inputMode=%d"
	  ",powerSupply=%d"
	  ",timeElapsed=%g"
	  ,3 /* class version */
	  ,ch->totalTicksSinceLastCount
	  ,ch->frequencyPrecision
	  ,ch->count
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->enabled
	  ,ch->filterType
	  ,ch->frequency
	  ,ch->maxFrequency
	  ,ch->frequencyCutoff
	  ,ch->minFrequencyCutoff
	  ,ch->maxFrequencyCutoff
	  ,ch->inputMode
	  ,ch->powerSupply
	  ,ch->timeElapsed
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetFrequencyCounterHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetFrequencyCounterHandle)phid;
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
	case BP_SETFILTERTYPE:
		if (!supportedFilterType(phid, (PhidgetFrequencyCounter_FilterType)getBridgePacketInt32(bp,
		  0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified FilterType is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->filterType = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "FilterType");
		}
		break;
	case BP_SETINPUTMODE:
		if (!supportedInputMode(phid, (Phidget_InputMode)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified InputMode is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->inputMode = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "InputMode");
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
	default:
		logerr("%"PRIphid": unsupported bridge packet:0x%x", phid, bp->vpkt);
		res = EPHIDGET_UNSUPPORTED;
	}

	return (res);
}

static PhidgetReturnCode CCONV
_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetFrequencyCounterDeviceHandle parentFrequencyCounter;
	PhidgetVINTDeviceHandle parentVINT;
	PhidgetFrequencyCounterHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetFrequencyCounterHandle)phid;

	ret = EPHIDGET_OK;

	parentFrequencyCounter = (PhidgetFrequencyCounterDeviceHandle)phid->parent;
	parentVINT = (PhidgetVINTDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1054_FREQUENCYCOUNTER_000:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxFrequency = 1000000;
		ch->maxFrequencyCutoff = 10;
		ch->minFrequencyCutoff = 0.01;
		ch->count = 0;
		ch->timeElapsed = 0;
		ch->frequency = 0;
		// Inputs, Settables
		ch->dataInterval = parentFrequencyCounter->frequencyCounterDataInterval[ch->phid.index];
		ch->frequencyCutoff = 1;
		ch->filterType = parentFrequencyCounter->filterType[ch->phid.index];
		ch->enabled = parentFrequencyCounter->enabled[ch->phid.index];
		break;
	case PHIDCHUID_DAQ1400_FREQUENCYCOUNTER_100:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->maxFrequency = 1000000;
		ch->maxFrequencyCutoff = 10;
		ch->minFrequencyCutoff = 0.01;
		ch->count = 0;
		ch->timeElapsed = 0;
		ch->frequency = 0;
		ch->filterType = FILTER_TYPE_LOGIC_LEVEL;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->frequencyCutoff = 1;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->inputMode = parentVINT->inputModeDevProp;
		break;
	case PHIDCHUID_DAQ1400_FREQUENCYCOUNTER_120:
		// Constants
		ch->minDataInterval = 20;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 50;
		ch->maxFrequency = 1000000;
		ch->maxFrequencyCutoff = 10;
		ch->minFrequencyCutoff = 0.01;
		ch->count = 0;
		ch->timeElapsed = 0;
		ch->frequency = 0;
		ch->filterType = FILTER_TYPE_LOGIC_LEVEL;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->frequencyCutoff = 1;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->inputMode = parentVINT->inputModeDevProp;
		break;
	case PHIDCHUID_DAQ1400_FREQUENCYCOUNTER_130:
		// Constants
		ch->minDataInterval = 10;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->maxFrequency = 1000000;
		ch->maxFrequencyCutoff = 10;
		ch->minFrequencyCutoff = 0.01;
		ch->count = 0;
		ch->timeElapsed = 0;
		ch->frequency = 0;
		ch->filterType = FILTER_TYPE_LOGIC_LEVEL;
		ch->enabled = 1;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->frequencyCutoff = 1;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->inputMode = parentVINT->inputModeDevProp;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	ch->totalTicksSinceLastCount = 0;
	ch->frequencyPrecision = 0;

	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetFrequencyCounterHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetFrequencyCounterHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1054_FREQUENCYCOUNTER_000:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->filterType = FILTER_TYPE_LOGIC_LEVEL;
		ch->enabled = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETFILTERTYPE, NULL, NULL, 1, "%d", ch->filterType);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETENABLED, NULL, NULL, 1, "%d", ch->enabled);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_FREQUENCYCOUNTER_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		// (Device Property - check if already set)
		if (ch->inputMode == PUNK_ENUM)
			ch->inputMode = INPUT_MODE_NPN;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETINPUTMODE, NULL, NULL, 1, "%d", ch->inputMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_FREQUENCYCOUNTER_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		// (Device Property - check if already set)
		if (ch->inputMode == PUNK_ENUM)
			ch->inputMode = INPUT_MODE_NPN;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETINPUTMODE, NULL, NULL, 1, "%d", ch->inputMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_FREQUENCYCOUNTER_130:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 10;
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		// (Device Property - check if already set)
		if (ch->inputMode == PUNK_ENUM)
			ch->inputMode = INPUT_MODE_NPN;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETINPUTMODE, NULL, NULL, 1, "%d", ch->inputMode);
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

	mos_free(*ch, sizeof (struct _PhidgetFrequencyCounter));
}

static PhidgetReturnCode CCONV
_create(PhidgetFrequencyCounterHandle *phidp) {

	CHANNELCREATE_BODY(FrequencyCounter, PHIDCHCLASS_FREQUENCYCOUNTER);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_delete(PhidgetFrequencyCounterHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetFrequencyCounter_getCount(PhidgetFrequencyCounterHandle ch, uint64_t *count) {

	TESTPTR_PR(ch);
	TESTPTR_PR(count);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*count = ch->count;
	if (ch->count == (uint64_t)PUNK_UINT64)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setDataInterval(PhidgetFrequencyCounterHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetFrequencyCounter_getDataInterval(PhidgetFrequencyCounterHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMinDataInterval(PhidgetFrequencyCounterHandle ch,
  uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMaxDataInterval(PhidgetFrequencyCounterHandle ch,
  uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setDataRate(PhidgetFrequencyCounterHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetFrequencyCounter_getDataRate(PhidgetFrequencyCounterHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMinDataRate(PhidgetFrequencyCounterHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMaxDataRate(PhidgetFrequencyCounterHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setEnabled(PhidgetFrequencyCounterHandle ch, int enabled) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETENABLED, NULL, NULL, 1, "%d", enabled));
}

API_PRETURN
PhidgetFrequencyCounter_getEnabled(PhidgetFrequencyCounterHandle ch, int *enabled) {

	TESTPTR_PR(ch);
	TESTPTR_PR(enabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*enabled = ch->enabled;
	if (ch->enabled == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setFilterType(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_FilterType filterType) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFILTERTYPE, NULL, NULL, 1, "%d",
	  filterType));
}

API_PRETURN
PhidgetFrequencyCounter_getFilterType(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_FilterType *filterType) {

	TESTPTR_PR(ch);
	TESTPTR_PR(filterType);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*filterType = ch->filterType;
	if (ch->filterType == (PhidgetFrequencyCounter_FilterType)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getFrequency(PhidgetFrequencyCounterHandle ch, double *frequency) {

	TESTPTR_PR(ch);
	TESTPTR_PR(frequency);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*frequency = ch->frequency;
	if (ch->frequency == (double)PUNK_DBL || isnan(ch->frequency))
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	if (ch->frequency > ch->maxFrequency)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVALHIGH));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMaxFrequency(PhidgetFrequencyCounterHandle ch, double *maxFrequency) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFrequency);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*maxFrequency = ch->maxFrequency;
	if (ch->maxFrequency == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getFrequencyCutoff(PhidgetFrequencyCounterHandle ch, double *frequencyCutoff) {

	TESTPTR_PR(ch);
	TESTPTR_PR(frequencyCutoff);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*frequencyCutoff = ch->frequencyCutoff;
	if (ch->frequencyCutoff == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMinFrequencyCutoff(PhidgetFrequencyCounterHandle ch,
  double *minFrequencyCutoff) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minFrequencyCutoff);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*minFrequencyCutoff = ch->minFrequencyCutoff;
	if (ch->minFrequencyCutoff == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_getMaxFrequencyCutoff(PhidgetFrequencyCounterHandle ch,
  double *maxFrequencyCutoff) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFrequencyCutoff);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*maxFrequencyCutoff = ch->maxFrequencyCutoff;
	if (ch->maxFrequencyCutoff == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setInputMode(PhidgetFrequencyCounterHandle ch, Phidget_InputMode inputMode) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETINPUTMODE, NULL, NULL, 1, "%d",
	  inputMode));
}

API_PRETURN
PhidgetFrequencyCounter_getInputMode(PhidgetFrequencyCounterHandle ch, Phidget_InputMode *inputMode) {

	TESTPTR_PR(ch);
	TESTPTR_PR(inputMode);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1054_FREQUENCYCOUNTER_000:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*inputMode = ch->inputMode;
	if (ch->inputMode == (Phidget_InputMode)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setPowerSupply(PhidgetFrequencyCounterHandle ch,
  Phidget_PowerSupply powerSupply) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d",
	  powerSupply));
}

API_PRETURN
PhidgetFrequencyCounter_getPowerSupply(PhidgetFrequencyCounterHandle ch,
  Phidget_PowerSupply *powerSupply) {

	TESTPTR_PR(ch);
	TESTPTR_PR(powerSupply);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1054_FREQUENCYCOUNTER_000:
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
PhidgetFrequencyCounter_getTimeElapsed(PhidgetFrequencyCounterHandle ch, double *timeElapsed) {

	TESTPTR_PR(ch);
	TESTPTR_PR(timeElapsed);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);
	TESTATTACHED_PR(ch);

	*timeElapsed = ch->timeElapsed;
	if (ch->timeElapsed == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setOnCountChangeHandler(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_OnCountChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->CountChange = NULL;
		MEMORY_BARRIER();
		ch->CountChangeCtx = NULL;
	} else {
		ch->CountChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->CountChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetFrequencyCounter_setOnFrequencyChangeHandler(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_OnFrequencyChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_FREQUENCYCOUNTER);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->FrequencyChange = NULL;
		MEMORY_BARRIER();
		ch->FrequencyChangeCtx = NULL;
	} else {
		ch->FrequencyChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->FrequencyChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
