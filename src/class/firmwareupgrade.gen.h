#ifndef _FIRMWAREUPGRADE_H_
#define _FIRMWAREUPGRADE_H_
#ifdef INCLUDE_PRIVATE
typedef struct _PhidgetFirmwareUpgrade *PhidgetFirmwareUpgradeHandle;

/* Methods */
API_PRETURN_HDR PhidgetFirmwareUpgrade_create(PhidgetFirmwareUpgradeHandle *ch);
API_PRETURN_HDR PhidgetFirmwareUpgrade_delete(PhidgetFirmwareUpgradeHandle *ch);
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_sendFirmware(PhidgetFirmwareUpgradeHandle ch, const uint8_t *data,
  size_t dataLen);
#endif

/* Properties */
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_getActualDeviceID(PhidgetFirmwareUpgradeHandle ch,
  Phidget_DeviceID *actualDeviceID);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_getActualDeviceName(PhidgetFirmwareUpgradeHandle ch,
  const char **actualDeviceName);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_getActualDeviceSKU(PhidgetFirmwareUpgradeHandle ch,
  const char **actualDeviceSKU);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_getActualDeviceVersion(PhidgetFirmwareUpgradeHandle ch,
  int *actualDeviceVersion);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_getActualDeviceVINTID(PhidgetFirmwareUpgradeHandle ch,
  uint32_t *actualDeviceVINTID);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetFirmwareUpgrade_getProgress(PhidgetFirmwareUpgradeHandle ch, double *progress);
#endif

/* Events */
#ifdef INCLUDE_PRIVATE
typedef void (CCONV *PhidgetFirmwareUpgrade_OnProgressChangeCallback)(PhidgetFirmwareUpgradeHandle ch,
  void *ctx, double progress);

API_PRETURN_HDR PhidgetFirmwareUpgrade_setOnProgressChangeHandler(PhidgetFirmwareUpgradeHandle ch,
  PhidgetFirmwareUpgrade_OnProgressChangeCallback fptr, void *ctx);
#endif

#endif /* INCLUDE_PRIVATE */
#endif /* _FIRMWAREUPGRADE_H_ */
