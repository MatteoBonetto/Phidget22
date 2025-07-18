#ifndef _RCSERVO_H_
#define _RCSERVO_H_
typedef struct _PhidgetRCServo *PhidgetRCServoHandle;

/* Methods */
API_PRETURN_HDR PhidgetRCServo_create(PhidgetRCServoHandle *ch);
API_PRETURN_HDR PhidgetRCServo_delete(PhidgetRCServoHandle *ch);
API_PRETURN_HDR PhidgetRCServo_enableFailsafe(PhidgetRCServoHandle ch, uint32_t failsafeTime);
API_PRETURN_HDR PhidgetRCServo_resetFailsafe(PhidgetRCServoHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetRCServo_setAcceleration(PhidgetRCServoHandle ch, double acceleration);
API_PRETURN_HDR PhidgetRCServo_getAcceleration(PhidgetRCServoHandle ch, double *acceleration);
API_PRETURN_HDR PhidgetRCServo_getMinAcceleration(PhidgetRCServoHandle ch, double *minAcceleration);
API_PRETURN_HDR PhidgetRCServo_getMaxAcceleration(PhidgetRCServoHandle ch, double *maxAcceleration);
API_PRETURN_HDR PhidgetRCServo_setDataInterval(PhidgetRCServoHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetRCServo_getDataInterval(PhidgetRCServoHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetRCServo_getMinDataInterval(PhidgetRCServoHandle ch, uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetRCServo_getMaxDataInterval(PhidgetRCServoHandle ch, uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetRCServo_setDataRate(PhidgetRCServoHandle ch, double dataRate);
API_PRETURN_HDR PhidgetRCServo_getDataRate(PhidgetRCServoHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetRCServo_getMinDataRate(PhidgetRCServoHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetRCServo_getMaxDataRate(PhidgetRCServoHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetRCServo_setEngaged(PhidgetRCServoHandle ch, int engaged);
API_PRETURN_HDR PhidgetRCServo_getEngaged(PhidgetRCServoHandle ch, int *engaged);
API_PRETURN_HDR PhidgetRCServo_getMinFailsafeTime(PhidgetRCServoHandle ch, uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetRCServo_getMaxFailsafeTime(PhidgetRCServoHandle ch, uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetRCServo_getIsMoving(PhidgetRCServoHandle ch, int *isMoving);
API_PRETURN_HDR PhidgetRCServo_getPosition(PhidgetRCServoHandle ch, double *position);
API_PRETURN_HDR PhidgetRCServo_setMinPosition(PhidgetRCServoHandle ch, double minPosition);
API_PRETURN_HDR PhidgetRCServo_getMinPosition(PhidgetRCServoHandle ch, double *minPosition);
API_PRETURN_HDR PhidgetRCServo_setMaxPosition(PhidgetRCServoHandle ch, double maxPosition);
API_PRETURN_HDR PhidgetRCServo_getMaxPosition(PhidgetRCServoHandle ch, double *maxPosition);
API_PRETURN_HDR PhidgetRCServo_setMinPulseWidth(PhidgetRCServoHandle ch, double minPulseWidth);
API_PRETURN_HDR PhidgetRCServo_getMinPulseWidth(PhidgetRCServoHandle ch, double *minPulseWidth);
API_PRETURN_HDR PhidgetRCServo_setMaxPulseWidth(PhidgetRCServoHandle ch, double maxPulseWidth);
API_PRETURN_HDR PhidgetRCServo_getMaxPulseWidth(PhidgetRCServoHandle ch, double *maxPulseWidth);
API_PRETURN_HDR PhidgetRCServo_getMinPulseWidthLimit(PhidgetRCServoHandle ch,
  double *minPulseWidthLimit);
API_PRETURN_HDR PhidgetRCServo_getMaxPulseWidthLimit(PhidgetRCServoHandle ch,
  double *maxPulseWidthLimit);
API_PRETURN_HDR PhidgetRCServo_setSpeedRampingState(PhidgetRCServoHandle ch, int speedRampingState);
API_PRETURN_HDR PhidgetRCServo_getSpeedRampingState(PhidgetRCServoHandle ch, int *speedRampingState);
API_PRETURN_HDR PhidgetRCServo_setTargetPosition(PhidgetRCServoHandle ch, double targetPosition);
API_VRETURN_HDR PhidgetRCServo_setTargetPosition_async(PhidgetRCServoHandle ch, double targetPosition,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetRCServo_getTargetPosition(PhidgetRCServoHandle ch, double *targetPosition);
API_PRETURN_HDR PhidgetRCServo_setTorque(PhidgetRCServoHandle ch, double torque);
API_PRETURN_HDR PhidgetRCServo_getTorque(PhidgetRCServoHandle ch, double *torque);
API_PRETURN_HDR PhidgetRCServo_getMinTorque(PhidgetRCServoHandle ch, double *minTorque);
API_PRETURN_HDR PhidgetRCServo_getMaxTorque(PhidgetRCServoHandle ch, double *maxTorque);
API_PRETURN_HDR PhidgetRCServo_getVelocity(PhidgetRCServoHandle ch, double *velocity);
API_PRETURN_HDR PhidgetRCServo_setVelocityLimit(PhidgetRCServoHandle ch, double velocityLimit);
API_PRETURN_HDR PhidgetRCServo_getVelocityLimit(PhidgetRCServoHandle ch, double *velocityLimit);
API_PRETURN_HDR PhidgetRCServo_getMinVelocityLimit(PhidgetRCServoHandle ch, double *minVelocityLimit);
API_PRETURN_HDR PhidgetRCServo_getMaxVelocityLimit(PhidgetRCServoHandle ch, double *maxVelocityLimit);
API_PRETURN_HDR PhidgetRCServo_setVoltage(PhidgetRCServoHandle ch, PhidgetRCServo_Voltage voltage);
API_PRETURN_HDR PhidgetRCServo_getVoltage(PhidgetRCServoHandle ch, PhidgetRCServo_Voltage *voltage);

/* Events */
typedef void (CCONV *PhidgetRCServo_OnPositionChangeCallback)(PhidgetRCServoHandle ch, void *ctx,
  double position);

API_PRETURN_HDR PhidgetRCServo_setOnPositionChangeHandler(PhidgetRCServoHandle ch,
  PhidgetRCServo_OnPositionChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetRCServo_OnTargetPositionReachedCallback)(PhidgetRCServoHandle ch, void *ctx,
  double position);

API_PRETURN_HDR PhidgetRCServo_setOnTargetPositionReachedHandler(PhidgetRCServoHandle ch,
  PhidgetRCServo_OnTargetPositionReachedCallback fptr, void *ctx);
typedef void (CCONV *PhidgetRCServo_OnVelocityChangeCallback)(PhidgetRCServoHandle ch, void *ctx,
  double velocity);

API_PRETURN_HDR PhidgetRCServo_setOnVelocityChangeHandler(PhidgetRCServoHandle ch,
  PhidgetRCServo_OnVelocityChangeCallback fptr, void *ctx);

#endif /* _RCSERVO_H_ */
