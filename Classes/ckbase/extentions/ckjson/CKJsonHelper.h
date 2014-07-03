#ifndef __CKJSONHELPER_H__
#define __CKJSONHELPER_H__

#include "cocos2d.h"
#include "CKJsonData.h"

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
	// Returns:   CKJsonData*
	// Qualifier:
	// Parameter: const char * json
	//************************************
	CKJsonData* parseJsonToJsonData(const char* json);
			
private:
	CKJsonHelper(void);
	
	~CKJsonHelper(void);

	//************************************
	// Method:    parseRapidJsonObject
	// FullName:  CKJsonHelper::parseRapidJsonObject
	// Access:    private 
	// Returns:   CKJsonData*
	// Qualifier: 
	// Parameter: rapidjson::Value & jsonDoc
	//************************************
	CKJsonData* parseRapidJsonObject(rapidjson::Value& jsonObj);
};

#endif // __CKJSONHELPER_H__