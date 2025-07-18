#ifndef _MAGNETOMETER_H_
#define _MAGNETOMETER_H_
typedef struct _PhidgetMagnetometer *PhidgetMagnetometerHandle;

/* Methods */
API_PRETURN_HDR PhidgetMagnetometer_create(PhidgetMagnetometerHandle *ch);
API_PRETURN_HDR PhidgetMagnetometer_delete(PhidgetMagnetometerHandle *ch);
API_PRETURN_HDR PhidgetMagnetometer_setCorrectionParameters(PhidgetMagnetometerHandle ch,
  double magneticField, double offset0, double offset1, double offset2, double gain0, double gain1, double gain2, double T0, double T1, double T2, double T3, double T4, double T5);
API_PRETURN_HDR PhidgetMagnetometer_resetCorrectionParameters(PhidgetMagnetometerHandle ch);
API_PRETURN_HDR PhidgetMagnetometer_saveCorrectionParameters(PhidgetMagnetometerHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetMagnetometer_getAxisCount(PhidgetMagnetometerHandle ch, int *axisCount);
API_PRETURN_HDR PhidgetMagnetometer_setDataInterval(PhidgetMagnetometerHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetMagnetometer_getDataInterval(PhidgetMagnetometerHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetMagnetometer_getMinDataInterval(PhidgetMagnetometerHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetMagnetometer_getMaxDataInterval(PhidgetMagnetometerHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetMagnetometer_setDataRate(PhidgetMagnetometerHandle ch, double dataRate);
API_PRETURN_HDR PhidgetMagnetometer_getDataRate(PhidgetMagnetometerHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetMagnetometer_getMinDataRate(PhidgetMagnetometerHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetMagnetometer_getMaxDataRate(PhidgetMagnetometerHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetMagnetometer_setHeatingEnabled(PhidgetMagnetometerHandle ch, int heatingEnabled);
API_PRETURN_HDR PhidgetMagnetometer_getHeatingEnabled(PhidgetMagnetometerHandle ch,
  int *heatingEnabled);
API_PRETURN_HDR PhidgetMagnetometer_getMagneticField(PhidgetMagnetometerHandle ch,
  double (*magneticField)[3]);
API_PRETURN_HDR PhidgetMagnetometer_getMinMagneticField(PhidgetMagnetometerHandle ch,
  double (*minMagneticField)[3]);
API_PRETURN_HDR PhidgetMagnetometer_getMaxMagneticField(PhidgetMagnetometerHandle ch,
  double (*maxMagneticField)[3]);
API_PRETURN_HDR PhidgetMagnetometer_setMagneticFieldChangeTrigger(PhidgetMagnetometerHandle ch,
  double magneticFieldChangeTrigger);
API_PRETURN_HDR PhidgetMagnetometer_getMagneticFieldChangeTrigger(PhidgetMagnetometerHandle ch,
  double *magneticFieldChangeTrigger);
API_PRETURN_HDR PhidgetMagnetometer_getMinMagneticFieldChangeTrigger(PhidgetMagnetometerHandle ch,
  double *minMagneticFieldChangeTrigger);
API_PRETURN_HDR PhidgetMagnetometer_getMaxMagneticFieldChangeTrigger(PhidgetMagnetometerHandle ch,
  double *maxMagneticFieldChangeTrigger);
API_PRETURN_HDR PhidgetMagnetometer_getTimestamp(PhidgetMagnetometerHandle ch, double *timestamp);

/* Events */
typedef void (CCONV *PhidgetMagnetometer_OnMagneticFieldChangeCallback)(PhidgetMagnetometerHandle ch,
  void *ctx, const double magneticField[3], double timestamp);

API_PRETURN_HDR PhidgetMagnetometer_setOnMagneticFieldChangeHandler(PhidgetMagnetometerHandle ch,
  PhidgetMagnetometer_OnMagneticFieldChangeCallback fptr, void *ctx);

#endif /* _MAGNETOMETER_H_ */
