
#include <json/json.h>

#include "zcfg_common.h"
#include "zcfg_fe_rdm_string.h"
#include "zcfg_fe_rdm_struct.h"
#include "zcfg_rdm_oid.h"
#include "zcfg_rdm_obj.h"
#include "zcfg_debug.h"
#include "zcfg_msg.h"
#include "zcfg_fe_dal_common.h"
#include "zcfg_webgui_flag.h"

#define SETCALLBLOCK			0
#define CLEANALLCALLBLOCK		1

dal_param_t VOIP_CALLBLOCK_param[]={
	{"Enable",									dalType_string,	0,	0,	NULL},
	{"Direction",								dalType_string,	0,	0,	NULL},
	{"Description",								dalType_string,	0,	0,	NULL},
	{"PhoneNumber",								dalType_string,	0,	0,	NULL},
	{NULL,										0,				0,	0,	NULL},
};

struct json_object *multiJobj;
struct json_object *callBlockListJobj;

objIndex_t CallBlockIid = {0};

bool cleanAll;
bool callBlockType;

const char* Enable;
const char* Direction;
const char* PhoneNumber;
const char* Description;

void initCallBlockGlobalObjects(){
	multiJobj = NULL;
	callBlockListJobj = NULL;
	return;
}

void getCallBlockBasicInfo(struct json_object *Jobj){
	Enable = json_object_get_string(json_object_object_get(Jobj, "Enable"));
	Direction = json_object_get_string(json_object_object_get(Jobj, "Direction"));
	PhoneNumber = json_object_get_string(json_object_object_get(Jobj, "PhoneNumber"));
	Description = json_object_get_string(json_object_object_get(Jobj, "Description"));

	return;
}

zcfgRet_t zcfgFeDalCallBlockObjEditIidGet(struct json_object *Jobj){
	zcfgRet_t ret = ZCFG_SUCCESS;

	cleanAll = json_object_get_boolean(json_object_object_get(Jobj, "CleanAll"));
	if(cleanAll == TRUE){
		callBlockType = CLEANALLCALLBLOCK;
	}else{
		callBlockType = SETCALLBLOCK;
	}

	return ret;
}

void freeAllCallBlockObjects(){
	if(multiJobj) json_object_put(multiJobj);
	if(callBlockListJobj) json_object_put(callBlockListJobj);

	return;
}

zcfgRet_t zcfgFeDalVoipCleanAllCallBlock(struct json_object *Jobj){
	zcfgRet_t ret = ZCFG_SUCCESS;
	struct json_object *setJson = NULL;
	IID_INIT(CallBlockIid);
	//printf("%s() Enter \n ",__FUNCTION__);

	while(zcfgFeObjJsonGetNextWithoutUpdate(RDM_OID_CALL_POLICY_BOOK_LIST, &CallBlockIid, &callBlockListJobj) == ZCFG_SUCCESS) {
		json_object_object_add(callBlockListJobj, "Enable", json_object_new_boolean(false));
		json_object_object_add(callBlockListJobj, "Direction", json_object_new_string("Incoming"));
		json_object_object_add(callBlockListJobj, "PhoneNumber", json_object_new_string(""));
		json_object_object_add(callBlockListJobj, "Description", json_object_new_string(""));

		if((setJson = zcfgFeJsonMultiObjAppend(RDM_OID_CALL_POLICY_BOOK_LIST, &CallBlockIid, multiJobj, callBlockListJobj)) == NULL){
			printf("%s:(ERROR) fail to append object oid(%d)\n", __FUNCTION__, RDM_OID_CALL_POLICY_BOOK_LIST);
			zcfgFeJsonObjFree(callBlockListJobj);
			return ZCFG_INTERNAL_ERROR;
		}
		zcfgFeJsonObjFree(callBlockListJobj);
	}

	//printf("%s(): Append call policy book list obj to multiJobj (%s) \n ",__FUNCTION__,json_object_to_json_string(multiJobj));
	//printf("%s() exit \n ",__FUNCTION__);
	return ret;

}

zcfgRet_t zcfgFeDalVoipSetAllCallBlock(struct json_object *Jobj){
	struct json_object *setJson = NULL;
	zcfgRet_t ret = ZCFG_SUCCESS;
	//printf("%s() Enter \n ",__FUNCTION__);
	char *enable;
	char *direction;
	char *phoneNumber;
	char *description;

	IID_INIT(CallBlockIid);
	while(zcfgFeObjJsonGetNextWithoutUpdate(RDM_OID_CALL_POLICY_BOOK_LIST, &CallBlockIid, &callBlockListJobj) == ZCFG_SUCCESS) {
		if((enable = strsplit_getfirst(&Enable, ",")) != NULL){
			//printf("enable:%s\n" , enable);
		}
		if((direction = strsplit_getfirst(&Direction, ",")) != NULL){
			//printf("direction:%s\n" , direction);
		}
		if((phoneNumber = strsplit_getfirst(&PhoneNumber, ",")) != NULL){
			//printf("phoneNumber:%s\n" , phoneNumber);
		}
		if((description = strsplit_getfirst(&Description, ",")) != NULL){
			//printf("description:%s\n" , description);
		}

		if(strcmp(enable,"true") == 0){
			json_object_object_add(callBlockListJobj, "Enable", json_object_new_boolean(true));
		}else{
			json_object_object_add(callBlockListJobj, "Enable", json_object_new_boolean(false));
		}
		json_object_object_add(callBlockListJobj, "Direction", json_object_new_string(direction));

		if(strcmp(phoneNumber,"None") != 0){
			json_object_object_add(callBlockListJobj, "PhoneNumber", json_object_new_string(phoneNumber));
		}else{
			json_object_object_add(callBlockListJobj, "PhoneNumber", json_object_new_string(""));
		}
		if(strcmp(description,"None") != 0){
			json_object_object_add(callBlockListJobj, "Description", json_object_new_string(description));
		}else{
			json_object_object_add(callBlockListJobj, "Description", json_object_new_string(""));
		}

		if((setJson = zcfgFeJsonMultiObjAppend(RDM_OID_CALL_POLICY_BOOK_LIST, &CallBlockIid, multiJobj, callBlockListJobj)) == NULL){
			printf("%s:(ERROR) fail to append object oid(%d)\n", __FUNCTION__, RDM_OID_CALL_POLICY_BOOK_LIST);
			zcfgFeJsonObjFree(callBlockListJobj);
			return ZCFG_INTERNAL_ERROR;
		}

		zcfgFeJsonObjFree(callBlockListJobj);
	}

	//printf("%s(): Append call policy book list obj to multiJobj (%s) \n ",__FUNCTION__,json_object_to_json_string(multiJobj));
	//rintf("%s() exit \n ",__FUNCTION__);
	return ret;

}


zcfgRet_t zcfgFeDalVoipCallBlockEdit(struct json_object *Jobj, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	printf("%s(): input --- %s \n ",__FUNCTION__,json_object_to_json_string(Jobj));

	initCallBlockGlobalObjects();
	getCallBlockBasicInfo(Jobj);
	zcfgFeDalCallBlockObjEditIidGet(Jobj);
	multiJobj = zcfgFeJsonObjNew();

	if(callBlockType == CLEANALLCALLBLOCK){
		if((ret = zcfgFeDalVoipCleanAllCallBlock(Jobj)) != ZCFG_SUCCESS){
			printf("%s:(ERROR) fail to edit call policy book list obj \n", __FUNCTION__);
			goto exit;
		}
	}else if(callBlockType == SETCALLBLOCK){
		if((ret = zcfgFeDalVoipSetAllCallBlock(Jobj)) != ZCFG_SUCCESS){
			printf("%s:(ERROR) fail to edit call policy book list obj \n", __FUNCTION__);
			goto exit;
		}
	}

	if((ret = zcfgFeMultiObjJsonSet(multiJobj, NULL)) != ZCFG_SUCCESS){
		printf("%s:(ERROR) fail to set object %d\n", __FUNCTION__, RDM_OID_CALL_POLICY_BOOK_LIST);
		goto exit;
	}

exit:
	freeAllCallBlockObjects();
	return ret;
}

zcfgRet_t zcfgFeDalVoipCallBlock(const char *method, struct json_object *Jobj, struct json_object *Jarray, char *replyMsg)
{
	zcfgRet_t ret = ZCFG_SUCCESS;

	if(!method || !Jobj)
		return ZCFG_INTERNAL_ERROR;

	if(!strcmp(method, "PUT")) {
		ret = zcfgFeDalVoipCallBlockEdit(Jobj, NULL);
	}

	return ret;
}

