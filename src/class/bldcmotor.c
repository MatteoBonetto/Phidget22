/* Generated: Fri Sep 16 2016 16:10:18 GMT-0600 (Mountain Daylight Time) */
/* Will not be regenerated. */

#include "phidgetbase.h"
#include "class/bldcmotor.gen.h"
#include "class/bldcmotor.gen.c"

double PhidgetBLDCMotor_getLastBrakingStrength(PhidgetBLDCMotorHandle);
int64_t PhidgetBLDCMotor_getLastPosition(PhidgetBLDCMotorHandle);

static void CCONV
PhidgetBLDCMotor_errorHandler(PhidgetChannelHandle phid, Phidget_ErrorEventCode code) {}

static void CCONV
PhidgetBLDCMotor_free(PhidgetChannelHandle *ch) {
	_free(ch);
}

API_PRETURN
PhidgetBLDCMotor_create(PhidgetBLDCMotorHandle *phidp) {
	return (_create(phidp));
}

static PhidgetReturnCode CCONV
PhidgetBLDCMotor_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	return (_setStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetBLDCMotor_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	return (_getStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetBLDCMotor_initAfterOpen(PhidgetChannelHandle phid) {
	return (_initAfterOpen(phid));
}

static PhidgetReturnCode CCONV
PhidgetBLDCMotor_setDefaults(PhidgetChannelHandle phid) {
	PhidgetReturnCode ret;

	ret = _setDefaults(phid);

	switch (ret) {
	case EPHIDGET_FAILSAFE:
		FIRE_ERROR(phid, EEPHIDGET_ESTOP, "External stop procedure initiated.");
		break;
	case EPHIDGET_BADPOWER:
		FIRE_ERROR(phid, EEPHIDGET_BADPOWER, "Your power supply voltage is too high for the motor controller to begin operation.");
		break;
	case EPHIDGET_POWERCYCLE:
		FIRE_ERROR(phid, EEPHIDGET_BADPOWER, "An overvoltage fault has triggered. Power your device off and on to resume operation. "
											 "We recommend a PowerGuard Phidget to prevent this in future.");
		break;
	case EPHIDGET_HALLSENSOR:
		FIRE_ERROR(phid, EEPHIDGET_BADCONNECTION, "The hall sensor of your BLDC motor is not reporting a valid input. "
												  "The cable is likely damaged or unplugged.");
		break;
	case EPHIDGET_BADCURRENT:
		FIRE_ERROR(phid, EEPHIDGET_BADCURRENT, "The current sensor is seeing an unacceptable offset in its readings. "
											   "Move the controller away from magnetic fields and try again.");
		break;
	}

	return ret;
}

static PhidgetReturnCode
PhidgetBLDCMotor_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetBLDCMotorHandle ch;
	PhidgetReturnCode res;
	double tmpDbl;

	ch = (PhidgetBLDCMotorHandle)phid;

	switch (bp->vpkt) {
	case BP_SETBRAKINGDUTYCYCLE:
	case BP_SETDUTYCYCLE:
		TESTRANGE_IOP(bp->iop, "%lf", getBridgePacketDouble(bp, 0), -ch->maxVelocity, ch->maxVelocity);
		res = _bridgeInput(phid, bp);
		break;
	case BP_POSITIONCHANGE:
		ch->position = getBridgePacketInt64(bp, 0);
		FIRECH(ch, PhidgetBLDCMotor, PositionChange, (ch->position + ch->positionOffset) * ch->rescaleFactor);
		res = EPHIDGET_OK;
		break;
	case BP_SETFAILSAFETIME:
		TESTRANGE_IOP(bp->iop, "%u", getBridgePacketUInt32(bp, 0), ch->minFailsafeTime, ch->maxFailsafeTime);
		res = _bridgeInput(phid, bp);
		break;
	case BP_INDUCTANCECHANGE:
		ch->inductance = getBridgePacketDouble(bp, 0);
		FIRE_PROPERTYCHANGE(ch, "Inductance");
		res = EPHIDGET_OK;
		break;
	case BP_DATAINTERVALCHANGE:
		if (bp->entrycnt > 1)
			ch->dataInterval = getBridgePacketDouble(bp, 1);
		else
			ch->dataInterval = (double)getBridgePacketUInt32(bp, 0);
		FIRE_PROPERTYCHANGE(ch, "DataInterval");
		FIRE_PROPERTYCHANGE(ch, "DataRate");
		res = EPHIDGET_OK;
		break;
	case BP_CURRENTLIMITCHANGE:
		ch->currentLimit = getBridgePacketDouble(bp, 0);
		FIRE_PROPERTYCHANGE(ch, "CurrentLimit");
		res = EPHIDGET_OK;
		break;
	case BP_SURGECURRENTLIMITCHANGE:
		ch->surgeCurrentLimit = getBridgePacketDouble(bp, 0);
		FIRE_PROPERTYCHANGE(ch, "SurgeCurrentLimit");
		res = EPHIDGET_OK;
		break;
	case BP_ACTIVECURRENTLIMITCHANGE:
		tmpDbl = getBridgePacketDouble(bp, 0);
		if (ch->activeCurrentLimit != tmpDbl) {
			ch->activeCurrentLimit = tmpDbl;
			FIRE_PROPERTYCHANGE(ch, "ActiveCurrentLimit");
		}
		res = EPHIDGET_OK;
		break;
	default:
		res = _bridgeInput(phid, bp);
		break;
	}

	return (res);
}

static void CCONV
PhidgetBLDCMotor_fireInitialEvents(PhidgetChannelHandle phid) {
	_fireInitialEvents(phid);
}

static int
PhidgetBLDCMotor_hasInitialState(PhidgetChannelHandle phid) {

	if (supportedBridgePacket(phid, BP_INDUCTANCECHANGE) && ((PhidgetBLDCMotorHandle)phid)->inductance == PUNK_DBL)
		return (PFALSE);

	return (_hasInitialState(phid));
}

API_PRETURN
PhidgetBLDCMotor_setRescaleFactor(PhidgetBLDCMotorHandle ch, double rescaleFactor) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	if (rescaleFactor == 0)
		return (PHID_RETURN(EPHIDGET_INVALIDARG));

	ch->rescaleFactor = rescaleFactor;
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetBLDCMotor_getPosition(PhidgetBLDCMotorHandle ch, double *position) {

	TESTPTR_PR(ch);
	TESTPTR_PR(position);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	*position = (ch->position + ch->positionOffset) * ch->rescaleFactor;
	if (ch->position == PUNK_INT64)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetBLDCMotor_getMinPosition(PhidgetBLDCMotorHandle ch, double *minPosition) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minPosition);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	*minPosition = (ch->minPosition + ch->positionOffset) * ch->rescaleFactor;
	if (ch->minPosition == PUNK_INT64)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetBLDCMotor_getMaxPosition(PhidgetBLDCMotorHandle ch, double *maxPosition) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxPosition);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	*maxPosition = (ch->maxPosition + ch->positionOffset) * ch->rescaleFactor;
	if (ch->maxPosition == PUNK_INT64)
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetBLDCMotor_addPositionOffset(PhidgetBLDCMotorHandle ch, double positionOffset) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	ch->positionOffset += roundl(positionOffset / ch->rescaleFactor);
	return (EPHIDGET_OK);
}

API_PRETURN
PhidgetBLDCMotor_setStallVelocity(PhidgetBLDCMotorHandle ch, double stallVelocity) {

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	return (bridgeSendToDevice((PhidgetChannelHandle)ch, BP_SETSTALLVELOCITY, NULL, NULL, 1, "%g",
							   stallVelocity / fabs(ch->rescaleFactor)));
}

API_PRETURN
PhidgetBLDCMotor_getStallVelocity(PhidgetBLDCMotorHandle ch, double *stallVelocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(stallVelocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	// Only supported on DCC1100
	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_DCC1100_BLDCMOTOR_100:
	case PHIDCHUID_DCC1100_BLDCMOTOR_120:
		if (ch->stallVelocity == (double)PUNK_DBL)
			return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));

		*stallVelocity = ch->stallVelocity * fabs(ch->rescaleFactor);

		return (EPHIDGET_OK);

	default:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	}
}

API_PRETURN
PhidgetBLDCMotor_getMinStallVelocity(PhidgetBLDCMotorHandle ch, double *minStallVelocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(minStallVelocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	// Only supported on DCC1100
	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_DCC1100_BLDCMOTOR_100:
	case PHIDCHUID_DCC1100_BLDCMOTOR_120:
		if (ch->minStallVelocity == (double)PUNK_DBL)
			return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));

		*minStallVelocity = ch->minStallVelocity * fabs(ch->rescaleFactor);

		return (EPHIDGET_OK);

	default:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	}
}

API_PRETURN
PhidgetBLDCMotor_getMaxStallVelocity(PhidgetBLDCMotorHandle ch, double *maxStallVelocity) {

	TESTPTR_PR(ch);
	TESTPTR_PR(maxStallVelocity);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	// Only supported on DCC1100
	switch (ch->phid.UCD->uid) {
	case PHIDCHUID_DCC1100_BLDCMOTOR_100:
	case PHIDCHUID_DCC1100_BLDCMOTOR_120:
		if (ch->maxStallVelocity == (double)PUNK_DBL)
			return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));

		*maxStallVelocity = ch->maxStallVelocity * fabs(ch->rescaleFactor);

		return (EPHIDGET_OK);

	default:
		return (PHID_RETURN(EPHIDGET_UNSUPPORTED));
	}
}

double
PhidgetBLDCMotor_getLastBrakingStrength(PhidgetBLDCMotorHandle ch) {

	return (ch->brakingStrength);
}

API_PRETURN
PhidgetBLDCMotor_setBrakingEnabled(PhidgetBLDCMotorHandle ch, int brakingEnabled) {

	return PhidgetBLDCMotor_setTargetBrakingStrength(ch, brakingEnabled ? 1.0 : 0.0);
}

API_PRETURN
PhidgetBLDCMotor_getBrakingEnabled(PhidgetBLDCMotorHandle ch, int *brakingEnabled) {
	TESTPTR_PR(ch);
	TESTPTR_PR(brakingEnabled);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_BLDCMOTOR);
	TESTATTACHED_PR(ch);

	if (ch->targetBrakingStrength == (double)PUNK_DBL) {
		*brakingEnabled = PUNK_BOOL;
		return (PHID_RETURN(EPHIDGET_UNKNOWNVAL));
	}

	*brakingEnabled = ch->targetBrakingStrength ? PTRUE : PFALSE;

	return (EPHIDGET_OK);
}

int64_t
PhidgetBLDCMotor_getLastPosition(PhidgetBLDCMotorHandle ch) {

	return (ch->position);
}
