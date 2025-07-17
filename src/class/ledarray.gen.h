#ifndef _LEDARRAY_H_
#define _LEDARRAY_H_
#ifdef INCLUDE_PRIVATE
typedef struct _PhidgetLEDArray *PhidgetLEDArrayHandle;

/* Methods */
API_PRETURN_HDR PhidgetLEDArray_create(PhidgetLEDArrayHandle *ch);
API_PRETURN_HDR PhidgetLEDArray_delete(PhidgetLEDArrayHandle *ch);
API_PRETURN_HDR PhidgetLEDArray_setAnimation(PhidgetLEDArrayHandle ch, int32_t animationID,
  const PhidgetLEDArray_Color *pattern, size_t patternLen, PhidgetLEDArray_Animation *animation);
API_PRETURN_HDR PhidgetLEDArray_clearLEDs(PhidgetLEDArrayHandle ch);
API_PRETURN_HDR PhidgetLEDArray_setLED(PhidgetLEDArrayHandle ch, uint32_t address,
  PhidgetLEDArray_Color *color, uint32_t fadeTime);
API_PRETURN_HDR PhidgetLEDArray_setLEDs(PhidgetLEDArrayHandle ch, uint32_t startAddress,
  uint32_t endAddress, const PhidgetLEDArray_Color *leds, size_t ledsLen, uint32_t fadeTime);
API_VRETURN_HDR PhidgetLEDArray_setLEDs_async(PhidgetLEDArrayHandle ch, uint32_t startAddress,
  uint32_t endAddress, const PhidgetLEDArray_Color *leds, size_t ledsLen, uint32_t fadeTime, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetLEDArray_stopAnimation(PhidgetLEDArrayHandle ch, int32_t animationID);
API_PRETURN_HDR PhidgetLEDArray_synchronizeAnimations(PhidgetLEDArrayHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetLEDArray_getMinAddress(PhidgetLEDArrayHandle ch, uint32_t *minAddress);
API_PRETURN_HDR PhidgetLEDArray_getMaxAddress(PhidgetLEDArrayHandle ch, uint32_t *maxAddress);
API_PRETURN_HDR PhidgetLEDArray_getMinAnimationID(PhidgetLEDArrayHandle ch, int32_t *minAnimationID);
API_PRETURN_HDR PhidgetLEDArray_getMaxAnimationID(PhidgetLEDArrayHandle ch, int32_t *maxAnimationID);
API_PRETURN_HDR PhidgetLEDArray_getMinAnimationPatternCount(PhidgetLEDArrayHandle ch,
  uint32_t *minAnimationPatternCount);
API_PRETURN_HDR PhidgetLEDArray_getMaxAnimationPatternCount(PhidgetLEDArrayHandle ch,
  uint32_t *maxAnimationPatternCount);
API_PRETURN_HDR PhidgetLEDArray_setBrightness(PhidgetLEDArrayHandle ch, double brightness);
API_PRETURN_HDR PhidgetLEDArray_getBrightness(PhidgetLEDArrayHandle ch, double *brightness);
API_PRETURN_HDR PhidgetLEDArray_getMinBrightness(PhidgetLEDArrayHandle ch, double *minBrightness);
API_PRETURN_HDR PhidgetLEDArray_getMaxBrightness(PhidgetLEDArrayHandle ch, double *maxBrightness);
API_PRETURN_HDR PhidgetLEDArray_setColorOrder(PhidgetLEDArrayHandle ch,
  PhidgetLEDArray_ColorOrder colorOrder);
API_PRETURN_HDR PhidgetLEDArray_getColorOrder(PhidgetLEDArrayHandle ch,
  PhidgetLEDArray_ColorOrder *colorOrder);
API_PRETURN_HDR PhidgetLEDArray_getMinFadeTime(PhidgetLEDArrayHandle ch, uint32_t *minFadeTime);
API_PRETURN_HDR PhidgetLEDArray_getMaxFadeTime(PhidgetLEDArrayHandle ch, uint32_t *maxFadeTime);
API_PRETURN_HDR PhidgetLEDArray_setGamma(PhidgetLEDArrayHandle ch, double gamma);
API_PRETURN_HDR PhidgetLEDArray_getGamma(PhidgetLEDArrayHandle ch, double *gamma);
API_PRETURN_HDR PhidgetLEDArray_getMinGamma(PhidgetLEDArrayHandle ch, uint32_t *minGamma);
API_PRETURN_HDR PhidgetLEDArray_getMaxGamma(PhidgetLEDArrayHandle ch, uint32_t *maxGamma);
API_PRETURN_HDR PhidgetLEDArray_getMinLEDCount(PhidgetLEDArrayHandle ch, uint32_t *minLEDCount);
API_PRETURN_HDR PhidgetLEDArray_getMaxLEDCount(PhidgetLEDArrayHandle ch, uint32_t *maxLEDCount);
API_PRETURN_HDR PhidgetLEDArray_setPowerEnabled(PhidgetLEDArrayHandle ch, int powerEnabled);
API_PRETURN_HDR PhidgetLEDArray_getPowerEnabled(PhidgetLEDArrayHandle ch, int *powerEnabled);

/* Events */

#endif /* INCLUDE_PRIVATE */
#endif /* _LEDARRAY_H_ */
