#include "CKConstants.h"
#include "CKModel.h"

CK_INIT_STATIC_FIELD_WITH_NULL(CKConstants,USER_LOGIN_URL,const char*);
CK_INIT_STATIC_FIELD_WITH_NULL(CKConstants,GET_USER_SETTINGS_URL,const char*);
CK_INIT_STATIC_FIELD_WITH_NULL(CKConstants,CHECK_OVERDUE_URL,const char*);

#define LOAD_FROM_CONFIGFILE(key,field,doc) \
	static const char* field##_VALUE = DICTOOL->getStringValue_json(doc,key);\
	CKConstants::field = field##_VALUE;\
	CCLog("init url %s \n",CKConstants::field);\

bool CKConstants::init(){

	bool bRet = false;
    do {
		CKModel* rootModel = CKModel::create();

		rapidjson::Document jsonDict;

		CC_BREAK_IF(!parseJsonToDocument("jsondata/configfile.json",jsonDict));
	
		LOAD_FROM_CONFIGFILE("login",USER_LOGIN_URL,jsonDict);
		LOAD_FROM_CONFIGFILE("get_settings",GET_USER_SETTINGS_URL,jsonDict);	
		LOAD_FROM_CONFIGFILE("check_overdue",CHECK_OVERDUE_URL,jsonDict);
        
		bRet = true;
    } while (0);

	return bRet;
}
