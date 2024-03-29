

#include <json/json.h>

#include "zcfg_common.h"
#include "zcfg_fe_rdm_access.h"
#include "zcfg_fe_rdm_string.h"
#include "zcfg_fe_rdm_struct.h"
#include "zcmd_schema.h"
#include "zcfg_rdm_oid.h"
#include "zcfg_rdm_obj.h"
#include "zcfg_msg.h"
#include "zcfg_debug.h"
#include "zcfg_fe_tr98.h"
#include "cellular_parameter.h"

extern tr98Object_t tr98Obj[];


/* InternetGatewayDevice.Cellular.AccessPoint */
zcfgRet_t cellularAccessPointObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag)
{
	zcfgRet_t ret;
	char accessPointObjFormate[128] = "InternetGatewayDevice.Cellular.AccessPoint.%hhu";
	uint32_t  accessPointOid = 0;
	objIndex_t accessPointIid;
	struct json_object *accessPointObj = NULL;
	struct json_object *paramValue = NULL;
	tr98Parameter_t *paramList = NULL;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);
	IID_INIT(accessPointIid);
	accessPointIid.level= 1;
	if(sscanf(tr98FullPathName, accessPointObjFormate, accessPointIid.idx) != 1) return ZCFG_INVALID_OBJECT;	
	accessPointOid = RDM_OID_CELL_ACCESS_POINT;
	
	if((ret = feObjJsonGet(accessPointOid, &accessPointIid, &accessPointObj, updateFlag)) != ZCFG_SUCCESS)
		return ret;

	/*fill up tr98 AccessPoint object*/
	*tr98Jobj = json_object_new_object();
	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		paramValue = json_object_object_get(accessPointObj, paramList->name);
		if(paramValue != NULL) {	
			json_object_object_add(*tr98Jobj, paramList->name, JSON_OBJ_COPY(paramValue));
			paramList++;
			continue;
		}
		/*Not defined in tr181, give it a default value*/
		zcfgLog(ZCFG_LOG_DEBUG, "Can't find parameter %s in TR181\n", paramList->name);
		paramList++;
	}
	json_object_put(accessPointObj);

	return ZCFG_SUCCESS;
}

zcfgRet_t cellularAccessPointObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault)
{
	zcfgRet_t ret;
	char accessPointObjFormate[128] = "InternetGatewayDevice.Cellular.AccessPoint.%hhu";
	uint32_t  accessPointOid = 0;
	objIndex_t accessPointIid;
	struct json_object *accessPointObj = NULL;
	struct json_object *paramValue = NULL;
	struct json_object *tr181ParamValue = NULL;
	struct json_object *tmpObj = NULL;
	tr98Parameter_t *paramList = NULL;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(accessPointIid);
	accessPointIid.level= 1;
	if(sscanf(tr98FullPathName, accessPointObjFormate, accessPointIid.idx) != 1) return ZCFG_INVALID_OBJECT;	
	accessPointOid = RDM_OID_CELL_ACCESS_POINT;

	if((ret = zcfgFeObjJsonGet(accessPointOid, &accessPointIid, &accessPointObj)) != ZCFG_SUCCESS)
		return ret;
	if(multiJobj){
		tmpObj = accessPointObj;
		accessPointObj = NULL;
		accessPointObj = zcfgFeJsonMultiObjAppend(accessPointOid, &accessPointIid, multiJobj, tmpObj);
	}

	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		/*Write new parameter value from tr98 object to tr181 objects*/
		paramValue = json_object_object_get(tr98Jobj, paramList->name);
		if(paramValue != NULL) {
			tr181ParamValue = json_object_object_get(accessPointObj, paramList->name);
			if(tr181ParamValue != NULL) {
				json_object_object_add(accessPointObj, paramList->name, JSON_OBJ_COPY(paramValue));
				paramList++;
				continue;
			}
		}
		paramList++;	
	} /*Edn while*/
	
	/*Set */
	if(multiJobj){
		json_object_put(tmpObj);
	}
	else{
		if((ret = zcfgFeObjJsonSet(accessPointOid, &accessPointIid, accessPointObj, NULL)) != ZCFG_SUCCESS ) {
			json_object_put(accessPointObj);
			return ret;
		}
		json_object_put(accessPointObj);
	}

	return ZCFG_SUCCESS;
}

zcfgRet_t cellularAccessPointObjAdd(char *tr98FullPathName, int *idx)
{
	zcfgRet_t ret;
	uint32_t  accessPointOid = 0;
	objIndex_t accessPointIid;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(accessPointIid);
	accessPointOid = RDM_OID_CELL_ACCESS_POINT;

	if((ret = zcfgFeObjStructAdd(accessPointOid, &accessPointIid, NULL)) != ZCFG_SUCCESS) {
		zcfgLog(ZCFG_LOG_DEBUG,"%s : Add Cellular Fail.\n", __FUNCTION__);
		return ret;
	}

	*idx = accessPointIid.idx[0];
	
	return ZCFG_SUCCESS;
}

zcfgRet_t cellularAccessPointObjDel(char *tr98FullPathName)
{
	zcfgRet_t ret;
	char accessPointObjFormate[128] = "InternetGatewayDevice.Cellular.AccessPoint.%hhu";
	uint32_t  accessPointOid = 0;
	objIndex_t accessPointIid;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(accessPointIid);
	accessPointIid.level= 1;
	if(sscanf(tr98FullPathName, accessPointObjFormate, accessPointIid.idx) != 1) return ZCFG_INVALID_OBJECT;	
	accessPointOid = RDM_OID_CELL_ACCESS_POINT;


	ret = zcfgFeObjStructDel(accessPointOid, &accessPointIid, NULL);
	if (ret != ZCFG_SUCCESS) {
		zcfgLog(ZCFG_LOG_DEBUG, "%s : Delete Cellular.%hhu Fail\n", __FUNCTION__, accessPointIid.idx[0]);
	}

	return ret;
}

/* InternetGatewayDevice.Cellular.Interface */
zcfgRet_t cellularInterfaceObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag)
{
	zcfgRet_t ret;
	char interfaceObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu";
	uint32_t  interfaceOid = 0;
	objIndex_t interfaceIid;
	struct json_object *interfaceObj = NULL;
	struct json_object *paramValue = NULL;
	tr98Parameter_t *paramList = NULL;
	const char *bands_without_info = NULL;
	char bands_buffer[128];
	
	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);
	IID_INIT(interfaceIid);
	interfaceIid.level= 1;
	if(sscanf(tr98FullPathName, interfaceObjFormate, interfaceIid.idx) != 1) return ZCFG_INVALID_OBJECT;	
	interfaceOid = RDM_OID_CELL_INTF;
	
	if((ret = feObjJsonGet(interfaceOid, &interfaceIid, &interfaceObj, updateFlag)) != ZCFG_SUCCESS)
		return ret;

	/*fill up tr98 Cellular Interface object*/
	*tr98Jobj = json_object_new_object();
	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		paramValue = json_object_object_get(interfaceObj, paramList->name);
		if(paramValue != NULL) {
			bands_without_info = json_object_get_string(json_object_object_get(interfaceObj, paramList->name));
			if (!strcmp(bands_without_info, "LTE_BC1")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC1 (LTE 2100)");
				json_object_object_add(*tr98Jobj, "X_ZYXEL_CurrentBand", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC3")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC3 (LTE 1800+)");
				json_object_object_add(*tr98Jobj, "X_ZYXEL_CurrentBand", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC7")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC7 (LTE 2600)");
				json_object_object_add(*tr98Jobj, "X_ZYXEL_CurrentBand", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC20")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC20 (LTE 800 DD)");
				json_object_object_add(*tr98Jobj, "X_ZYXEL_CurrentBand", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC28")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC28 (LTE 700 APT)");
				json_object_object_add(*tr98Jobj, "X_ZYXEL_CurrentBand", json_object_new_string(bands_buffer));
			} else {
				json_object_object_add(*tr98Jobj, paramList->name, JSON_OBJ_COPY(paramValue));
			}
			paramList++;
			continue;
		}
		/*Not defined in tr181, give it a default value*/
		zcfgLog(ZCFG_LOG_DEBUG, "Can't find parameter %s in TR181\n", paramList->name);
		paramList++;
	}
	json_object_put(interfaceObj);

	return ZCFG_SUCCESS;
}

zcfgRet_t cellularInterfaceObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault)
{
	zcfgRet_t ret;
	char interfaceObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu";
	uint32_t  interfaceOid = 0;
	objIndex_t interfaceIid;
	struct json_object *interfaceObj = NULL;
	struct json_object *paramValue = NULL;
	struct json_object *tr181ParamValue = NULL;
	struct json_object *tmpObj = NULL;
	tr98Parameter_t *paramList = NULL;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(interfaceIid);
	interfaceIid.level= 1;
	if(sscanf(tr98FullPathName, interfaceObjFormate, interfaceIid.idx) != 1) return ZCFG_INVALID_OBJECT;	
	interfaceOid = RDM_OID_CELL_INTF;

	if((ret = zcfgFeObjJsonGet(interfaceOid, &interfaceIid, &interfaceObj)) != ZCFG_SUCCESS)
		return ret;
	if(multiJobj){
		tmpObj = interfaceObj;
		interfaceObj = NULL;
		interfaceObj = zcfgFeJsonMultiObjAppend(interfaceOid, &interfaceIid, multiJobj, tmpObj);
	}

	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		/*Write new parameter value from tr98 object to tr181 objects*/
		paramValue = json_object_object_get(tr98Jobj, paramList->name);
		if(paramValue != NULL) {
			tr181ParamValue = json_object_object_get(interfaceObj, paramList->name);
			if(tr181ParamValue != NULL) {
				json_object_object_add(interfaceObj, paramList->name, JSON_OBJ_COPY(paramValue));
				paramList++;
				continue;
			}
		}
		paramList++;	
	} /*Edn while*/
	
	/*Set */
	if(multiJobj){
		json_object_put(tmpObj);
	}
	else{
		if((ret = zcfgFeObjJsonSet(interfaceOid, &interfaceIid, interfaceObj, NULL)) != ZCFG_SUCCESS ) {
			json_object_put(interfaceObj);
			return ret;
		}
		json_object_put(interfaceObj);
	}

	return ZCFG_SUCCESS;
}

zcfgRet_t cellularInterfaceObjAdd(char *tr98FullPathName, int *idx)
{
	zcfgRet_t ret;
	uint32_t  interfaceOid = 0;
	objIndex_t interfaceIid;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(interfaceIid);
	interfaceOid = RDM_OID_CELL_INTF;

	if((ret = zcfgFeObjStructAdd(interfaceOid, &interfaceIid, NULL)) != ZCFG_SUCCESS) {
		zcfgLog(ZCFG_LOG_DEBUG,"%s : Add Cellular Fail.\n", __FUNCTION__);
		return ret;
	}

	*idx = interfaceIid.idx[0];
	
	return ZCFG_SUCCESS;
}

zcfgRet_t cellularInterfaceObjDel(char *tr98FullPathName)
{
	zcfgRet_t ret;
	char interfaceObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu";
	uint32_t  interfaceOid = 0;
	objIndex_t interfaceIid;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(interfaceIid);
	interfaceIid.level= 1;
	if(sscanf(tr98FullPathName, interfaceObjFormate, interfaceIid.idx) != 1) return ZCFG_INVALID_OBJECT;	
	interfaceOid = RDM_OID_CELL_INTF;


	ret = zcfgFeObjStructDel(interfaceOid, &interfaceIid, NULL);
	if (ret != ZCFG_SUCCESS) {
		zcfgLog(ZCFG_LOG_DEBUG, "%s : Delete Cellular.%hhu Fail\n", __FUNCTION__, interfaceIid.idx[0]);
	}

	return ret;
}

/* InternetGatewayDevice.Cellular.Interface.i.X_ZYXEL_SecondaryComponentCarrier.i */
zcfgRet_t cellularInterfaceSCCObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag)
{
	zcfgRet_t ret;
	char ruleObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.X_ZYXEL_SecondaryComponentCarrier.%hhu";
	uint32_t  ruleOid = 0;
	objIndex_t ruleIid;
	struct json_object *ruleObj = NULL;
	struct json_object *paramValue = NULL;
	tr98Parameter_t *paramList = NULL;
	const char *bands_without_info = NULL;
	char bands_buffer[128];
	
	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(ruleIid);
	ruleIid.level = 2;
	if(sscanf(tr98FullPathName, ruleObjFormate, &ruleIid.idx[0], &ruleIid.idx[1]) != 2) return ZCFG_INVALID_OBJECT;	
	ruleOid = RDM_OID_CELL_INTF_ZY_SCC;

	if((ret = feObjJsonGet(ruleOid, &ruleIid, &ruleObj, updateFlag)) != ZCFG_SUCCESS)
		return ret;
		

	/*fill up tr98 rule object*/
	*tr98Jobj = json_object_new_object();
	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		paramValue = json_object_object_get(ruleObj, paramList->name);
		if(paramValue != NULL) {
			bands_without_info = json_object_get_string(json_object_object_get(ruleObj, paramList->name));
			if (!strcmp(bands_without_info, "LTE_BC1")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC1 (LTE 2100)");
				json_object_object_add(*tr98Jobj, "Band", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC3")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC3 (LTE 1800+)");
				json_object_object_add(*tr98Jobj, "Band", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC7")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC7 (LTE 2600)");
				json_object_object_add(*tr98Jobj, "Band", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC20")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC20 (LTE 800 DD)");
				json_object_object_add(*tr98Jobj, "Band", json_object_new_string(bands_buffer));
			}
			else if (!strcmp(bands_without_info, "LTE_BC28")){
				snprintf(bands_buffer, sizeof(bands_buffer), "%s", "LTE_BC28 (LTE 700 APT)");
				json_object_object_add(*tr98Jobj, "Band", json_object_new_string(bands_buffer));
			} else {
				json_object_object_add(*tr98Jobj, paramList->name, JSON_OBJ_COPY(paramValue));
			}
			paramList++;
			continue;
		}
		/*Not defined in tr181, give it a default value*/
		zcfgLog(ZCFG_LOG_DEBUG, "Can't find parameter %s in TR181\n", paramList->name);
		paramList++;
	}
	json_object_put(ruleObj);

	return ZCFG_SUCCESS;
}

zcfgRet_t cellularInterfaceSCCObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault)
{
	zcfgRet_t ret;
	char ruleObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.X_ZYXEL_SecondaryComponentCarrier.%hhu";
	uint32_t  ruleOid = 0;
	objIndex_t ruleIid;
	struct json_object *ruleObj = NULL;
	struct json_object *paramValue = NULL;
	struct json_object *tr181ParamValue = NULL;
	struct json_object *tmpObj = NULL;
	tr98Parameter_t *paramList = NULL;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(ruleIid);
	ruleIid.level = 2;
	if(sscanf(tr98FullPathName, ruleObjFormate, &ruleIid.idx[0], &ruleIid.idx[1]) != 2) return ZCFG_INVALID_OBJECT;	
	ruleOid = RDM_OID_CELL_INTF_ZY_SCC;

	if((ret = zcfgFeObjJsonGet(ruleOid, &ruleIid, &ruleObj)) != ZCFG_SUCCESS)
		return ret;
	if(multiJobj){
		tmpObj = ruleObj;
		ruleObj = NULL;
		ruleObj = zcfgFeJsonMultiObjAppend(ruleOid, &ruleIid, multiJobj, tmpObj);
	}

	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		/*Write new parameter value from tr98 object to tr181 objects*/
		paramValue = json_object_object_get(tr98Jobj, paramList->name);
		if(paramValue != NULL) {
			tr181ParamValue = json_object_object_get(ruleObj, paramList->name);
			if(tr181ParamValue != NULL) {
				json_object_object_add(ruleObj, paramList->name, JSON_OBJ_COPY(paramValue));
				paramList++;
				continue;
			}
		}
		paramList++;	
	} /*Edn while*/
	
	/*Set */
	if(multiJobj){
		json_object_put(tmpObj);
	}
	else{
		if((ret = zcfgFeObjJsonSet(ruleOid, &ruleIid, ruleObj, NULL)) != ZCFG_SUCCESS ) {
			json_object_put(ruleObj);
			return ret;
		}
		json_object_put(ruleObj);
	}

	return ZCFG_SUCCESS;
}

zcfgRet_t cellularInterfaceSCCObjAdd(char *tr98FullPathName, int *idx)
{
	zcfgRet_t ret;
	char ruleObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.X_ZYXEL_SecondaryComponentCarrier";
	uint32_t  ruleOid = 0;
	objIndex_t ruleIid;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(ruleIid);
	ruleIid.level = 1;
	if(sscanf(tr98FullPathName, ruleObjFormate, &ruleIid.idx[0]) != 1) return ZCFG_INVALID_OBJECT;	
	ruleOid = RDM_OID_CELL_INTF_ZY_SCC;

	if((ret = zcfgFeObjStructAdd(ruleOid, &ruleIid, NULL)) != ZCFG_SUCCESS) {
		zcfgLog(ZCFG_LOG_DEBUG,"%s : Add Cellular.Interface.%hhu.X_ZYXEL_SecondaryComponentCarrier. Fail.\n", __FUNCTION__, ruleIid.idx[0]);
		return ret;
	}

	*idx = ruleIid.idx[1];
	
	return ZCFG_SUCCESS;
}

zcfgRet_t cellularInterfaceSCCObjDel(char *tr98FullPathName)
{
	zcfgRet_t ret;
	char ruleObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.X_ZYXEL_SecondaryComponentCarrier.%hhu";
	uint32_t  ruleOid = 0;
	objIndex_t ruleIid;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(ruleIid);
	ruleIid.level = 2;
	if(sscanf(tr98FullPathName, ruleObjFormate, &ruleIid.idx[0], &ruleIid.idx[1]) != 2) return ZCFG_INVALID_OBJECT;	
	ruleOid = RDM_OID_CELL_INTF_ZY_SCC;

	ret = zcfgFeObjStructDel(ruleOid, &ruleIid, NULL);
	if (ret != ZCFG_SUCCESS) {
		zcfgLog(ZCFG_LOG_DEBUG, "%s : Delete Cellular.Interface.%hhu.X_ZYXEL_SecondaryComponentCarrier.%hhu Fail\n", __FUNCTION__, ruleIid.idx[0], ruleIid.idx[1]);
	}

	return ret;
}

/* InternetGatewayDevice.Cellular.Interface.i.X_ZYXEL_NeighbourCell.i */
zcfgRet_t cellIntfZyNbrCellObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag)
{
	zcfgRet_t ret;
	char pathFormat[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.X_ZYXEL_NeighbourCell.%hhu";
	zcfg_offset_t oid = RDM_OID_CELL_INTF_ZY_NBR_CELL;
	objIndex_t iid;
	json_object *obj = NULL;
	json_object *paramValue = NULL;
	tr98Parameter_t *paramList = NULL;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(iid);
	iid.level = 2;
	if(sscanf(tr98FullPathName, pathFormat, &iid.idx[0], &iid.idx[1]) != 2)
		return ZCFG_INVALID_OBJECT;

	if((ret = feObjJsonGet(oid, &iid, &obj, updateFlag)) != ZCFG_SUCCESS)
		return ret;

	/*fill up tr98 rule object*/
	*tr98Jobj = json_object_new_object();
	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		paramValue = json_object_object_get(obj, paramList->name);
		if(paramValue != NULL) {
			json_object_object_add(*tr98Jobj, paramList->name, JSON_OBJ_COPY(paramValue));
			paramList++;
			continue;
		}
		/*Not defined in tr181, give it a default value*/
		zcfgLog(ZCFG_LOG_DEBUG, "Can't find parameter %s in TR181\n", paramList->name);
		paramList++;
	}
	json_object_put(obj);

	return ZCFG_SUCCESS;
}

#if 1//Jessie
/* InternetGatewayDevice.Cellular.Interface.i.USIM */
zcfgRet_t cellularInterfaceUSIMObjGet(char *tr98FullPathName, int handler, struct json_object **tr98Jobj, bool updateFlag)
{
	zcfgRet_t ret;
	char ruleObjFormate[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.USIM";
	uint32_t  ruleOid = 0;
	objIndex_t ruleIid;
	struct json_object *ruleObj = NULL;
	struct json_object *paramValue = NULL;
	tr98Parameter_t *paramList = NULL;
	
	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);
printf("%s() Jessie tr98FullPathName=%s\n", __FUNCTION__, tr98FullPathName);
	IID_INIT(ruleIid);
	ruleIid.level = 1;//2->1 Jessie
	if(sscanf(tr98FullPathName, ruleObjFormate, &ruleIid.idx[0]) != 1) return ZCFG_INVALID_OBJECT;	
	ruleOid = RDM_OID_CELL_INTF_USIM;
printf("%s() Jessie ruleIid.idx[0]=%d\n", __FUNCTION__, ruleIid.idx[0]);
	if((ret = feObjJsonGet(ruleOid, &ruleIid, &ruleObj, updateFlag)) != ZCFG_SUCCESS)
		return ret;
		

	/*fill up tr98 rule object*/
	*tr98Jobj = json_object_new_object();
	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		printf("%s() Jessie paramList->name=%s\n", __FUNCTION__, paramList->name);
		paramValue = json_object_object_get(ruleObj, paramList->name);
		if(paramValue != NULL) {
			json_object_object_add(*tr98Jobj, paramList->name, JSON_OBJ_COPY(paramValue));
			
			paramList++;
			continue;
		}
		/*Not defined in tr181, give it a default value*/
		zcfgLog(ZCFG_LOG_DEBUG, "Can't find parameter %s in TR181\n", paramList->name);
		paramList++;
	}
	json_object_put(ruleObj);

	return ZCFG_SUCCESS;
}
#endif

zcfgRet_t cellIntfZyNbrCellObjSet(char *tr98FullPathName, int handler, struct json_object *tr98Jobj, struct json_object *multiJobj, char *paramfault)
{
	zcfgRet_t ret;
	char pathFormat[128] = "InternetGatewayDevice.Cellular.Interface.%hhu.X_ZYXEL_NeighbourCell.%hhu";
	zcfg_offset_t oid = RDM_OID_CELL_INTF_ZY_NBR_CELL;
	objIndex_t iid;
	json_object *obj = NULL;
	json_object *paramValue = NULL;
	json_object *tr181ParamValue = NULL;
	json_object *tmpObj = NULL;
	tr98Parameter_t *paramList = NULL;

	zcfgLog(ZCFG_LOG_DEBUG, "Enter %s\n", __FUNCTION__);

	IID_INIT(iid);
	iid.level = 2;
	if(sscanf(tr98FullPathName, pathFormat, &iid.idx[0], &iid.idx[1]) != 2)
		return ZCFG_INVALID_OBJECT;

	if((ret = zcfgFeObjJsonGet(oid, &iid, &obj)) != ZCFG_SUCCESS)
		return ret;
	if(multiJobj){
		tmpObj = obj;
		obj = NULL;
		obj = zcfgFeJsonMultiObjAppend(oid, &iid, multiJobj, tmpObj);
	}

	paramList = tr98Obj[handler].parameter;
	while(paramList->name != NULL) {
		/*Write new parameter value from tr98 object to tr181 objects*/
		paramValue = json_object_object_get(tr98Jobj, paramList->name);
		if(paramValue != NULL) {
			tr181ParamValue = json_object_object_get(obj, paramList->name);
			if(tr181ParamValue != NULL) {
				json_object_object_add(obj, paramList->name, JSON_OBJ_COPY(paramValue));
				paramList++;
				continue;
			}
		}
		paramList++;
	} /*Edn while*/

	/*Set */
	if(multiJobj){
		json_object_put(tmpObj);
	}
	else{
		if((ret = zcfgFeObjJsonSet(oid, &iid, obj, NULL)) != ZCFG_SUCCESS ) {
			json_object_put(obj);
			return ret;
		}
		json_object_put(obj);
	}

	return ZCFG_SUCCESS;
}

