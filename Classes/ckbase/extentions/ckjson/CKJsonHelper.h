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

	CKJsonData* parseJsonToJsonData(const char* json);
			
private:
	CKJsonHelper(void);
	
	~CKJsonHelper(void);

	CKJsonData* parseRapidJsonObject(rapidjson::Value& jsonDoc);
};

#endif // __CKJSONHELPER_H__