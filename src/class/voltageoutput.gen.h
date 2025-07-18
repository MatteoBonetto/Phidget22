#ifndef _VOLTAGEOUTPUT_H_
#define _VOLTAGEOUTPUT_H_
typedef struct _PhidgetVoltageOutput *PhidgetVoltageOutputHandle;

/* Methods */
API_PRETURN_HDR PhidgetVoltageOutput_create(PhidgetVoltageOutputHandle *ch);
API_PRETURN_HDR PhidgetVoltageOutput_delete(PhidgetVoltageOutputHandle *ch);
API_PRETURN_HDR PhidgetVoltageOutput_enableFailsafe(PhidgetVoltageOutputHandle ch,
  uint32_t failsafeTime);
API_PRETURN_HDR PhidgetVoltageOutput_resetFailsafe(PhidgetVoltageOutputHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetVoltageOutput_setEnabled(PhidgetVoltageOutputHandle ch, int enabled);
API_PRETURN_HDR PhidgetVoltageOutput_getEnabled(PhidgetVoltageOutputHandle ch, int *enabled);
API_PRETURN_HDR PhidgetVoltageOutput_getMinFailsafeTime(PhidgetVoltageOutputHandle ch,
  uint32_t *minFailsafeTime);
API_PRETURN_HDR PhidgetVoltageOutput_getMaxFailsafeTime(PhidgetVoltageOutputHandle ch,
  uint32_t *maxFailsafeTime);
API_PRETURN_HDR PhidgetVoltageOutput_setVoltage(PhidgetVoltageOutputHandle ch, double voltage);
API_VRETURN_HDR PhidgetVoltageOutput_setVoltage_async(PhidgetVoltageOutputHandle ch, double voltage,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetVoltageOutput_getVoltage(PhidgetVoltageOutputHandle ch, double *voltage);
API_PRETURN_HDR PhidgetVoltageOutput_getMinVoltage(PhidgetVoltageOutputHandle ch, double *minVoltage);
API_PRETURN_HDR PhidgetVoltageOutput_getMaxVoltage(PhidgetVoltageOutputHandle ch, double *maxVoltage);
API_PRETURN_HDR PhidgetVoltageOutput_setVoltageOutputRange(PhidgetVoltageOutputHandle ch,
  PhidgetVoltageOutput_VoltageOutputRange voltageOutputRange);
API_PRETURN_HDR PhidgetVoltageOutput_getVoltageOutputRange(PhidgetVoltageOutputHandle ch,
  PhidgetVoltageOutput_VoltageOutputRange *voltageOutputRange);

/* Events */

#endif /* _VOLTAGEOUTPUT_H_ */
