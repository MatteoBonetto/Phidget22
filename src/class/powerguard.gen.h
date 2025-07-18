#ifndef _POWERGUARD_H_
#define _POWERGUARD_H_
typedef struct _PhidgetPowerGuard *PhidgetPowerGuardHandle;

/* Methods */
API_PRETURN_HDR PhidgetPowerGuard_create(PhidgetPowerGuardHandle *ch);
API_PRETURN_HDR PhidgetPowerGuard_delete(PhidgetPowerGuardHandle *ch);
API_PRETURN_HDR PhidgetPowerGuard_enableFailsafe(PhidgetPowerGuardHandle ch, uint32_t failsafeTime);
API_PRETURN_HDR PhidgetPowerGuard_resetFailsafe(PhidgetPowerGuardHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetPowerGuard_getMinFailsafeTime(PhidgetPowerGuardHandle ch,
  uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetPowerGuard_getMaxFailsafeTime(PhidgetPowerGuardHandle ch,
  uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetPowerGuard_setFanMode(PhidgetPowerGuardHandle ch, Phidget_FanMode fanMode);
API_PRETURN_HDR PhidgetPowerGuard_getFanMode(PhidgetPowerGuardHandle ch, Phidget_FanMode *fanMode);
API_PRETURN_HDR PhidgetPowerGuard_setOverVoltage(PhidgetPowerGuardHandle ch, double overVoltage);
API_PRETURN_HDR PhidgetPowerGuard_getOverVoltage(PhidgetPowerGuardHandle ch, double *overVoltage);
API_PRETURN_HDR PhidgetPowerGuard_getMinOverVoltage(PhidgetPowerGuardHandle ch, double *minOverVoltage);
API_PRETURN_HDR PhidgetPowerGuard_getMaxOverVoltage(PhidgetPowerGuardHandle ch, double *maxOverVoltage);
API_PRETURN_HDR PhidgetPowerGuard_setPowerEnabled(PhidgetPowerGuardHandle ch, int powerEnabled);
API_PRETURN_HDR PhidgetPowerGuard_getPowerEnabled(PhidgetPowerGuardHandle ch, int *powerEnabled);

/* Events */

#endif /* _POWERGUARD_H_ */
