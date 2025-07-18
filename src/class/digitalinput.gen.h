#ifndef _DIGITALINPUT_H_
#define _DIGITALINPUT_H_
typedef struct _PhidgetDigitalInput *PhidgetDigitalInputHandle;

/* Methods */
API_PRETURN_HDR PhidgetDigitalInput_create(PhidgetDigitalInputHandle *ch);
API_PRETURN_HDR PhidgetDigitalInput_delete(PhidgetDigitalInputHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetDigitalInput_setInputMode(PhidgetDigitalInputHandle ch,
  Phidget_InputMode inputMode);
API_PRETURN_HDR PhidgetDigitalInput_getInputMode(PhidgetDigitalInputHandle ch,
  Phidget_InputMode *inputMode);
API_PRETURN_HDR PhidgetDigitalInput_setPowerSupply(PhidgetDigitalInputHandle ch,
  Phidget_PowerSupply powerSupply);
API_PRETURN_HDR PhidgetDigitalInput_getPowerSupply(PhidgetDigitalInputHandle ch,
  Phidget_PowerSupply *powerSupply);
API_PRETURN_HDR PhidgetDigitalInput_getState(PhidgetDigitalInputHandle ch, int *state);

/* Events */
typedef void (CCONV *PhidgetDigitalInput_OnStateChangeCallback)(PhidgetDigitalInputHandle ch, void *ctx,
  int state);

API_PRETURN_HDR PhidgetDigitalInput_setOnStateChangeHandler(PhidgetDigitalInputHandle ch,
  PhidgetDigitalInput_OnStateChangeCallback fptr, void *ctx);

#endif /* _DIGITALINPUT_H_ */
