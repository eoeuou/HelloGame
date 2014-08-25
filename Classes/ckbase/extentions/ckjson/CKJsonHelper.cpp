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

CKJsonModel* CKJsonHelper::convertJsonValue2JsonModel(rapidjson::Value& jsonObj, CKJsonModel* result)
{
	CCAssert(jsonObj.GetType()== rapidjson::kObjectType,"jsonDoc must be object");
	
	if (result == nullptr)
	{
		result = CKJsonModel::create();
	}
	
	for (auto it = jsonObj.MemberonBegin(); it !=  jsonObj.MemberonEnd(); ++it)
	{
		__String * keyStr = __String::create((*it).name.GetString());
		const char* key = keyStr->getCString();

        log("key=%s",key);

		rapidjson::Type type = (*it).value.GetType();
		switch (type)
		{
		case rapidjson::kNullType:
			CCAssert(false,"not imp");
			break;
		case rapidjson::kFalseType:
		case rapidjson::kTrueType:
            {
                cocos2d::Value v((*it).value.GetBool());
                result->addChild(key, v);
            }
			break;
		case rapidjson::kObjectType:
			result->addObjectChild(key,convertJsonValue2JsonModel((*it).value));
			break;
		case rapidjson::kArrayType:
			{
				CKJsonModelVector vector = convertJsonValue2JsonModelVector((*it).value);
				result->addArrayChild(key,vector);
			}
			break;
		case rapidjson::kStringType:
			{
				__String * valueStr = __String::create((*it).value.GetString());
				const char* value = valueStr->getCString();
                
                cocos2d::Value v(value);
                result->addChild(key, v);
			}
			break;
		case rapidjson::kNumberType:
			{
				if ((*it).value.IsInt())
				{
					__Integer* valueInter = __Integer::create((*it).value.GetInt());
                    cocos2d::Value v(valueInter->getValue());
                    result->addChild(key, v);
				}
				else if ((*it).value.IsDouble())
				{
					__Double* valueDouble = __Double::create((*it).value.GetDouble());
                    cocos2d::Value v(valueDouble->getValue());
                    result->addChild(key, v);
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

CKJsonModelVector CKJsonHelper::convertJsonValue2JsonModelVector(rapidjson::Value& jsonObj, CKJsonModel* result)
{
	CKJsonModelVector vector;
	if (result == nullptr)
	{
		result = CKJsonModel::create();
	}
	if (jsonObj.GetType()!=rapidjson::Type::kArrayType)
	{
		CCAssert(false,"convertJsonValue2JsonModelVector error");
		return vector;
	}

    for (auto i = jsonObj.onBegin(); i !=  jsonObj.onEnd(); ++i)
	{
		rapidjson::Value& child = (*i);
		CKJsonModel* model = convertJsonValue2JsonModel(child);
		vector.pushBack(model);
	}

	return vector;
}

CKJsonModel* CKJsonHelper::parseJsonToJsonModel(const char* json, CKJsonModel* result, bool isFile)
{
	bool parseResult = false;
	do {
		rapidjson::Document jsonDoc;

		if (isFile)
		{
			parseResult = parseJsonFileToDocument(json,jsonDoc);
		}
		else
		{
			parseResult = parseJsonStrToDocument(json,jsonDoc);
		}

		CCAssert(parseResult,"parseResult is false,maybe json is wrong");

		CC_BREAK_IF(!parseResult);

		result = convertJsonValue2JsonModel(jsonDoc,result);

	} while (0);

	CCAssert(result,"result is null,maybe json is wrong");

	result->logJsonString();

	return result;
}
