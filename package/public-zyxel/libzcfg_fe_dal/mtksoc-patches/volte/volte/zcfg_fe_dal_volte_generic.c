#include <ctype.h>
#include <json/json.h>
//#include <json/json_object.h>
#include <time.h>

#include "zcfg_common.h"
#include "zcfg_fe_rdm_string.h"
#include "zcfg_fe_rdm_struct.h"
#include "zcfg_fe_rdm_access.h"
#include "zcfg_rdm_oid.h"
#include "zcfg_rdm_obj.h"
#include "zcfg_debug.h"
#include "zcfg_msg.h"
#include "zcfg_fe_dal_common.h"
#include "zcfg_webgui_flag.h"

dal_param_t VOLTE_param[] =
{
	{"voiceSelVal", dalType_boolean,    0,    0,    NULL},
	{NULL,             0,                  0,    0,    NULL},
};

zcfgRet_t zcfgFeDalShowVolte(struct json_object *Jarray, char *replyMsg){
	int i, len = 0;
	struct json_object *obj = NULL;

	if(json_object_get_type(Jarray) != json_type_array){
		printf("wrong Jobj format!\n");
		return;
	}

	len = json_object_array_length(Jarray);
	printf("VoLTE Enable Configuration\n");
	for(i=0; i<len; i++){
		obj = json_object_array_get_idx(Jarray, i);
		printf("%-20s %d \n","VolteEnable :",json_object_get_boolean(json_object_object_get(obj, "voiceSelVal")));
	}

	return;
}

zcfgRet_t zcfgFeDal_volteGeneral_Edit(struct json_object *Jobj, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	struct json_object *volteObj = NULL;
	objIndex_t volteIid = {0};
	bool volteEnable = false;

	IID_INIT(volteIid); 
	while( zcfgFeObjJsonGetNext(RDM_OID_VOICE_VOLTE, &volteIid, &volteObj) == ZCFG_SUCCESS ){ 
		if(json_object_object_get(Jobj, "voiceSelVal") != NULL){ 
			volteEnable = json_object_get_boolean(json_object_object_get(Jobj, "voiceSelVal")); 
			json_object_object_add(volteObj, "VolteEnable", json_object_new_boolean(volteEnable)); 

			/*Device.Services.VoiceService.i.X_ZYXEL_VOLTE.volte_Enable*/
			if((ret = zcfgFeObjJsonSet(RDM_OID_VOICE_VOLTE, &volteIid, volteObj, NULL)) != ZCFG_SUCCESS){ 
				printf("%s: Set RDM_OID_VOICE_VOLTE object fail. ret=[%d]\n", __FUNCTION__,ret); 
				return ret; 
			} 
			if(volteObj) 
				zcfgFeJsonObjFree(volteObj); 
		}
	} 

#if 1	// After configuration changed, it need to do "reboot" or "/usr/bin/zyims.sh restart" when VoIP/VoLTE support in the same time.
	if(ret==ZCFG_SUCCESS)
		zcfgFeReqReboot(NULL);
//		system("/usr/bin/zyims.sh restart");	//need test.
#endif

	return ret;
}

zcfgRet_t zcfgFeDal_volteGeneral_Get(struct json_object *Jobj, struct json_object *Jarray, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	struct json_object *paramJobj = NULL;
	struct json_object *volteObj = NULL;
	objIndex_t objIid = {0};

	IID_INIT(objIid);
	paramJobj = json_object_new_object();

	while( zcfgFeObjJsonGetNext(RDM_OID_VOICE_VOLTE, &objIid, &volteObj) == ZCFG_SUCCESS){ 
	 	json_object_object_add(paramJobj, "voiceSelVal", JSON_OBJ_COPY(json_object_object_get(volteObj, "VolteEnable"))); 
		//printf("json_object_get_boolean(json_object_object_get(paramJobj,VolteEnable) = %d\n", json_object_get_boolean(json_object_object_get(paramJobj, "VolteEnable")));
	 	zcfgFeJsonObjFree(volteObj); 
	} 

	json_object_array_add(Jarray, paramJobj);

	return ret;
}


zcfgRet_t zcfgFeDalVolte(const char *method, struct json_object *Jobj, struct json_object *Jarray, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;

	if(!method || !Jobj)
		return ZCFG_INTERNAL_ERROR;

	if(!strcmp(method, "PUT")) {
		ret = zcfgFeDal_volteGeneral_Edit(Jobj, NULL);
	}else if(!strcmp(method, "GET"))
		ret = zcfgFeDal_volteGeneral_Get(Jobj, Jarray, NULL);
	else
		printf("Unknown method:%s\n", method);

	return ret;
}

