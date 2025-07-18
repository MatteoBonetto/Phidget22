#ifndef _BLDCMOTOR_H_
#define _BLDCMOTOR_H_
typedef struct _PhidgetBLDCMotor *PhidgetBLDCMotorHandle;

/* Methods */
API_PRETURN_HDR PhidgetBLDCMotor_create(PhidgetBLDCMotorHandle *ch);
API_PRETURN_HDR PhidgetBLDCMotor_delete(PhidgetBLDCMotorHandle *ch);
API_PRETURN_HDR PhidgetBLDCMotor_enableFailsafe(PhidgetBLDCMotorHandle ch, uint32_t failsafeTime);
API_PRETURN_HDR PhidgetBLDCMotor_addPositionOffset(PhidgetBLDCMotorHandle ch, double positionOffset);
API_PRETURN_HDR PhidgetBLDCMotor_resetFailsafe(PhidgetBLDCMotorHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetBLDCMotor_setAcceleration(PhidgetBLDCMotorHandle ch, double acceleration);
API_PRETURN_HDR PhidgetBLDCMotor_getAcceleration(PhidgetBLDCMotorHandle ch, double *acceleration);
API_PRETURN_HDR PhidgetBLDCMotor_getMinAcceleration(PhidgetBLDCMotorHandle ch, double *minAcceleration);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxAcceleration(PhidgetBLDCMotorHandle ch, double *maxAcceleration);
API_PRETURN_HDR PhidgetBLDCMotor_getActiveCurrentLimit(PhidgetBLDCMotorHandle ch,
  double *activeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_setBrakingEnabled(PhidgetBLDCMotorHandle ch, int brakingEnabled);
API_PRETURN_HDR PhidgetBLDCMotor_getBrakingEnabled(PhidgetBLDCMotorHandle ch, int *brakingEnabled);
API_PRETURN_HDR PhidgetBLDCMotor_getBrakingStrength(PhidgetBLDCMotorHandle ch, double *brakingStrength);
API_PRETURN_HDR PhidgetBLDCMotor_getMinBrakingStrength(PhidgetBLDCMotorHandle ch,
  double *minBrakingStrength);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxBrakingStrength(PhidgetBLDCMotorHandle ch,
  double *maxBrakingStrength);
API_PRETURN_HDR PhidgetBLDCMotor_setCurrentLimit(PhidgetBLDCMotorHandle ch, double currentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getCurrentLimit(PhidgetBLDCMotorHandle ch, double *currentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getMinCurrentLimit(PhidgetBLDCMotorHandle ch, double *minCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxCurrentLimit(PhidgetBLDCMotorHandle ch, double *maxCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_setDataInterval(PhidgetBLDCMotorHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetBLDCMotor_getDataInterval(PhidgetBLDCMotorHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetBLDCMotor_getMinDataInterval(PhidgetBLDCMotorHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxDataInterval(PhidgetBLDCMotorHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetBLDCMotor_setDataRate(PhidgetBLDCMotorHandle ch, double dataRate);
API_PRETURN_HDR PhidgetBLDCMotor_getDataRate(PhidgetBLDCMotorHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetBLDCMotor_getMinDataRate(PhidgetBLDCMotorHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxDataRate(PhidgetBLDCMotorHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetBLDCMotor_setDriveMode(PhidgetBLDCMotorHandle ch, Phidget_DriveMode driveMode);
API_PRETURN_HDR PhidgetBLDCMotor_getDriveMode(PhidgetBLDCMotorHandle ch, Phidget_DriveMode *driveMode);
API_PRETURN_HDR PhidgetBLDCMotor_setFailsafeBrakingEnabled(PhidgetBLDCMotorHandle ch,
  int failsafeBrakingEnabled);
API_PRETURN_HDR PhidgetBLDCMotor_getFailsafeBrakingEnabled(PhidgetBLDCMotorHandle ch,
  int *failsafeBrakingEnabled);
API_PRETURN_HDR PhidgetBLDCMotor_setFailsafeCurrentLimit(PhidgetBLDCMotorHandle ch,
  double failsafeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getFailsafeCurrentLimit(PhidgetBLDCMotorHandle ch,
  double *failsafeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getMinFailsafeTime(PhidgetBLDCMotorHandle ch,
  uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxFailsafeTime(PhidgetBLDCMotorHandle ch,
  uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetBLDCMotor_setInductance(PhidgetBLDCMotorHandle ch, double inductance);
API_PRETURN_HDR PhidgetBLDCMotor_getInductance(PhidgetBLDCMotorHandle ch, double *inductance);
API_PRETURN_HDR PhidgetBLDCMotor_getMinInductance(PhidgetBLDCMotorHandle ch, double *minInductance);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxInductance(PhidgetBLDCMotorHandle ch, double *maxInductance);
API_PRETURN_HDR PhidgetBLDCMotor_getPosition(PhidgetBLDCMotorHandle ch, double *position);
API_PRETURN_HDR PhidgetBLDCMotor_getMinPosition(PhidgetBLDCMotorHandle ch, double *minPosition);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxPosition(PhidgetBLDCMotorHandle ch, double *maxPosition);
API_PRETURN_HDR PhidgetBLDCMotor_setRescaleFactor(PhidgetBLDCMotorHandle ch, double rescaleFactor);
API_PRETURN_HDR PhidgetBLDCMotor_getRescaleFactor(PhidgetBLDCMotorHandle ch, double *rescaleFactor);
API_PRETURN_HDR PhidgetBLDCMotor_setStallVelocity(PhidgetBLDCMotorHandle ch, double stallVelocity);
API_PRETURN_HDR PhidgetBLDCMotor_getStallVelocity(PhidgetBLDCMotorHandle ch, double *stallVelocity);
API_PRETURN_HDR PhidgetBLDCMotor_getMinStallVelocity(PhidgetBLDCMotorHandle ch,
  double *minStallVelocity);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxStallVelocity(PhidgetBLDCMotorHandle ch,
  double *maxStallVelocity);
API_PRETURN_HDR PhidgetBLDCMotor_setSurgeCurrentLimit(PhidgetBLDCMotorHandle ch,
  double surgeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getSurgeCurrentLimit(PhidgetBLDCMotorHandle ch,
  double *surgeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getMinSurgeCurrentLimit(PhidgetBLDCMotorHandle ch,
  double *minSurgeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxSurgeCurrentLimit(PhidgetBLDCMotorHandle ch,
  double *maxSurgeCurrentLimit);
API_PRETURN_HDR PhidgetBLDCMotor_setTargetBrakingStrength(PhidgetBLDCMotorHandle ch,
  double targetBrakingStrength);
API_PRETURN_HDR PhidgetBLDCMotor_getTargetBrakingStrength(PhidgetBLDCMotorHandle ch,
  double *targetBrakingStrength);
API_PRETURN_HDR PhidgetBLDCMotor_setTargetVelocity(PhidgetBLDCMotorHandle ch, double targetVelocity);
API_VRETURN_HDR PhidgetBLDCMotor_setTargetVelocity_async(PhidgetBLDCMotorHandle ch, double targetVelocity,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetBLDCMotor_getTargetVelocity(PhidgetBLDCMotorHandle ch, double *targetVelocity);
API_PRETURN_HDR PhidgetBLDCMotor_getVelocity(PhidgetBLDCMotorHandle ch, double *velocity);
API_PRETURN_HDR PhidgetBLDCMotor_getMinVelocity(PhidgetBLDCMotorHandle ch, double *minVelocity);
API_PRETURN_HDR PhidgetBLDCMotor_getMaxVelocity(PhidgetBLDCMotorHandle ch, double *maxVelocity);

/* Events */
typedef void (CCONV *PhidgetBLDCMotor_OnBrakingStrengthChangeCallback)(PhidgetBLDCMotorHandle ch,
  void *ctx, double brakingStrength);

API_PRETURN_HDR PhidgetBLDCMotor_setOnBrakingStrengthChangeHandler(PhidgetBLDCMotorHandle ch,
  PhidgetBLDCMotor_OnBrakingStrengthChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetBLDCMotor_OnPositionChangeCallback)(PhidgetBLDCMotorHandle ch, void *ctx,
  double position);

API_PRETURN_HDR PhidgetBLDCMotor_setOnPositionChangeHandler(PhidgetBLDCMotorHandle ch,
  PhidgetBLDCMotor_OnPositionChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetBLDCMotor_OnVelocityUpdateCallback)(PhidgetBLDCMotorHandle ch, void *ctx,
  double velocity);

API_PRETURN_HDR PhidgetBLDCMotor_setOnVelocityUpdateHandler(PhidgetBLDCMotorHandle ch,
  PhidgetBLDCMotor_OnVelocityUpdateCallback fptr, void *ctx);

#endif /* _BLDCMOTOR_H_ */
