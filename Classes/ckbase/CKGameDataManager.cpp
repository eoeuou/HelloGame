#include "CKGameDataManager.h"
#include "CKConstants.h"

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
		CKConstants::init();
    }

    return s_singleInstance;
}

void CKGameDataManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

#define CONVERT_VALUE_MODEL(key,model,doc) \
	if(!model)\
	{\
		return;\
	}\
	const char* value = DICTOOL->getStringValue_json(doc,key.c_str());\
	model->setProperty(key.c_str(),value);\

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

		CC_BREAK_IF(!parseJsonToDocument("jsondata/data.json",jsonDict));
	
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