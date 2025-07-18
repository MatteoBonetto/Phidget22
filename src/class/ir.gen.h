#ifndef _IR_H_
#define _IR_H_
typedef struct _PhidgetIR *PhidgetIRHandle;

/* Methods */
API_PRETURN_HDR PhidgetIR_create(PhidgetIRHandle *ch);
API_PRETURN_HDR PhidgetIR_delete(PhidgetIRHandle *ch);
API_PRETURN_HDR PhidgetIR_getLastCode(PhidgetIRHandle ch, char *code, size_t codeLen,
  uint32_t *bitCount);
API_PRETURN_HDR PhidgetIR_getLastLearnedCode(PhidgetIRHandle ch, char *code, size_t codeLen,
  PhidgetIR_CodeInfo *codeInfo);
API_PRETURN_HDR PhidgetIR_transmit(PhidgetIRHandle ch, const char *code, PhidgetIR_CodeInfo *codeInfo);
API_PRETURN_HDR PhidgetIR_transmitRaw(PhidgetIRHandle ch, const uint32_t *data, size_t dataLen,
  uint32_t carrierFrequency, double dutyCycle, uint32_t gap);
API_PRETURN_HDR PhidgetIR_transmitRepeat(PhidgetIRHandle ch);

/* Properties */

/* Events */
typedef void (CCONV *PhidgetIR_OnCodeCallback)(PhidgetIRHandle ch, void *ctx, const char *code,
  uint32_t bitCount, int isRepeat);

API_PRETURN_HDR PhidgetIR_setOnCodeHandler(PhidgetIRHandle ch, PhidgetIR_OnCodeCallback fptr,
  void *ctx);
typedef void (CCONV *PhidgetIR_OnLearnCallback)(PhidgetIRHandle ch, void *ctx, const char *code,
  PhidgetIR_CodeInfo *codeInfo);

API_PRETURN_HDR PhidgetIR_setOnLearnHandler(PhidgetIRHandle ch, PhidgetIR_OnLearnCallback fptr,
  void *ctx);
typedef void (CCONV *PhidgetIR_OnRawDataCallback)(PhidgetIRHandle ch, void *ctx, const uint32_t *data,
  size_t dataLen);

API_PRETURN_HDR PhidgetIR_setOnRawDataHandler(PhidgetIRHandle ch, PhidgetIR_OnRawDataCallback fptr,
  void *ctx);

#endif /* _IR_H_ */
