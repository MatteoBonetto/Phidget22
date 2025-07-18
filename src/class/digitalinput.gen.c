/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/interfacekitdevice.h"
#include "device/encoderdevice.h"
#include "device/motorcontroldevice.h"
#include "device/stepperdevice.h"
#include "device/textlcddevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetDigitalInput_errorHandler(PhidgetChannelHandle ch,
  Phidget_ErrorEventCode code);
static void CCONV PhidgetDigitalInput_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetDigitalInput_bridgeInput(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetDigitalInput_setStatus(PhidgetChannelHandle phid,
  BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetDigitalInput_getStatus(PhidgetChannelHandle phid,
  BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetDigitalInput_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetDigitalInput_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetDigitalInput_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetDigitalInput_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetDigitalInput {
	struct _PhidgetChannel phid;
	Phidget_InputMode inputMode;
	Phidget_PowerSupply powerSupply;
	int state;
	PhidgetDigitalInput_OnStateChangeCallback StateChange;
	void *StateChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDigitalInputHandle ch;
	int nsversion;

	ch = (PhidgetDigitalInputHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 0) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 0 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "inputMode"))
		ch->inputMode = getBridgePacketInt32ByName(bp, "inputMode");
	if (hasBridgePacketByName(bp, "powerSupply"))
		ch->powerSupply = getBridgePacketInt32ByName(bp, "powerSupply");
	if (hasBridgePacketByName(bp, "state"))
		ch->state = getBridgePacketInt32ByName(bp, "state");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetDigitalInputHandle ch;

	ch = (PhidgetDigitalInputHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 4, "_class_version_=%u"
	  ",inputMode=%d"
	  ",powerSupply=%d"
	  ",state=%d"
	  ,0 /* class version */
	  ,ch->inputMode
	  ,ch->powerSupply
	  ,ch->state
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDigitalInputHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetDigitalInputHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SETINPUTMODE:
		if (!supportedInputMode(phid, (Phidget_InputMode)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified InputMode is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->inputMode = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "InputMode");
		}
		break;
	case BP_SETPOWERSUPPLY:
		if (!supportedPowerSupply(phid, (Phidget_PowerSupply)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified PowerSupply is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->powerSupply = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "PowerSupply");
		}
		break;
	case BP_STATECHANGE:
		ch->state = getBridgePacketInt32(bp, 0);
		FIRECH(ch, PhidgetDigitalInput, StateChange, ch->state);
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
	PhidgetMotorControlDeviceHandle parentMotorControl;
	PhidgetEncoderDeviceHandle parentEncoder;
	PhidgetStepperDeviceHandle parentStepper;
	PhidgetTextLCDDeviceHandle parentTextLCD;
	PhidgetVINTDeviceHandle parentVINT;
	PhidgetDigitalInputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetDigitalInputHandle)phid;

	ret = EPHIDGET_OK;

	parentInterfaceKit = (PhidgetInterfaceKitDeviceHandle)phid->parent;
	parentMotorControl = (PhidgetMotorControlDeviceHandle)phid->parent;
	parentEncoder = (PhidgetEncoderDeviceHandle)phid->parent;
	parentStepper = (PhidgetStepperDeviceHandle)phid->parent;
	parentTextLCD = (PhidgetTextLCDDeviceHandle)phid->parent;
	parentVINT = (PhidgetVINTDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1011_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1012_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1012_DIGITALINPUT_601:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1012_DIGITALINPUT_602:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1013_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1018_DIGITALINPUT_821:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1018_DIGITALINPUT_900:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1018_DIGITALINPUT_1000:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1047_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = parentEncoder->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1047_DIGITALINPUT_200:
		// Constants
		// Inputs, Settables
		ch->state = parentEncoder->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1047_DIGITALINPUT_300:
		// Constants
		// Inputs, Settables
		ch->state = parentEncoder->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1052_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentEncoder->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1052_DIGITALINPUT_101:
		// Constants
		// Inputs, Settables
		ch->state = parentEncoder->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1052_DIGITALINPUT_110:
		// Constants
		// Inputs, Settables
		ch->state = parentEncoder->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1060_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = parentMotorControl->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1063_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = parentStepper->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1065_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = parentMotorControl->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1202_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1202_DIGITALINPUT_120:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1202_DIGITALINPUT_300:
		// Constants
		// Inputs, Settables
		ch->state = parentInterfaceKit->inputState[ch->phid.index];
		break;
	case PHIDCHUID_1219_DIGITALINPUT_000:
		// Constants
		// Inputs, Settables
		ch->state = parentTextLCD->inputState[ch->phid.index];
		break;
	case PHIDCHUID_HUB_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_DAQ1200_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_DAQ1300_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_DAQ1301_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_DAQ1400_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->inputMode = parentVINT->inputModeDevProp;
		break;
	case PHIDCHUID_DAQ1400_DIGITALINPUT_120:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->inputMode = parentVINT->inputModeDevProp;
		break;
	case PHIDCHUID_DAQ1400_DIGITALINPUT_130:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		ch->powerSupply = parentVINT->powerSupplyDevProp;
		ch->inputMode = parentVINT->inputModeDevProp;
		break;
	case PHIDCHUID_HIN1101_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		break;
	case PHIDCHUID_HIN1100_DIGITALINPUT_100:
		// Constants
		// Inputs, Settables
		ch->state = PUNK_BOOL;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetDigitalInputHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetDigitalInputHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1011_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1012_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1012_DIGITALINPUT_601:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1012_DIGITALINPUT_602:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1013_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1018_DIGITALINPUT_821:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1018_DIGITALINPUT_900:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1018_DIGITALINPUT_1000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1047_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1047_DIGITALINPUT_200:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1047_DIGITALINPUT_300:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1052_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1052_DIGITALINPUT_101:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1052_DIGITALINPUT_110:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1060_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1063_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1065_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1202_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1202_DIGITALINPUT_120:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1202_DIGITALINPUT_300:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_1219_DIGITALINPUT_000:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_HUB_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DAQ1200_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DAQ1300_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DAQ1301_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_DAQ1400_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		// (Device Property - check if already set)
		if (ch->inputMode == PUNK_ENUM)
			ch->inputMode = INPUT_MODE_NPN;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETINPUTMODE, NULL, NULL, 1, "%d", ch->inputMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_DIGITALINPUT_120:
		// Reset values
		// Must-set values
		// Default values
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		// (Device Property - check if already set)
		if (ch->inputMode == PUNK_ENUM)
			ch->inputMode = INPUT_MODE_NPN;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETINPUTMODE, NULL, NULL, 1, "%d", ch->inputMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DAQ1400_DIGITALINPUT_130:
		// Reset values
		// Must-set values
		// Default values
		// (Device Property - check if already set)
		if (ch->powerSupply == PUNK_ENUM)
			ch->powerSupply = POWER_SUPPLY_12V;
		// (Device Property - check if already set)
		if (ch->inputMode == PUNK_ENUM)
			ch->inputMode = INPUT_MODE_NPN;
		ret = bridgeSendToDevice(phid, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d", ch->powerSupply);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETINPUTMODE, NULL, NULL, 1, "%d", ch->inputMode);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_HIN1101_DIGITALINPUT_100:
		// Reset values
		// Must-set values
		// Default values
		break;
	case PHIDCHUID_HIN1100_DIGITALINPUT_100:
		// Reset values
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
	PhidgetDigitalInputHandle ch;

	ch = (PhidgetDigitalInputHandle)phid;

	if(ch->state != PUNK_BOOL)
		FIRECH(ch, PhidgetDigitalInput, StateChange, ch->state);

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {
	PhidgetDigitalInputHandle ch;

	ch = (PhidgetDigitalInputHandle)phid;

	if(ch->state == PUNK_BOOL)
		return (PFALSE);

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetDigitalInput));
}

static PhidgetReturnCode CCONV
_create(PhidgetDigitalInputHandle *phidp) {

	CHANNELCREATE_BODY(DigitalInput, PHIDCHCLASS_DIGITALINPUT);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalInput_delete(PhidgetDigitalInputHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetDigitalInput_setInputMode(PhidgetDigitalInputHandle ch, Phidget_InputMode inputMode) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETINPUTMODE, NULL, NULL, 1, "%d",
	  inputMode));
}

API_PRETURN
PhidgetDigitalInput_getInputMode(PhidgetDigitalInputHandle ch, Phidget_InputMode *inputMode) {

	TESTPTR_PR(ch);
	TESTPTR_PR(inputMode);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALINPUT_000:
	case PHIDCHUID_1011_DIGITALINPUT_000:
	case PHIDCHUID_1012_DIGITALINPUT_000:
	case PHIDCHUID_1012_DIGITALINPUT_601:
	case PHIDCHUID_1012_DIGITALINPUT_602:
	case PHIDCHUID_1013_DIGITALINPUT_000:
	case PHIDCHUID_1018_DIGITALINPUT_821:
	case PHIDCHUID_1018_DIGITALINPUT_900:
	case PHIDCHUID_1018_DIGITALINPUT_1000:
	case PHIDCHUID_1047_DIGITALINPUT_100:
	case PHIDCHUID_1047_DIGITALINPUT_200:
	case PHIDCHUID_1047_DIGITALINPUT_300:
	case PHIDCHUID_1052_DIGITALINPUT_000:
	case PHIDCHUID_1052_DIGITALINPUT_101:
	case PHIDCHUID_1052_DIGITALINPUT_110:
	case PHIDCHUID_1060_DIGITALINPUT_100:
	case PHIDCHUID_1063_DIGITALINPUT_100:
	case PHIDCHUID_1065_DIGITALINPUT_100:
	case PHIDCHUID_1202_DIGITALINPUT_000:
	case PHIDCHUID_1202_DIGITALINPUT_120:
	case PHIDCHUID_1202_DIGITALINPUT_300:
	case PHIDCHUID_1219_DIGITALINPUT_000:
	case PHIDCHUID_HUB_DIGITALINPUT_100:
	case PHIDCHUID_DAQ1200_DIGITALINPUT_100:
	case PHIDCHUID_DAQ1300_DIGITALINPUT_100:
	case PHIDCHUID_DAQ1301_DIGITALINPUT_100:
	case PHIDCHUID_HIN1101_DIGITALINPUT_100:
	case PHIDCHUID_HIN1100_DIGITALINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*inputMode = ch->inputMode;
	if (ch->inputMode == (Phidget_InputMode)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalInput_setPowerSupply(PhidgetDigitalInputHandle ch, Phidget_PowerSupply powerSupply) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALINPUT);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETPOWERSUPPLY, NULL, NULL, 1, "%d",
	  powerSupply));
}

API_PRETURN
PhidgetDigitalInput_getPowerSupply(PhidgetDigitalInputHandle ch, Phidget_PowerSupply *powerSupply) {

	TESTPTR_PR(ch);
	TESTPTR_PR(powerSupply);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALINPUT);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_ifkit488_DIGITALINPUT_000:
	case PHIDCHUID_1011_DIGITALINPUT_000:
	case PHIDCHUID_1012_DIGITALINPUT_000:
	case PHIDCHUID_1012_DIGITALINPUT_601:
	case PHIDCHUID_1012_DIGITALINPUT_602:
	case PHIDCHUID_1013_DIGITALINPUT_000:
	case PHIDCHUID_1018_DIGITALINPUT_821:
	case PHIDCHUID_1018_DIGITALINPUT_900:
	case PHIDCHUID_1018_DIGITALINPUT_1000:
	case PHIDCHUID_1047_DIGITALINPUT_100:
	case PHIDCHUID_1047_DIGITALINPUT_200:
	case PHIDCHUID_1047_DIGITALINPUT_300:
	case PHIDCHUID_1052_DIGITALINPUT_000:
	case PHIDCHUID_1052_DIGITALINPUT_101:
	case PHIDCHUID_1052_DIGITALINPUT_110:
	case PHIDCHUID_1060_DIGITALINPUT_100:
	case PHIDCHUID_1063_DIGITALINPUT_100:
	case PHIDCHUID_1065_DIGITALINPUT_100:
	case PHIDCHUID_1202_DIGITALINPUT_000:
	case PHIDCHUID_1202_DIGITALINPUT_120:
	case PHIDCHUID_1202_DIGITALINPUT_300:
	case PHIDCHUID_1219_DIGITALINPUT_000:
	case PHIDCHUID_HUB_DIGITALINPUT_100:
	case PHIDCHUID_DAQ1200_DIGITALINPUT_100:
	case PHIDCHUID_DAQ1300_DIGITALINPUT_100:
	case PHIDCHUID_DAQ1301_DIGITALINPUT_100:
	case PHIDCHUID_HIN1101_DIGITALINPUT_100:
	case PHIDCHUID_HIN1100_DIGITALINPUT_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*powerSupply = ch->powerSupply;
	if (ch->powerSupply == (Phidget_PowerSupply)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalInput_getState(PhidgetDigitalInputHandle ch, int *state) {

	TESTPTR_PR(ch);
	TESTPTR_PR(state);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALINPUT);
	TESTATTACHED_PR(ch);

	*state = ch->state;
	if (ch->state == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDigitalInput_setOnStateChangeHandler(PhidgetDigitalInputHandle ch,
  PhidgetDigitalInput_OnStateChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DIGITALINPUT);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->StateChange = NULL;
		MEMORY_BARRIER();
		ch->StateChangeCtx = NULL;
	} else {
		ch->StateChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->StateChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
