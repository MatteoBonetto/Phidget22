#ifndef _ENCODER_H_
#define _ENCODER_H_
typedef struct _PhidgetEncoder *PhidgetEncoderHandle;

/* Methods */
API_PRETURN_HDR PhidgetEncoder_create(PhidgetEncoderHandle *ch);
API_PRETURN_HDR PhidgetEncoder_delete(PhidgetEncoderHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetEncoder_setDataInterval(PhidgetEncoderHandle ch, uint32_t dataInterval);
API_PRETURN_HDR PhidgetEncoder_getDataInterval(PhidgetEncoderHandle ch, uint32_t *dataInterval);
API_PRETURN_HDR PhidgetEncoder_getMinDataInterval(PhidgetEncoderHandle ch, uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetEncoder_getMaxDataInterval(PhidgetEncoderHandle ch, uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetEncoder_setDataRate(PhidgetEncoderHandle ch, double dataRate);
API_PRETURN_HDR PhidgetEncoder_getDataRate(PhidgetEncoderHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetEncoder_getMinDataRate(PhidgetEncoderHandle ch, double *minDataRate);
API_PRETURN_HDR PhidgetEncoder_getMaxDataRate(PhidgetEncoderHandle ch, double *maxDataRate);
API_PRETURN_HDR PhidgetEncoder_setEnabled(PhidgetEncoderHandle ch, int enabled);
API_PRETURN_HDR PhidgetEncoder_getEnabled(PhidgetEncoderHandle ch, int *enabled);
API_PRETURN_HDR PhidgetEncoder_getIndexPosition(PhidgetEncoderHandle ch, int64_t *indexPosition);
API_PRETURN_HDR PhidgetEncoder_setIOMode(PhidgetEncoderHandle ch, Phidget_EncoderIOMode IOMode);
API_PRETURN_HDR PhidgetEncoder_getIOMode(PhidgetEncoderHandle ch, Phidget_EncoderIOMode *IOMode);
API_PRETURN_HDR PhidgetEncoder_setPosition(PhidgetEncoderHandle ch, int64_t position);
API_PRETURN_HDR PhidgetEncoder_getPosition(PhidgetEncoderHandle ch, int64_t *position);
API_PRETURN_HDR PhidgetEncoder_setPositionChangeTrigger(PhidgetEncoderHandle ch,
  uint32_t positionChangeTrigger);
API_PRETURN_HDR PhidgetEncoder_getPositionChangeTrigger(PhidgetEncoderHandle ch,
  uint32_t *positionChangeTrigger);
API_PRETURN_HDR PhidgetEncoder_getMinPositionChangeTrigger(PhidgetEncoderHandle ch,
  uint32_t *minPositionChangeTrigger);
API_PRETURN_HDR PhidgetEncoder_getMaxPositionChangeTrigger(PhidgetEncoderHandle ch,
  uint32_t *maxPositionChangeTrigger);

/* Events */
typedef void (CCONV *PhidgetEncoder_OnPositionChangeCallback)(PhidgetEncoderHandle ch, void *ctx,
  int positionChange, double timeChange, int indexTriggered);

API_PRETURN_HDR PhidgetEncoder_setOnPositionChangeHandler(PhidgetEncoderHandle ch,
  PhidgetEncoder_OnPositionChangeCallback fptr, void *ctx);

#endif /* _ENCODER_H_ */
