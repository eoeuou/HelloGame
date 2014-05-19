#ifndef __CKGAMEDATAMANAGER_H__
#define __CKGAMEDATAMANAGER_H__

#include "CKCommon.h"

class CKGameDataManager
{
public:

    static CKGameDataManager* getInstance();

    static void destroyInstance();
		
	bool loadGameData();
			
private:
	CKGameDataManager(void);
	
	~CKGameDataManager(void);
	
    static CKGameDataManager* s_singleInstance;
		
	void convertDocumentToModel(std::string key,CKModel* model,rapidjson::Document& doc);
	void convertValueToModel(std::string key,CKModel* model,const rapidjson::Value& doc);
};

#endif // __CKGAMEDATAMANAGER_H__