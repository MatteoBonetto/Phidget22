#ifndef _PHSENSOR_H_
#define _PHSENSOR_H_
typedef struct _PhidgetPHSensor *PhidgetPHSensorHandle;

/* Methods */
API_PRETURN_HDR PhidgetPHSensor_create(PhidgetPHSensorHandle *ch);
API_PRETURN_HDR PhidgetPHSensor_delete(PhidgetPHSensorHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetPHSensor_setCorrectionTemperature(PhidgetPHSensorHandle ch,
  double correctionTemperature);
API_PRETURN_HDR PhidgetPHSensor_getCorrectionTemperature(PhidgetPHSensorHandle ch,
  double *correctionTemperature);
API_PRETURN_HDR PhidgetPHSensor_getMinCorrectionTemperature(PhidgetPHSensorHandle ch,
  double *minCorrectionTemperature);
API_PRETURN_HDR PhidgetPHSensor_getMaxCorrectionTemperature(PhidgetPHSensorHandle ch,
  double *maxCorrectionTemperature);
API_PRETURN_HDR PhidgetPHSensor_setDataInterval(PhidgetPHSensorHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetPHSensor_getDataInterval(PhidgetPHSensorHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetPHSensor_getMinDataInterval(PhidgetPHSensorHandle ch, uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetPHSensor_getMaxDataInterval(PhidgetPHSensorHandle ch, uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetPHSensor_setDataRate(PhidgetPHSensorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetPHSensor_getDataRate(PhidgetPHSensorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetPHSensor_getMinDataRate(PhidgetPHSensorHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetPHSensor_getMaxDataRate(PhidgetPHSensorHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetPHSensor_getPH(PhidgetPHSensorHandle ch, double *PH);
API_PRETURN_HDR PhidgetPHSensor_getMinPH(PhidgetPHSensorHandle ch, double *minPH);
API_PRETURN_HDR PhidgetPHSensor_getMaxPH(PhidgetPHSensorHandle ch, double *maxPH);
API_PRETURN_HDR PhidgetPHSensor_setPHChangeTrigger(PhidgetPHSensorHandle ch, double PHChangeTrigger);
API_PRETURN_HDR PhidgetPHSensor_getPHChangeTrigger(PhidgetPHSensorHandle ch, double *PHChangeTrigger);
API_PRETURN_HDR PhidgetPHSensor_getMinPHChangeTrigger(PhidgetPHSensorHandle ch,
  double *minPHChangeTrigger);
API_PRETURN_HDR PhidgetPHSensor_getMaxPHChangeTrigger(PhidgetPHSensorHandle ch,
  double *maxPHChangeTrigger);

/* Events */
typedef void (CCONV *PhidgetPHSensor_OnPHChangeCallback)(PhidgetPHSensorHandle ch, void *ctx,
  double PH);

API_PRETURN_HDR PhidgetPHSensor_setOnPHChangeHandler(PhidgetPHSensorHandle ch,
  PhidgetPHSensor_OnPHChangeCallback fptr, void *ctx);

#endif /* _PHSENSOR_H_ */
