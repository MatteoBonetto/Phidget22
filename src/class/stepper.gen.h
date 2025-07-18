#ifndef _STEPPER_H_
#define _STEPPER_H_
typedef struct _PhidgetStepper *PhidgetStepperHandle;

/* Methods */
API_PRETURN_HDR PhidgetStepper_create(PhidgetStepperHandle *ch);
API_PRETURN_HDR PhidgetStepper_delete(PhidgetStepperHandle *ch);
API_PRETURN_HDR PhidgetStepper_enableFailsafe(PhidgetStepperHandle ch, uint32_t failsafeTime);
API_PRETURN_HDR PhidgetStepper_addPositionOffset(PhidgetStepperHandle ch, double positionOffset);
API_PRETURN_HDR PhidgetStepper_resetFailsafe(PhidgetStepperHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetStepper_setAcceleration(PhidgetStepperHandle ch, double acceleration);
API_PRETURN_HDR PhidgetStepper_getAcceleration(PhidgetStepperHandle ch, double *acceleration);
API_PRETURN_HDR PhidgetStepper_getMinAcceleration(PhidgetStepperHandle ch, double *minAcceleration);
API_PRETURN_HDR PhidgetStepper_getMaxAcceleration(PhidgetStepperHandle ch, double *maxAcceleration);
API_PRETURN_HDR PhidgetStepper_setControlMode(PhidgetStepperHandle ch,
  PhidgetStepper_ControlMode controlMode);
API_PRETURN_HDR PhidgetStepper_getControlMode(PhidgetStepperHandle ch,
  PhidgetStepper_ControlMode *controlMode);
API_PRETURN_HDR PhidgetStepper_setCurrentLimit(PhidgetStepperHandle ch, double currentLimit);
API_PRETURN_HDR PhidgetStepper_getCurrentLimit(PhidgetStepperHandle ch, double *currentLimit);
API_PRETURN_HDR PhidgetStepper_getMinCurrentLimit(PhidgetStepperHandle ch, double *minCurrentLimit);
API_PRETURN_HDR PhidgetStepper_getMaxCurrentLimit(PhidgetStepperHandle ch, double *maxCurrentLimit);
API_PRETURN_HDR PhidgetStepper_setDataInterval(PhidgetStepperHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetStepper_getDataInterval(PhidgetStepperHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetStepper_getMinDataInterval(PhidgetStepperHandle ch, uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetStepper_getMaxDataInterval(PhidgetStepperHandle ch, uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetStepper_setDataRate(PhidgetStepperHandle ch, double dataRate);
API_PRETURN_HDR PhidgetStepper_getDataRate(PhidgetStepperHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetStepper_getMinDataRate(PhidgetStepperHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetStepper_getMaxDataRate(PhidgetStepperHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetStepper_setEngaged(PhidgetStepperHandle ch, int engaged);
API_PRETURN_HDR PhidgetStepper_getEngaged(PhidgetStepperHandle ch, int *engaged);
API_PRETURN_HDR PhidgetStepper_getMinFailsafeTime(PhidgetStepperHandle ch, uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetStepper_getMaxFailsafeTime(PhidgetStepperHandle ch, uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetStepper_setHoldingCurrentLimit(PhidgetStepperHandle ch,
  double holdingCurrentLimit);
API_PRETURN_HDR PhidgetStepper_getHoldingCurrentLimit(PhidgetStepperHandle ch,
  double *holdingCurrentLimit);
API_PRETURN_HDR PhidgetStepper_getIsMoving(PhidgetStepperHandle ch, int *isMoving);
API_PRETURN_HDR PhidgetStepper_getPosition(PhidgetStepperHandle ch, double *position);
API_PRETURN_HDR PhidgetStepper_getMinPosition(PhidgetStepperHandle ch, double *minPosition);
API_PRETURN_HDR PhidgetStepper_getMaxPosition(PhidgetStepperHandle ch, double *maxPosition);
API_PRETURN_HDR PhidgetStepper_setRescaleFactor(PhidgetStepperHandle ch, double rescaleFactor);
API_PRETURN_HDR PhidgetStepper_getRescaleFactor(PhidgetStepperHandle ch, double *rescaleFactor);
API_PRETURN_HDR PhidgetStepper_setTargetPosition(PhidgetStepperHandle ch, double targetPosition);
API_VRETURN_HDR PhidgetStepper_setTargetPosition_async(PhidgetStepperHandle ch, double targetPosition,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetStepper_getTargetPosition(PhidgetStepperHandle ch, double *targetPosition);
API_PRETURN_HDR PhidgetStepper_getVelocity(PhidgetStepperHandle ch, double *velocity);
API_PRETURN_HDR PhidgetStepper_setVelocityLimit(PhidgetStepperHandle ch, double velocityLimit);
API_PRETURN_HDR PhidgetStepper_getVelocityLimit(PhidgetStepperHandle ch, double *velocityLimit);
API_PRETURN_HDR PhidgetStepper_getMinVelocityLimit(PhidgetStepperHandle ch, double *minVelocityLimit);
API_PRETURN_HDR PhidgetStepper_getMaxVelocityLimit(PhidgetStepperHandle ch, double *maxVelocityLimit);

/* Events */
typedef void (CCONV *PhidgetStepper_OnPositionChangeCallback)(PhidgetStepperHandle ch, void *ctx,
  double position);

API_PRETURN_HDR PhidgetStepper_setOnPositionChangeHandler(PhidgetStepperHandle ch,
  PhidgetStepper_OnPositionChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetStepper_OnStoppedCallback)(PhidgetStepperHandle ch, void *ctx);

API_PRETURN_HDR PhidgetStepper_setOnStoppedHandler(PhidgetStepperHandle ch,
  PhidgetStepper_OnStoppedCallback fptr, void *ctx);
typedef void (CCONV *PhidgetStepper_OnVelocityChangeCallback)(PhidgetStepperHandle ch, void *ctx,
  double velocity);

API_PRETURN_HDR PhidgetStepper_setOnVelocityChangeHandler(PhidgetStepperHandle ch,
  PhidgetStepper_OnVelocityChangeCallback fptr, void *ctx);

#endif /* _STEPPER_H_ */
