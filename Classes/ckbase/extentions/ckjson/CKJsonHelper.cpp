#include "CKJsonHelper.h"

CK_SINGLETON_METHOD_INIT(CKJsonHelper,s_singleInstance);

CKJsonHelper::CKJsonHelper(void)
{

}

CKJsonHelper::~CKJsonHelper(void)
{
	
}

void CKJsonHelper::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKJsonHelper::init()
{
	return true;
}

CKJsonModel* CKJsonHelper::parseRapidJsonObject(rapidjson::Value& jsonObj,CKJsonModel* result)
{
	CCAssert(jsonObj.GetType()== rapidjson::kObjectType,"jsonDoc must be object");
	
	if (result == nullptr)
	{
		result = CKJsonModel::create();
	}

	for (auto it = jsonObj.MemberonBegin(); it !=  jsonObj.MemberonEnd(); ++it)
	{		
		const rapidjson::Value::Ch* k = (*it).name.GetString();
		char* key = new char[strlen(k)+1];
		sprintf(key, "%s", k);
				
		rapidjson::Type type = (*it).value.GetType();
		switch (type)
		{
		case rapidjson::kNullType:
			CCAssert(false,"not imp");
			break;
		case rapidjson::kFalseType:
		case rapidjson::kTrueType:
			(*result)[key] = (*it).value.GetBool();
			break;
		case rapidjson::kObjectType:
			result->addObjectChild(key,parseRapidJsonObject((*it).value));
			result->addObjectChild(key,parseRapidJsonObject((*it).value));
			break;
		case rapidjson::kArrayType:
			{
				for (auto i = (*it).value.onBegin(); i !=  (*it).value.onEnd(); ++i)
				{
					result->addArrayChild(key,parseRapidJsonObject(*i));
				}
			}
			break;
		case rapidjson::kStringType:
			{
				const rapidjson::Value::Ch* v = (*it).value.GetString();
				char* value = new char[strlen(v)+1];
				sprintf(value, "%s", v);

				(*result)[key] = value;
			}
			break;
		case rapidjson::kNumberType:
			{
				if ((*it).value.IsInt())
				{
					(*result)[key] = (*it).value.GetInt();
				}
				else if ((*it).value.IsInt64())
				{
					(*result)[key] = (*it).value.GetInt64();
				}
				else if ((*it).value.IsDouble())
				{
					(*result)[key] = (*it).value.GetDouble();
				}
				else
				{
					CCAssert(false,"unknown type");
				}
			}
			break;
		default:
			break;
		}
	}
	
	result->logJsonString();

	return result;
}

CKJsonModel* CKJsonHelper::parseJsonToJsonModel(const char* json, CKJsonModel* result)
{
	bool parseResult = false;
	do {
		rapidjson::Document jsonDoc;

		parseResult = parseJsonStrToDocument(json,jsonDoc);

		CCAssert(parseResult,"parseResult is false,maybe json is wrong");

		CC_BREAK_IF(!parseResult);

		result = parseRapidJsonObject(jsonDoc,result);	

	} while (0);
		
	CCAssert(result,"result is null,maybe json is wrong");

	result->logJsonString();

	return result;
}
