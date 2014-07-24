#include "CKGameDataManager.h"

CK_SINGLETON_METHOD_INIT(CKGameDataManager,s_singleInstance);

CKGameDataManager::CKGameDataManager(void)
{
	
}

CKGameDataManager::~CKGameDataManager(void)
{
	
}

void CKGameDataManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKGameDataManager::init()
{
	return true;
}

bool CKGameDataManager::downloadGameData()
{
	
	return true;
}

void CKGameDataManager::convertDocumentToModel(std::string key,CKModel* model,rapidjson::Document& doc)
{
	CONVERT_VALUE_MODEL(key,model,doc);
}

void CKGameDataManager::convertValueToModel(std::string key,CKModel* model,const rapidjson::Value& doc)
{	
	CONVERT_VALUE_MODEL(key,model,doc);
}

bool CKGameDataManager::loadGameData()
{	
    bool bRet = false;
    do {
		CKModel* rootModel = CKModel::create();

		rapidjson::Document jsonDict;

		CC_BREAK_IF(!parseJsonFileToDocument("jsondata/data.json",jsonDict));
	
		convertDocumentToModel("classname",rootModel,jsonDict);
		convertDocumentToModel("version",rootModel,jsonDict);
				
		const rapidjson::Value& subData = DICTOOL->getSubDictionary_json(jsonDict,"animation");

		CKModel* subModel = CKModel::create();
		convertValueToModel("classname",subModel,subData);
		convertValueToModel("name",subModel,subData);

		rootModel->setForeignProperty("animation",subModel);
        
		bRet = true;
    } while (0);

    return bRet;
}

bool CKGameDataManager::loadQuestionsData()
{
	bool bRet = false;
	do {
		CKModel* rootModel = CKModel::create();

		rapidjson::Document jsonDict;

		CC_BREAK_IF(!parseJsonFileToDocument("jsondata/questions.json",jsonDict));
		
		convertDocumentToModel("version",rootModel,jsonDict);

		int queCount = DICTOOL->getArrayCount_json(jsonDict, "questions");
		__Array* questionsArray = __Array::create();
		for (int i = 0; i < queCount; i++)
		{
			const rapidjson::Value &questionsDic = DICTOOL->getDictionaryFromArray_json(jsonDict, "questions", i);

			CKModel* questionModel = CKModel::create();
			convertValueToModel("id",questionModel,questionsDic);
			convertValueToModel("title",questionModel,questionsDic);
			convertValueToModel("right",questionModel,questionsDic);

			const rapidjson::Value &answersDic = DICTOOL->getSubDictionary_json(questionsDic, "answers");

			CKModel* answerModel = CKModel::create();
			convertValueToModel("a",answerModel,answersDic);
			convertValueToModel("b",answerModel,answersDic);
			convertValueToModel("c",answerModel,answersDic);
			convertValueToModel("d",answerModel,answersDic);

			questionModel->setForeignProperty("answers",answerModel);

			questionsArray->addObject(questionModel);
		}
		rootModel->setForeignArray("questions",questionsArray);

		m_questionsModel = rootModel;
		bRet = true;
	} while (0);

	return bRet;
}