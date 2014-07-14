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
	// Method:    parseJsonToJsonData
	// FullName:  CKJsonHelper::parseJsonToJsonData
	// Access:    public 
	// Returns:   CKJsonModel*
	// Qualifier:
	// Parameter: const char * json
	//************************************
	CKJsonModel* parseJsonToJsonData(const char* json);
			
private:
	CKJsonHelper(void);
	
	~CKJsonHelper(void);

	//************************************
	// Method:    parseRapidJsonObject
	// FullName:  CKJsonHelper::parseRapidJsonObject
	// Access:    private 
	// Returns:   CKJsonModel*
	// Qualifier: 
	// Parameter: rapidjson::Value & jsonDoc
	//************************************
	CKJsonModel* parseRapidJsonObject(rapidjson::Value& jsonObj);
};

#endif // __CKJSONHELPER_H__