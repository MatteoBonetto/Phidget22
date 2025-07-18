#ifndef _GPS_H_
#define _GPS_H_
typedef struct _PhidgetGPS *PhidgetGPSHandle;

/* Methods */
API_PRETURN_HDR PhidgetGPS_create(PhidgetGPSHandle *ch);
API_PRETURN_HDR PhidgetGPS_delete(PhidgetGPSHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetGPS_getAltitude(PhidgetGPSHandle ch, double *altitude);
API_PRETURN_HDR PhidgetGPS_getDate(PhidgetGPSHandle ch, PhidgetGPS_Date *date);
API_PRETURN_HDR PhidgetGPS_getHeading(PhidgetGPSHandle ch, double *heading);
API_PRETURN_HDR PhidgetGPS_getLatitude(PhidgetGPSHandle ch, double *latitude);
API_PRETURN_HDR PhidgetGPS_getLongitude(PhidgetGPSHandle ch, double *longitude);
API_PRETURN_HDR PhidgetGPS_getNMEAData(PhidgetGPSHandle ch, PhidgetGPS_NMEAData *NMEAData);
API_PRETURN_HDR PhidgetGPS_getPositionFixState(PhidgetGPSHandle ch, int *positionFixState);
API_PRETURN_HDR PhidgetGPS_getTime(PhidgetGPSHandle ch, PhidgetGPS_Time *time);
API_PRETURN_HDR PhidgetGPS_getVelocity(PhidgetGPSHandle ch, double *velocity);

/* Events */
typedef void (CCONV *PhidgetGPS_OnHeadingChangeCallback)(PhidgetGPSHandle ch, void *ctx, double heading,
  double velocity);

API_PRETURN_HDR PhidgetGPS_setOnHeadingChangeHandler(PhidgetGPSHandle ch,
  PhidgetGPS_OnHeadingChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetGPS_OnPositionChangeCallback)(PhidgetGPSHandle ch, void *ctx, double latitude,
  double longitude, double altitude);

API_PRETURN_HDR PhidgetGPS_setOnPositionChangeHandler(PhidgetGPSHandle ch,
  PhidgetGPS_OnPositionChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetGPS_OnPositionFixStateChangeCallback)(PhidgetGPSHandle ch, void *ctx,
  int positionFixState);

API_PRETURN_HDR PhidgetGPS_setOnPositionFixStateChangeHandler(PhidgetGPSHandle ch,
  PhidgetGPS_OnPositionFixStateChangeCallback fptr, void *ctx);

#endif /* _GPS_H_ */
