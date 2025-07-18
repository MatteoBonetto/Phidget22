#ifndef _GYROSCOPE_H_
#define _GYROSCOPE_H_
typedef struct _PhidgetGyroscope *PhidgetGyroscopeHandle;

/* Methods */
API_PRETURN_HDR PhidgetGyroscope_create(PhidgetGyroscopeHandle *ch);
API_PRETURN_HDR PhidgetGyroscope_delete(PhidgetGyroscopeHandle *ch);
API_PRETURN_HDR PhidgetGyroscope_zero(PhidgetGyroscopeHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetGyroscope_getAngularRate(PhidgetGyroscopeHandle ch, double (*angularRate)[3]);
API_PRETURN_HDR PhidgetGyroscope_getMinAngularRate(PhidgetGyroscopeHandle ch,
  double (*minAngularRate)[3]);
API_PRETURN_HDR PhidgetGyroscope_getMaxAngularRate(PhidgetGyroscopeHandle ch,
  double (*maxAngularRate)[3]);
API_PRETURN_HDR PhidgetGyroscope_getAxisCount(PhidgetGyroscopeHandle ch, int *axisCount);
API_PRETURN_HDR PhidgetGyroscope_setDataInterval(PhidgetGyroscopeHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetGyroscope_getDataInterval(PhidgetGyroscopeHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetGyroscope_getMinDataInterval(PhidgetGyroscopeHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetGyroscope_getMaxDataInterval(PhidgetGyroscopeHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetGyroscope_setDataRate(PhidgetGyroscopeHandle ch, double dataRate);
API_PRETURN_HDR PhidgetGyroscope_getDataRate(PhidgetGyroscopeHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetGyroscope_getMinDataRate(PhidgetGyroscopeHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetGyroscope_getMaxDataRate(PhidgetGyroscopeHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetGyroscope_setHeatingEnabled(PhidgetGyroscopeHandle ch, int heatingEnabled);
API_PRETURN_HDR PhidgetGyroscope_getHeatingEnabled(PhidgetGyroscopeHandle ch, int *heatingEnabled);
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetGyroscope_setPrecision(PhidgetGyroscopeHandle ch,
  Phidget_SpatialPrecision precision);
API_PRETURN_HDR PhidgetGyroscope_getPrecision(PhidgetGyroscopeHandle ch,
  Phidget_SpatialPrecision *precision);
#endif
API_PRETURN_HDR PhidgetGyroscope_getTimestamp(PhidgetGyroscopeHandle ch, double *timestamp);

/* Events */
typedef void (CCONV *PhidgetGyroscope_OnAngularRateUpdateCallback)(PhidgetGyroscopeHandle ch, void *ctx,
  const double angularRate[3], double timestamp);

API_PRETURN_HDR PhidgetGyroscope_setOnAngularRateUpdateHandler(PhidgetGyroscopeHandle ch,
  PhidgetGyroscope_OnAngularRateUpdateCallback fptr, void *ctx);

#endif /* _GYROSCOPE_H_ */
