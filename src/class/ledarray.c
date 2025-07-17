/* Generated: Mon Dec 09 2024 15:18:07 GMT-0700 (Mountain Standard Time) */
/* Will not be regenerated. */

#include "phidgetbase.h"
#include "util/ledarraysupport.h"
#include "class/ledarray.gen.h"
#include "class/ledarray.gen.c"

static void CCONV
PhidgetLEDArray_errorHandler(PhidgetChannelHandle phid, Phidget_ErrorEventCode code) {
	PhidgetLEDArrayHandle ch = ((PhidgetLEDArrayHandle)phid);
	switch (code) {
	case EEPHIDGET_OVERCURRENT:
		ch->powerEnabled = 0;
		FIRE_PROPERTYCHANGE(ch, "PowerEnabled");
		break;
	}
}

static void CCONV
PhidgetLEDArray_free(PhidgetChannelHandle *ch) {

	if (ch && *ch)
		PhidgetLEDArraySupport_free((PhidgetLEDArraySupportHandle *)&(*ch)->private);
	_free(ch);
}

API_PRETURN
PhidgetLEDArray_create(PhidgetLEDArrayHandle *phidp) {
	PhidgetReturnCode res;

	res = _create(phidp);
	if (res == EPHIDGET_OK)
		res = PhidgetLEDArraySupport_create((PhidgetLEDArraySupportHandle *)&(*phidp)->phid.private);

	return (res);
}

static PhidgetReturnCode CCONV
PhidgetLEDArray_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	return (_setStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetLEDArray_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	return (_getStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetLEDArray_initAfterOpen(PhidgetChannelHandle phid) {
	if (phid)
		PhidgetLEDArraySupport_init((PhidgetLEDArraySupportHandle)phid->private);
	return (_initAfterOpen(phid));
}

static PhidgetReturnCode CCONV
PhidgetLEDArray_setDefaults(PhidgetChannelHandle phid) {
	return (_setDefaults(phid));
}

static PhidgetReturnCode
PhidgetLEDArray_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetReturnCode res;
	PhidgetLEDArrayHandle ch = ((PhidgetLEDArrayHandle)phid);
	uint32_t prevMaxLEDCount;

	switch (bp->vpkt) {
	case BP_SETPROTOCOL:
		res = _bridgeInput(phid, bp);
		if (res != EPHIDGET_OK)
			return res;
		prevMaxLEDCount = ch->maxLEDCount;
		switch (getBridgePacketInt32(bp, 0)) {
		case LED_COLOR_ORDER_RGB:
		case LED_COLOR_ORDER_GRB:
			ch->maxLEDCount = 2048;
			ch->maxAddress = 2047;
			ch->maxAnimationPatternCount = 128;
			if (ch->maxLEDCount == prevMaxLEDCount)
				break;
			if (bridgePacketIsFromNet(bp)) {
				FIRE_PROPERTYCHANGE(ch, "MaxLEDCount");
				FIRE_PROPERTYCHANGE(ch, "MaxAnimationPatternCount");
				FIRE_PROPERTYCHANGE(ch, "MaxAddress");
			} else {
				DISPATCH_PROPERTYCHANGE(ch, "MaxLEDCount");
				DISPATCH_PROPERTYCHANGE(ch, "MaxAnimationPatternCount");
				DISPATCH_PROPERTYCHANGE(ch, "MaxAddress");
			}
			break;
		case LED_COLOR_ORDER_RGBW:
		case LED_COLOR_ORDER_GRBW:
			ch->maxLEDCount = 1536;
			ch->maxAddress = 1535;
			ch->maxAnimationPatternCount = 96;
			if (ch->maxLEDCount == prevMaxLEDCount)
				break;
			if (bridgePacketIsFromNet(bp)) {
				FIRE_PROPERTYCHANGE(ch, "MaxLEDCount");
				FIRE_PROPERTYCHANGE(ch, "MaxAnimationPatternCount");
				FIRE_PROPERTYCHANGE(ch, "MaxAddress");
			} else {
				DISPATCH_PROPERTYCHANGE(ch, "MaxLEDCount");
				DISPATCH_PROPERTYCHANGE(ch, "MaxAnimationPatternCount");
				DISPATCH_PROPERTYCHANGE(ch, "MaxAddress");
			}
			break;
		}
		break;
	default:
		res = _bridgeInput(phid, bp);
		break;
	}

	return (res);
}

static void CCONV
PhidgetLEDArray_fireInitialEvents(PhidgetChannelHandle phid) {
	_fireInitialEvents(phid);
}

static int CCONV
PhidgetLEDArray_hasInitialState(PhidgetChannelHandle phid) {
	return (_hasInitialState(phid));
}

API_PRETURN
PhidgetLEDArray_setLED(PhidgetLEDArrayHandle ch, uint32_t index, PhidgetLEDArray_Color *color, uint32_t fadeTime) {

	return PhidgetLEDArray_setLEDs(ch, index, index, color, 1, fadeTime);
}

API_PRETURN
PhidgetLEDArray_setLEDs(PhidgetLEDArrayHandle ch, uint32_t startAddress, uint32_t endAddress, const PhidgetLEDArray_Color *leds, size_t ledsLen, uint32_t fadeTime) {
	uint32_t segmentLength;

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	TESTRANGE_PR(fadeTime, "%u", ch->minFadeTime, ch->maxFadeTime);

	if (ledsLen == 0)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "LED array cannot be empty"));

	if (startAddress > ch->maxAddress)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Start Adddress must be less than or equal to %u", ch->maxAddress));

	if (endAddress > ch->maxAddress)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "End Adddress must be less than or euqal to %u", ch->maxAddress));

	if (endAddress < startAddress)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "End Address must be larger than Start Address"));

	segmentLength = (endAddress - startAddress) + 1;
	if ((size_t)segmentLength > ledsLen)
		segmentLength = (uint32_t)ledsLen;

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_DATAOUT, NULL, NULL, 3, "%u%u%u%*R", startAddress, endAddress, fadeTime, (segmentLength * 4), leds);
}

API_VRETURN_HDR
PhidgetLEDArray_setLEDs_async(PhidgetLEDArrayHandle ch, uint32_t startAddress, uint32_t endAddress, const PhidgetLEDArray_Color *leds, size_t ledsLen, uint32_t fadeTime,
							  Phidget_AsyncCallback fptr, void *ctx) {
	uint32_t segmentLength;
	PhidgetReturnCode res;

	if (ch == NULL) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}
	if (ch->phid.class != PHIDCHCLASS_LEDARRAY) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_WRONGDEVICE);
		return;
	}
	if (!ISATTACHED(ch)) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_NOTATTACHED);
		return;
	}

	if ((fadeTime < ch->minFadeTime) || (fadeTime > ch->maxFadeTime)) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}

	if (ledsLen == 0) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}

	if (startAddress > ch->maxAddress) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}

	if (endAddress > ch->maxAddress) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}

	if (endAddress < startAddress) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}

	segmentLength = (endAddress - startAddress) + 1;
	if ((size_t)segmentLength > ledsLen)
		segmentLength = (uint32_t)ledsLen;

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_DATAOUT, fptr, ctx, 3, "%u%u%u%*R", startAddress, endAddress, fadeTime, (segmentLength * 4), leds);
	if (res != EPHIDGET_OK && fptr != NULL)
		fptr((PhidgetHandle)ch, ctx, res);
}

API_PRETURN
PhidgetLEDArray_setAnimation(PhidgetLEDArrayHandle ch, int32_t animationID, const PhidgetLEDArray_Color *pattern, size_t patternLen, PhidgetLEDArray_Animation *animation) {
	uint32_t segmentLength;

	TESTPTR_PR(ch);
	TESTPTR_PR(animation);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_LEDARRAY);
	TESTATTACHED_PR(ch);

	if (patternLen == 0)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Pattern array cannot be empty"));

	if (patternLen > ch->maxAnimationPatternCount)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Pattern must contain %d or fewer elements", ch->maxAnimationPatternCount));

	if (patternLen > BPE_MAXARRAY_LEN / 4)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Too many RGBW values specified"));

	if (animation->startAddress > ch->maxAddress)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Start Adddress must be less than or equal to %u", ch->maxAddress));
	if ((uint32_t)(animation->endAddress) > ch->maxAddress)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "End Adddress must be less than or equal to %u", ch->maxAddress));

	if (animation->endAddress < animation->startAddress)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "End Address must be larger than Start Address"));

	if (!supportedLEDArrayAnimationType((PhidgetChannelHandle)ch, (PhidgetLEDArray_AnimationType)animation->animationType))
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Specified AnimationType is unsupported by this device."));

	TESTRANGE_PR(animationID, "%d", ch->minAnimationID, ch->maxAnimationID);
	TESTRANGE_PR(animation->time, "%d", ch->minFadeTime, ch->maxFadeTime);

	segmentLength = (animation->endAddress - animation->startAddress) + 1;

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETANIMATION, NULL, NULL, 6, "%d%d%d%d%d%*R", animationID, animation->startAddress,
							  segmentLength, animation->time, animation->animationType, patternLen * sizeof(PhidgetLEDArray_Color), (const uint8_t *)pattern);
}
