/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/motorcontroldevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetDCMotor_errorHandler(PhidgetChannelHandle ch, Phidget_ErrorEventCode code);
static void CCONV PhidgetDCMotor_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetDCMotor_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetDCMotor_setStatus(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetDCMotor_getStatus(PhidgetChannelHandle phid, BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetDCMotor_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetDCMotor_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetDCMotor_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetDCMotor_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetDCMotor {
	struct _PhidgetChannel phid;
	double acceleration;
	double minAcceleration;
	double maxAcceleration;
	double activeCurrentLimit;
	double backEMF;
	int backEMFSensingState;
	double brakingStrength;
	double minBrakingStrength;
	double maxBrakingStrength;
	double currentLimit;
	double minCurrentLimit;
	double maxCurrentLimit;
	double currentRegulatorGain;
	double minCurrentRegulatorGain;
	double maxCurrentRegulatorGain;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	Phidget_DriveMode driveMode;
	int failsafeBrakingEnabled;
	double failsafeCurrentLimit;
	uint32_t minFailsafeTime;
	uint32_t maxFailsafeTime;
	Phidget_FanMode fanMode;
	double inductance;
	double minInductance;
	double maxInductance;
	double surgeCurrentLimit;
	double minSurgeCurrentLimit;
	double maxSurgeCurrentLimit;
	double targetBrakingStrength;
	double targetVelocity;
	double velocity;
	double minVelocity;
	double maxVelocity;
	PhidgetDCMotor_OnBackEMFChangeCallback BackEMFChange;
	void *BackEMFChangeCtx;
	PhidgetDCMotor_OnBrakingStrengthChangeCallback BrakingStrengthChange;
	void *BrakingStrengthChangeCtx;
	PhidgetDCMotor_OnVelocityUpdateCallback VelocityUpdate;
	void *VelocityUpdateCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDCMotorHandle ch;
	int nsversion;

	ch = (PhidgetDCMotorHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 4) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 4 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "acceleration"))
		ch->acceleration = getBridgePacketDoubleByName(bp, "acceleration");
	if (hasBridgePacketByName(bp, "minAcceleration"))
		ch->minAcceleration = getBridgePacketDoubleByName(bp, "minAcceleration");
	if (hasBridgePacketByName(bp, "maxAcceleration"))
		ch->maxAcceleration = getBridgePacketDoubleByName(bp, "maxAcceleration");
	if (hasBridgePacketByName(bp, "activeCurrentLimit"))
		ch->activeCurrentLimit = getBridgePacketDoubleByName(bp, "activeCurrentLimit");
	if (hasBridgePacketByName(bp, "backEMF"))
		ch->backEMF = getBridgePacketDoubleByName(bp, "backEMF");
	if (hasBridgePacketByName(bp, "backEMFSensingState"))
		ch->backEMFSensingState = getBridgePacketInt32ByName(bp, "backEMFSensingState");
	if (hasBridgePacketByName(bp, "brakingStrength"))
		ch->brakingStrength = getBridgePacketDoubleByName(bp, "brakingStrength");
	if (hasBridgePacketByName(bp, "minBrakingStrength"))
		ch->minBrakingStrength = getBridgePacketDoubleByName(bp, "minBrakingStrength");
	if (hasBridgePacketByName(bp, "maxBrakingStrength"))
		ch->maxBrakingStrength = getBridgePacketDoubleByName(bp, "maxBrakingStrength");
	if (hasBridgePacketByName(bp, "currentLimit"))
		ch->currentLimit = getBridgePacketDoubleByName(bp, "currentLimit");
	if (hasBridgePacketByName(bp, "minCurrentLimit"))
		ch->minCurrentLimit = getBridgePacketDoubleByName(bp, "minCurrentLimit");
	if (hasBridgePacketByName(bp, "maxCurrentLimit"))
		ch->maxCurrentLimit = getBridgePacketDoubleByName(bp, "maxCurrentLimit");
	if (hasBridgePacketByName(bp, "currentRegulatorGain"))
		ch->currentRegulatorGain = getBridgePacketDoubleByName(bp, "currentRegulatorGain");
	if (hasBridgePacketByName(bp, "minCurrentRegulatorGain"))
		ch->minCurrentRegulatorGain = getBridgePacketDoubleByName(bp, "minCurrentRegulatorGain");
	if (hasBridgePacketByName(bp, "maxCurrentRegulatorGain"))
		ch->maxCurrentRegulatorGain = getBridgePacketDoubleByName(bp, "maxCurrentRegulatorGain");
	if (hasBridgePacketByName(bp, "minDataInterval"))
		ch->minDataInterval = getBridgePacketUInt32ByName(bp, "minDataInterval");
	if (hasBridgePacketByName(bp, "maxDataInterval"))
		ch->maxDataInterval = getBridgePacketUInt32ByName(bp, "maxDataInterval");
	if (hasBridgePacketByName(bp, "dataIntervalDbl"))
		ch->dataInterval = getBridgePacketDoubleByName(bp, "dataIntervalDbl");
	else if(hasBridgePacketByName(bp, "dataInterval"))
		ch->dataInterval = (double)getBridgePacketUInt32ByName(bp, "dataInterval");
	if (hasBridgePacketByName(bp, "minDataRate"))
		ch->minDataRate = getBridgePacketDoubleByName(bp, "minDataRate");
	else if(hasBridgePacketByName(bp, "maxDataInterval"))
		ch->minDataRate = (double)(1000.0 / getBridgePacketUInt32ByName(bp, "maxDataInterval"));
	if (hasBridgePacketByName(bp, "maxDataRate"))
		ch->maxDataRate = getBridgePacketDoubleByName(bp, "maxDataRate");
	else if(hasBridgePacketByName(bp, "minDataInterval"))
		ch->maxDataRate = (double)(1000.0 / getBridgePacketUInt32ByName(bp, "minDataInterval"));
	if (hasBridgePacketByName(bp, "driveMode"))
		ch->driveMode = getBridgePacketInt32ByName(bp, "driveMode");
	if (hasBridgePacketByName(bp, "failsafeBrakingEnabled"))
		ch->failsafeBrakingEnabled = getBridgePacketInt32ByName(bp, "failsafeBrakingEnabled");
	if (hasBridgePacketByName(bp, "failsafeCurrentLimit"))
		ch->failsafeCurrentLimit = getBridgePacketDoubleByName(bp, "failsafeCurrentLimit");
	if (hasBridgePacketByName(bp, "minFailsafeTime"))
		ch->minFailsafeTime = getBridgePacketUInt32ByName(bp, "minFailsafeTime");
	if (hasBridgePacketByName(bp, "maxFailsafeTime"))
		ch->maxFailsafeTime = getBridgePacketUInt32ByName(bp, "maxFailsafeTime");
	if (hasBridgePacketByName(bp, "fanMode"))
		ch->fanMode = getBridgePacketInt32ByName(bp, "fanMode");
	if (hasBridgePacketByName(bp, "inductance"))
		ch->inductance = getBridgePacketDoubleByName(bp, "inductance");
	if (hasBridgePacketByName(bp, "minInductance"))
		ch->minInductance = getBridgePacketDoubleByName(bp, "minInductance");
	if (hasBridgePacketByName(bp, "maxInductance"))
		ch->maxInductance = getBridgePacketDoubleByName(bp, "maxInductance");
	if (hasBridgePacketByName(bp, "surgeCurrentLimit"))
		ch->surgeCurrentLimit = getBridgePacketDoubleByName(bp, "surgeCurrentLimit");
	if (hasBridgePacketByName(bp, "minSurgeCurrentLimit"))
		ch->minSurgeCurrentLimit = getBridgePacketDoubleByName(bp, "minSurgeCurrentLimit");
	if (hasBridgePacketByName(bp, "maxSurgeCurrentLimit"))
		ch->maxSurgeCurrentLimit = getBridgePacketDoubleByName(bp, "maxSurgeCurrentLimit");
	if (hasBridgePacketByName(bp, "targetBrakingStrength"))
		ch->targetBrakingStrength = getBridgePacketDoubleByName(bp, "targetBrakingStrength");
	if (hasBridgePacketByName(bp, "targetVelocity"))
		ch->targetVelocity = getBridgePacketDoubleByName(bp, "targetVelocity");
	if (hasBridgePacketByName(bp, "velocity"))
		ch->velocity = getBridgePacketDoubleByName(bp, "velocity");
	if (hasBridgePacketByName(bp, "minVelocity"))
		ch->minVelocity = getBridgePacketDoubleByName(bp, "minVelocity");
	if (hasBridgePacketByName(bp, "maxVelocity"))
		ch->maxVelocity = getBridgePacketDoubleByName(bp, "maxVelocity");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetDCMotorHandle ch;

	ch = (PhidgetDCMotorHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 39, "_class_version_=%u"
	  ",acceleration=%g"
	  ",minAcceleration=%g"
	  ",maxAcceleration=%g"
	  ",activeCurrentLimit=%g"
	  ",backEMF=%g"
	  ",backEMFSensingState=%d"
	  ",brakingStrength=%g"
	  ",minBrakingStrength=%g"
	  ",maxBrakingStrength=%g"
	  ",currentLimit=%g"
	  ",minCurrentLimit=%g"
	  ",maxCurrentLimit=%g"
	  ",currentRegulatorGain=%g"
	  ",minCurrentRegulatorGain=%g"
	  ",maxCurrentRegulatorGain=%g"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",driveMode=%d"
	  ",failsafeBrakingEnabled=%d"
	  ",failsafeCurrentLimit=%g"
	  ",minFailsafeTime=%u"
	  ",maxFailsafeTime=%u"
	  ",fanMode=%d"
	  ",inductance=%g"
	  ",minInductance=%g"
	  ",maxInductance=%g"
	  ",surgeCurrentLimit=%g"
	  ",minSurgeCurrentLimit=%g"
	  ",maxSurgeCurrentLimit=%g"
	  ",targetBrakingStrength=%g"
	  ",targetVelocity=%g"
	  ",velocity=%g"
	  ",minVelocity=%g"
	  ",maxVelocity=%g"
	  ,4 /* class version */
	  ,ch->acceleration
	  ,ch->minAcceleration
	  ,ch->maxAcceleration
	  ,ch->activeCurrentLimit
	  ,ch->backEMF
	  ,ch->backEMFSensingState
	  ,ch->brakingStrength
	  ,ch->minBrakingStrength
	  ,ch->maxBrakingStrength
	  ,ch->currentLimit
	  ,ch->minCurrentLimit
	  ,ch->maxCurrentLimit
	  ,ch->currentRegulatorGain
	  ,ch->minCurrentRegulatorGain
	  ,ch->maxCurrentRegulatorGain
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->driveMode
	  ,ch->failsafeBrakingEnabled
	  ,ch->failsafeCurrentLimit
	  ,ch->minFailsafeTime
	  ,ch->maxFailsafeTime
	  ,ch->fanMode
	  ,ch->inductance
	  ,ch->minInductance
	  ,ch->maxInductance
	  ,ch->surgeCurrentLimit
	  ,ch->minSurgeCurrentLimit
	  ,ch->maxSurgeCurrentLimit
	  ,ch->targetBrakingStrength
	  ,ch->targetVelocity
	  ,ch->velocity
	  ,ch->minVelocity
	  ,ch->maxVelocity
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDCMotorHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetDCMotorHandle)phid;
	res = EPHIDGET_OK;

	switch (bp->vpkt) {
	case BP_SETFAILSAFETIME:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_FAILSAFERESET:
		res = DEVBRIDGEINPUT(phid, bp);
		break;
	case BP_SETACCELERATION:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minAcceleration,
		  ch->maxAcceleration);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->acceleration = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Acceleration");
		}
		break;
	case BP_SETBACKEMFSENSINGSTATE:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->backEMFSensingState = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "BackEMFSensingState");
		}
		break;
	case BP_SETCURRENTLIMIT:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minCurrentLimit,
		  ch->maxCurrentLimit);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->currentLimit = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "CurrentLimit");
		}
		break;
	case BP_SETCURRENTREGULATORGAIN:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minCurrentRegulatorGain,
		  ch->maxCurrentRegulatorGain);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->currentRegulatorGain = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "CurrentRegulatorGain");
		}
		break;
	case BP_SETDATAINTERVAL:
		if (bp->entrycnt > 1)
			TESTRANGE_IOP(bp->iop, "%lf", round_double((1000.0 / getBridgePacketDouble(bp, 1)), 4),
			  ch->minDataRate, ch->maxDataRate);
		else
			TESTRANGE_IOP(bp->iop, "%"PRIu32, getBridgePacketUInt32(bp, 0), ch->minDataInterval,
			  ch->maxDataInterval);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		if (bp->entrycnt > 1)
			ch->dataInterval = getBridgePacketDouble(bp, 1);
		else
			ch->dataInterval = (double)getBridgePacketUInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "DataInterval");
			FIRE_PROPERTYCHANGE(ch, "DataRate");
		}
		break;
	case BP_DRIVEMODE:
		if (!supportedDriveMode(phid, (Phidget_DriveMode)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified DriveMode is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->driveMode = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "DriveMode");
		}
		break;
	case BP_SETFAILSAFEBRAKINGDUTYCYCLE:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->failsafeBrakingEnabled = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "FailsafeBrakingEnabled");
		}
		break;
	case BP_SETFAILSAFECURRENTLIMIT:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->failsafeCurrentLimit = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "FailsafeCurrentLimit");
		}
		break;
	case BP_SETFANMODE:
		if (!supportedFanMode(phid, (Phidget_FanMode)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified FanMode is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->fanMode = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "FanMode");
		}
		break;
	case BP_SETINDUCTANCE:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minInductance,
		  ch->maxInductance);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->inductance = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Inductance");
		}
		break;
	case BP_SETSURGECURRENTLIMIT:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minSurgeCurrentLimit,
		  ch->maxSurgeCurrentLimit);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->surgeCurrentLimit = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "SurgeCurrentLimit");
		}
		break;
	case BP_SETBRAKINGDUTYCYCLE:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->targetBrakingStrength = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "TargetBrakingStrength");
		}
		break;
	case BP_SETDUTYCYCLE:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->targetVelocity = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "TargetVelocity");
		}
		break;
	case BP_BACKEMFCHANGE:
		ch->backEMF = getBridgePacketDouble(bp, 0);
		FIRECH(ch, PhidgetDCMotor, BackEMFChange, ch->backEMF);
		break;
	case BP_BRAKINGSTRENGTHCHANGE:
		ch->brakingStrength = getBridgePacketDouble(bp, 0);
		FIRECH(ch, PhidgetDCMotor, BrakingStrengthChange, ch->brakingStrength);
		break;
	case BP_DUTYCYCLECHANGE:
		ch->velocity = getBridgePacketDouble(bp, 0);
		FIRECH(ch, PhidgetDCMotor, VelocityUpdate, ch->velocity);
		break;
	default:
		logerr("%"PRIphid": unsupported bridge packet:0x%x", phid, bp->vpkt);
		res = EPHIDGET_UNSUPPORTED;
	}

	return (res);
}

static PhidgetReturnCode CCONV
_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetMotorControlDeviceHandle parentMotorControl;
	PhidgetDCMotorHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetDCMotorHandle)phid;

	ret = EPHIDGET_OK;

	parentMotorControl = (PhidgetMotorControlDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 64;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 15.625;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 12.45;
		ch->minAcceleration = 0.0122;
		ch->targetBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->dcMotorDataInterval[ch->phid.index];
		ch->targetVelocity = parentMotorControl->targetVelocity[ch->phid.index];
		ch->acceleration = parentMotorControl->acceleration[ch->phid.index];
		ch->velocity = parentMotorControl->dutyCycle[ch->phid.index];
		break;
	case PHIDCHUID_1064_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 32;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 19.4;
		ch->minAcceleration = 0.019;
		ch->targetBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->dcMotorDataInterval[ch->phid.index];
		ch->targetVelocity = parentMotorControl->targetVelocity[ch->phid.index];
		ch->acceleration = parentMotorControl->acceleration[ch->phid.index];
		ch->velocity = parentMotorControl->dutyCycle[ch->phid.index];
		break;
	case PHIDCHUID_1065_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 8;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 125;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 62.5;
		ch->minAcceleration = 0.2778;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = parentMotorControl->dcMotorDataInterval[ch->phid.index];
		ch->targetVelocity = parentMotorControl->targetVelocity[ch->phid.index];
		ch->acceleration = parentMotorControl->acceleration[ch->phid.index];
		ch->targetBrakingStrength = parentMotorControl->targetBrakingStrength[ch->phid.index];
		ch->backEMFSensingState = parentMotorControl->backEMFSensingState[ch->phid.index];
		ch->backEMF = parentMotorControl->backEMF[ch->phid.index];
		ch->velocity = parentMotorControl->dutyCycle[ch->phid.index];
		break;
	case PHIDCHUID_DCC1000_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 25;
		ch->minCurrentLimit = 2;
		ch->maxCurrentRegulatorGain = 100;
		ch->minCurrentRegulatorGain = 1;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->currentRegulatorGain = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->fanMode = PUNK_ENUM;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_DCMOTOR_200:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 25;
		ch->minCurrentLimit = 2;
		ch->maxCurrentRegulatorGain = 100;
		ch->minCurrentRegulatorGain = 1;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->currentRegulatorGain = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->fanMode = PUNK_ENUM;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1000_DCMOTOR_210:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 25;
		ch->minCurrentLimit = 2;
		ch->maxCurrentRegulatorGain = 100;
		ch->minCurrentRegulatorGain = 1;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->currentRegulatorGain = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->fanMode = PUNK_ENUM;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1020_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 10;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 100;
		ch->maxSurgeCurrentLimit = 75;
		ch->minSurgeCurrentLimit = 5;
		ch->maxCurrentLimit = 50;
		ch->minCurrentLimit = 5;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 1000;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		ch->maxInductance = 0.01;
		ch->minInductance = 0.0001;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->surgeCurrentLimit = PUNK_DBL;
		ch->activeCurrentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->failsafeCurrentLimit = PUNK_DBL;
		ch->failsafeBrakingEnabled = PUNK_BOOL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		ch->inductance = PUNK_DBL;
		ch->driveMode = PUNK_ENUM;
		break;
	case PHIDCHUID_DCC1001_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 2;
		ch->minCurrentLimit = 0;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1001_DCMOTOR_120:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 2;
		ch->minCurrentLimit = 0;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1002_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 4;
		ch->minCurrentLimit = 0;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1002_DCMOTOR_110:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 4;
		ch->minCurrentLimit = 0;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1003_DCMOTOR_100:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 4;
		ch->minCurrentLimit = 0;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		// Constants
		ch->minDataInterval = 100;
		ch->maxDataInterval = 60000;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 10;
		ch->maxCurrentLimit = 4;
		ch->minCurrentLimit = 0;
		ch->maxVelocity = 1;
		ch->minVelocity = 0;
		ch->maxAcceleration = 100;
		ch->minAcceleration = 0.1;
		ch->maxBrakingStrength = 1;
		ch->minBrakingStrength = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->dataInterval = PUNK_UINT32;
		ch->currentLimit = PUNK_DBL;
		ch->targetVelocity = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->targetBrakingStrength = PUNK_DBL;
		ch->velocity = PUNK_DBL;
		ch->brakingStrength = PUNK_DBL;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetDCMotorHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetDCMotorHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
		// Reset values
		ch->targetVelocity = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->acceleration = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1064_DCMOTOR_100:
		// Reset values
		ch->targetVelocity = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->acceleration = 1;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1065_DCMOTOR_100:
		// Reset values
		ch->targetVelocity = 0;
		// Must-set values
		// Default values
		ch->dataInterval = 256;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ch->backEMFSensingState = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBACKEMFSENSINGSTATE, NULL, NULL, 1, "%d",
		  ch->backEMFSensingState);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_DCMOTOR_100:
		// Reset values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->currentRegulatorGain = 10;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ch->fanMode = FAN_MODE_AUTO;
		// Must-set values
		// Default values
		ch->targetVelocity = 0;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_DCMOTOR_200:
		// Reset values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->currentRegulatorGain = 10;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ch->fanMode = FAN_MODE_AUTO;
		// Must-set values
		// Default values
		ch->targetVelocity = 0;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1000_DCMOTOR_210:
		// Reset values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->currentRegulatorGain = 10;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ch->fanMode = FAN_MODE_AUTO;
		// Must-set values
		// Default values
		ch->targetVelocity = 0;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1020_DCMOTOR_100:
		// Reset values
		ch->surgeCurrentLimit = 5;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ch->failsafeCurrentLimit = 5;
		ch->failsafeBrakingEnabled = 0;
		ch->driveMode = DRIVE_MODE_COAST;
		// Must-set values
		// Default values
		ch->dataInterval = 100;
		ch->currentLimit = 5;
		ch->targetVelocity = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1001_DCMOTOR_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->targetVelocity = 0;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1001_DCMOTOR_120:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->targetVelocity = 0;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1002_DCMOTOR_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->targetVelocity = 0;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1002_DCMOTOR_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->targetVelocity = 0;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1003_DCMOTOR_100:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->targetVelocity = 0;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		// Reset values
		// Must-set values
		// Default values
		ch->dataInterval = 250;
		ch->currentLimit = 2;
		ch->targetVelocity = 0;
		ch->acceleration = 1;
		ch->targetBrakingStrength = 0;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g", ch->currentLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g", ch->targetVelocity);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
		  ch->targetBrakingStrength);
		if (ret != EPHIDGET_OK)
			break;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}

	return (ret);
}

static void CCONV
_fireInitialEvents(PhidgetChannelHandle phid) {
	PhidgetDCMotorHandle ch;

	ch = (PhidgetDCMotorHandle)phid;

	if(ch->backEMF != PUNK_DBL)
		FIRECH(ch, PhidgetDCMotor, BackEMFChange, ch->backEMF);
	if(ch->brakingStrength != PUNK_DBL)
		FIRECH(ch, PhidgetDCMotor, BrakingStrengthChange, ch->brakingStrength);
	if(ch->velocity != PUNK_DBL)
		FIRECH(ch, PhidgetDCMotor, VelocityUpdate, ch->velocity);

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {
	PhidgetDCMotorHandle ch;

	ch = (PhidgetDCMotorHandle)phid;

	if(ch->backEMF == PUNK_DBL)
		return (PFALSE);
	if(ch->brakingStrength == PUNK_DBL)
		return (PFALSE);
	if(ch->velocity == PUNK_DBL)
		return (PFALSE);

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetDCMotor));
}

static PhidgetReturnCode CCONV
_create(PhidgetDCMotorHandle *phidp) {

	CHANNELCREATE_BODY(DCMotor, PHIDCHCLASS_DCMOTOR);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_delete(PhidgetDCMotorHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetDCMotor_enableFailsafe(PhidgetDCMotorHandle ch, uint32_t failsafeTime) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFAILSAFETIME, NULL, NULL, 1, "%u",
	  failsafeTime); 
}

API_PRETURN
PhidgetDCMotor_resetFailsafe(PhidgetDCMotorHandle ch) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_FAILSAFERESET, NULL, NULL, 0, NULL); 
}

API_PRETURN
PhidgetDCMotor_setAcceleration(PhidgetDCMotorHandle ch, double acceleration) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETACCELERATION, NULL, NULL, 1, "%g",
	  acceleration));
}

API_PRETURN
PhidgetDCMotor_getAcceleration(PhidgetDCMotorHandle ch, double *acceleration) {

	TESTPTR_PR(ch);
	TESTPTR_PR(acceleration);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*acceleration = ch->acceleration;
	if (ch->acceleration == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinAcceleration(PhidgetDCMotorHandle ch, double *minAcceleration) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minAcceleration);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*minAcceleration = ch->minAcceleration;
	if (ch->minAcceleration == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxAcceleration(PhidgetDCMotorHandle ch, double *maxAcceleration) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxAcceleration);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*maxAcceleration = ch->maxAcceleration;
	if (ch->maxAcceleration == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getActiveCurrentLimit(PhidgetDCMotorHandle ch, double *activeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(activeCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*activeCurrentLimit = ch->activeCurrentLimit;
	if (ch->activeCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getBackEMF(PhidgetDCMotorHandle ch, double *backEMF) {

	TESTPTR_PR(ch);
	TESTPTR_PR(backEMF);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1020_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*backEMF = ch->backEMF;
	if (ch->backEMF == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setBackEMFSensingState(PhidgetDCMotorHandle ch, int backEMFSensingState) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETBACKEMFSENSINGSTATE, NULL, NULL, 1, "%d",
	  backEMFSensingState));
}

API_PRETURN
PhidgetDCMotor_getBackEMFSensingState(PhidgetDCMotorHandle ch, int *backEMFSensingState) {

	TESTPTR_PR(ch);
	TESTPTR_PR(backEMFSensingState);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1020_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*backEMFSensingState = ch->backEMFSensingState;
	if (ch->backEMFSensingState == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getBrakingStrength(PhidgetDCMotorHandle ch, double *brakingStrength) {

	TESTPTR_PR(ch);
	TESTPTR_PR(brakingStrength);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*brakingStrength = ch->brakingStrength;
	if (ch->brakingStrength == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinBrakingStrength(PhidgetDCMotorHandle ch, double *minBrakingStrength) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minBrakingStrength);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minBrakingStrength = ch->minBrakingStrength;
	if (ch->minBrakingStrength == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxBrakingStrength(PhidgetDCMotorHandle ch, double *maxBrakingStrength) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxBrakingStrength);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxBrakingStrength = ch->maxBrakingStrength;
	if (ch->maxBrakingStrength == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setCurrentLimit(PhidgetDCMotorHandle ch, double currentLimit) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETCURRENTLIMIT, NULL, NULL, 1, "%g",
	  currentLimit));
}

API_PRETURN
PhidgetDCMotor_getCurrentLimit(PhidgetDCMotorHandle ch, double *currentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(currentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*currentLimit = ch->currentLimit;
	if (ch->currentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinCurrentLimit(PhidgetDCMotorHandle ch, double *minCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minCurrentLimit = ch->minCurrentLimit;
	if (ch->minCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxCurrentLimit(PhidgetDCMotorHandle ch, double *maxCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxCurrentLimit = ch->maxCurrentLimit;
	if (ch->maxCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setCurrentRegulatorGain(PhidgetDCMotorHandle ch, double currentRegulatorGain) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETCURRENTREGULATORGAIN, NULL, NULL, 1, "%g",
	  currentRegulatorGain));
}

API_PRETURN
PhidgetDCMotor_getCurrentRegulatorGain(PhidgetDCMotorHandle ch, double *currentRegulatorGain) {

	TESTPTR_PR(ch);
	TESTPTR_PR(currentRegulatorGain);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1020_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*currentRegulatorGain = ch->currentRegulatorGain;
	if (ch->currentRegulatorGain == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinCurrentRegulatorGain(PhidgetDCMotorHandle ch, double *minCurrentRegulatorGain) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minCurrentRegulatorGain);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1020_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minCurrentRegulatorGain = ch->minCurrentRegulatorGain;
	if (ch->minCurrentRegulatorGain == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxCurrentRegulatorGain(PhidgetDCMotorHandle ch, double *maxCurrentRegulatorGain) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxCurrentRegulatorGain);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1020_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxCurrentRegulatorGain = ch->maxCurrentRegulatorGain;
	if (ch->maxCurrentRegulatorGain == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setDataInterval(PhidgetDCMotorHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetDCMotor_getDataInterval(PhidgetDCMotorHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinDataInterval(PhidgetDCMotorHandle ch, uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxDataInterval(PhidgetDCMotorHandle ch, uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setDataRate(PhidgetDCMotorHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetDCMotor_getDataRate(PhidgetDCMotorHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinDataRate(PhidgetDCMotorHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxDataRate(PhidgetDCMotorHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setDriveMode(PhidgetDCMotorHandle ch, Phidget_DriveMode driveMode) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_DRIVEMODE, NULL, NULL, 1, "%d",
	  driveMode));
}

API_PRETURN
PhidgetDCMotor_getDriveMode(PhidgetDCMotorHandle ch, Phidget_DriveMode *driveMode) {

	TESTPTR_PR(ch);
	TESTPTR_PR(driveMode);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*driveMode = ch->driveMode;
	if (ch->driveMode == (Phidget_DriveMode)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setFailsafeBrakingEnabled(PhidgetDCMotorHandle ch, int failsafeBrakingEnabled) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFAILSAFEBRAKINGDUTYCYCLE, NULL, NULL, 1,
	  "%d", failsafeBrakingEnabled));
}

API_PRETURN
PhidgetDCMotor_getFailsafeBrakingEnabled(PhidgetDCMotorHandle ch, int *failsafeBrakingEnabled) {

	TESTPTR_PR(ch);
	TESTPTR_PR(failsafeBrakingEnabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*failsafeBrakingEnabled = ch->failsafeBrakingEnabled;
	if (ch->failsafeBrakingEnabled == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setFailsafeCurrentLimit(PhidgetDCMotorHandle ch, double failsafeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFAILSAFECURRENTLIMIT, NULL, NULL, 1, "%g",
	  failsafeCurrentLimit));
}

API_PRETURN
PhidgetDCMotor_getFailsafeCurrentLimit(PhidgetDCMotorHandle ch, double *failsafeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(failsafeCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*failsafeCurrentLimit = ch->failsafeCurrentLimit;
	if (ch->failsafeCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinFailsafeTime(PhidgetDCMotorHandle ch, uint32_t *minFailsafeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minFailsafeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
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
PhidgetDCMotor_getMaxFailsafeTime(PhidgetDCMotorHandle ch, uint32_t *maxFailsafeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFailsafeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
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
PhidgetDCMotor_setFanMode(PhidgetDCMotorHandle ch, Phidget_FanMode fanMode) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFANMODE, NULL, NULL, 1, "%d", fanMode));
}

API_PRETURN
PhidgetDCMotor_getFanMode(PhidgetDCMotorHandle ch, Phidget_FanMode *fanMode) {

	TESTPTR_PR(ch);
	TESTPTR_PR(fanMode);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1020_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*fanMode = ch->fanMode;
	if (ch->fanMode == (Phidget_FanMode)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setInductance(PhidgetDCMotorHandle ch, double inductance) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETINDUCTANCE, NULL, NULL, 1, "%g",
	  inductance));
}

API_PRETURN
PhidgetDCMotor_getInductance(PhidgetDCMotorHandle ch, double *inductance) {

	TESTPTR_PR(ch);
	TESTPTR_PR(inductance);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*inductance = ch->inductance;
	if (ch->inductance == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinInductance(PhidgetDCMotorHandle ch, double *minInductance) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minInductance);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minInductance = ch->minInductance;
	if (ch->minInductance == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxInductance(PhidgetDCMotorHandle ch, double *maxInductance) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxInductance);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxInductance = ch->maxInductance;
	if (ch->maxInductance == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setSurgeCurrentLimit(PhidgetDCMotorHandle ch, double surgeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSURGECURRENTLIMIT, NULL, NULL, 1, "%g",
	  surgeCurrentLimit));
}

API_PRETURN
PhidgetDCMotor_getSurgeCurrentLimit(PhidgetDCMotorHandle ch, double *surgeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(surgeCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*surgeCurrentLimit = ch->surgeCurrentLimit;
	if (ch->surgeCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinSurgeCurrentLimit(PhidgetDCMotorHandle ch, double *minSurgeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minSurgeCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minSurgeCurrentLimit = ch->minSurgeCurrentLimit;
	if (ch->minSurgeCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxSurgeCurrentLimit(PhidgetDCMotorHandle ch, double *maxSurgeCurrentLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxSurgeCurrentLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1060_DCMOTOR_100:
	case PHIDCHUID_1064_DCMOTOR_100:
	case PHIDCHUID_1065_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_100:
	case PHIDCHUID_DCC1000_DCMOTOR_200:
	case PHIDCHUID_DCC1000_DCMOTOR_210:
	case PHIDCHUID_DCC1001_DCMOTOR_100:
	case PHIDCHUID_DCC1001_DCMOTOR_120:
	case PHIDCHUID_DCC1002_DCMOTOR_100:
	case PHIDCHUID_DCC1002_DCMOTOR_110:
	case PHIDCHUID_DCC1003_DCMOTOR_100:
	case PHIDCHUID_DCC1003_DCMOTOR_110:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxSurgeCurrentLimit = ch->maxSurgeCurrentLimit;
	if (ch->maxSurgeCurrentLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setTargetBrakingStrength(PhidgetDCMotorHandle ch, double targetBrakingStrength) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETBRAKINGDUTYCYCLE, NULL, NULL, 1, "%g",
	  targetBrakingStrength));
}

API_PRETURN
PhidgetDCMotor_getTargetBrakingStrength(PhidgetDCMotorHandle ch, double *targetBrakingStrength) {

	TESTPTR_PR(ch);
	TESTPTR_PR(targetBrakingStrength);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*targetBrakingStrength = ch->targetBrakingStrength;
	if (ch->targetBrakingStrength == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setTargetVelocity(PhidgetDCMotorHandle ch, double targetVelocity) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g",
	  targetVelocity));
}

API_VRETURN
PhidgetDCMotor_setTargetVelocity_async(PhidgetDCMotorHandle ch, double targetVelocity,
  Phidget_AsyncCallback fptr, void *ctx) {
	PhidgetReturnCode res;

	if (ch == NULL) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}
	if (ch->phid.class != PHIDCHCLASS_DCMOTOR) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_WRONGDEVICE);
		return;
	}
	if (!ISATTACHED(ch)) {
		if (fptr) fptr((PhidgetHandle)ch, ctx, EPHIDGET_NOTATTACHED);
		return;
	}

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDUTYCYCLE, fptr, ctx, 1, "%g",
	  targetVelocity);
	if (res != EPHIDGET_OK && fptr != NULL)
		fptr((PhidgetHandle)ch, ctx, res);
}

API_PRETURN
PhidgetDCMotor_getTargetVelocity(PhidgetDCMotorHandle ch, double *targetVelocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(targetVelocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*targetVelocity = ch->targetVelocity;
	if (ch->targetVelocity == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getVelocity(PhidgetDCMotorHandle ch, double *velocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(velocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*velocity = ch->velocity;
	if (ch->velocity == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMinVelocity(PhidgetDCMotorHandle ch, double *minVelocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minVelocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*minVelocity = ch->minVelocity;
	if (ch->minVelocity == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_getMaxVelocity(PhidgetDCMotorHandle ch, double *maxVelocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxVelocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);
	TESTATTACHED_PR(ch);

	*maxVelocity = ch->maxVelocity;
	if (ch->maxVelocity == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setOnBackEMFChangeHandler(PhidgetDCMotorHandle ch,
  PhidgetDCMotor_OnBackEMFChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->BackEMFChange = NULL;
		MEMORY_BARRIER();
		ch->BackEMFChangeCtx = NULL;
	} else {
		ch->BackEMFChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->BackEMFChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setOnBrakingStrengthChangeHandler(PhidgetDCMotorHandle ch,
  PhidgetDCMotor_OnBrakingStrengthChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->BrakingStrengthChange = NULL;
		MEMORY_BARRIER();
		ch->BrakingStrengthChangeCtx = NULL;
	} else {
		ch->BrakingStrengthChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->BrakingStrengthChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetDCMotor_setOnVelocityUpdateHandler(PhidgetDCMotorHandle ch,
  PhidgetDCMotor_OnVelocityUpdateCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DCMOTOR);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->VelocityUpdate = NULL;
		MEMORY_BARRIER();
		ch->VelocityUpdateCtx = NULL;
	} else {
		ch->VelocityUpdateCtx = ctx;
		MEMORY_BARRIER();
		ch->VelocityUpdate = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
