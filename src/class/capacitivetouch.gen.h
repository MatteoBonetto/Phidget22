#ifndef _CAPACITIVETOUCH_H_
#define _CAPACITIVETOUCH_H_
typedef struct _PhidgetCapacitiveTouch *PhidgetCapacitiveTouchHandle;

/* Methods */
API_PRETURN_HDR PhidgetCapacitiveTouch_create(PhidgetCapacitiveTouchHandle *ch);
API_PRETURN_HDR PhidgetCapacitiveTouch_delete(PhidgetCapacitiveTouchHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetCapacitiveTouch_setDataInterval(PhidgetCapacitiveTouchHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetCapacitiveTouch_getDataInterval(PhidgetCapacitiveTouchHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMinDataInterval(PhidgetCapacitiveTouchHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMaxDataInterval(PhidgetCapacitiveTouchHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetCapacitiveTouch_setDataRate(PhidgetCapacitiveTouchHandle ch, double dataRate);
API_PRETURN_HDR PhidgetCapacitiveTouch_getDataRate(PhidgetCapacitiveTouchHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMinDataRate(PhidgetCapacitiveTouchHandle ch,
  double *minDataRate);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMaxDataRate(PhidgetCapacitiveTouchHandle ch,
  double *maxDataRate);
API_PRETURN_HDR PhidgetCapacitiveTouch_setSensitivity(PhidgetCapacitiveTouchHandle ch,
  double sensitivity);
API_PRETURN_HDR PhidgetCapacitiveTouch_getSensitivity(PhidgetCapacitiveTouchHandle ch,
  double *sensitivity);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMinSensitivity(PhidgetCapacitiveTouchHandle ch,
  double *minSensitivity);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMaxSensitivity(PhidgetCapacitiveTouchHandle ch,
  double *maxSensitivity);
API_PRETURN_HDR PhidgetCapacitiveTouch_getIsTouched(PhidgetCapacitiveTouchHandle ch, int *isTouched);
API_PRETURN_HDR PhidgetCapacitiveTouch_getTouchValue(PhidgetCapacitiveTouchHandle ch,
  double *touchValue);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMinTouchValue(PhidgetCapacitiveTouchHandle ch,
  double *minTouchValue);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMaxTouchValue(PhidgetCapacitiveTouchHandle ch,
  double *maxTouchValue);
API_PRETURN_HDR PhidgetCapacitiveTouch_setTouchValueChangeTrigger(PhidgetCapacitiveTouchHandle ch,
  double touchValueChangeTrigger);
API_PRETURN_HDR PhidgetCapacitiveTouch_getTouchValueChangeTrigger(PhidgetCapacitiveTouchHandle ch,
  double *touchValueChangeTrigger);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMinTouchValueChangeTrigger(PhidgetCapacitiveTouchHandle ch,
  double *minTouchValueChangeTrigger);
API_PRETURN_HDR PhidgetCapacitiveTouch_getMaxTouchValueChangeTrigger(PhidgetCapacitiveTouchHandle ch,
  double *maxTouchValueChangeTrigger);

/* Events */
typedef void (CCONV *PhidgetCapacitiveTouch_OnTouchCallback)(PhidgetCapacitiveTouchHandle ch, void *ctx,
  double touchValue);

API_PRETURN_HDR PhidgetCapacitiveTouch_setOnTouchHandler(PhidgetCapacitiveTouchHandle ch,
  PhidgetCapacitiveTouch_OnTouchCallback fptr, void *ctx);
typedef void (CCONV *PhidgetCapacitiveTouch_OnTouchEndCallback)(PhidgetCapacitiveTouchHandle ch,
  void *ctx);

API_PRETURN_HDR PhidgetCapacitiveTouch_setOnTouchEndHandler(PhidgetCapacitiveTouchHandle ch,
  PhidgetCapacitiveTouch_OnTouchEndCallback fptr, void *ctx);

#endif /* _CAPACITIVETOUCH_H_ */
