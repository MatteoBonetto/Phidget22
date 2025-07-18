#ifndef _FREQUENCYCOUNTER_H_
#define _FREQUENCYCOUNTER_H_
typedef struct _PhidgetFrequencyCounter *PhidgetFrequencyCounterHandle;

/* Methods */
API_PRETURN_HDR PhidgetFrequencyCounter_create(PhidgetFrequencyCounterHandle *ch);
API_PRETURN_HDR PhidgetFrequencyCounter_delete(PhidgetFrequencyCounterHandle *ch);
API_PRETURN_HDR PhidgetFrequencyCounter_reset(PhidgetFrequencyCounterHandle ch);

/* Properties */
API_PRETURN_HDR PhidgetFrequencyCounter_getCount(PhidgetFrequencyCounterHandle ch, uint64_t *count);
API_PRETURN_HDR PhidgetFrequencyCounter_setDataInterval(PhidgetFrequencyCounterHandle ch,
  uint32_t dataInterval);
API_PRETURN_HDR PhidgetFrequencyCounter_getDataInterval(PhidgetFrequencyCounterHandle ch,
  uint32_t *dataInterval);
API_PRETURN_HDR PhidgetFrequencyCounter_getMinDataInterval(PhidgetFrequencyCounterHandle ch,
  uint32_t *minDataInterval);
API_PRETURN_HDR PhidgetFrequencyCounter_getMaxDataInterval(PhidgetFrequencyCounterHandle ch,
  uint32_t *maxDataInterval);
API_PRETURN_HDR PhidgetFrequencyCounter_setDataRate(PhidgetFrequencyCounterHandle ch, double dataRate);
API_PRETURN_HDR PhidgetFrequencyCounter_getDataRate(PhidgetFrequencyCounterHandle ch, double *dataRate);
API_PRETURN_HDR PhidgetFrequencyCounter_getMinDataRate(PhidgetFrequencyCounterHandle ch,
  double *minDataRate);
API_PRETURN_HDR PhidgetFrequencyCounter_getMaxDataRate(PhidgetFrequencyCounterHandle ch,
  double *maxDataRate);
API_PRETURN_HDR PhidgetFrequencyCounter_setEnabled(PhidgetFrequencyCounterHandle ch, int enabled);
API_PRETURN_HDR PhidgetFrequencyCounter_getEnabled(PhidgetFrequencyCounterHandle ch, int *enabled);
API_PRETURN_HDR PhidgetFrequencyCounter_setFilterType(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_FilterType filterType);
API_PRETURN_HDR PhidgetFrequencyCounter_getFilterType(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_FilterType *filterType);
API_PRETURN_HDR PhidgetFrequencyCounter_getFrequency(PhidgetFrequencyCounterHandle ch,
  double *frequency);
API_PRETURN_HDR PhidgetFrequencyCounter_getMaxFrequency(PhidgetFrequencyCounterHandle ch,
  double *maxFrequency);
API_PRETURN_HDR PhidgetFrequencyCounter_setFrequencyCutoff(PhidgetFrequencyCounterHandle ch,
  double frequencyCutoff);
API_PRETURN_HDR PhidgetFrequencyCounter_getFrequencyCutoff(PhidgetFrequencyCounterHandle ch,
  double *frequencyCutoff);
API_PRETURN_HDR PhidgetFrequencyCounter_getMinFrequencyCutoff(PhidgetFrequencyCounterHandle ch,
  double *minFrequencyCutoff);
API_PRETURN_HDR PhidgetFrequencyCounter_getMaxFrequencyCutoff(PhidgetFrequencyCounterHandle ch,
  double *maxFrequencyCutoff);
API_PRETURN_HDR PhidgetFrequencyCounter_setInputMode(PhidgetFrequencyCounterHandle ch,
  Phidget_InputMode inputMode);
API_PRETURN_HDR PhidgetFrequencyCounter_getInputMode(PhidgetFrequencyCounterHandle ch,
  Phidget_InputMode *inputMode);
API_PRETURN_HDR PhidgetFrequencyCounter_setPowerSupply(PhidgetFrequencyCounterHandle ch,
  Phidget_PowerSupply powerSupply);
API_PRETURN_HDR PhidgetFrequencyCounter_getPowerSupply(PhidgetFrequencyCounterHandle ch,
  Phidget_PowerSupply *powerSupply);
API_PRETURN_HDR PhidgetFrequencyCounter_getTimeElapsed(PhidgetFrequencyCounterHandle ch,
  double *timeElapsed);

/* Events */
typedef void (CCONV *PhidgetFrequencyCounter_OnCountChangeCallback)(PhidgetFrequencyCounterHandle ch,
  void *ctx, uint64_t counts, double timeChange);

API_PRETURN_HDR PhidgetFrequencyCounter_setOnCountChangeHandler(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_OnCountChangeCallback fptr, void *ctx);
typedef void (CCONV *PhidgetFrequencyCounter_OnFrequencyChangeCallback)(PhidgetFrequencyCounterHandle ch,
  void *ctx, double frequency);

API_PRETURN_HDR PhidgetFrequencyCounter_setOnFrequencyChangeHandler(PhidgetFrequencyCounterHandle ch,
  PhidgetFrequencyCounter_OnFrequencyChangeCallback fptr, void *ctx);

#endif /* _FREQUENCYCOUNTER_H_ */
