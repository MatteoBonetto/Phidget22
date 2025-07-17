/* Generated: Wed Jun 22 2016 14:15:21 GMT-0600 (Mountain Daylight Time) */
/* Will not be regenerated. */

#include "phidgetbase.h"
#include "util/dataadaptersupport.h"
#include "class/dataadapter.gen.h"
#include "class/dataadapter.gen.c"

// Access the PhidgetDataAdapterSupport struct via the channel private pointer
#define DATAADAPTER_SUPPORT(ch) ((PhidgetDataAdapterSupportHandle)(((PhidgetChannelHandle)(ch))->private))

static void CCONV
PhidgetDataAdapter_errorHandler(PhidgetChannelHandle phid, Phidget_ErrorEventCode code) {}

static void CCONV
PhidgetDataAdapter_free(PhidgetChannelHandle *ch) {

	if (ch && *ch)
		PhidgetDataAdapterSupport_free((PhidgetDataAdapterSupportHandle *)&(*ch)->private);
	_free(ch);
}

API_PRETURN
PhidgetDataAdapter_create(PhidgetDataAdapterHandle *phidp) {
	PhidgetReturnCode res;

	res = _create(phidp);
	if (res == EPHIDGET_OK)
		res = PhidgetDataAdapterSupport_create((PhidgetDataAdapterSupportHandle *)&(*phidp)->phid.private);

	return (res);
}

static PhidgetReturnCode CCONV
PhidgetDataAdapter_setStatus(PhidgetChannelHandle phid, BridgePacket *bp) {
	return (_setStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetDataAdapter_getStatus(PhidgetChannelHandle phid, BridgePacket **bp) {
	return (_getStatus(phid, bp));
}

static PhidgetReturnCode CCONV
PhidgetDataAdapter_initAfterOpen(PhidgetChannelHandle phid) {
	PhidgetDataAdapterSupport_init(DATAADAPTER_SUPPORT(phid));
	return (_initAfterOpen(phid));
}

static PhidgetReturnCode CCONV
PhidgetDataAdapter_setDefaults(PhidgetChannelHandle phid) {
	return (_setDefaults(phid));
}

static PhidgetReturnCode
PhidgetDataAdapter_bridgeInput(PhidgetChannelHandle phid, BridgePacket *bp) {
	PhidgetDataAdapterHandle ch;
	PhidgetReturnCode res;

	ch = (PhidgetDataAdapterHandle)phid;

	switch (bp->vpkt) {
	case BP_IOVOLTAGECHANGE:
		ch->dataAdapterVoltage = getBridgePacketInt32(bp, 0);
		FIRE_PROPERTYCHANGE(ch, "DataAdapterVoltage");
		return (EPHIDGET_OK);
	default:
		res = _bridgeInput(phid, bp);
		break;
	}

	return (res);
}

static void
PhidgetDataAdapter_fireInitialEvents(PhidgetChannelHandle phid) {
	_fireInitialEvents(phid);
}

static int
PhidgetDataAdapter_hasInitialState(PhidgetChannelHandle phid) {
	return (_hasInitialState(phid));
}

API_PRETURN
PhidgetDataAdapter_sendPacket(PhidgetDataAdapterHandle ch, const uint8_t *data, size_t dataLen) {
	PhidgetReturnCode res = EPHIDGET_OK;

	TESTPTR_PR(ch);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DATAADAPTER);
	TESTATTACHED_PR(ch);

	if (dataLen == 0)
		return EPHIDGET_OK;

	if (dataLen > ch->maxSendPacketLength)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Send packet length must be less than %u", ch->maxSendPacketLength));

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_DATAOUT, NULL, NULL, 1, "%*R", dataLen, data);
	if (res != EPHIDGET_OK) {
		if (res == EPHIDGET_TIMEOUT)
			return (PHID_RETURN_ERRSTR(EPHIDGET_TIMEOUT, "The packet timed out while waiting to be transmitted. Check that your system can keep up with the data being sent."));
		return res;
	}

	if (res == EPHIDGET_TIMEOUT)
		return (PHID_RETURN_ERRSTR(EPHIDGET_TIMEOUT, "The packet timed out while waiting to be transmitted. Check that your system can keep up with the data being sent."));
	return res;
}

API_VRETURN
PhidgetDataAdapter_sendPacket_async(PhidgetDataAdapterHandle ch, const uint8_t *data, size_t dataLen,
									Phidget_AsyncCallback fptr, void *ctx) {
	PhidgetReturnCode res = EPHIDGET_OK;

	if (ch == NULL) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}
	if (ch->phid.class != PHIDCHCLASS_DATAADAPTER) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_WRONGDEVICE);
		return;
	}
	if (!ISATTACHED(ch)) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_NOTATTACHED);
		return;
	}
	if (dataLen > ch->maxSendPacketLength) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_INVALIDARG);
		return;
	}

	// No data is ok!
	if (dataLen == 0) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, EPHIDGET_OK);
		return;
	}

	res = bridgeSendToDevice((PhidgetChannelHandle)ch, BP_DATAOUT, fptr, ctx, 1, "%*R", dataLen, data);

	if (res != EPHIDGET_OK) {
		if (fptr)
			fptr((PhidgetHandle)ch, ctx, res);
	}
}

API_PRETURN
PhidgetDataAdapter_i2cSendReceive(PhidgetDataAdapterHandle ch, int address, const uint8_t *data, size_t dataLen, uint8_t *recvData, size_t recvDataLen) {
	TESTPTR_PR(ch);
	TESTPTR_PR(data);
	TESTPTR_PR(recvData);
	TESTRANGE_PR(address, "%d", 0, 127);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DATAADAPTER);

	if (recvDataLen > ch->maxReceivePacketLength)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Specified receive packet length must be less than %u", ch->maxReceivePacketLength));

	if (dataLen > ch->maxSendPacketLength)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Specified send packet length must be less than %u", ch->maxSendPacketLength));

	TESTATTACHED_PR(ch);

	char formatString[128];

	if (dataLen == 0 && recvDataLen == 0)
		return EPHIDGET_OK;
	else if (recvDataLen == 0)
		sprintf(formatString, "sT%dp", (int)dataLen);
	else if (dataLen == 0)
		sprintf(formatString, "sR%dp", (int)recvDataLen);
	else
		sprintf(formatString, "sT%dsR%dp", (int)dataLen, (int)(recvDataLen));

	return PhidgetDataAdapter_i2cComplexTransaction(ch, address, formatString, data, dataLen, recvData, &recvDataLen);
}

API_PRETURN
PhidgetDataAdapter_i2cComplexTransaction(PhidgetDataAdapterHandle ch, int address, char *formatString, const uint8_t *data, size_t dataLen, uint8_t *recvData, size_t *recvDataLen) {
	uint8_t response[DATAADAPTER_MAX_PACKET_LENGTH];
	size_t responseLen = DATAADAPTER_MAX_PACKET_LENGTH;
	PhidgetReturnCode res;
	TESTPTR_PR(ch);
	TESTPTR_PR(data);
	TESTPTR_PR(recvData);
	TESTPTR_PR(formatString);
	TESTRANGE_PR(address, "%d", 0, 127);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DATAADAPTER);

	if (*recvDataLen > ch->maxReceivePacketLength)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Specified receive packet length must be less than %u", ch->maxReceivePacketLength));

	if (dataLen > ch->maxSendPacketLength)
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Specified send packet length must be less than %u", ch->maxSendPacketLength));

	TESTATTACHED_PR(ch);

	res = bridgeSendToDeviceWithReply((PhidgetChannelHandle)ch, BP_I2CDATAEXCHANGE, NULL, NULL, (uint8_t *)response, (uint32_t *)&responseLen, 1, "%*R%u%s", dataLen, data, address, formatString);

	if (res) {
		if (res == EPHIDGET_TIMEOUT)
			return (PHID_RETURN_ERRSTR(EPHIDGET_TIMEOUT, "The packet timed out while waiting to be transmitted. Check that your system can keep up with the data being sent."));
		return res;
	}

	if (*recvDataLen < responseLen) {
		*recvDataLen = 0;
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Receive array length too short."));
	}

	*recvDataLen = responseLen;
	memcpy(recvData, response, responseLen);
	if (res == EPHIDGET_OK)
		unpack32(&response[responseLen]);
	return (res);
}

API_PRETURN
PhidgetDataAdapter_sendPacketWaitResponse(PhidgetDataAdapterHandle ch, const uint8_t *data, size_t dataLen, uint8_t *recvData, size_t *recvDataLen) {
	PhidgetReturnCode res;
	TESTPTR_PR(ch);
	TESTPTR_PR(data);
	TESTPTR_PR(recvData);
	TESTPTR_PR(recvDataLen);
	TESTCHANNELCLASS_PR(ch, PHIDCHCLASS_DATAADAPTER);
	TESTATTACHED_PR(ch);
	uint8_t response[DATAADAPTER_MAX_PACKET_LENGTH];
	size_t responseLen = DATAADAPTER_MAX_PACKET_LENGTH;
	uint32_t maxSendReceiveLength;

	switch (ch->phid.parent->deviceInfo.UDD->uid) {
#if (PHIDUID_ADP0001_USB_SUPPORTED || PHIDUID_ADP0001_VINT_SUPPORTED)
	#if PHIDUID_ADP0001_USB_SUPPORTED
	case PHIDUID_ADP0001_USB:
	#endif
	#if PHIDUID_ADP0001_VINT_SUPPORTED
	case PHIDUID_ADP0001_VINT:
	#endif
		// send 0 and expecting a response is valid for I2C
		break;
#endif
	default:
		// Sending nothing is technically valid, and already done.
		if (dataLen == 0)
			return EPHIDGET_OK;
		break;
	}

	switch (ch->phid.UCD->uid) {
#if (PHIDUID_ADP0002_USB_SUPPORTED || PHIDUID_ADP0002_VINT_SUPPORTED)
	#if PHIDUID_ADP0002_VINT_SUPPORTED
	case PHIDCHUID_ADP0002_DATAADAPTER_100_VINT:
	#endif
	#if PHIDUID_ADP0002_USB_SUPPORTED
	case PHIDCHUID_ADP0002_DATAADAPTER_100_USB:
	#endif
		maxSendReceiveLength = ch->maxReceivePacketLength;
		break;
#endif
	default:
		maxSendReceiveLength = ch->maxSendPacketLength;
		break;
	}
	if ((uint32_t)dataLen > maxSendReceiveLength) {
		*recvDataLen = 0;
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Send/receive packet length must be less than %u", maxSendReceiveLength));
	}

	res = bridgeSendToDeviceWithReply((PhidgetChannelHandle)ch, BP_DATAEXCHANGE, NULL, NULL, (uint8_t *)response, (uint32_t *)&responseLen, 1, "%*R", dataLen, data);

	if (res) {
		*recvDataLen = 0;
		if (res == EPHIDGET_TIMEOUT)
			return (PHID_RETURN_ERRSTR(EPHIDGET_TIMEOUT, "The packet timed out while waiting to be transmitted. Check that your system can keep up with the data being sent."));
		return res;
	}

	if (*recvDataLen < responseLen) {
		*recvDataLen = 0;
		return (PHID_RETURN_ERRSTR(EPHIDGET_INVALIDARG, "Receive array length too short."));
	}

	// Check if we can null terminate
	if (*recvDataLen >= (responseLen + 1))
		recvData[ch->eventDataLen] = 0;

	memcpy(recvData, response, responseLen);
	*recvDataLen = responseLen;
	if (res == EPHIDGET_OK)
		unpack32(&response[responseLen]);
	return (res);
}
