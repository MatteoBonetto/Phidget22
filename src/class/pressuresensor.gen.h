#ifndef _PRESSURESENSOR_H_
#define _PRESSURESENSOR_H_
typedef struct _PhidgetPressureSensor *PhidgetPressureSensorHandle;

/* Methods */
API_PRETURN_HDR PhidgetPressureSensor_create(PhidgetPressureSensorHandle *ch);
API_PRETURN_HDR PhidgetPressureSensor_delete(PhidgetPressureSensorHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetPressureSensor_setDataInterval(PhidgetPressureSensorHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetPressureSensor_getDataInterval(PhidgetPressureSensorHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetPressureSensor_getMinDataInterval(PhidgetPressureSensorHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetPressureSensor_getMaxDataInterval(PhidgetPressureSensorHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetPressureSensor_setDataRate(PhidgetPressureSensorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetPressureSensor_getDataRate(PhidgetPressureSensorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetPressureSensor_getMinDataRate(PhidgetPressureSensorHandle ch,
  double *minDataRate);
API_PRETURN_HDR PhidgetPressureSensor_getMaxDataRate(PhidgetPressureSensorHandle ch,
  double *maxDataRate);
API_PRETURN_HDR PhidgetPressureSensor_getPressure(PhidgetPressureSensorHandle ch, double *pressure);
API_PRETURN_HDR PhidgetPressureSensor_getMinPressure(PhidgetPressureSensorHandle ch,
  double *minPressure);
API_PRETURN_HDR PhidgetPressureSensor_getMaxPressure(PhidgetPressureSensorHandle ch,
  double *maxPressure);
API_PRETURN_HDR PhidgetPressureSensor_setPressureChangeTrigger(PhidgetPressureSensorHandle ch,
  double pressureChangeTrigger);
API_PRETURN_HDR PhidgetPressureSensor_getPressureChangeTrigger(PhidgetPressureSensorHandle ch,
  double *pressureChangeTrigger);
API_PRETURN_HDR PhidgetPressureSensor_getMinPressureChangeTrigger(PhidgetPressureSensorHandle ch,
  double *minPressureChangeTrigger);
API_PRETURN_HDR PhidgetPressureSensor_getMaxPressureChangeTrigger(PhidgetPressureSensorHandle ch,
  double *maxPressureChangeTrigger);

/* Events */
typedef void (CCONV *PhidgetPressureSensor_OnPressureChangeCallback)(PhidgetPressureSensorHandle ch,
  void *ctx, double pressure);

API_PRETURN_HDR PhidgetPressureSensor_setOnPressureChangeHandler(PhidgetPressureSensorHandle ch,
  PhidgetPressureSensor_OnPressureChangeCallback fptr, void *ctx);

#endif /* _PRESSURESENSOR_H_ */
