#ifndef _VOLTAGEINPUT_H_
#define _VOLTAGEINPUT_H_
typedef struct _PhidgetVoltageInput *PhidgetVoltageInputHandle;

/* Methods */
API_PRETURN_HDR PhidgetVoltageInput_create(PhidgetVoltageInputHandle *ch);
API_PRETURN_HDR PhidgetVoltageInput_delete(PhidgetVoltageInputHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetVoltageInput_setDataInterval(PhidgetVoltageInputHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetVoltageInput_getDataInterval(PhidgetVoltageInputHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetVoltageInput_getMinDataInterval(PhidgetVoltageInputHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetVoltageInput_getMaxDataInterval(PhidgetVoltageInputHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetVoltageInput_setDataRate(PhidgetVoltageInputHandle ch, double dataRate);
API_PRETURN_HDR PhidgetVoltageInput_getDataRate(PhidgetVoltageInputHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetVoltageInput_getMinDataRate(PhidgetVoltageInputHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetVoltageInput_getMaxDataRate(PhidgetVoltageInputHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetVoltageInput_setPowerSupply(PhidgetVoltageInputHandle ch,
  Phidget_PowerSupply powerSupply);
API_PRETURN_HDR PhidgetVoltageInput_getPowerSupply(PhidgetVoltageInputHandle ch,
  Phidget_PowerSupply *powerSupply);
API_PRETURN_HDR PhidgetVoltageInput_setSensorType(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_SensorType sensorType);
API_PRETURN_HDR PhidgetVoltageInput_getSensorType(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_SensorType *sensorType);
API_PRETURN_HDR PhidgetVoltageInput_getSensorUnit(PhidgetVoltageInputHandle ch,
  Phidget_UnitInfo *sensorUnit);
API_PRETURN_HDR PhidgetVoltageInput_getSensorValue(PhidgetVoltageInputHandle ch, double *sensorValue);
API_PRETURN_HDR PhidgetVoltageInput_setSensorValueChangeTrigger(PhidgetVoltageInputHandle ch,
  double sensorValueChangeTrigger);
API_PRETURN_HDR PhidgetVoltageInput_getSensorValueChangeTrigger(PhidgetVoltageInputHandle ch,
  double *sensorValueChangeTrigger);
API_PRETURN_HDR PhidgetVoltageInput_getVoltage(PhidgetVoltageInputHandle ch, double *voltage);
API_PRETURN_HDR PhidgetVoltageInput_getMinVoltage(PhidgetVoltageInputHandle ch, double *minVoltage);
API_PRETURN_HDR PhidgetVoltageInput_getMaxVoltage(PhidgetVoltageInputHandle ch, double *maxVoltage);
API_PRETURN_HDR PhidgetVoltageInput_setVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double voltageChangeTrigger);
API_PRETURN_HDR PhidgetVoltageInput_getVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double *voltageChangeTrigger);
API_PRETURN_HDR PhidgetVoltageInput_getMinVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double *minVoltageChangeTrigger);
API_PRETURN_HDR PhidgetVoltageInput_getMaxVoltageChangeTrigger(PhidgetVoltageInputHandle ch,
  double *maxVoltageChangeTrigger);
API_PRETURN_HDR PhidgetVoltageInput_setVoltageRange(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_VoltageRange voltageRange);
API_PRETURN_HDR PhidgetVoltageInput_getVoltageRange(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_VoltageRange *voltageRange);

/* Events */
typedef void (CCONV *PhidgetVoltageInput_OnSensorChangeCallback)(PhidgetVoltageInputHandle ch, void *ctx,
  double sensorValue, Phidget_UnitInfo *sensorUnit);

API_PRETURN_HDR PhidgetVoltageInput_setOnSensorChangeHandler(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_OnSensorChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetVoltageInput_OnVoltageChangeCallback)(PhidgetVoltageInputHandle ch, void *ctx,
  double voltage);

API_PRETURN_HDR PhidgetVoltageInput_setOnVoltageChangeHandler(PhidgetVoltageInputHandle ch,
  PhidgetVoltageInput_OnVoltageChangeCallback fptr, void *ctx);

#endif /* _VOLTAGEINPUT_H_ */
