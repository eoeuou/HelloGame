#ifndef __CKJSONHELPER_H__
#define __CKJSONHELPER_H__

#include "cocos2d.h"
#include "CKJsonModel.h"
#include "CKCommon.h"

USING_NS_CC;

using namespace std;

class CKJsonHelper
{
public:

	CK_SINGLETON_METHOD_LAZY(CKJsonHelper,s_singleInstance,Instance);

    static void destroyInstance();
	
	bool init();

	//************************************
	// Method:    parseJsonToJsonModel
	// FullName:  CKJsonHelper::parseJsonToJsonModel
	// Access:    public 
	// Returns:   CKJsonModel*
	// Qualifier:
	// Parameter: const char * json
	// Parameter: CKJsonModel * result
	// Parameter: bool isFile
	//************************************
	CKJsonModel* parseJsonToJsonModel(const char* json,CKJsonModel* result = nullptr,bool isFile = false);

	//************************************
	// Method:    convertJsonValue2JsonModel
	// FullName:  CKJsonHelper::convertJsonValue2JsonModel
	// Access:    public 
	// Returns:   CKJsonModel*
	// Qualifier: 将jsonValue 转换为JsonModel对象
	// Parameter: rapidjson::Value & jsonObj
	// Parameter: CKJsonModel * result
	//************************************
	CKJsonModel* convertJsonValue2JsonModel(rapidjson::Value& jsonObj, CKJsonModel* result = nullptr);

	//************************************
	// Method:    convertJsonValue2JsonModelVector
	// FullName:  CKJsonHelper::convertJsonValue2JsonModelVector
	// Access:    public 
	// Returns:   CKJsonModelVector*
	// Qualifier: 将jsonValue 转换为CKJsonModelVector对象
	// Parameter: rapidjson::Value & jsonObj
	// Parameter: CKJsonModel * result
	//************************************
	CKJsonModelVector convertJsonValue2JsonModelVector(rapidjson::Value& jsonObj, CKJsonModel* result = nullptr);
private:
	CKJsonHelper(void);
	
	~CKJsonHelper(void);

};

#endif // __CKJSONHELPER_H__