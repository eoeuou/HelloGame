#include "CKGameDataManager.h"

CKGameDataManager* CKGameDataManager::s_singleInstance = nullptr;

CKGameDataManager::CKGameDataManager(void)
{
	
}

CKGameDataManager::~CKGameDataManager(void)
{
	
}

CKGameDataManager* CKGameDataManager::getInstance()
{
    if (! s_singleInstance)
    {
        s_singleInstance = new CKGameDataManager();
    }

    return s_singleInstance;
}

void CKGameDataManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKGameDataManager::loadGameData()
{	
    bool bRet = false;
    do {
		CKModel* rootModel = CKModel::create();

		rapidjson::Document jsonDict;
	
		bool result = parseJsonToDocument("data.json",jsonDict);

		CC_BREAK_IF(!result);
	
		convertDocumentToModel("classname",rootModel,jsonDict);
		convertDocumentToModel("version",rootModel,jsonDict);
		
		const rapidjson::Value& subData = DICTOOL->getSubDictionary_json(jsonDict,"animation");

		CKModel* subModel = CKModel::create();
		convertValueToModel("classname",subModel,subData);
		convertValueToModel("name",subModel,subData);

		rootModel->setProperty("animation",subModel);
        
		bRet = true;
    } while (0);

    return bRet;
}

void CKGameDataManager::convertDocumentToModel(std::string key,CKModel* model,rapidjson::Document& doc)
{
	if(!model)
	{
		return;
	}
	const char* value = DICTOOL->getStringValue_json(doc,key.c_str());

	model->setProperty(key,value);
}

void CKGameDataManager::convertValueToModel(std::string key,CKModel* model,const rapidjson::Value& doc)
{	
	if(!model)
	{
		return;
	}
	const char* value = DICTOOL->getStringValue_json(doc,key.c_str());

	model->setProperty(key,value);
}