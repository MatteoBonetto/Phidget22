/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/interfacekitdevice.h"
#include "device/vintdevice.h"
#include "device/rfiddevice.h"
#include "device/leddevice.h"
#include "device/textlcddevice.h"
static void CCONV PhidgetDigitalOutput_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetDigitalOutput_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetDigitalOutput_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetDigitalOutput_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetDigitalOutput_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetDigitalOutput_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetDigitalOutput_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetDigitalOutput_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetDigitalOutput_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetDigitalOutput {
	struct _PhidgetChannel phid;
	double dutyCycle;
	double minDutyCycle;
	double maxDutyCycle;
	uint32_t minFailsafeTime;
	uint32_t maxFailsafeTime;
	double frequency;
	double minFrequency;
	double maxFrequency;
	double LEDCurrentLimit;
	double minLEDCurrentLimit;
	double maxLEDCurrentLimit;
	PhidgetDigitalOutput_LEDForwardVoltage LEDForwardVoltage;
	int state;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDigitalOutputHandle ch;
	int nsversion;

	ch = (PhidgetDigitalOutputHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 2) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 2 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "dutyCycle"))
		ch->dutyCycle = getBridgePacketDoubleByName(bp, "dutyCycle");
	if (hasBridgePacketByName(bp, "minDutyCycle"))
		ch->minDutyCycle = getBridgePacketDoubleByName(bp, "minDutyCycle");
	if (hasBridgePacketByName(bp, "maxDutyCycle"))
		ch->maxDutyCycle = getBridgePacketDoubleByName(bp, "maxDutyCycle");
	if (hasBridgePacketByName(bp, "minFailsafeTime"))
		ch->minFailsafeTime = getBridgePacketUInt32ByName(bp, "minFailsafeTime");
	if (hasBridgePacketByName(bp, "maxFailsafeTime"))
		ch->maxFailsafeTime = getBridgePacketUInt32ByName(bp, "maxFailsafeTime");
	if (hasBridgePacketByName(bp, "frequency"))
		ch->frequency = getBridgePacketDoubleByName(bp, "frequency");
	if (hasBridgePacketByName(bp, "minFrequency"))
		ch->minFrequency = getBridgePacketDoubleByName(bp, "minFrequency");
	if (hasBridgePacketByName(bp, "maxFrequency"))
		ch->maxFrequency = getBridgePacketDoubleByName(bp, "maxFrequency");
	if (hasBridgePacketByName(bp, "LEDCurrentLimit"))
		ch->LEDCurrentLimit = getBridgePacketDoubleByName(bp, "LEDCurrentLimit");
	if (hasBridgePacketByName(bp, "minLEDCurrentLimit"))
		ch->minLEDCurrentLimit = getBridgePacketDoubleByName(bp, "minLEDCurrentLimit");
	if (hasBridgePacketByName(bp, "maxLEDCurrentLimit"))
		ch->maxLEDCurrentLimit = getBridgePacketDoubleByName(bp, "maxLEDCurrentLimit");
	if (hasBridgePacketByName(bp, "LEDForwardVoltage"))
		ch->LEDForwardVoltage = getBridgePacketInt32ByName(bp, "LEDForwardVoltage");
	if (hasBridgePacketByName(bp, "state"))
		ch->state = getBridgePacketInt32ByName(bp, "state");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetDigitalOutputHandle ch;

	ch = (PhidgetDigitalOutputHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 14, "_class_version_=%u"
	  ",dutyCycle=%g"
	  ",minDutyCycle=%g"
	  ",maxDutyCycle=%g"
	  ",minFailsafeTime=%u"
	  ",maxFailsafeTime=%u"
	  ",frequency=%g"
	  ",minFrequency=%g"
	  ",maxFrequency=%g"
	  ",LEDCurrentLimit=%g"
	  ",minLEDCurrentLimit=%g"
	  ",maxLEDCurrentLimit=%g"
	  ",LEDForwardVoltage=%d"
	  ",state=%d"
	  ,2 /* class version */
	  ,ch->dutyCycle
	  ,ch->minDutyCycle
	  ,ch->maxDutyCycle
	  ,ch->minFailsafeTime
	  ,ch->maxFailsafeTime
	  ,ch->frequency
	  ,ch->minFrequency
	  ,ch->maxFrequency
	  ,ch->LEDCurrentLimit
	  ,ch->minLEDCurrentLimit
	  ,ch->maxLEDCurrentLimit
	  ,ch->LEDForwardVoltage
	  ,ch->state
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDigitalOutputHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetDigitalOutputHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SETFAILSAFETIME:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_FAILSAFERESET:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_SETDUTYCYCLE:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minDutyCycle,
		  ch->maxDutyCycle);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->dutyCycle = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "DutyCycle");
		}
		break;
	case BP_SETFREQUENCY:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minFrequency,
		  ch->maxFrequency);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->frequency = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Frequency");
		}
		break;
	case BP_SETLEDCURRENTLIMIT:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minLEDCurrentLimit,
		  ch->maxLEDCurrentLimit);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->LEDCurrentLimit = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "LEDCurrentLimit");
		}
		break;
	case BP_SETLEDFORWARDVOLTAGE:
		if (!supportedLEDForwardVoltage(phid,
		  (PhidgetDigitalOutput_LEDForwardVoltage)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified LEDForwardVoltage is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->LEDForwardVoltage = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "LEDForwardVoltage");
		}
		break;
	case BP_SETSTATE:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->state = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "State");
		}
		break;
	default:
		logerr("%"PRIphid": unsupported bridge packet:0x%x", phid, bp->vpkt);
		res = EPHIDGET_UNSUPPORTED;
	}

	return (res);
}

static PhidgetReturnCode CCONV
_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetInterfaceKitDeviceHandle parentInterfaceKit;
	PhidgetTextLCDDeviceHandle parentTextLCD;
	PhidgetRFIDDeviceHandle parentRFID;
	PhidgetVINTDeviceHandle parentVINT;
	PhidgetLEDDeviceHandle parentLED;
	PhidgetDigitalOutputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetDigitalOutputHandle)phid;

	ret = EPHIDGET_OK;

	parentInterfaceKit = (PhidgetInterfaceKitDeviceHandle)phid->parent;
	parentTextLCD = (PhidgetTextLCDDeviceHandle)phid->parent;
	parentRFID = (PhidgetRFIDDeviceHandle)phid->parent;
	parentVINT = (PhidgetVINTDeviceHandle)phid->parent;
	parentLED = (PhidgetLEDDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentRFID->dutyCycle[ch->phid.index];
		ch->state = parentRFID->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->LEDCurrentLimit = 0.03;
		ch->minLEDCurrentLimit = 0.03;
		ch->maxLEDCurrentLimit = 0.03;
		ch->LEDForwardVoltage = LED_FORWARD_VOLTAGE_3_2V;
		// Inputs, Settables
		ch->dutyCycle = parentLED->dutyCycle[ch->phid.index];
		ch->state = parentLED->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->minLEDCurrentLimit = 0;
		ch->maxLEDCurrentLimit = 0.08;
		// Inputs, Settables
		ch->dutyCycle = parentLED->dutyCycle[ch->phid.index];
		ch->LEDCurrentLimit = parentLED->LEDCurrentLimitDevProp;
		ch->LEDForwardVoltage = parentLED->LEDForwardVoltageDevProp;
		ch->state = parentLED->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->minLEDCurrentLimit = 0;
		ch->maxLEDCurrentLimit = 0.08;
		// Inputs, Settables
		ch->dutyCycle = parentLED->dutyCycle[ch->phid.index];
		ch->LEDCurrentLimit = parentLED->LEDCurrentLimit[ch->phid.index];
		ch->LEDForwardVoltage = parentLED->LEDForwardVoltageDevProp;
		ch->state = parentLED->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentInterfaceKit->dutyCycle[ch->phid.index];
		ch->state = parentInterfaceKit->outputState[ch->phid.index];
		break;
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = parentTextLCD->dutyCycle[ch->phid.index];
		ch->state = parentTextLCD->outputState[ch->phid.index];
		break;
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 60000;
		ch->minFailsafeTime = 100;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_120:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		ch->maxFrequency = 20000;
		ch->minFrequency = 100;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		ch->frequency = PUNK_DBL;
		break;
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->minLEDCurrentLimit = 0;
		ch->maxLEDCurrentLimit = 0.04;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->LEDCurrentLimit = PUNK_DBL;
		ch->LEDForwardVoltage = parentVINT->LEDForwardVoltageDevProp;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1100_DIGITALOUTPUT_120:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		ch->maxFrequency = 20000;
		ch->minFrequency = 100;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		ch->frequency = PUNK_DBL;
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_FREQ_200:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		ch->maxFrequency = 20000;
		ch->minFrequency = 100;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		ch->frequency = PUNK_DBL;
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		// Constants
		ch->maxDutyCycle = 1;
		ch->minDutyCycle = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dutyCycle = PUNK_DBL;
		ch->state = PUNK_BOOL;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetDigitalOutputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetDigitalOutputHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		// (Device Property - check if already set)
		if (ch->LEDCurrentLimit == PUNK_DBL)
			ch->LEDCurrentLimit = 0.02;
		// (Device Property - check if already set)
		if (ch->LEDForwardVoltage == PUNK_ENUM)
			ch->LEDForwardVoltage = LED_FORWARD_VOLTAGE_2_75V;
		ret = bridgeSendToDevice(phid, BP_SETLEDCURRENTLIMIT, NULL, NULL, 1, "%g",
		  ch->LEDCurrentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETLEDFORWARDVOLTAGE, NULL, NULL, 1, "%d",
		  ch->LEDForwardVoltage);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		ch->LEDCurrentLimit = 0.02;
		// (Device Property - check if already set)
		if (ch->LEDForwardVoltage == PUNK_ENUM)
			ch->LEDForwardVoltage = LED_FORWARD_VOLTAGE_2_75V;
		ret = bridgeSendToDevice(phid, BP_SETLEDCURRENTLIMIT, NULL, NULL, 1, "%g",
		  ch->LEDCurrentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETLEDFORWARDVOLTAGE, NULL, NULL, 1, "%d",
		  ch->LEDForwardVoltage);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_120:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		ch->frequency = 15625;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->LEDCurrentLimit = 0.02;
		// (Device Property - check if already set)
		if (ch->LEDForwardVoltage == PUNK_ENUM)
			ch->LEDForwardVoltage = LED_FORWARD_VOLTAGE_3_2V;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1100_DIGITALOUTPUT_120:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		ch->frequency = 15625;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_FREQ_200:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		ch->frequency = 20000;
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		// Reset values
		ch->dutyCycle = 0;
		ch->state = 0;
		// Must-set values
		// Default values
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	return (ret);
}

static void CCONV
_fireInitialEvents(PhidgetChannelHandle phid) {

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetDigitalOutput));
}

static PhidgetReturnCode CCONV
_create(PhidgetDigitalOutputHandle *phidp) {

	CHANNELCREATE_BODY(DigitalOutput, PHIDCHCLASS_DIGITALOUTPUT);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_delete(PhidgetDigitalOutputHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetDigitalOutput_enableFailsafe(PhidgetDigitalOutputHandle ch, uint32_t failsafeTime) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFAILSAFETIME, NULL, NULL, 1, "%u",
	  failsafeTime); 
}

API_PRETURN
PhidgetDigitalOutput_resetFailsafe(PhidgetDigitalOutputHandle ch) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_FAILSAFERESET, NULL, NULL, 0, NULL); 
}

API_PRETURN
PhidgetDigitalOutput_setDutyCycle(PhidgetDigitalOutputHandle ch, double dutyCycle) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g",
	  dutyCycle));
}

API_VRETURN
PhidgetDigitalOutput_setDutyCycle_async(PhidgetDigitalOutputHandle ch, double dutyCycle,
  Phidget_AsyncCallback fptr, void *ctx) {
	PhidgetReturnCode res;

	if (ch == NULL) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}
	if (ch->phid.class != PHIDCHCLASS_DIGITALOUTPUT) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_WRONGDEVICE);
		return;
	}
	if (!ISATTACHED(ch)) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_NOTATTACHED);
		return;
	}

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDUTYCYCLE, fptr, ctx, 1, "%g", dutyCycle);
	if (res != EPHIDGET_OK && fptr != NULL)
		fptr((PhidgetHandle)ch, ctx, res);
}

API_PRETURN
PhidgetDigitalOutput_getDutyCycle(PhidgetDigitalOutputHandle ch, double *dutyCycle) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dutyCycle);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	*dutyCycle = ch->dutyCycle;
	if (ch->dutyCycle == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMinDutyCycle(PhidgetDigitalOutputHandle ch, double *minDutyCycle) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDutyCycle);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	*minDutyCycle = ch->minDutyCycle;
	if (ch->minDutyCycle == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMaxDutyCycle(PhidgetDigitalOutputHandle ch, double *maxDutyCycle) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDutyCycle);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	*maxDutyCycle = ch->maxDutyCycle;
	if (ch->maxDutyCycle == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMinFailsafeTime(PhidgetDigitalOutputHandle ch, uint32_t *minFailsafeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minFailsafeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minFailsafeTime = ch->minFailsafeTime;
	if (ch->minFailsafeTime == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMaxFailsafeTime(PhidgetDigitalOutputHandle ch, uint32_t *maxFailsafeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFailsafeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxFailsafeTime = ch->maxFailsafeTime;
	if (ch->maxFailsafeTime == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_setFrequency(PhidgetDigitalOutputHandle ch, double frequency) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFREQUENCY, NULL, NULL, 1, "%g",
	  frequency));
}

API_PRETURN
PhidgetDigitalOutput_getFrequency(PhidgetDigitalOutputHandle ch, double *frequency) {

	TESTPTR_PR(ch);
	TESTPTR_PR(frequency);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*frequency = ch->frequency;
	if (ch->frequency == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMinFrequency(PhidgetDigitalOutputHandle ch, double *minFrequency) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minFrequency);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minFrequency = ch->minFrequency;
	if (ch->minFrequency == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMaxFrequency(PhidgetDigitalOutputHandle ch, double *maxFrequency) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFrequency);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1030_DIGITALOUTPUT_100:
	case PHIDCHUID_1031_DIGITALOUTPUT_100:
	case PHIDCHUID_1032_DIGITALOUTPUT_200:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_LED1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxFrequency = ch->maxFrequency;
	if (ch->maxFrequency == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_setLEDCurrentLimit(PhidgetDigitalOutputHandle ch, double LEDCurrentLimit) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETLEDCURRENTLIMIT, NULL, NULL, 1, "%g",
	  LEDCurrentLimit));
}

API_VRETURN
PhidgetDigitalOutput_setLEDCurrentLimit_async(PhidgetDigitalOutputHandle ch, double LEDCurrentLimit,
  Phidget_AsyncCallback fptr, void *ctx) {
	PhidgetReturnCode res;

	if (ch == NULL) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}
	if (ch->phid.class != PHIDCHCLASS_DIGITALOUTPUT) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_WRONGDEVICE);
		return;
	}
	if (!ISATTACHED(ch)) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_NOTATTACHED);
		return;
	}

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETLEDCURRENTLIMIT, fptr, ctx, 1, "%g",
	  LEDCurrentLimit);
	if (res != EPHIDGET_OK && fptr != NULL)
		fptr((PhidgetHandle)ch, ctx, res);
}

API_PRETURN
PhidgetDigitalOutput_getLEDCurrentLimit(PhidgetDigitalOutputHandle ch, double *LEDCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(LEDCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_FREQ_200:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*LEDCurrentLimit = ch->LEDCurrentLimit;
	if (ch->LEDCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMinLEDCurrentLimit(PhidgetDigitalOutputHandle ch, double *minLEDCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minLEDCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_FREQ_200:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minLEDCurrentLimit = ch->minLEDCurrentLimit;
	if (ch->minLEDCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_getMaxLEDCurrentLimit(PhidgetDigitalOutputHandle ch, double *maxLEDCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxLEDCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_FREQ_200:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxLEDCurrentLimit = ch->maxLEDCurrentLimit;
	if (ch->maxLEDCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_setLEDForwardVoltage(PhidgetDigitalOutputHandle ch,
  PhidgetDigitalOutput_LEDForwardVoltage LEDForwardVoltage) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETLEDFORWARDVOLTAGE, NULL, NULL, 1, "%d",
	  LEDForwardVoltage));
}

API_PRETURN
PhidgetDigitalOutput_getLEDForwardVoltage(PhidgetDigitalOutputHandle ch,
  PhidgetDigitalOutput_LEDForwardVoltage *LEDForwardVoltage) {

	TESTPTR_PR(ch);
	TESTPTR_PR(LEDForwardVoltage);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALOUTPUT_000:
	case PHIDCHUID_1011_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_000:
	case PHIDCHUID_1012_DIGITALOUTPUT_601:
	case PHIDCHUID_1012_DIGITALOUTPUT_602:
	case PHIDCHUID_1013_DIGITALOUTPUT_000:
	case PHIDCHUID_1018_DIGITALOUTPUT_821:
	case PHIDCHUID_1014_DIGITALOUTPUT_000:
	case PHIDCHUID_1014_DIGITALOUTPUT_704:
	case PHIDCHUID_1014_DIGITALOUTPUT_710:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_USB:
	case PHIDCHUID_1014_DIGITALOUTPUT_800_VINT:
	case PHIDCHUID_1017_DIGITALOUTPUT_000:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_USB:
	case PHIDCHUID_1017_DIGITALOUTPUT_200_VINT:
	case PHIDCHUID_1018_DIGITALOUTPUT_900:
	case PHIDCHUID_1018_DIGITALOUTPUT_1000:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_200:
	case PHIDCHUID_1023_DIGITALOUTPUT_5V_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_LED_201:
	case PHIDCHUID_1023_DIGITALOUTPUT_ONBOARD_LED_201:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_100:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_300_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_310_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_USB:
	case PHIDCHUID_1024_DIGITALOUTPUT_5V_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_LED_320_VINT:
	case PHIDCHUID_1024_DIGITALOUTPUT_ONBOARD_LED_320_VINT:
	case PHIDCHUID_1202_DIGITALOUTPUT_000:
	case PHIDCHUID_1202_DIGITALOUTPUT_120:
	case PHIDCHUID_1202_DIGITALOUTPUT_300:
	case PHIDCHUID_1219_DIGITALOUTPUT_000:
	case PHIDCHUID_HUB_DIGITALOUTPUT_100:
	case PHIDCHUID_HUB_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_100:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_110:
	case PHIDCHUID_OUT1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1000_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1100_DIGITALOUTPUT_120:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_100:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_110:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_FREQ_200:
	case PHIDCHUID_REL1101_DIGITALOUTPUT_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*LEDForwardVoltage = ch->LEDForwardVoltage;
	if (ch->LEDForwardVoltage == (PhidgetDigitalOutput_LEDForwardVoltage)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalOutput_setState(PhidgetDigitalOutputHandle ch, int state) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSTATE, NULL, NULL, 1, "%d", state));
}

API_VRETURN
PhidgetDigitalOutput_setState_async(PhidgetDigitalOutputHandle ch, int state, Phidget_AsyncCallback fptr,
  void *ctx) {
	PhidgetReturnCode res;

	if (ch == NULL) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}
	if (ch->phid.class != PHIDCHCLASS_DIGITALOUTPUT) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_WRONGDEVICE);
		return;
	}
	if (!ISATTACHED(ch)) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_NOTATTACHED);
		return;
	}

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSTATE, fptr, ctx, 1, "%d", state);
	if (res != EPHIDGET_OK && fptr != NULL)
		fptr((PhidgetHandle)ch, ctx, res);
}

API_PRETURN
PhidgetDigitalOutput_getState(PhidgetDigitalOutputHandle ch, int *state) {

	TESTPTR_PR(ch);
	TESTPTR_PR(state);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALOUTPUT);
	TESTATTACHED_PR(ch);

	*state = ch->state;
	if (ch->state == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}
