#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_
typedef struct _PhidgetAccelerometer *PhidgetAccelerometerHandle;

/* Methods */
API_PRETURN_HDR PhidgetAccelerometer_create(PhidgetAccelerometerHandle *ch);
API_PRETURN_HDR PhidgetAccelerometer_delete(PhidgetAccelerometerHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetAccelerometer_getAcceleration(PhidgetAccelerometerHandle ch,
  double (*acceleration)[3]);
API_PRETURN_HDR PhidgetAccelerometer_getMinAcceleration(PhidgetAccelerometerHandle ch,
  double (*minAcceleration)[3]);
API_PRETURN_HDR PhidgetAccelerometer_getMaxAcceleration(PhidgetAccelerometerHandle ch,
  double (*maxAcceleration)[3]);
API_PRETURN_HDR PhidgetAccelerometer_setAccelerationChangeTrigger(PhidgetAccelerometerHandle ch,
  double accelerationChangeTrigger);
API_PRETURN_HDR PhidgetAccelerometer_getAccelerationChangeTrigger(PhidgetAccelerometerHandle ch,
  double *accelerationChangeTrigger);
API_PRETURN_HDR PhidgetAccelerometer_getMinAccelerationChangeTrigger(PhidgetAccelerometerHandle ch,
  double *minAccelerationChangeTrigger);
API_PRETURN_HDR PhidgetAccelerometer_getMaxAccelerationChangeTrigger(PhidgetAccelerometerHandle ch,
  double *maxAccelerationChangeTrigger);
API_PRETURN_HDR PhidgetAccelerometer_getAxisCount(PhidgetAccelerometerHandle ch, int *axisCount);
API_PRETURN_HDR PhidgetAccelerometer_setDataInterval(PhidgetAccelerometerHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetAccelerometer_getDataInterval(PhidgetAccelerometerHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetAccelerometer_getMinDataInterval(PhidgetAccelerometerHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetAccelerometer_getMaxDataInterval(PhidgetAccelerometerHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetAccelerometer_setDataRate(PhidgetAccelerometerHandle ch, double dataRate);
API_PRETURN_HDR PhidgetAccelerometer_getDataRate(PhidgetAccelerometerHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetAccelerometer_getMinDataRate(PhidgetAccelerometerHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetAccelerometer_getMaxDataRate(PhidgetAccelerometerHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetAccelerometer_setHeatingEnabled(PhidgetAccelerometerHandle ch,
  int heatingEnabled);
API_PRETURN_HDR PhidgetAccelerometer_getHeatingEnabled(PhidgetAccelerometerHandle ch,
  int *heatingEnabled);
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetAccelerometer_setPrecision(PhidgetAccelerometerHandle ch,
  Phidget_SpatialPrecision precision);
API_PRETURN_HDR PhidgetAccelerometer_getPrecision(PhidgetAccelerometerHandle ch,
  Phidget_SpatialPrecision *precision);
#endif
API_PRETURN_HDR PhidgetAccelerometer_getTimestamp(PhidgetAccelerometerHandle ch, double *timestamp);

/* Events */
typedef void (CCONV *PhidgetAccelerometer_OnAccelerationChangeCallback)(PhidgetAccelerometerHandle ch,
  void *ctx, const double acceleration[3], double timestamp);

API_PRETURN_HDR PhidgetAccelerometer_setOnAccelerationChangeHandler(PhidgetAccelerometerHandle ch,
  PhidgetAccelerometer_OnAccelerationChangeCallback fptr, void *ctx);

#endif /* _ACCELEROMETER_H_ */
