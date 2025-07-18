#ifndef _DIGITALOUTPUT_H_
#define _DIGITALOUTPUT_H_
typedef struct _PhidgetDigitalOutput *PhidgetDigitalOutputHandle;

/* Methods */
API_PRETURN_HDR PhidgetDigitalOutput_create(PhidgetDigitalOutputHandle *ch);
API_PRETURN_HDR PhidgetDigitalOutput_delete(PhidgetDigitalOutputHandle *ch);
API_PRETURN_HDR PhidgetDigitalOutput_enableFailsafe(PhidgetDigitalOutputHandle ch,
  uint32_t failsafeTime);
API_PRETURN_HDR PhidgetDigitalOutput_resetFailsafe(PhidgetDigitalOutputHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetDigitalOutput_setDutyCycle(PhidgetDigitalOutputHandle ch, double dutyCycle);
API_VRETURN_HDR PhidgetDigitalOutput_setDutyCycle_async(PhidgetDigitalOutputHandle ch, double dutyCycle,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetDigitalOutput_getDutyCycle(PhidgetDigitalOutputHandle ch, double *dutyCycle);
API_PRETURN_HDR PhidgetDigitalOutput_getMinDutyCycle(PhidgetDigitalOutputHandle ch,
  double *minDutyCycle);
API_PRETURN_HDR PhidgetDigitalOutput_getMaxDutyCycle(PhidgetDigitalOutputHandle ch,
  double *maxDutyCycle);
API_PRETURN_HDR PhidgetDigitalOutput_getMinFailsafeTime(PhidgetDigitalOutputHandle ch,
  uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetDigitalOutput_getMaxFailsafeTime(PhidgetDigitalOutputHandle ch,
  uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetDigitalOutput_setFrequency(PhidgetDigitalOutputHandle ch, double frequency);
API_PRETURN_HDR PhidgetDigitalOutput_getFrequency(PhidgetDigitalOutputHandle ch, double *frequency);
API_PRETURN_HDR PhidgetDigitalOutput_getMinFrequency(PhidgetDigitalOutputHandle ch,
  double *minFrequency);
API_PRETURN_HDR PhidgetDigitalOutput_getMaxFrequency(PhidgetDigitalOutputHandle ch,
  double *maxFrequency);
API_PRETURN_HDR PhidgetDigitalOutput_setLEDCurrentLimit(PhidgetDigitalOutputHandle ch,
  double LEDCurrentLimit);
API_VRETURN_HDR PhidgetDigitalOutput_setLEDCurrentLimit_async(PhidgetDigitalOutputHandle ch,
  double LEDCurrentLimit, Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetDigitalOutput_getLEDCurrentLimit(PhidgetDigitalOutputHandle ch,
  double *LEDCurrentLimit);
API_PRETURN_HDR PhidgetDigitalOutput_getMinLEDCurrentLimit(PhidgetDigitalOutputHandle ch,
  double *minLEDCurrentLimit);
API_PRETURN_HDR PhidgetDigitalOutput_getMaxLEDCurrentLimit(PhidgetDigitalOutputHandle ch,
  double *maxLEDCurrentLimit);
API_PRETURN_HDR PhidgetDigitalOutput_setLEDForwardVoltage(PhidgetDigitalOutputHandle ch,
  PhidgetDigitalOutput_LEDForwardVoltage LEDForwardVoltage);
API_PRETURN_HDR PhidgetDigitalOutput_getLEDForwardVoltage(PhidgetDigitalOutputHandle ch,
  PhidgetDigitalOutput_LEDForwardVoltage *LEDForwardVoltage);
API_PRETURN_HDR PhidgetDigitalOutput_setState(PhidgetDigitalOutputHandle ch, int state);
API_VRETURN_HDR PhidgetDigitalOutput_setState_async(PhidgetDigitalOutputHandle ch, int state,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetDigitalOutput_getState(PhidgetDigitalOutputHandle ch, int *state);

/* Events */

#endif /* _DIGITALOUTPUT_H_ */
