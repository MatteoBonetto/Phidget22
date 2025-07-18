#ifndef _LIGHTSENSOR_H_
#define _LIGHTSENSOR_H_
typedef struct _PhidgetLightSensor *PhidgetLightSensorHandle;

/* Methods */
API_PRETURN_HDR PhidgetLightSensor_create(PhidgetLightSensorHandle *ch);
API_PRETURN_HDR PhidgetLightSensor_delete(PhidgetLightSensorHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetLightSensor_setDataInterval(PhidgetLightSensorHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetLightSensor_getDataInterval(PhidgetLightSensorHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetLightSensor_getMinDataInterval(PhidgetLightSensorHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetLightSensor_getMaxDataInterval(PhidgetLightSensorHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetLightSensor_setDataRate(PhidgetLightSensorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetLightSensor_getDataRate(PhidgetLightSensorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetLightSensor_getMinDataRate(PhidgetLightSensorHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetLightSensor_getMaxDataRate(PhidgetLightSensorHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetLightSensor_getIlluminance(PhidgetLightSensorHandle ch, double *illuminance);
API_PRETURN_HDR PhidgetLightSensor_getMinIlluminance(PhidgetLightSensorHandle ch,
  double *minIlluminance);
API_PRETURN_HDR PhidgetLightSensor_getMaxIlluminance(PhidgetLightSensorHandle ch,
  double *maxIlluminance);
API_PRETURN_HDR PhidgetLightSensor_setIlluminanceChangeTrigger(PhidgetLightSensorHandle ch,
  double illuminanceChangeTrigger);
API_PRETURN_HDR PhidgetLightSensor_getIlluminanceChangeTrigger(PhidgetLightSensorHandle ch,
  double *illuminanceChangeTrigger);
API_PRETURN_HDR PhidgetLightSensor_getMinIlluminanceChangeTrigger(PhidgetLightSensorHandle ch,
  double *minIlluminanceChangeTrigger);
API_PRETURN_HDR PhidgetLightSensor_getMaxIlluminanceChangeTrigger(PhidgetLightSensorHandle ch,
  double *maxIlluminanceChangeTrigger);

/* Events */
typedef void (CCONV *PhidgetLightSensor_OnIlluminanceChangeCallback)(PhidgetLightSensorHandle ch,
  void *ctx, double illuminance);

API_PRETURN_HDR PhidgetLightSensor_setOnIlluminanceChangeHandler(PhidgetLightSensorHandle ch,
  PhidgetLightSensor_OnIlluminanceChangeCallback fptr, void *ctx);

#endif /* _LIGHTSENSOR_H_ */
