#ifndef __CKJSONHELPER_H__
#define __CKJSONHELPER_H__

#include "cocos2d.h"
#include "CKJsonModel.h"

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
private:
	CKJsonHelper(void);
	
	~CKJsonHelper(void);

	//************************************
	// Method:    parseRapidJsonObject
	// FullName:  CKJsonHelper::parseRapidJsonObject
	// Access:    private 
	// Returns:   CKJsonModel*
	// Qualifier:
	// Parameter: rapidjson::Value & jsonObj
	// Parameter: CKJsonModel * result
	//************************************
	CKJsonModel* parseRapidJsonObject(rapidjson::Value& jsonObj,CKJsonModel* result = nullptr);
};

#endif // __CKJSONHELPER_H__