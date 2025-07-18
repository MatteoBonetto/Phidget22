#ifndef _HUB_H_
#define _HUB_H_
typedef struct _PhidgetHub *PhidgetHubHandle;

/* Methods */
API_PRETURN_HDR PhidgetHub_create(PhidgetHubHandle *ch);
API_PRETURN_HDR PhidgetHub_delete(PhidgetHubHandle *ch);
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetHub_setADCCalibrationValues(PhidgetHubHandle ch, double voltageInputGain[6],
  double voltageRatioGain[6]);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetHub_setADCCalibrationValues2(PhidgetHubHandle ch, const double *voltageInputOffset,
  size_t voltageInputOffsetLen, const double *voltageInputGain, size_t voltageInputGainLen, const double *voltageRatioOffset, size_t voltageRatioOffsetLen, const double *voltageRatioGain, size_t voltageRatioGainLen);
#endif
#ifdef INCLUDE_PRIVATE
API_PRETURN_HDR PhidgetHub_setFirmwareUpgradeFlag(PhidgetHubHandle ch, int port, uint32_t timeout);
#endif
API_PRETURN_HDR PhidgetHub_setPortAutoSetSpeed(PhidgetHubHandle ch, int port, int state);
API_PRETURN_HDR PhidgetHub_getPortMaxSpeed(PhidgetHubHandle ch, int port, uint32_t *state);
API_PRETURN_HDR PhidgetHub_getPortMode(PhidgetHubHandle ch, int port, PhidgetHub_PortMode *mode);
API_PRETURN_HDR PhidgetHub_setPortMode(PhidgetHubHandle ch, int port, PhidgetHub_PortMode mode);
API_PRETURN_HDR PhidgetHub_getPortPower(PhidgetHubHandle ch, int port, int *state);
API_PRETURN_HDR PhidgetHub_setPortPower(PhidgetHubHandle ch, int port, int state);
API_PRETURN_HDR PhidgetHub_getPortSupportsAutoSetSpeed(PhidgetHubHandle ch, int port, int *state);
API_PRETURN_HDR PhidgetHub_getPortSupportsSetSpeed(PhidgetHubHandle ch, int port, int *state);

/* Properties */

/* Events */

#endif /* _HUB_H_ */
