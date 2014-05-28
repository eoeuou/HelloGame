#ifndef __CKGAMEDATAMANAGER_H__
#define __CKGAMEDATAMANAGER_H__

#include "CKCommon.h"

class CKGameDataManager
{
private:
	CC_SYNTHESIZE_READONLY(CKModel*,m_questionsModel,QuestionsModel);
public:
	
	CK_SINGLETON_METHOD_LAZY(CKGameDataManager,s_singleInstance,Instance);

	bool downloadGameData();
		
	bool loadGameData();

	bool loadQuestionsData();
			
private:
	CKGameDataManager(void);
	
	~CKGameDataManager(void);
		
	void convertDocumentToModel(std::string key,CKModel* model,rapidjson::Document& doc);
	void convertValueToModel(std::string key,CKModel* model,const rapidjson::Value& doc);

};

#endif // __CKGAMEDATAMANAGER_H__