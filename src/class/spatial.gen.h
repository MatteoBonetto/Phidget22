#ifndef _SPATIAL_H_
#define _SPATIAL_H_
typedef struct _PhidgetSpatial *PhidgetSpatialHandle;

/* Methods */
API_PRETURN_HDR PhidgetSpatial_create(PhidgetSpatialHandle *ch);
API_PRETURN_HDR PhidgetSpatial_delete(PhidgetSpatialHandle *ch);
API_PRETURN_HDR PhidgetSpatial_setAHRSParameters(PhidgetSpatialHandle ch, double angularVelocityThreshold,
  double angularVelocityDeltaThreshold, double accelerationThreshold, double magTime, double accelTime, double biasTime);
API_PRETURN_HDR PhidgetSpatial_setMagnetometerCorrectionParameters(PhidgetSpatialHandle ch,
  double magneticField, double offset0, double offset1, double offset2, double gain0, double gain1, double gain2, double T0, double T1, double T2, double T3, double T4, double T5);
API_PRETURN_HDR PhidgetSpatial_resetMagnetometerCorrectionParameters(PhidgetSpatialHandle ch);
API_PRETURN_HDR PhidgetSpatial_saveMagnetometerCorrectionParameters(PhidgetSpatialHandle ch);
API_PRETURN_HDR PhidgetSpatial_zeroAlgorithm(PhidgetSpatialHandle ch);
API_PRETURN_HDR PhidgetSpatial_zeroGyro(PhidgetSpatialHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetSpatial_getMinAcceleration(PhidgetSpatialHandle ch,
  double (*minAcceleration)[3]);
API_PRETURN_HDR PhidgetSpatial_getMaxAcceleration(PhidgetSpatialHandle ch,
  double (*maxAcceleration)[3]);
API_PRETURN_HDR PhidgetSpatial_setAlgorithm(PhidgetSpatialHandle ch,
  Phidget_SpatialAlgorithm algorithm);
API_PRETURN_HDR PhidgetSpatial_getAlgorithm(PhidgetSpatialHandle ch,
  Phidget_SpatialAlgorithm *algorithm);
API_PRETURN_HDR PhidgetSpatial_setAlgorithmMagnetometerGain(PhidgetSpatialHandle ch,
  double algorithmMagnetometerGain);
API_PRETURN_HDR PhidgetSpatial_getAlgorithmMagnetometerGain(PhidgetSpatialHandle ch,
  double *algorithmMagnetometerGain);
API_PRETURN_HDR PhidgetSpatial_getMinAngularRate(PhidgetSpatialHandle ch, double (*minAngularRate)[3]);
API_PRETURN_HDR PhidgetSpatial_getMaxAngularRate(PhidgetSpatialHandle ch, double (*maxAngularRate)[3]);
API_PRETURN_HDR PhidgetSpatial_setDataInterval(PhidgetSpatialHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetSpatial_getDataInterval(PhidgetSpatialHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetSpatial_getMinDataInterval(PhidgetSpatialHandle ch, uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetSpatial_getMaxDataInterval(PhidgetSpatialHandle ch, uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetSpatial_setDataRate(PhidgetSpatialHandle ch, double dataRate);
API_PRETURN_HDR PhidgetSpatial_getDataRate(PhidgetSpatialHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetSpatial_getMinDataRate(PhidgetSpatialHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetSpatial_getMaxDataRate(PhidgetSpatialHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetSpatial_getEulerAngles(PhidgetSpatialHandle ch,
  PhidgetSpatial_SpatialEulerAngles *eulerAngles);
API_PRETURN_HDR PhidgetSpatial_setHeatingEnabled(PhidgetSpatialHandle ch, int heatingEnabled);
API_PRETURN_HDR PhidgetSpatial_getHeatingEnabled(PhidgetSpatialHandle ch, int *heatingEnabled);
API_PRETURN_HDR PhidgetSpatial_getMinMagneticField(PhidgetSpatialHandle ch,
  double (*minMagneticField)[3]);
API_PRETURN_HDR PhidgetSpatial_getMaxMagneticField(PhidgetSpatialHandle ch,
  double (*maxMagneticField)[3]);
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetSpatial_setPrecision(PhidgetSpatialHandle ch,
  Phidget_SpatialPrecision precision);
API_PRETURN_HDR PhidgetSpatial_getPrecision(PhidgetSpatialHandle ch,
  Phidget_SpatialPrecision *precision);
#endif
API_PRETURN_HDR PhidgetSpatial_getQuaternion(PhidgetSpatialHandle ch,
  PhidgetSpatial_SpatialQuaternion *quaternion);

/* Events */
typedef void (CCONV *PhidgetSpatial_OnAlgorithmDataCallback)(PhidgetSpatialHandle ch, void *ctx,
  const double quaternion[4], double timestamp);

API_PRETURN_HDR PhidgetSpatial_setOnAlgorithmDataHandler(PhidgetSpatialHandle ch,
  PhidgetSpatial_OnAlgorithmDataCallback fptr, void *ctx);
typedef void (CCONV *PhidgetSpatial_OnSpatialDataCallback)(PhidgetSpatialHandle ch, void *ctx,
  const double acceleration[3], const double angularRate[3], const double magneticField[3], double timestamp);

API_PRETURN_HDR PhidgetSpatial_setOnSpatialDataHandler(PhidgetSpatialHandle ch,
  PhidgetSpatial_OnSpatialDataCallback fptr, void *ctx);

#endif /* _SPATIAL_H_ */
