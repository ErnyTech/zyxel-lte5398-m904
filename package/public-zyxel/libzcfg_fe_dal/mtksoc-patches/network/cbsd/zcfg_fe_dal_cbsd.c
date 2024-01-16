#include <ctype.h>
#include <json/json.h>
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

#ifdef ZYXEL_WEB_GUI_SUPPORT_SAS_CBSD

dal_param_t CBSD_param[]={
{"Enable", dalType_boolean, 0, 0, NULL},
{"DebugEnable", dalType_boolean, 0, 0, NULL},
{"AutoRegistration", dalType_boolean, 0, 0, NULL},
{"Status", dalType_string, 0, 32, NULL},
{"State", dalType_string, 0, 32, NULL},
{"ResponseCode",dalType_int, 0, 2000, NULL},
{"ResponseData", dalType_string, 0, 128, NULL},
{"ProcedureType",dalType_int, 0, 100, NULL},
{"MaximiseTxPower", dalType_boolean, 0, 0, NULL},
{"MsgType",dalType_int, 0, 100, NULL},
{"UserId", dalType_string, 0, 64, NULL},
{"FccId", dalType_string, 0, 20, NULL},
{"CbsdSerialNumber", dalType_string, 0, 64, NULL},
{"CallSign", dalType_string, 0, 128, NULL},
{"CbsdCategory", dalType_string, 0, 4, NULL},
{"Vendor", dalType_string, 0, 64, NULL},
{"Model", dalType_string, 0, 64, NULL},
{"SoftwareVersion", dalType_string, 0, 64, NULL},
{"HardwareVersion", dalType_string, 0, 64, NULL},
{"FirmwareVersion", dalType_string, 0, 64, NULL},
{"RadioTechnology", dalType_string, 0, 64, NULL},
{"InstallationParametersFlag", dalType_boolean, 0, 0, NULL},
{"Latitude", dalType_int, -90000000, 90000000, NULL},
{"Longitude", dalType_int, -180000000, 180000000, NULL},
{"Height", dalType_int, -180000000, 180000000, NULL},
{"HeightType", dalType_int, 0, 1, NULL},
{"HorizontalAccuracy", dalType_int, 0, 50000000, NULL},
{"VerticalAccuracy", dalType_int, 0, 3000000, NULL},
{"IndoorDeployment", dalType_boolean, 0, 0, NULL},
{"AntennaAzimuth", dalType_int, 0, 359, NULL},
{"AntennaDowntilt", dalType_int, -90, 90, NULL},
{"AntennaGain", dalType_int, -127, 128, NULL},
{"EirpCapability", dalType_int, -127, 47, NULL},
{"AntennaBeamwidth", dalType_int, 0, 360, NULL},
{"AntennaModel", dalType_string, 0, 128, NULL},
{"MeasCapability", dalType_string, 0, 32, NULL},
{"LowFrequency", dalType_int, 0, 0, NULL},
{"HighFrequency", dalType_int, 0, 0, NULL},
{"MaximumEirp", dalType_int, -137, 37, NULL},
{"SasOperator", dalType_string, 0, 64, NULL},
{"SasAddress", dalType_string, 0, 52, NULL},
{"RootCertificate", dalType_string, 0, 256, NULL},
{"UutCertificate", dalType_string, 0, 256, NULL},
{"UutCertificateExpiryDate", dalType_string, 0, 64, NULL},
{"BoundInterface", dalType_string, 0, 64, NULL},
{"EncryptInstallFlag", dalType_boolean, 0, 0, NULL},
{"CpiId", dalType_string, 0, 256, NULL},
{"CpiName", dalType_string, 0, 256, NULL},
{"InstallCertificationTime", dalType_string, 0, 24, NULL},
{"CpiCertificate", dalType_string, 0, 256, NULL},
{"CpiSignatureDataFlag", dalType_boolean, 0, 0, NULL},
{"ProtectedHeader", dalType_string, 0, 128, NULL},
{"EncodedCpiSignedData", dalType_string, 0, 1024, NULL},
{"DigitalSignature", dalType_string, 0, 1024, NULL},
{ NULL,	0,	0,	0,	NULL}

};

#define CBSD_DEV_INFO_STR_LEN 64
typedef struct cbsd_dev_info_s {
	char	cbsdSn[CBSD_DEV_INFO_STR_LEN];
	char	vendor[CBSD_DEV_INFO_STR_LEN];
	char	model[CBSD_DEV_INFO_STR_LEN];
	char	swVer[CBSD_DEV_INFO_STR_LEN];
	char	hwVer[CBSD_DEV_INFO_STR_LEN];
}cbsd_dev_info_t;

typedef struct cbsd_dev_info_handler_s {
	char		*srcParaName;
	char		*dstParaName;
	char		*retrvValue;
}cbsd_dev_info_handler_t;

zcfgRet_t retrvDevInfo(cbsd_dev_info_handler_t *cbsdDevInfoHandler){
	zcfgRet_t ret = ZCFG_SUCCESS;
	objIndex_t iid = {0};
	struct json_object *devInfoObj = NULL;
	int n = 0;
	const char *srcParaName;

	IID_INIT(iid);
	if((ret = zcfgFeObjJsonGetWithoutUpdate(RDM_OID_DEV_INFO, &iid, &devInfoObj)) == ZCFG_SUCCESS){
		while((srcParaName = (const char *)cbsdDevInfoHandler[n].srcParaName) != NULL) {
			if(Jget(devInfoObj, srcParaName)) {
				strcpy(cbsdDevInfoHandler[n].retrvValue, Jgets(devInfoObj, srcParaName));
				printf("[%d] F:%s, srcParaName:%s, retrvValue:%s\n", __LINE__,  __func__, srcParaName, cbsdDevInfoHandler[n].retrvValue);
			}
			n++;
		}
		zcfgFeJsonObjFree(devInfoObj);
	}

	return ret;
}


zcfgRet_t zcfgFeDalCbsdEdit(struct json_object *Jobj, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	objIndex_t iid = {0};
	const char *paraName, *dstParaName;
	struct json_object *cbsdObj = NULL;
	int paramModified = 0, paramDevInfo = 0, n = 0, p;
	cbsd_dev_info_t rCbsdDevInfoObj;
	cbsd_dev_info_handler_t cbsdDevInfoHandler[]={
		{"SerialNumber", "CbsdSerialNumber", (rCbsdDevInfoObj.cbsdSn)},
		{"Manufacturer", "Vendor", (rCbsdDevInfoObj.vendor)},
		{"ModelName", "Model", (rCbsdDevInfoObj.model)},
		{"SoftwareVersion", "SoftwareVersion", (rCbsdDevInfoObj.swVer)},
		{"HardwareVersion", "HardwareVersion", (rCbsdDevInfoObj.hwVer)},
		{ NULL,	NULL, NULL}
	};

	IID_INIT(iid);
	if((ret = zcfgFeObjJsonGetWithoutUpdate(RDM_OID_ZY_SAS_CBSD, &iid, &cbsdObj)) != ZCFG_SUCCESS){
		printf("[%d] F:%s, Object retrieve fail.\n", __LINE__,  __func__);
		return ret;
	}

	if((ret = retrvDevInfo(cbsdDevInfoHandler)) != ZCFG_SUCCESS){
		printf("[%d] F:%s, retrvDevInfo fail.\n", __LINE__,  __func__);
		return ret;
	}

	while((paraName = (const char *)CBSD_param[n].paraName) != NULL) {
		struct json_object *paramValue = json_object_object_get(Jobj, paraName);
		if(!paramValue) {
			n++;
			continue;
		}

		p = 0;
		paramDevInfo = 0;
		while((dstParaName = (const char *)cbsdDevInfoHandler[p].dstParaName) != NULL) {
			if(!strcmp(paraName, dstParaName)) {
				paramDevInfo = 1;
				break;
			}
			p++;
		}

		if(paramDevInfo)
			Jadds(cbsdObj, paraName, cbsdDevInfoHandler[p].retrvValue);
		else
			json_object_object_add(cbsdObj, paraName, JSON_OBJ_COPY(paramValue));

		paramModified = 1;
		n++;
	}

	if(paramModified) {
		if((ret = zcfgFeObjJsonSet(RDM_OID_ZY_SAS_CBSD, &iid, cbsdObj, NULL)) != ZCFG_SUCCESS)
			printf("[%d] F:%s, Write object fail.\n", __LINE__,  __func__);
	}

	zcfgFeJsonObjFree(cbsdObj);

	return ret;
}

zcfgRet_t zcfgFeDalCbsdGet(struct json_object *Jobj, struct json_object *Jarray, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;
	objIndex_t iid = {0};
	const char *paraName;
	struct json_object *paramJobj = NULL, *cbsdObj = NULL;
	struct json_object *certListJarray = NULL, *certObj = NULL, *certSignJarray = NULL, *certCaJarray = NULL;
	struct json_object *wanLanListJarray = NULL, *wanLanObj = NULL, *wanIntfJarray = NULL;
	char *certType, *ipIntfType;
	int i, n = 0, len = 0;

	IID_INIT(iid);
	if((ret = zcfgFeObjJsonGetWithoutUpdate(RDM_OID_ZY_SAS_CBSD, &iid, &cbsdObj)) != ZCFG_SUCCESS){
		printf("[%d] F:%s, Object retrieve fail.\n", __LINE__,  __func__);
		return ret;
	}

	paramJobj = json_object_new_object();

	while((paraName = (const char *)CBSD_param[n].paraName) != NULL) {
		json_object_object_add(paramJobj, paraName, JSON_OBJ_COPY(Jget(cbsdObj, paraName)));
		n++;
	}
	zcfgFeJsonObjFree(cbsdObj);

	certSignJarray = json_object_new_array();
	certCaJarray = json_object_new_array();
	getCertList(&certListJarray);
	len = json_object_array_length(certListJarray);
	for(i=0; i<len; i++){
		certObj = json_object_array_get_idx(certListJarray, i);
		certType = Jgets(certObj, "X_ZYXEL_Type");
		if(!strcmp(certType, "signed"))
			json_object_array_add(certSignJarray, JSON_OBJ_COPY(Jget(certObj, "X_ZYXEL_Name")));
		if(!strcmp(certType, "ca"))
			json_object_array_add(certCaJarray, JSON_OBJ_COPY(Jget(certObj, "X_ZYXEL_Name")));
	}
	/* printf("certListJarray: %s\n", json_object_to_json_string(certListJarray)); */
	zcfgFeJsonObjFree(certListJarray);
	json_object_object_add(paramJobj, "CertSignedNames", JSON_OBJ_COPY(certSignJarray));
	json_object_object_add(paramJobj, "CertCaNames", JSON_OBJ_COPY(certCaJarray));
	zcfgFeJsonObjFree(certSignJarray);
	zcfgFeJsonObjFree(certCaJarray);

	wanIntfJarray = json_object_new_array();
	getWanLanList_ext(&wanLanListJarray);
	len = json_object_array_length(wanLanListJarray);
	for(i=0; i<len; i++){
		wanLanObj = json_object_array_get_idx(wanLanListJarray, i);
		ipIntfType = Jgets(wanLanObj, "X_ZYXEL_Type");
		if(!strcmp(ipIntfType, "WAN")){
			json_object *ipIntfTempObj = json_object_new_object();
			json_object_object_add(ipIntfTempObj, "IpIfacePath", JSON_OBJ_COPY(Jget(wanLanObj, "IpIfacePath")));
			json_object_object_add(ipIntfTempObj, "IfName", JSON_OBJ_COPY(Jget(wanLanObj, "X_ZYXEL_IfName")));
			json_object_object_add(ipIntfTempObj, "SrvName", JSON_OBJ_COPY(Jget(wanLanObj, "X_ZYXEL_SrvName")));
			json_object_array_add(wanIntfJarray, JSON_OBJ_COPY(ipIntfTempObj));
			zcfgFeJsonObjFree(ipIntfTempObj);
		}
	}
	/* printf("wanLanListJarray: %s\n", json_object_to_json_string(wanLanListJarray)); */
	zcfgFeJsonObjFree(wanLanListJarray);
	json_object_object_add(paramJobj, "WanIntfNames", JSON_OBJ_COPY(wanIntfJarray));
	zcfgFeJsonObjFree(wanIntfJarray);

	json_object_array_add(Jarray, JSON_OBJ_COPY(paramJobj));
	zcfgFeJsonObjFree(paramJobj);

	return ret;
}

void zcfgFeDalShowCbsd(struct json_object *Jarray){
	struct json_object *obj = NULL;
	const char *paraName;
	int n = 0;

	if(json_object_get_type(Jarray) != json_type_array){
		printf("wrong Jobj format!\n");
		return;
	}

	obj = json_object_array_get_idx(Jarray, 0);

	printf("\nCBSD Settings:\n");
	while((paraName = (const char *)CBSD_param[n].paraName) != NULL) {
		struct json_object *paramValue = json_object_object_get(obj, paraName);
		if(!paramValue) {
			n++;
			continue;
		}
		printf("%-30s: %-10s \n", paraName, json_object_get_string(paramValue));
		n++;
	}
}


zcfgRet_t zcfgFeDalCbsd(const char *method, struct json_object *Jobj,  struct json_object *Jarray, char *replyMsg){
	zcfgRet_t ret = ZCFG_SUCCESS;

	if(!strcmp(method, "PUT"))
		ret = zcfgFeDalCbsdEdit(Jobj, replyMsg);
	else if(!strcmp(method, "GET"))
		ret = zcfgFeDalCbsdGet(Jobj, Jarray, replyMsg);
	else
		printf("Unknown method:%s\n", method);

	return ret;
}

#endif

