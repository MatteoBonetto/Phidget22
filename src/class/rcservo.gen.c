/* Generated: Mon Jul 14 2025 12:40:24 GMT-0600 (Mountain Daylight Time) */

#include "device/servodevice.h"
#include "device/advancedservodevice.h"
#include "device/vintdevice.h"
static void CCONV PhidgetRCServo_errorHandler(PhidgetChannelHandle ch, Phidget_ErrorEventCode code);
static void CCONV PhidgetRCServo_free(PhidgetChannelHandle *ch);
static PhidgetReturnCode CCONV PhidgetRCServo_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetRCServo_setStatus(PhidgetChannelHandle phid, BridgePacket *bp);
static PhidgetReturnCode CCONV PhidgetRCServo_getStatus(PhidgetChannelHandle phid, BridgePacket **bp);
static PhidgetReturnCode CCONV PhidgetRCServo_initAfterOpen(PhidgetChannelHandle phid);
static PhidgetReturnCode CCONV PhidgetRCServo_setDefaults(PhidgetChannelHandle phid);
static void CCONV PhidgetRCServo_fireInitialEvents(PhidgetChannelHandle phid);
static int CCONV PhidgetRCServo_hasInitialState(PhidgetChannelHandle phid);

struct _PhidgetRCServo {
	struct _PhidgetChannel phid;
	double acceleration;
	double minAcceleration;
	double maxAcceleration;
	double dataInterval;
	uint32_t minDataInterval;
	uint32_t maxDataInterval;
	double minDataRate;
	double maxDataRate;
	int engaged;
	uint32_t minFailsafeTime;
	uint32_t maxFailsafeTime;
	int isMoving;
	double position;
	double minPosition;
	double maxPosition;
	double minPulseWidth;
	double maxPulseWidth;
	double minPulseWidthLimit;
	double maxPulseWidthLimit;
	int speedRampingState;
	double targetPosition;
	double torque;
	double minTorque;
	double maxTorque;
	double velocity;
	double velocityLimit;
	double minVelocityLimit;
	double maxVelocityLimit;
	PhidgetRCServo_Voltage voltage;
	PhidgetRCServo_OnPositionChangeCallback PositionChange;
	void *PositionChangeCtx;
	PhidgetRCServo_OnTargetPositionReachedCallback TargetPositionReached;
	void *TargetPositionReachedCtx;
	PhidgetRCServo_OnVelocityChangeCallback VelocityChange;
	void *VelocityChangeCtx;
};

static PhidgetReturnCode CCONV
_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRCServoHandle ch;
	int nsversion;

	ch = (PhidgetRCServoHandle)phid;

	nsversion = getBridgePacketUInt32ByName(bp, "_class_version_");
	if (nsversion != 5) {
		loginfo("%"PRIphid": server/client class version mismatch: %d != 5 - functionality may be limited.", phid, nsversion);
	}

	if (hasBridgePacketByName(bp, "acceleration"))
		ch->acceleration = getBridgePacketDoubleByName(bp, "acceleration");
	if (hasBridgePacketByName(bp, "minAcceleration"))
		ch->minAcceleration = getBridgePacketDoubleByName(bp, "minAcceleration");
	if (hasBridgePacketByName(bp, "maxAcceleration"))
		ch->maxAcceleration = getBridgePacketDoubleByName(bp, "maxAcceleration");
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
	if (hasBridgePacketByName(bp, "engaged"))
		ch->engaged = getBridgePacketInt32ByName(bp, "engaged");
	if (hasBridgePacketByName(bp, "minFailsafeTime"))
		ch->minFailsafeTime = getBridgePacketUInt32ByName(bp, "minFailsafeTime");
	if (hasBridgePacketByName(bp, "maxFailsafeTime"))
		ch->maxFailsafeTime = getBridgePacketUInt32ByName(bp, "maxFailsafeTime");
	if (hasBridgePacketByName(bp, "isMoving"))
		ch->isMoving = getBridgePacketInt32ByName(bp, "isMoving");
	if (hasBridgePacketByName(bp, "position"))
		ch->position = getBridgePacketDoubleByName(bp, "position");
	if (hasBridgePacketByName(bp, "minPosition"))
		ch->minPosition = getBridgePacketDoubleByName(bp, "minPosition");
	if (hasBridgePacketByName(bp, "maxPosition"))
		ch->maxPosition = getBridgePacketDoubleByName(bp, "maxPosition");
	if (hasBridgePacketByName(bp, "minPulseWidth"))
		ch->minPulseWidth = getBridgePacketDoubleByName(bp, "minPulseWidth");
	if (hasBridgePacketByName(bp, "maxPulseWidth"))
		ch->maxPulseWidth = getBridgePacketDoubleByName(bp, "maxPulseWidth");
	if (hasBridgePacketByName(bp, "minPulseWidthLimit"))
		ch->minPulseWidthLimit = getBridgePacketDoubleByName(bp, "minPulseWidthLimit");
	if (hasBridgePacketByName(bp, "maxPulseWidthLimit"))
		ch->maxPulseWidthLimit = getBridgePacketDoubleByName(bp, "maxPulseWidthLimit");
	if (hasBridgePacketByName(bp, "speedRampingState"))
		ch->speedRampingState = getBridgePacketInt32ByName(bp, "speedRampingState");
	if (hasBridgePacketByName(bp, "targetPosition"))
		ch->targetPosition = getBridgePacketDoubleByName(bp, "targetPosition");
	if (hasBridgePacketByName(bp, "torque"))
		ch->torque = getBridgePacketDoubleByName(bp, "torque");
	if (hasBridgePacketByName(bp, "minTorque"))
		ch->minTorque = getBridgePacketDoubleByName(bp, "minTorque");
	if (hasBridgePacketByName(bp, "maxTorque"))
		ch->maxTorque = getBridgePacketDoubleByName(bp, "maxTorque");
	if (hasBridgePacketByName(bp, "velocity"))
		ch->velocity = getBridgePacketDoubleByName(bp, "velocity");
	if (hasBridgePacketByName(bp, "velocityLimit"))
		ch->velocityLimit = getBridgePacketDoubleByName(bp, "velocityLimit");
	if (hasBridgePacketByName(bp, "minVelocityLimit"))
		ch->minVelocityLimit = getBridgePacketDoubleByName(bp, "minVelocityLimit");
	if (hasBridgePacketByName(bp, "maxVelocityLimit"))
		ch->maxVelocityLimit = getBridgePacketDoubleByName(bp, "maxVelocityLimit");
	if (hasBridgePacketByName(bp, "voltage"))
		ch->voltage = getBridgePacketInt32ByName(bp, "voltage");

	return (EPHIDGET_OK);
}

static PhidgetReturnCode CCONV
_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	PhidgetRCServoHandle ch;

	ch = (PhidgetRCServoHandle)phid;

	return (createBridgePacket(bp, BP_SETSTATUS, 31, "_class_version_=%u"
	  ",acceleration=%g"
	  ",minAcceleration=%g"
	  ",maxAcceleration=%g"
	  ",dataInterval=%u"
	  ",minDataInterval=%u"
	  ",maxDataInterval=%u"
	  ",dataIntervalDbl=%g"
	  ",minDataRate=%g"
	  ",maxDataRate=%g"
	  ",engaged=%d"
	  ",minFailsafeTime=%u"
	  ",maxFailsafeTime=%u"
	  ",isMoving=%d"
	  ",position=%g"
	  ",minPosition=%g"
	  ",maxPosition=%g"
	  ",minPulseWidth=%g"
	  ",maxPulseWidth=%g"
	  ",minPulseWidthLimit=%g"
	  ",maxPulseWidthLimit=%g"
	  ",speedRampingState=%d"
	  ",targetPosition=%g"
	  ",torque=%g"
	  ",minTorque=%g"
	  ",maxTorque=%g"
	  ",velocity=%g"
	  ",velocityLimit=%g"
	  ",minVelocityLimit=%g"
	  ",maxVelocityLimit=%g"
	  ",voltage=%d"
	  ,5 /* class version */
	  ,ch->acceleration
	  ,ch->minAcceleration
	  ,ch->maxAcceleration
	  ,(uint32_t)round(ch->dataInterval)
	  ,ch->minDataInterval
	  ,ch->maxDataInterval
	  ,ch->dataInterval
	  ,ch->minDataRate
	  ,ch->maxDataRate
	  ,ch->engaged
	  ,ch->minFailsafeTime
	  ,ch->maxFailsafeTime
	  ,ch->isMoving
	  ,ch->position
	  ,ch->minPosition
	  ,ch->maxPosition
	  ,ch->minPulseWidth
	  ,ch->maxPulseWidth
	  ,ch->minPulseWidthLimit
	  ,ch->maxPulseWidthLimit
	  ,ch->speedRampingState
	  ,ch->targetPosition
	  ,ch->torque
	  ,ch->minTorque
	  ,ch->maxTorque
	  ,ch->velocity
	  ,ch->velocityLimit
	  ,ch->minVelocityLimit
	  ,ch->maxVelocityLimit
	  ,ch->voltage
	));
}

static PhidgetReturnCode CCONV
_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetRCServoHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetRCServoHandle)phid;
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
	case BP_SETENGAGED:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->engaged = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Engaged");
		}
		break;
	case BP_SETMINPULSEWIDTH:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->minPulseWidth = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "MinPulseWidth");
		}
		break;
	case BP_SETMAXPULSEWIDTH:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->maxPulseWidth = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "MaxPulseWidth");
		}
		break;
	case BP_SETSPEEDRAMPINGSTATE:
		TESTBOOL_IOP(bp->iop, getBridgePacketInt32(bp, 0));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->speedRampingState = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "SpeedRampingState");
		}
		break;
	case BP_SETTARGETPOSITION:
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->targetPosition = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "TargetPosition");
		}
		break;
	case BP_SETDUTYCYCLE:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minTorque, ch->maxTorque);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->torque = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Torque");
		}
		break;
	case BP_SETVELOCITYLIMIT:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), ch->minVelocityLimit,
		  ch->maxVelocityLimit);
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->velocityLimit = getBridgePacketDouble(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "VelocityLimit");
		}
		break;
	case BP_SETVOLTAGE:
		if (!supportedRCServoVoltage(phid, (PhidgetRCServo_Voltage)getBridgePacketInt32(bp, 0)))
			return (MOS_ERROR(bp->iop, EPHIDGET_INVALIDARG,
			  "Specified RCServoVoltage is unsupported by this device."));
		res = DEVBRIDGEINPUT(phid, bp);
		if (res != EPHIDGET_OK)
			break;
		ch->voltage = getBridgePacketInt32(bp, 0);
		if (bridgePacketIsFromNet(bp)) {
			FIRE_PROPERTYCHANGE(ch, "Voltage");
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
	PhidgetAdvancedServoDeviceHandle parentAdvancedServo;
	PhidgetServoDeviceHandle parentServo;
	PhidgetVINTDeviceHandle parentVINT;
	PhidgetRCServoHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);
	ch = (PhidgetRCServoHandle)phid;

	ret = EPHIDGET_OK;

	parentAdvancedServo = (PhidgetAdvancedServoDeviceHandle)phid->parent;
	parentServo = (PhidgetServoDeviceHandle)phid->parent;
	parentVINT = (PhidgetVINTDeviceHandle)phid->parent;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
		// Constants
		ch->maxPulseWidthLimit = 2550;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
		// Constants
		ch->maxPulseWidthLimit = 2550;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1000_RCSERVO_300:
		// Constants
		ch->maxPulseWidthLimit = 4095;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1000_RCSERVO_313:
		// Constants
		ch->maxPulseWidthLimit = 4095;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
		// Constants
		ch->maxPulseWidthLimit = 2550;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
		// Constants
		ch->maxPulseWidthLimit = 2550;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1001_RCSERVO_313:
		// Constants
		ch->maxPulseWidthLimit = 4095;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1001_RCSERVO_400:
		// Constants
		ch->maxPulseWidthLimit = 4095;
		ch->minPulseWidthLimit = 1;
		ch->speedRampingState = 0;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		// Inputs, Settables
		ch->maxPulseWidth = parentServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentServo->position[ch->phid.index];
		ch->targetPosition = parentServo->targetPosition[ch->phid.index];
		ch->engaged = parentServo->engaged[ch->phid.index];
		break;
	case PHIDCHUID_1061_RCSERVO_100:
		// Constants
		ch->maxPulseWidthLimit = 2730.666;
		ch->maxVelocityLimit = 68266.666;
		ch->maxAcceleration = 3413333.333;
		ch->minPulseWidthLimit = 0.083;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 208.334;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		ch->maxDataInterval = 60000;
		ch->minDataInterval = 32;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		// Inputs, Settables
		ch->maxPulseWidth = parentAdvancedServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentAdvancedServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentAdvancedServo->position[ch->phid.index];
		ch->targetPosition = parentAdvancedServo->targetPosition[ch->phid.index];
		ch->velocityLimit = parentAdvancedServo->velocityLimit[ch->phid.index];
		ch->velocity = parentAdvancedServo->velocity[ch->phid.index];
		ch->acceleration = parentAdvancedServo->acceleration[ch->phid.index];
		ch->isMoving = parentAdvancedServo->isMoving[ch->phid.index];
		ch->engaged = parentAdvancedServo->engaged[ch->phid.index];
		ch->speedRampingState = parentAdvancedServo->speedRampingState[ch->phid.index];
		ch->dataInterval = parentAdvancedServo->dataInterval[ch->phid.index];
		break;
	case PHIDCHUID_1061_RCSERVO_200:
		// Constants
		ch->maxPulseWidthLimit = 2730.666;
		ch->maxVelocityLimit = 68266.666;
		ch->maxAcceleration = 3413333.333;
		ch->minPulseWidthLimit = 0.083;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 208.334;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		ch->maxDataInterval = 60000;
		ch->minDataInterval = 32;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		// Inputs, Settables
		ch->maxPulseWidth = parentAdvancedServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentAdvancedServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentAdvancedServo->position[ch->phid.index];
		ch->targetPosition = parentAdvancedServo->targetPosition[ch->phid.index];
		ch->velocityLimit = parentAdvancedServo->velocityLimit[ch->phid.index];
		ch->velocity = parentAdvancedServo->velocity[ch->phid.index];
		ch->acceleration = parentAdvancedServo->acceleration[ch->phid.index];
		ch->isMoving = parentAdvancedServo->isMoving[ch->phid.index];
		ch->engaged = parentAdvancedServo->engaged[ch->phid.index];
		ch->speedRampingState = parentAdvancedServo->speedRampingState[ch->phid.index];
		ch->dataInterval = parentAdvancedServo->dataInterval[ch->phid.index];
		break;
	case PHIDCHUID_1061_RCSERVO_300:
		// Constants
		ch->maxPulseWidthLimit = 2730.666;
		ch->maxVelocityLimit = 68266.666;
		ch->maxAcceleration = 3413333.333;
		ch->minPulseWidthLimit = 0.083;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 208.334;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		ch->maxDataInterval = 60000;
		ch->minDataInterval = 32;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		// Inputs, Settables
		ch->maxPulseWidth = parentAdvancedServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentAdvancedServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentAdvancedServo->position[ch->phid.index];
		ch->targetPosition = parentAdvancedServo->targetPosition[ch->phid.index];
		ch->velocityLimit = parentAdvancedServo->velocityLimit[ch->phid.index];
		ch->velocity = parentAdvancedServo->velocity[ch->phid.index];
		ch->acceleration = parentAdvancedServo->acceleration[ch->phid.index];
		ch->isMoving = parentAdvancedServo->isMoving[ch->phid.index];
		ch->engaged = parentAdvancedServo->engaged[ch->phid.index];
		ch->speedRampingState = parentAdvancedServo->speedRampingState[ch->phid.index];
		ch->dataInterval = parentAdvancedServo->dataInterval[ch->phid.index];
		break;
	case PHIDCHUID_RCC0004_RCSERVO_400:
		// Constants
		ch->maxPulseWidthLimit = 2730.666;
		ch->maxVelocityLimit = 68266.666;
		ch->maxAcceleration = 3413333.333;
		ch->minPulseWidthLimit = 0.083;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 208.334;
		ch->maxDataInterval = 60000;
		ch->minDataInterval = 32;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		// Inputs, Settables
		ch->maxPulseWidth = parentAdvancedServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentAdvancedServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentAdvancedServo->position[ch->phid.index];
		ch->targetPosition = parentAdvancedServo->targetPosition[ch->phid.index];
		ch->velocityLimit = parentAdvancedServo->velocityLimit[ch->phid.index];
		ch->velocity = parentAdvancedServo->velocity[ch->phid.index];
		ch->acceleration = parentAdvancedServo->acceleration[ch->phid.index];
		ch->isMoving = parentAdvancedServo->isMoving[ch->phid.index];
		ch->engaged = parentAdvancedServo->engaged[ch->phid.index];
		ch->speedRampingState = parentAdvancedServo->speedRampingState[ch->phid.index];
		ch->voltage = parentAdvancedServo->RCServoVoltageDevProp;
		ch->dataInterval = parentAdvancedServo->dataInterval[ch->phid.index];
		break;
	case PHIDCHUID_1066_RCSERVO_100:
		// Constants
		ch->maxPulseWidthLimit = 2730.666;
		ch->maxVelocityLimit = 68266.666;
		ch->maxAcceleration = 3413333.333;
		ch->minPulseWidthLimit = 0.083;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 208.334;
		ch->voltage = RCSERVO_VOLTAGE_5V;
		ch->maxDataInterval = 60000;
		ch->minDataInterval = 32;
		ch->minDataRate = 0.016666666666666666;
		ch->maxDataRate = 31.25;
		// Inputs, Settables
		ch->maxPulseWidth = parentAdvancedServo->maxPulseWidth[ch->phid.index];
		ch->maxPosition = 180;
		ch->minPulseWidth = parentAdvancedServo->minPulseWidth[ch->phid.index];
		ch->minPosition = 0;
		ch->position = parentAdvancedServo->position[ch->phid.index];
		ch->targetPosition = parentAdvancedServo->targetPosition[ch->phid.index];
		ch->velocityLimit = parentAdvancedServo->velocityLimit[ch->phid.index];
		ch->velocity = parentAdvancedServo->velocity[ch->phid.index];
		ch->acceleration = parentAdvancedServo->acceleration[ch->phid.index];
		ch->isMoving = parentAdvancedServo->isMoving[ch->phid.index];
		ch->engaged = parentAdvancedServo->engaged[ch->phid.index];
		ch->speedRampingState = parentAdvancedServo->speedRampingState[ch->phid.index];
		ch->dataInterval = parentAdvancedServo->dataInterval[ch->phid.index];
		break;
	case PHIDCHUID_RCC1000_RCSERVO_100:
		// Constants
		ch->maxPulseWidthLimit = 4000;
		ch->maxVelocityLimit = 781250;
		ch->maxAcceleration = 3906250;
		ch->minPulseWidthLimit = 0.063;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 156.25;
		// Inputs, Settables
		ch->maxPulseWidth = PUNK_DBL;
		ch->maxPosition = 180;
		ch->minPulseWidth = PUNK_DBL;
		ch->minPosition = 0;
		ch->position = PUNK_DBL;
		ch->targetPosition = PUNK_DBL;
		ch->velocityLimit = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->isMoving = PUNK_BOOL;
		ch->engaged = PUNK_BOOL;
		ch->speedRampingState = PUNK_BOOL;
		ch->voltage = parentVINT->RCServoVoltageDevProp;
		break;
	case PHIDCHUID_RCC1000_RCSERVO_110:
		// Constants
		ch->maxPulseWidthLimit = 4000;
		ch->maxVelocityLimit = 781250;
		ch->maxAcceleration = 3906250;
		ch->minPulseWidthLimit = 0.063;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 156.25;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->maxPulseWidth = PUNK_DBL;
		ch->maxPosition = 180;
		ch->minPulseWidth = PUNK_DBL;
		ch->minPosition = 0;
		ch->position = PUNK_DBL;
		ch->targetPosition = PUNK_DBL;
		ch->velocityLimit = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->isMoving = PUNK_BOOL;
		ch->engaged = PUNK_BOOL;
		ch->speedRampingState = PUNK_BOOL;
		ch->voltage = parentVINT->RCServoVoltageDevProp;
		break;
	case PHIDCHUID_RCC1000_RCSERVO_200:
		// Constants
		ch->maxPulseWidthLimit = 4000;
		ch->maxVelocityLimit = 781250;
		ch->maxAcceleration = 3906250;
		ch->minPulseWidthLimit = 0.063;
		ch->minVelocityLimit = 0;
		ch->minAcceleration = 156.25;
		ch->isMoving = 0;
		ch->maxFailsafeTime = 30000;
		ch->minFailsafeTime = 500;
		// Inputs, Settables
		ch->maxPulseWidth = PUNK_DBL;
		ch->maxPosition = 180;
		ch->minPulseWidth = PUNK_DBL;
		ch->minPosition = 0;
		ch->position = PUNK_DBL;
		ch->targetPosition = PUNK_DBL;
		ch->velocityLimit = PUNK_DBL;
		ch->acceleration = PUNK_DBL;
		ch->engaged = PUNK_BOOL;
		ch->speedRampingState = PUNK_BOOL;
		ch->voltage = parentVINT->RCServoVoltageDevProp;
		break;
	default:
		MOS_PANIC("Unsupported Channel");
	}


	return (ret);
}

static PhidgetReturnCode CCONV
_setDefaults(PhidgetChannelHandle phid) {
	PhidgetRCServoHandle ch;
	PhidgetReturnCode ret;

	TESTPTR(phid);

	ch = (PhidgetRCServoHandle)phid;
	ret = EPHIDGET_OK;

	switch (phid->UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1000_RCSERVO_300:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1000_RCSERVO_313:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1001_RCSERVO_313:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1001_RCSERVO_400:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1061_RCSERVO_100:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->speedRampingState = 1;
		ch->dataInterval = 256;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVELOCITYLIMIT, NULL, NULL, 1, "%g", ch->velocityLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSPEEDRAMPINGSTATE, NULL, NULL, 1, "%d",
		  ch->speedRampingState);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1061_RCSERVO_200:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->speedRampingState = 1;
		ch->dataInterval = 256;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVELOCITYLIMIT, NULL, NULL, 1, "%g", ch->velocityLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSPEEDRAMPINGSTATE, NULL, NULL, 1, "%d",
		  ch->speedRampingState);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1061_RCSERVO_300:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->speedRampingState = 1;
		ch->dataInterval = 256;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVELOCITYLIMIT, NULL, NULL, 1, "%g", ch->velocityLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSPEEDRAMPINGSTATE, NULL, NULL, 1, "%d",
		  ch->speedRampingState);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_RCC0004_RCSERVO_400:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->speedRampingState = 1;
		// (Device Property - check if already set)
		if (ch->voltage == PUNK_ENUM)
			ch->voltage = RCSERVO_VOLTAGE_5V;
		ch->dataInterval = 256;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVELOCITYLIMIT, NULL, NULL, 1, "%g", ch->velocityLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSPEEDRAMPINGSTATE, NULL, NULL, 1, "%d",
		  ch->speedRampingState);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVOLTAGE, NULL, NULL, 1, "%d", ch->voltage);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_1066_RCSERVO_100:
		// Reset values
		ch->engaged = 0;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->speedRampingState = 1;
		ch->dataInterval = 256;
		ret = bridgeSendToDevice(phid, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g", ch->maxPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g", ch->minPulseWidth);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETVELOCITYLIMIT, NULL, NULL, 1, "%g", ch->velocityLimit);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETACCELERATION, NULL, NULL, 1, "%g", ch->acceleration);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETSPEEDRAMPINGSTATE, NULL, NULL, 1, "%d",
		  ch->speedRampingState);
		if (ret != EPHIDGET_OK)
			break;
		ret = bridgeSendToDevice(phid, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
		  (uint32_t)round(ch->dataInterval));
		if (ret != EPHIDGET_OK)
			break;
		break;
	case PHIDCHUID_RCC1000_RCSERVO_100:
		// Reset values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->engaged = 0;
		ch->speedRampingState = 1;
		// (Device Property - check if already set)
		if (ch->voltage == PUNK_ENUM)
			ch->voltage = RCSERVO_VOLTAGE_5V;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		break;
	case PHIDCHUID_RCC1000_RCSERVO_110:
		// Reset values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->engaged = 0;
		ch->speedRampingState = 1;
		// (Device Property - check if already set)
		if (ch->voltage == PUNK_ENUM)
			ch->voltage = RCSERVO_VOLTAGE_5V;
		// Must-set values
		ch->targetPosition = PUNK_DBL;
		// Default values
		break;
	case PHIDCHUID_RCC1000_RCSERVO_200:
		// Reset values
		ch->maxPulseWidth = 2450;
		ch->minPulseWidth = 550;
		ch->velocityLimit = 1900;
		ch->acceleration = 3800;
		ch->engaged = 0;
		ch->speedRampingState = 1;
		// (Device Property - check if already set)
		if (ch->voltage == PUNK_ENUM)
			ch->voltage = RCSERVO_VOLTAGE_5V;
		// Must-set values
		// Default values
		ch->targetPosition = 1500;
		ret = bridgeSendToDevice(phid, BP_SETTARGETPOSITION, NULL, NULL, 1, "%g", ch->targetPosition);
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

}

static int CCONV
_hasInitialState(PhidgetChannelHandle phid) {

	return (PTRUE);
}

static void CCONV
_free(PhidgetChannelHandle *ch) {

	mos_free(*ch, sizeof (struct _PhidgetRCServo));
}

static PhidgetReturnCode CCONV
_create(PhidgetRCServoHandle *phidp) {

	CHANNELCREATE_BODY(RCServo, PHIDCHCLASS_RCSERVO);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_delete(PhidgetRCServoHandle *phidp) {

	return (Phidget_delete((PhidgetHandle *)phidp));
}

API_PRETURN
PhidgetRCServo_enableFailsafe(PhidgetRCServoHandle ch, uint32_t failsafeTime) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETFAILSAFETIME, NULL, NULL, 1, "%u",
	  failsafeTime); 
}

API_PRETURN
PhidgetRCServo_resetFailsafe(PhidgetRCServoHandle ch) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_FAILSAFERESET, NULL, NULL, 0, NULL); 
}

API_PRETURN
PhidgetRCServo_setDataInterval(PhidgetRCServoHandle ch, uint32_t dataInterval) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 1, "%u",
	  dataInterval));
}

API_PRETURN
PhidgetRCServo_getDataInterval(PhidgetRCServoHandle ch, uint32_t *dataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*dataInterval = (uint32_t)round(ch->dataInterval);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMinDataInterval(PhidgetRCServoHandle ch, uint32_t *minDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minDataInterval = ch->minDataInterval;
	if (ch->minDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMaxDataInterval(PhidgetRCServoHandle ch, uint32_t *maxDataInterval) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataInterval);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxDataInterval = ch->maxDataInterval;
	if (ch->maxDataInterval == (uint32_t)PUNK_UINT32)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setDataRate(PhidgetRCServoHandle ch, double dataRate) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDATAINTERVAL, NULL, NULL, 2, "%u%g",
	  (uint32_t)round(1000.0 / dataRate), (double)(1000.0 / dataRate));
}

API_PRETURN
PhidgetRCServo_getDataRate(PhidgetRCServoHandle ch, double *dataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(dataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*dataRate = round_double((1000.0 / ch->dataInterval), 4);
	if (ch->dataInterval == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMinDataRate(PhidgetRCServoHandle ch, double *minDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minDataRate = ch->minDataRate;
	if (ch->minDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMaxDataRate(PhidgetRCServoHandle ch, double *maxDataRate) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxDataRate);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxDataRate = ch->maxDataRate;
	if (ch->maxDataRate == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setEngaged(PhidgetRCServoHandle ch, int engaged) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETENGAGED, NULL, NULL, 1, "%d", engaged));
}

API_PRETURN
PhidgetRCServo_getEngaged(PhidgetRCServoHandle ch, int *engaged) {

	TESTPTR_PR(ch);
	TESTPTR_PR(engaged);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*engaged = ch->engaged;
	if (ch->engaged == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMinFailsafeTime(PhidgetRCServoHandle ch, uint32_t *minFailsafeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minFailsafeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_1061_RCSERVO_100:
	case PHIDCHUID_1061_RCSERVO_200:
	case PHIDCHUID_1061_RCSERVO_300:
	case PHIDCHUID_RCC0004_RCSERVO_400:
	case PHIDCHUID_1066_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_100:
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
PhidgetRCServo_getMaxFailsafeTime(PhidgetRCServoHandle ch, uint32_t *maxFailsafeTime) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxFailsafeTime);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_1061_RCSERVO_100:
	case PHIDCHUID_1061_RCSERVO_200:
	case PHIDCHUID_1061_RCSERVO_300:
	case PHIDCHUID_RCC0004_RCSERVO_400:
	case PHIDCHUID_1066_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_100:
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
PhidgetRCServo_getIsMoving(PhidgetRCServoHandle ch, int *isMoving) {

	TESTPTR_PR(ch);
	TESTPTR_PR(isMoving);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*isMoving = ch->isMoving;
	if (ch->isMoving == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMinPosition(PhidgetRCServoHandle ch, double *minPosition) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minPosition);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*minPosition = ch->minPosition;
	if (ch->minPosition == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMaxPosition(PhidgetRCServoHandle ch, double *maxPosition) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxPosition);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*maxPosition = ch->maxPosition;
	if (ch->maxPosition == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setMinPulseWidth(PhidgetRCServoHandle ch, double minPulseWidth) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETMINPULSEWIDTH, NULL, NULL, 1, "%g",
	  minPulseWidth));
}

API_PRETURN
PhidgetRCServo_getMinPulseWidth(PhidgetRCServoHandle ch, double *minPulseWidth) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minPulseWidth);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*minPulseWidth = ch->minPulseWidth;
	if (ch->minPulseWidth == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setMaxPulseWidth(PhidgetRCServoHandle ch, double maxPulseWidth) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETMAXPULSEWIDTH, NULL, NULL, 1, "%g",
	  maxPulseWidth));
}

API_PRETURN
PhidgetRCServo_getMaxPulseWidth(PhidgetRCServoHandle ch, double *maxPulseWidth) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxPulseWidth);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*maxPulseWidth = ch->maxPulseWidth;
	if (ch->maxPulseWidth == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMinPulseWidthLimit(PhidgetRCServoHandle ch, double *minPulseWidthLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minPulseWidthLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*minPulseWidthLimit = ch->minPulseWidthLimit;
	if (ch->minPulseWidthLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMaxPulseWidthLimit(PhidgetRCServoHandle ch, double *maxPulseWidthLimit) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxPulseWidthLimit);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*maxPulseWidthLimit = ch->maxPulseWidthLimit;
	if (ch->maxPulseWidthLimit == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setSpeedRampingState(PhidgetRCServoHandle ch, int speedRampingState) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSPEEDRAMPINGSTATE, NULL, NULL, 1, "%d",
	  speedRampingState));
}

API_PRETURN
PhidgetRCServo_getSpeedRampingState(PhidgetRCServoHandle ch, int *speedRampingState) {

	TESTPTR_PR(ch);
	TESTPTR_PR(speedRampingState);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*speedRampingState = ch->speedRampingState;
	if (ch->speedRampingState == (int)PUNK_BOOL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setTorque(PhidgetRCServoHandle ch, double torque) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETDUTYCYCLE, NULL, NULL, 1, "%g",
	  torque));
}

API_PRETURN
PhidgetRCServo_getTorque(PhidgetRCServoHandle ch, double *torque) {

	TESTPTR_PR(ch);
	TESTPTR_PR(torque);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_1061_RCSERVO_100:
	case PHIDCHUID_1061_RCSERVO_200:
	case PHIDCHUID_1061_RCSERVO_300:
	case PHIDCHUID_RCC0004_RCSERVO_400:
	case PHIDCHUID_1066_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*torque = ch->torque;
	if (ch->torque == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMinTorque(PhidgetRCServoHandle ch, double *minTorque) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minTorque);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_1061_RCSERVO_100:
	case PHIDCHUID_1061_RCSERVO_200:
	case PHIDCHUID_1061_RCSERVO_300:
	case PHIDCHUID_RCC0004_RCSERVO_400:
	case PHIDCHUID_1066_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*minTorque = ch->minTorque;
	if (ch->minTorque == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_getMaxTorque(PhidgetRCServoHandle ch, double *maxTorque) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxTorque);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_1000_RCSERVO_OLD1_200:
	case PHIDCHUID_1000_RCSERVO_OLD2_200:
	case PHIDCHUID_1000_RCSERVO_300:
	case PHIDCHUID_1000_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_OLD1_200:
	case PHIDCHUID_1001_RCSERVO_OLD2_200:
	case PHIDCHUID_1001_RCSERVO_313:
	case PHIDCHUID_1001_RCSERVO_400:
	case PHIDCHUID_1061_RCSERVO_100:
	case PHIDCHUID_1061_RCSERVO_200:
	case PHIDCHUID_1061_RCSERVO_300:
	case PHIDCHUID_RCC0004_RCSERVO_400:
	case PHIDCHUID_1066_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_100:
	case PHIDCHUID_RCC1000_RCSERVO_110:
	case PHIDCHUID_RCC1000_RCSERVO_200:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	default:
		break;
	}

	*maxTorque = ch->maxTorque;
	if (ch->maxTorque == (double)PUNK_DBL)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setVoltage(PhidgetRCServoHandle ch, PhidgetRCServo_Voltage voltage) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETVOLTAGE, NULL, NULL, 1, "%d", voltage));
}

API_PRETURN
PhidgetRCServo_getVoltage(PhidgetRCServoHandle ch, PhidgetRCServo_Voltage *voltage) {

	TESTPTR_PR(ch);
	TESTPTR_PR(voltage);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);
	TESTATTACHED_PR(ch);

	*voltage = ch->voltage;
	if (ch->voltage == (PhidgetRCServo_Voltage)PUNK_ENUM)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setOnPositionChangeHandler(PhidgetRCServoHandle ch,
  PhidgetRCServo_OnPositionChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->PositionChange = NULL;
		MEMORY_BARRIER();
		ch->PositionChangeCtx = NULL;
	} else {
		ch->PositionChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->PositionChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setOnTargetPositionReachedHandler(PhidgetRCServoHandle ch,
  PhidgetRCServo_OnTargetPositionReachedCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->TargetPositionReached = NULL;
		MEMORY_BARRIER();
		ch->TargetPositionReachedCtx = NULL;
	} else {
		ch->TargetPositionReachedCtx = ctx;
		MEMORY_BARRIER();
		ch->TargetPositionReached = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetRCServo_setOnVelocityChangeHandler(PhidgetRCServoHandle ch,
  PhidgetRCServo_OnVelocityChangeCallback fptr, void *ctx) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_RCSERVO);

	MEMORY_BARRIER();
	if (fptr == NULL) {
		ch->VelocityChange = NULL;
		MEMORY_BARRIER();
		ch->VelocityChangeCtx = NULL;
	} else {
		ch->VelocityChangeCtx = ctx;
		MEMORY_BARRIER();
		ch->VelocityChange = fptr;
	}
	MEMORY_BARRIER();

	return (EPHIDGET_OK);
}
