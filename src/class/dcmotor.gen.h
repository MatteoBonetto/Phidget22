#ifndef _DCMOTOR_H_
#define _DCMOTOR_H_
typedef struct _PhidgetDCMotor *PhidgetDCMotorHandle;

/* Methods */
API_PRETURN_HDR PhidgetDCMotor_create(PhidgetDCMotorHandle *ch);
API_PRETURN_HDR PhidgetDCMotor_delete(PhidgetDCMotorHandle *ch);
API_PRETURN_HDR PhidgetDCMotor_enableFailsafe(PhidgetDCMotorHandle ch, uint32_t failsafeTime);
API_PRETURN_HDR PhidgetDCMotor_resetFailsafe(PhidgetDCMotorHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetDCMotor_setAcceleration(PhidgetDCMotorHandle ch, double acceleration);
API_PRETURN_HDR PhidgetDCMotor_getAcceleration(PhidgetDCMotorHandle ch, double *acceleration);
API_PRETURN_HDR PhidgetDCMotor_getMinAcceleration(PhidgetDCMotorHandle ch, double *minAcceleration);
API_PRETURN_HDR PhidgetDCMotor_getMaxAcceleration(PhidgetDCMotorHandle ch, double *maxAcceleration);
API_PRETURN_HDR PhidgetDCMotor_getActiveCurrentLimit(PhidgetDCMotorHandle ch,
  double *activeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getBackEMF(PhidgetDCMotorHandle ch, double *backEMF);
API_PRETURN_HDR PhidgetDCMotor_setBackEMFSensingState(PhidgetDCMotorHandle ch, int backEMFSensingState);
API_PRETURN_HDR PhidgetDCMotor_getBackEMFSensingState(PhidgetDCMotorHandle ch,
  int *backEMFSensingState);
API_PRETURN_HDR PhidgetDCMotor_setBrakingEnabled(PhidgetDCMotorHandle ch, int brakingEnabled);
API_PRETURN_HDR PhidgetDCMotor_getBrakingEnabled(PhidgetDCMotorHandle ch, int *brakingEnabled);
API_PRETURN_HDR PhidgetDCMotor_getBrakingStrength(PhidgetDCMotorHandle ch, double *brakingStrength);
API_PRETURN_HDR PhidgetDCMotor_getMinBrakingStrength(PhidgetDCMotorHandle ch,
  double *minBrakingStrength);
API_PRETURN_HDR PhidgetDCMotor_getMaxBrakingStrength(PhidgetDCMotorHandle ch,
  double *maxBrakingStrength);
API_PRETURN_HDR PhidgetDCMotor_setCurrentLimit(PhidgetDCMotorHandle ch, double currentLimit);
API_PRETURN_HDR PhidgetDCMotor_getCurrentLimit(PhidgetDCMotorHandle ch, double *currentLimit);
API_PRETURN_HDR PhidgetDCMotor_getMinCurrentLimit(PhidgetDCMotorHandle ch, double *minCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getMaxCurrentLimit(PhidgetDCMotorHandle ch, double *maxCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_setCurrentRegulatorGain(PhidgetDCMotorHandle ch,
  double currentRegulatorGain);
API_PRETURN_HDR PhidgetDCMotor_getCurrentRegulatorGain(PhidgetDCMotorHandle ch,
  double *currentRegulatorGain);
API_PRETURN_HDR PhidgetDCMotor_getMinCurrentRegulatorGain(PhidgetDCMotorHandle ch,
  double *minCurrentRegulatorGain);
API_PRETURN_HDR PhidgetDCMotor_getMaxCurrentRegulatorGain(PhidgetDCMotorHandle ch,
  double *maxCurrentRegulatorGain);
API_PRETURN_HDR PhidgetDCMotor_setDataInterval(PhidgetDCMotorHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetDCMotor_getDataInterval(PhidgetDCMotorHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetDCMotor_getMinDataInterval(PhidgetDCMotorHandle ch, uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetDCMotor_getMaxDataInterval(PhidgetDCMotorHandle ch, uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetDCMotor_setDataRate(PhidgetDCMotorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetDCMotor_getDataRate(PhidgetDCMotorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetDCMotor_getMinDataRate(PhidgetDCMotorHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetDCMotor_getMaxDataRate(PhidgetDCMotorHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetDCMotor_setDriveMode(PhidgetDCMotorHandle ch, Phidget_DriveMode driveMode);
API_PRETURN_HDR PhidgetDCMotor_getDriveMode(PhidgetDCMotorHandle ch, Phidget_DriveMode *driveMode);
API_PRETURN_HDR PhidgetDCMotor_setFailsafeBrakingEnabled(PhidgetDCMotorHandle ch,
  int failsafeBrakingEnabled);
API_PRETURN_HDR PhidgetDCMotor_getFailsafeBrakingEnabled(PhidgetDCMotorHandle ch,
  int *failsafeBrakingEnabled);
API_PRETURN_HDR PhidgetDCMotor_setFailsafeCurrentLimit(PhidgetDCMotorHandle ch,
  double failsafeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getFailsafeCurrentLimit(PhidgetDCMotorHandle ch,
  double *failsafeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getMinFailsafeTime(PhidgetDCMotorHandle ch, uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetDCMotor_getMaxFailsafeTime(PhidgetDCMotorHandle ch, uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetDCMotor_setFanMode(PhidgetDCMotorHandle ch, Phidget_FanMode fanMode);
API_PRETURN_HDR PhidgetDCMotor_getFanMode(PhidgetDCMotorHandle ch, Phidget_FanMode *fanMode);
API_PRETURN_HDR PhidgetDCMotor_setInductance(PhidgetDCMotorHandle ch, double inductance);
API_PRETURN_HDR PhidgetDCMotor_getInductance(PhidgetDCMotorHandle ch, double *inductance);
API_PRETURN_HDR PhidgetDCMotor_getMinInductance(PhidgetDCMotorHandle ch, double *minInductance);
API_PRETURN_HDR PhidgetDCMotor_getMaxInductance(PhidgetDCMotorHandle ch, double *maxInductance);
API_PRETURN_HDR PhidgetDCMotor_setSurgeCurrentLimit(PhidgetDCMotorHandle ch, double surgeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getSurgeCurrentLimit(PhidgetDCMotorHandle ch, double *surgeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getMinSurgeCurrentLimit(PhidgetDCMotorHandle ch,
  double *minSurgeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_getMaxSurgeCurrentLimit(PhidgetDCMotorHandle ch,
  double *maxSurgeCurrentLimit);
API_PRETURN_HDR PhidgetDCMotor_setTargetBrakingStrength(PhidgetDCMotorHandle ch,
  double targetBrakingStrength);
API_PRETURN_HDR PhidgetDCMotor_getTargetBrakingStrength(PhidgetDCMotorHandle ch,
  double *targetBrakingStrength);
API_PRETURN_HDR PhidgetDCMotor_setTargetVelocity(PhidgetDCMotorHandle ch, double targetVelocity);
API_VRETURN_HDR PhidgetDCMotor_setTargetVelocity_async(PhidgetDCMotorHandle ch, double targetVelocity,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetDCMotor_getTargetVelocity(PhidgetDCMotorHandle ch, double *targetVelocity);
API_PRETURN_HDR PhidgetDCMotor_getVelocity(PhidgetDCMotorHandle ch, double *velocity);
API_PRETURN_HDR PhidgetDCMotor_getMinVelocity(PhidgetDCMotorHandle ch, double *minVelocity);
API_PRETURN_HDR PhidgetDCMotor_getMaxVelocity(PhidgetDCMotorHandle ch, double *maxVelocity);

/* Events */
typedef void (CCONV *PhidgetDCMotor_OnBackEMFChangeCallback)(PhidgetDCMotorHandle ch, void *ctx,
  double backEMF);

API_PRETURN_HDR PhidgetDCMotor_setOnBackEMFChangeHandler(PhidgetDCMotorHandle ch,
  PhidgetDCMotor_OnBackEMFChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetDCMotor_OnBrakingStrengthChangeCallback)(PhidgetDCMotorHandle ch, void *ctx,
  double brakingStrength);

API_PRETURN_HDR PhidgetDCMotor_setOnBrakingStrengthChangeHandler(PhidgetDCMotorHandle ch,
  PhidgetDCMotor_OnBrakingStrengthChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetDCMotor_OnVelocityUpdateCallback)(PhidgetDCMotorHandle ch, void *ctx,
  double velocity);

API_PRETURN_HDR PhidgetDCMotor_setOnVelocityUpdateHandler(PhidgetDCMotorHandle ch,
  PhidgetDCMotor_OnVelocityUpdateCallback fptr, void *ctx);

#endif /* _DCMOTOR_H_ */
