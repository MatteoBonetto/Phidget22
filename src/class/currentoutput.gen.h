#ifndef _CURRENTOUTPUT_H_
#define _CURRENTOUTPUT_H_
#ifdef INCLUDE_PRIVATE
typedef struct _PhidgetCurrentOutput *PhidgetCurrentOutputHandle;

/* Methods */
API_PRETURN_HDR PhidgetCurrentOutput_create(PhidgetCurrentOutputHandle *ch);
API_PRETURN_HDR PhidgetCurrentOutput_delete(PhidgetCurrentOutputHandle *ch);

/* Properties */
API_PRETURN_HDR PhidgetCurrentOutput_setCurrent(PhidgetCurrentOutputHandle ch, double current);
API_VRETURN_HDR PhidgetCurrentOutput_setCurrent_async(PhidgetCurrentOutputHandle ch, double current,
  Phidget_AsyncCallback fptr, void *ctx);
API_PRETURN_HDR PhidgetCurrentOutput_getCurrent(PhidgetCurrentOutputHandle ch, double *current);
API_PRETURN_HDR PhidgetCurrentOutput_getMinCurrent(PhidgetCurrentOutputHandle ch, double *minCurrent);
API_PRETURN_HDR PhidgetCurrentOutput_getMaxCurrent(PhidgetCurrentOutputHandle ch, double *maxCurrent);
API_PRETURN_HDR PhidgetCurrentOutput_setEnabled(PhidgetCurrentOutputHandle ch, int enabled);
API_PRETURN_HDR PhidgetCurrentOutput_getEnabled(PhidgetCurrentOutputHandle ch, int *enabled);

/* Events */

#endif /* INCLUDE_PRIVATE */
#endif /* _CURRENTOUTPUT_H_ */
