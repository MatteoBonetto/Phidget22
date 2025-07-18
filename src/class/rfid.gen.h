#ifndef _RFID_H_
#define _RFID_H_
typedef struct _PhidgetRFID *PhidgetRFIDHandle;

/* Methods */
API_PRETURN_HDR PhidgetRFID_create(PhidgetRFIDHandle *ch);
API_PRETURN_HDR PhidgetRFID_delete(PhidgetRFIDHandle *ch);
API_PRETURN_HDR PhidgetRFID_getLastTag(PhidgetRFIDHandle ch, char *tagString, size_t tagStringLen,
  PhidgetRFID_Protocol *protocol);
API_PRETURN_HDR PhidgetRFID_write(PhidgetRFIDHandle ch, const char *tagString,
  PhidgetRFID_Protocol protocol, int lockTag);
API_PRETURN_HDR PhidgetRFID_writeWithChipset(PhidgetRFIDHandle ch, const char *tagString,
  PhidgetRFID_Protocol protocol, int lockTag, PhidgetRFID_Chipset chipset);

/* Properties */
API_PRETURN_HDR PhidgetRFID_setAntennaEnabled(PhidgetRFIDHandle ch, int antennaEnabled);
API_PRETURN_HDR PhidgetRFID_getAntennaEnabled(PhidgetRFIDHandle ch, int *antennaEnabled);
API_PRETURN_HDR PhidgetRFID_getTagPresent(PhidgetRFIDHandle ch, int *tagPresent);

/* Events */
typedef void (CCONV *PhidgetRFID_OnTagCallback)(PhidgetRFIDHandle ch, void *ctx, const char *tag,
  PhidgetRFID_Protocol protocol);

API_PRETURN_HDR PhidgetRFID_setOnTagHandler(PhidgetRFIDHandle ch, PhidgetRFID_OnTagCallback fptr,
  void *ctx);
typedef void (CCONV *PhidgetRFID_OnTagLostCallback)(PhidgetRFIDHandle ch, void *ctx, const char *tag,
  PhidgetRFID_Protocol protocol);

API_PRETURN_HDR PhidgetRFID_setOnTagLostHandler(PhidgetRFIDHandle ch, PhidgetRFID_OnTagLostCallback fptr,
  void *ctx);

#endif /* _RFID_H_ */
