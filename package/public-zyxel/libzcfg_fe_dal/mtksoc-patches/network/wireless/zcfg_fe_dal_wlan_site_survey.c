#include <ctype.h>
#include <json/json.h>
//#include <json/json_object.h>
#include <time.h>

#include "zcfg_common.h"
#include "zcfg_fe_rdm_string.h"
#include "zcfg_fe_rdm_struct.h"
#include "zcfg_rdm_oid.h"
#include "zcfg_rdm_obj.h"
#include "zcfg_debug.h"
//#include "zcfg_eid.h"
#include "zcfg_msg.h"
#include "zcfg_fe_dal_common.h"

//#define JSON_OBJ_COPY(json_object) json_tokener_parse(json_object_to_json_string(json_object))

dal_param_t WLAN_SITE_SURVEY_param[]={
	{"Enable",						dalType_boolean,	0,	0,	NULL,	1,	dal_Edit},
#if defined(TELIA_CUSTOMIZATION) && defined(ZY_WIFI_ECONET_5G)
	{"Band",						dalType_string,		0,	0,	NULL,	"2.4GHz|5GHz",	dal_Get},
#endif
	{NULL,		0,	0,	0,	NULL,	NULL,	0},
};

void zcfgFeDalShowWlanSiteSurvey(struct json_object *Jarray){						
	char sysCmd[64] = {0};
	char cmd[512] = {0};
#if defined(TELIA_CUSTOMIZATION) && defined(ZY_WIFI_ECONET_5G)
	char *band = NULL;
	struct json_object *Jobj;
	char ifName[65] = {0};
	if(json_object_get_type(Jarray) != json_type_array){
		printf("%s: wrong Jobj format!\n", __FUNCTION__);
		return;
	}
	Jobj = json_object_array_get_idx(Jarray, 0);
	band = json_object_get_string(json_object_object_get(Jobj,"Band"));

	if(!strcmp(band, "2.4GHz")) {
		strcpy(ifName, "ra0");
	}
	else {
		strcpy(ifName, "rai0");
	}

	snprintf(sysCmd, sizeof(sysCmd), "dmesg -n 1; iwpriv %s set SiteSurvey=1 > /dev/null", ifName);
	system(sysCmd);
	
	sleep(5);
	snprintf(sysCmd, sizeof(sysCmd), "dmesg -n 7; iwpriv %s get_site_survey > /tmp/site_survey_ra0", ifName);
	system(sysCmd);
#else
	snprintf(sysCmd, sizeof(sysCmd), "dmesg -n 1; iwpriv ra0 set SiteSurvey=1 > /dev/null");
    system(sysCmd);
	
	sleep(5);
	
	snprintf(sysCmd, sizeof(sysCmd), "dmesg -n 7; iwpriv ra0 get_site_survey > /tmp/site_survey_ra0");
    system(sysCmd);
#endif	
    FILE *fp = fopen("/tmp/site_survey_ra0", "r");
    if(fp) {
		while(fgets(cmd, sizeof(cmd)-1, fp) != NULL) { 
			printf("%s", cmd);
			memset(cmd, 0, sizeof(cmd));
		}
		fclose(fp);
    }

	
}

zcfgRet_t zcfgFeDalWlanSiteSurveyGet(struct json_object *Jobj, struct json_object *Jarray, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
#if defined(TELIA_CUSTOMIZATION) && defined(ZY_WIFI_ECONET_5G)
	struct json_object *paramObj = NULL;
	paramObj = json_object_new_object();
	char *band = NULL;
	band = json_object_get_string(json_object_object_get(Jobj,"Band"));
	json_object_object_add(paramObj, "Band", json_object_new_string(band));
	json_object_array_add(Jarray,paramObj);
#endif
	return ret;
}

zcfgRet_t zcfgFeDalWlanSiteSurveyEdit(struct json_object *Jobj, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	char sysCmd[32] = {0};
	
	snprintf(sysCmd, sizeof(sysCmd), "iwpriv ra0 set SiteSurvey=1");
    system(sysCmd);
	return ret;
}

zcfgRet_t zcfgFeDalWlanSiteSurvey(const char *method, struct json_object *Jobj, struct json_object *Jarray, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	
	//if(!strcmp(method, "POST"))
		//ret = zcfgFeDalWifiOthersAdd(Jobj, NULL);
	if(!strcmp(method, "PUT"))
		ret = zcfgFeDalWlanSiteSurveyEdit(Jobj, NULL);
	else if(!strcmp(method, "GET"))
		ret = zcfgFeDalWlanSiteSurveyGet(Jobj, Jarray, replyMsg);
	else
		printf("Unknown method:%s\n", method);

	return ret;
}


