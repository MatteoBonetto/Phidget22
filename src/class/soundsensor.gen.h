#ifndef _SOUNDSENSOR_H_
#define _SOUNDSENSOR_H_
typedef struct _PhidgetSoundSensor *PhidgetSoundSensorHandle;

/* Methods */
API_PRETURN_HDR PhidgetSoundSensor_create(PhidgetSoundSensorHandle *ch);
API_PRETURN_HDR PhidgetSoundSensor_delete(PhidgetSoundSensorHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetSoundSensor_setDataInterval(PhidgetSoundSensorHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetSoundSensor_getDataInterval(PhidgetSoundSensorHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetSoundSensor_getMinDataInterval(PhidgetSoundSensorHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetSoundSensor_getMaxDataInterval(PhidgetSoundSensorHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetSoundSensor_setDataRate(PhidgetSoundSensorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetSoundSensor_getDataRate(PhidgetSoundSensorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetSoundSensor_getMinDataRate(PhidgetSoundSensorHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetSoundSensor_getMaxDataRate(PhidgetSoundSensorHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetSoundSensor_getdB(PhidgetSoundSensorHandle ch, double *dB);
API_PRETURN_HDR PhidgetSoundSensor_getdBA(PhidgetSoundSensorHandle ch, double *dBA);
API_PRETURN_HDR PhidgetSoundSensor_getdBC(PhidgetSoundSensorHandle ch, double *dBC);
API_PRETURN_HDR PhidgetSoundSensor_getMaxdB(PhidgetSoundSensorHandle ch, double *maxdB);
API_PRETURN_HDR PhidgetSoundSensor_getNoiseFloor(PhidgetSoundSensorHandle ch, double *noiseFloor);
API_PRETURN_HDR PhidgetSoundSensor_getOctaves(PhidgetSoundSensorHandle ch, double (*octaves)[10]);
API_PRETURN_HDR PhidgetSoundSensor_setSPLChangeTrigger(PhidgetSoundSensorHandle ch,
  double SPLChangeTrigger);
API_PRETURN_HDR PhidgetSoundSensor_getSPLChangeTrigger(PhidgetSoundSensorHandle ch,
  double *SPLChangeTrigger);
API_PRETURN_HDR PhidgetSoundSensor_getMinSPLChangeTrigger(PhidgetSoundSensorHandle ch,
  double *minSPLChangeTrigger);
API_PRETURN_HDR PhidgetSoundSensor_getMaxSPLChangeTrigger(PhidgetSoundSensorHandle ch,
  double *maxSPLChangeTrigger);
API_PRETURN_HDR PhidgetSoundSensor_setSPLRange(PhidgetSoundSensorHandle ch,
  PhidgetSoundSensor_SPLRange SPLRange);
API_PRETURN_HDR PhidgetSoundSensor_getSPLRange(PhidgetSoundSensorHandle ch,
  PhidgetSoundSensor_SPLRange *SPLRange);

/* Events */
typedef void (CCONV *PhidgetSoundSensor_OnSPLChangeCallback)(PhidgetSoundSensorHandle ch, void *ctx,
  double dB, double dBA, double dBC, const double octaves[10]);

API_PRETURN_HDR PhidgetSoundSensor_setOnSPLChangeHandler(PhidgetSoundSensorHandle ch,
  PhidgetSoundSensor_OnSPLChangeCallback fptr, void *ctx);

#endif /* _SOUNDSENSOR_H_ */
