/************************************************************************
 *
 *	Copyright (C) 2006 Trendchip Technologies, Corp.
 *	All Rights Reserved.
 *
 * Trendchip Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of Trendchip Technologies, Co. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * Trendchip Technologeis, Co.
 *
 *************************************************************************/
#ifndef _VOLTE_MONITOR_H_
#define _VOLTE_MONITOR_H_

#define CALL_ID_OUTGOING_CALL	4097	//0x1001
#define CALL_ID_INCOMING_CALL	32768	//0x8000

#define VOICEAPP_IPTK_CHANNEL_PATH	"/var/voiceApp_iptk.chanl"

#define CALL_VOICE_MODE		0
#define AT_COMMAND_PREFIX	"/usr/bin/atcmd"

typedef enum {
	PHONE_STATUS_INIT,
	PHONE_STATUS_IDLE,
	PHONE_STATUS_DIAL,
	PHONE_STATUS_ALERT,
	PHONE_STATUS_RING,
	PHONE_STATUS_DATA
} PhoneStatus_t;

typedef enum {
	CALL_STATUS_ACTIVE		= 0,
	CALL_STATUS_HELD		= 1,
	CALL_STATUS_DIALING		= 2,
	CALL_STATUS_ALERTING	= 3,
	CALL_STATUS_INCOMING	= 4,
	CALL_STATUS_WAITING		= 5,
	CALL_STATUS_NO_CALL
} CallStatus_t;

typedef struct {
	PhoneStatus_t state;
	void (*func)(PhoneStatus_t *phone_status, CallStatus_t call_status);
} StateMachine_t;

void processStatusInit(PhoneStatus_t *phone_status, CallStatus_t call_status);
void processStatusIdle(PhoneStatus_t *phone_status, CallStatus_t call_status);
void processStatusDial(PhoneStatus_t *phone_status, CallStatus_t call_status);
void processStatusAlert(PhoneStatus_t *phone_status, CallStatus_t call_status);
void processStatusRing(PhoneStatus_t *phone_status, CallStatus_t call_status);
void processStatusData(PhoneStatus_t *phone_status, CallStatus_t call_status);

int fill_incoming_call_event_data(void **buf);
int fill_call_terminate_event_data(void **buf);
int fill_call_connect_event_data(void **buf);

void sendData(void *buf);

int getCallStatus(CallStatus_t *call_status);
int isVolteReady();

#endif
