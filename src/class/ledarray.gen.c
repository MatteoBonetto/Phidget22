/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

static void CCONV PhidgetLEDArray_errorHandler(PhidgetChannelHandle ch, Phidget_ErrorEventCode code);
static void CCONV PhidgetLEDArray_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetLEDArray_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetLEDArray_setStatus(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetLEDArray_getStatus(PhidgetChannelHandle phid, BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetLEDArray_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetLEDArray_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetLEDArray_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetLEDArray_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetLEDArray {
	struct _PhidgetChannel phid;
	uint32_t minAddress;
	uint32_t maxAddress;
	int32_t minAnimationID;
	int32_t maxAnimationID;
	uint32_t minAnimationPatternCount;
	uint32_t maxAnimationPatternCount;
	double brightness;
	double minBrightness;
	double maxBrightness;
	PhidgetLEDArray_ColorOrder colorOrder;
	uint32_t minFadeTime;
	uint32_t maxFadeTime;
	double gamma;
	uint32_t minGamma;
	uint32_t maxGamma;
	uint32_t minLEDCount;
	uint32_t maxLEDCount;
	int powerEnabled;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetLEDArrayHandle ch;
	int nsversion;

	ch = (PhidgetLEDArrayHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 3) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 3 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "minAddress"))
		ch->minAddress = getBridgePacketUInt32ByName(bp, "minAddress");
	if (hasBridgePacketByName(bp, "maxAddress"))
		ch->maxAddress = getBridgePacketUInt32ByName(bp, "maxAddress");
	if (hasBridgePacketByName(bp, "minAnimationID"))
		ch->minAnimationID = getBridgePacketInt32ByName(bp, "minAnimationID");
	if (hasBridgePacketByName(bp, "maxAnimationID"))
		ch->maxAnimationID = getBridgePacketInt32ByName(bp, "maxAnimationID");
	if (hasBridgePacketByName(bp, "minAnimationPatternCount"))
		ch->minAnimationPatternCount = getBridgePacketUInt32ByName(bp, "minAnimationPatternCount");
	if (hasBridgePacketByName(bp, "maxAnimationPatternCount"))
		ch->maxAnimationPatternCount = getBridgePacketUInt32ByName(bp, "maxAnimationPatternCount");
	if (hasBridgePacketByName(bp, "brightness"))
		ch->brightness = getBridgePacketDoubleByName(bp, "brightness");
	if (hasBridgePacketByName(bp, "minBrightness"))
		ch->minBrightness = getBridgePacketDoubleByName(bp, "minBrightness");
	if (hasBridgePacketByName(bp, "maxBrightness"))
		ch->maxBrightness = getBridgePacketDoubleByName(bp, "maxBrightness");
	if (hasBridgePacketByName(bp, "colorOrder"))
		ch->colorOrder = getBridgePacketInt32ByName(bp, "colorOrder");
	if (hasBridgePacketByName(bp, "minFadeTime"))
		ch->minFadeTime = getBridgePacketUInt32ByName(bp, "minFadeTime");
	if (hasBridgePacketByName(bp, "maxFadeTime"))
		ch->maxFadeTime = getBridgePacketUInt32ByName(bp, "maxFadeTime");
	if (hasBridgePacketByName(bp, "gamma"))
		ch->gamma = getBridgePacketDoubleByName(bp, "gamma");
	if (hasBridgePacketByName(bp, "minGamma"))
		ch->minGamma = getBridgePacketUInt32ByName(bp, "minGamma");
	if (hasBridgePacketByName(bp, "maxGamma"))
		ch->maxGamma = getBridgePacketUInt32ByName(bp, "maxGamma");
	if (hasBridgePacketByName(bp, "minLEDCount"))
		ch->minLEDCount = getBridgePacketUInt32ByName(bp, "minLEDCount");
	if (hasBridgePacketByName(bp, "maxLEDCount"))
		ch->maxLEDCount = getBridgePacketUInt32ByName(bp, "maxLEDCount");
	if (hasBridgePacketByName(bp, "powerEnabled"))
		ch->powerEnabled = getBridgePacketInt32ByName(bp, "powerEnabled");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetLEDArrayHandle ch;

	ch = (PhidgetLEDArrayHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 19, "_class_version_=%u"
	  ",minAddress=%u"
	  ",maxAddress=%u"
	  ",minAnimationID=%d"
	  ",maxAnimationID=%d"
	  ",minAnimationPatternCount=%u"
	  ",maxAnimationPatternCount=%u"
	  ",brightness=%g"
	  ",minBrightness=%g"
	  ",maxBrightness=%g"
	  ",colorOrder=%d"
	  ",minFadeTime=%u"
	  ",maxFadeTime=%u"
	  ",gamma=%g"
	  ",minGamma=%u"
	  ",maxGamma=%u"
	  ",minLEDCount=%u"
	  ",maxLEDCount=%u"
	  ",powerEnabled=%d"
	  ,3 /* class version */
	  ,ch->minAddress
	  ,ch->maxAddress
	  ,ch->minAnimationID
	  ,ch->maxAnimationID
	  ,ch->minAnimationPatternCount
	  ,ch->maxAnimationPatternCount
	  ,ch->brightness
	  ,ch->minBrightness
	  ,ch->maxBrightness
	  ,ch->colorOrder
	  ,ch->minFadeTime
	  ,ch->maxFadeTime
	  ,ch->gamma
	  ,ch->minGamma
	  ,ch->maxGamma
	  ,ch->minLEDCount
	  ,ch->maxLEDCount
	  ,ch->powerEnabled
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetLEDArrayHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetLEDArrayHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SETANIMATION:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_CLEAR:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_DATAOUT:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_STOPANIMATION:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_SYNCHRONIZE:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_SETBRIGHTNESS:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minBrightness,
		  ch->maxBrightness);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->brightness = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Brightness");
		}
		break;
	case BP_SETPROTOCOL:
		if (!supportedLEDArrayColorOrder(phid, (PhidgetLEDArray_ColorOrder)getBridgePacketInt32(bp,
		  0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified LEDArrayColorOrder is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->colorOrder = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "ColorOrder");
		}
		break;
	case BP_SETGAMMA:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minGamma, ch->maxGamma);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->gamma = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Gamma");
		}
		break;
	case BP_SETENABLED:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->powerEnabled = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "PowerEnabled");
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
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ret = EPHIDGET_OK;


	switch (phid->UCD->uid) {
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

	mos_free(*ch, sizeof (struct _PhidgetLEDArray));
}

static PhidgetReturnCode CCONV
_create(PhidgetLEDArrayHandle *phidp) {

	CHANNELCREATE_BODY(LEDArray, PHIDCHCLASS_LEDARRAY);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_delete(PhidgetLEDArrayHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetLEDArray_clearLEDs(PhidgetLEDArrayHandle ch) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_CLEAR, NULL, NULL, 0, NULL); 
}

API_PRETURN
PhidgetLEDArray_stopAnimation(PhidgetLEDArrayHandle ch, int32_t animationID) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_STOPANIMATION, NULL, NULL, 1, "%d",
	  animationID); 
}

API_PRETURN
PhidgetLEDArray_synchronizeAnimations(PhidgetLEDArrayHandle ch) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SYNCHRONIZE, NULL, NULL, 0, NULL); 
}

API_PRETURN
PhidgetLEDArray_getMinAddress(PhidgetLEDArrayHandle ch, uint32_t *minAddress) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minAddress);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minAddress = ch->minAddress;
	if (ch->minAddress == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxAddress(PhidgetLEDArrayHandle ch, uint32_t *maxAddress) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxAddress);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxAddress = ch->maxAddress;
	if (ch->maxAddress == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMinAnimationID(PhidgetLEDArrayHandle ch, int32_t *minAnimationID) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minAnimationID);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minAnimationID = ch->minAnimationID;
	if (ch->minAnimationID == (int32_t)PUNK_INT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxAnimationID(PhidgetLEDArrayHandle ch, int32_t *maxAnimationID) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxAnimationID);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxAnimationID = ch->maxAnimationID;
	if (ch->maxAnimationID == (int32_t)PUNK_INT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMinAnimationPatternCount(PhidgetLEDArrayHandle ch,
  uint32_t *minAnimationPatternCount) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minAnimationPatternCount);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minAnimationPatternCount = ch->minAnimationPatternCount;
	if (ch->minAnimationPatternCount == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxAnimationPatternCount(PhidgetLEDArrayHandle ch,
  uint32_t *maxAnimationPatternCount) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxAnimationPatternCount);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxAnimationPatternCount = ch->maxAnimationPatternCount;
	if (ch->maxAnimationPatternCount == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_setBrightness(PhidgetLEDArrayHandle ch, double brightness) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETBRIGHTNESS, NULL, NULL, 1, "%g",
	  brightness));
}

API_PRETURN
PhidgetLEDArray_getBrightness(PhidgetLEDArrayHandle ch, double *brightness) {

	TESTPTR_PR(ch);
	TESTPTR_PR(brightness);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*brightness = ch->brightness;
	if (ch->brightness == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMinBrightness(PhidgetLEDArrayHandle ch, double *minBrightness) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minBrightness);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minBrightness = ch->minBrightness;
	if (ch->minBrightness == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxBrightness(PhidgetLEDArrayHandle ch, double *maxBrightness) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxBrightness);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxBrightness = ch->maxBrightness;
	if (ch->maxBrightness == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_setColorOrder(PhidgetLEDArrayHandle ch, PhidgetLEDArray_ColorOrder colorOrder) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETPROTOCOL, NULL, NULL, 1, "%d",
	  colorOrder));
}

API_PRETURN
PhidgetLEDArray_getColorOrder(PhidgetLEDArrayHandle ch, PhidgetLEDArray_ColorOrder *colorOrder) {

	TESTPTR_PR(ch);
	TESTPTR_PR(colorOrder);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*colorOrder = ch->colorOrder;
	if (ch->colorOrder == (PhidgetLEDArray_ColorOrder)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMinFadeTime(PhidgetLEDArrayHandle ch, uint32_t *minFadeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minFadeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minFadeTime = ch->minFadeTime;
	if (ch->minFadeTime == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxFadeTime(PhidgetLEDArrayHandle ch, uint32_t *maxFadeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFadeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxFadeTime = ch->maxFadeTime;
	if (ch->maxFadeTime == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_setGamma(PhidgetLEDArrayHandle ch, double gamma) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETGAMMA, NULL, NULL, 1, "%g", gamma));
}

API_PRETURN
PhidgetLEDArray_getGamma(PhidgetLEDArrayHandle ch, double *gamma) {

	TESTPTR_PR(ch);
	TESTPTR_PR(gamma);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*gamma = ch->gamma;
	if (ch->gamma == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMinGamma(PhidgetLEDArrayHandle ch, uint32_t *minGamma) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minGamma);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minGamma = ch->minGamma;
	if (ch->minGamma == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxGamma(PhidgetLEDArrayHandle ch, uint32_t *maxGamma) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxGamma);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxGamma = ch->maxGamma;
	if (ch->maxGamma == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMinLEDCount(PhidgetLEDArrayHandle ch, uint32_t *minLEDCount) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minLEDCount);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*minLEDCount = ch->minLEDCount;
	if (ch->minLEDCount == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_getMaxLEDCount(PhidgetLEDArrayHandle ch, uint32_t *maxLEDCount) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxLEDCount);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*maxLEDCount = ch->maxLEDCount;
	if (ch->maxLEDCount == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetLEDArray_setPowerEnabled(PhidgetLEDArrayHandle ch, int powerEnabled) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETENABLED, NULL, NULL, 1, "%d",
	  powerEnabled));
}

API_PRETURN
PhidgetLEDArray_getPowerEnabled(PhidgetLEDArrayHandle ch, int *powerEnabled) {

	TESTPTR_PR(ch);
	TESTPTR_PR(powerEnabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	*powerEnabled = ch->powerEnabled;
	if (ch->powerEnabled == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}
