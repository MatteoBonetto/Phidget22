#ifndef _HUMIDITYSENSOR_H_
#define _HUMIDITYSENSOR_H_
typedef struct _PhidgetHumiditySensor *PhidgetHumiditySensorHandle;

/* Methods */
API_PRETURN_HDR PhidgetHumiditySensor_create(PhidgetHumiditySensorHandle *ch);
API_PRETURN_HDR PhidgetHumiditySensor_delete(PhidgetHumiditySensorHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetHumiditySensor_setDataInterval(PhidgetHumiditySensorHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetHumiditySensor_getDataInterval(PhidgetHumiditySensorHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetHumiditySensor_getMinDataInterval(PhidgetHumiditySensorHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetHumiditySensor_getMaxDataInterval(PhidgetHumiditySensorHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetHumiditySensor_setDataRate(PhidgetHumiditySensorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetHumiditySensor_getDataRate(PhidgetHumiditySensorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetHumiditySensor_getMinDataRate(PhidgetHumiditySensorHandle ch,
  double *minDataRate);
API_PRETURN_HDR PhidgetHumiditySensor_getMaxDataRate(PhidgetHumiditySensorHandle ch,
  double *maxDataRate);
API_PRETURN_HDR PhidgetHumiditySensor_getHumidity(PhidgetHumiditySensorHandle ch, double *humidity);
API_PRETURN_HDR PhidgetHumiditySensor_getMinHumidity(PhidgetHumiditySensorHandle ch,
  double *minHumidity);
API_PRETURN_HDR PhidgetHumiditySensor_getMaxHumidity(PhidgetHumiditySensorHandle ch,
  double *maxHumidity);
API_PRETURN_HDR PhidgetHumiditySensor_setHumidityChangeTrigger(PhidgetHumiditySensorHandle ch,
  double humidityChangeTrigger);
API_PRETURN_HDR PhidgetHumiditySensor_getHumidityChangeTrigger(PhidgetHumiditySensorHandle ch,
  double *humidityChangeTrigger);
API_PRETURN_HDR PhidgetHumiditySensor_getMinHumidityChangeTrigger(PhidgetHumiditySensorHandle ch,
  double *minHumidityChangeTrigger);
API_PRETURN_HDR PhidgetHumiditySensor_getMaxHumidityChangeTrigger(PhidgetHumiditySensorHandle ch,
  double *maxHumidityChangeTrigger);

/* Events */
typedef void (CCONV *PhidgetHumiditySensor_OnHumidityChangeCallback)(PhidgetHumiditySensorHandle ch,
  void *ctx, double humidity);

API_PRETURN_HDR PhidgetHumiditySensor_setOnHumidityChangeHandler(PhidgetHumiditySensorHandle ch,
  PhidgetHumiditySensor_OnHumidityChangeCallback fptr, void *ctx);

#endif /* _HUMIDITYSENSOR_H_ */
