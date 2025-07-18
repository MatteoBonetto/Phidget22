#ifndef _CURRENTINPUT_H_
#define _CURRENTINPUT_H_
typedef struct _PhidgetCurrentInput *PhidgetCurrentInputHandle;

/* Methods */
API_PRETURN_HDR PhidgetCurrentInput_create(PhidgetCurrentInputHandle *ch);
API_PRETURN_HDR PhidgetCurrentInput_delete(PhidgetCurrentInputHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetCurrentInput_getCurrent(PhidgetCurrentInputHandle ch, double *current);
API_PRETURN_HDR PhidgetCurrentInput_getMinCurrent(PhidgetCurrentInputHandle ch, double *minCurrent);
API_PRETURN_HDR PhidgetCurrentInput_getMaxCurrent(PhidgetCurrentInputHandle ch, double *maxCurrent);
API_PRETURN_HDR PhidgetCurrentInput_setCurrentChangeTrigger(PhidgetCurrentInputHandle ch,
  double currentChangeTrigger);
API_PRETURN_HDR PhidgetCurrentInput_getCurrentChangeTrigger(PhidgetCurrentInputHandle ch,
  double *currentChangeTrigger);
API_PRETURN_HDR PhidgetCurrentInput_getMinCurrentChangeTrigger(PhidgetCurrentInputHandle ch,
  double *minCurrentChangeTrigger);
API_PRETURN_HDR PhidgetCurrentInput_getMaxCurrentChangeTrigger(PhidgetCurrentInputHandle ch,
  double *maxCurrentChangeTrigger);
API_PRETURN_HDR PhidgetCurrentInput_setDataInterval(PhidgetCurrentInputHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetCurrentInput_getDataInterval(PhidgetCurrentInputHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetCurrentInput_getMinDataInterval(PhidgetCurrentInputHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetCurrentInput_getMaxDataInterval(PhidgetCurrentInputHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetCurrentInput_setDataRate(PhidgetCurrentInputHandle ch, double dataRate);
API_PRETURN_HDR PhidgetCurrentInput_getDataRate(PhidgetCurrentInputHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetCurrentInput_getMinDataRate(PhidgetCurrentInputHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetCurrentInput_getMaxDataRate(PhidgetCurrentInputHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetCurrentInput_setPowerSupply(PhidgetCurrentInputHandle ch,
  Phidget_PowerSupply powerSupply);
API_PRETURN_HDR PhidgetCurrentInput_getPowerSupply(PhidgetCurrentInputHandle ch,
  Phidget_PowerSupply *powerSupply);

/* Events */
typedef void (CCONV *PhidgetCurrentInput_OnCurrentChangeCallback)(PhidgetCurrentInputHandle ch, void *ctx,
  double current);

API_PRETURN_HDR PhidgetCurrentInput_setOnCurrentChangeHandler(PhidgetCurrentInputHandle ch,
  PhidgetCurrentInput_OnCurrentChangeCallback fptr, void *ctx);

#endif /* _CURRENTINPUT_H_ */
