#ifndef _DISTANCESENSOR_H_
#define _DISTANCESENSOR_H_
typedef struct _PhidgetDistanceSensor *PhidgetDistanceSensorHandle;

/* Methods */
API_PRETURN_HDR PhidgetDistanceSensor_create(PhidgetDistanceSensorHandle *ch);
API_PRETURN_HDR PhidgetDistanceSensor_delete(PhidgetDistanceSensorHandle *ch);
API_PRETURN_HDR PhidgetDistanceSensor_getSonarReflections(PhidgetDistanceSensorHandle ch,
  uint32_t (*distances)[8], uint32_t (*amplitudes)[8], uint32_t *count);

/* Properties */
API_PRETURN_HDR PhidgetDistanceSensor_setDataInterval(PhidgetDistanceSensorHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetDistanceSensor_getDataInterval(PhidgetDistanceSensorHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetDistanceSensor_getMinDataInterval(PhidgetDistanceSensorHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetDistanceSensor_getMaxDataInterval(PhidgetDistanceSensorHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetDistanceSensor_setDataRate(PhidgetDistanceSensorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetDistanceSensor_getDataRate(PhidgetDistanceSensorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetDistanceSensor_getMinDataRate(PhidgetDistanceSensorHandle ch,
  double *minDataRate);
API_PRETURN_HDR PhidgetDistanceSensor_getMaxDataRate(PhidgetDistanceSensorHandle ch,
  double *maxDataRate);
API_PRETURN_HDR PhidgetDistanceSensor_getDistance(PhidgetDistanceSensorHandle ch, uint32_t *distance);
API_PRETURN_HDR PhidgetDistanceSensor_getMinDistance(PhidgetDistanceSensorHandle ch,
  uint32_t *minDistance);
API_PRETURN_HDR PhidgetDistanceSensor_getMaxDistance(PhidgetDistanceSensorHandle ch,
  uint32_t *maxDistance);
API_PRETURN_HDR PhidgetDistanceSensor_setDistanceChangeTrigger(PhidgetDistanceSensorHandle ch,
  uint32_t distanceChangeTrigger);
API_PRETURN_HDR PhidgetDistanceSensor_getDistanceChangeTrigger(PhidgetDistanceSensorHandle ch,
  uint32_t *distanceChangeTrigger);
API_PRETURN_HDR PhidgetDistanceSensor_getMinDistanceChangeTrigger(PhidgetDistanceSensorHandle ch,
  uint32_t *minDistanceChangeTrigger);
API_PRETURN_HDR PhidgetDistanceSensor_getMaxDistanceChangeTrigger(PhidgetDistanceSensorHandle ch,
  uint32_t *maxDistanceChangeTrigger);
API_PRETURN_HDR PhidgetDistanceSensor_setSonarQuietMode(PhidgetDistanceSensorHandle ch,
  int sonarQuietMode);
API_PRETURN_HDR PhidgetDistanceSensor_getSonarQuietMode(PhidgetDistanceSensorHandle ch,
  int *sonarQuietMode);

/* Events */
typedef void (CCONV *PhidgetDistanceSensor_OnDistanceChangeCallback)(PhidgetDistanceSensorHandle ch,
  void *ctx, uint32_t distance);

API_PRETURN_HDR PhidgetDistanceSensor_setOnDistanceChangeHandler(PhidgetDistanceSensorHandle ch,
  PhidgetDistanceSensor_OnDistanceChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetDistanceSensor_OnSonarReflectionsUpdateCallback)(PhidgetDistanceSensorHandle ch, void *ctx, const uint32_t distances[8], const uint32_t amplitudes[8], uint32_t count);

API_PRETURN_HDR PhidgetDistanceSensor_setOnSonarReflectionsUpdateHandler(PhidgetDistanceSensorHandle ch,
  PhidgetDistanceSensor_OnSonarReflectionsUpdateCallback fptr, void *ctx);

#endif /* _DISTANCESENSOR_H_ */
