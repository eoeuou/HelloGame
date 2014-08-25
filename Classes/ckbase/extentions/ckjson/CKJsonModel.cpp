#include "CKJsonModel.h"
#include "CKJsonHelper.h"

CKJsonModel::CKJsonModel(void)
{
	document.SetObject();
}

CKJsonModel::~CKJsonModel(void)
{

}

bool CKJsonModel::init()
{	
	document.SetObject();
	return true;
}

int CKJsonModel::size()
{
	return CKModel::size();
}

void CKJsonModel::clear()
{
	document.Clear();
}

void CKJsonModel::logJsonString()
{
	log("%s",getJsonString().c_str());
}

std::string CKJsonModel::getJsonString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	const char* out = buffer.GetString();

	return out;
}

bool CKJsonModel::hasChild(const char* key)
{
	return this->hasValue(key);
}

const Value& CKJsonModel::getChildByKey(const char* key)
{
	return this->getValue(key);
}

void CKJsonModel::addChild(std::string key, Value& value)
{
	this->addChild(key.c_str(),value);
}

void CKJsonModel::addChild(const char* key, Value& value)
{
    this->setValue(key, value);

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	if (document.HasMember(key))
	{
		document.RemoveMember(key);
	}
    switch (value.getType()) {
        case Value::Type::INTEGER:
			{
				__Integer* valueInter = __Integer::create(value.asInt());
				document.AddMember(key,valueInter->getValue(),allocator);
			}
            break;
        case Value::Type::STRING:
			{
				__String * valueStr = __String::create(value.asString());
				document.AddMember(key,valueStr->getCString(),allocator);
			}
            break;
		case Value::Type::BOOLEAN:
			document.AddMember(key,value.asBool(),allocator);
            break;
		case Value::Type::FLOAT:
			document.AddMember(key,value.asFloat(),allocator);
            break;
		case Value::Type::DOUBLE:
			document.AddMember(key,value.asDouble(),allocator);
            break;
            
        default:
            CCASSERT(false, "addChild type error");
            break;
    }
}

CKJsonModel* CKJsonModel::getObjectChildByKey(const char* key)
{
	if (!document.HasMember(key))
	{
		return nullptr;
	}
	else
	{
		return dynamic_cast<CKJsonModel*>(this->getForeignProperty(key));
	}

	return nullptr;
}

void CKJsonModel::addObjectChild(std::string key, CKJsonModel* data)
{
	this->addObjectChild(key.c_str(),data);
}

void CKJsonModel::addObjectChild(const char* key, CKJsonModel* data)
{
    this->setForeignProperty(key, data);
    
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value object(rapidjson::kObjectType);
    
	for (auto it = data->document.MemberonBegin(); it !=  data->document.MemberonEnd(); ++it)
	{
		object.AddMember((*it).name,(*it).value,allocator);
	}
	
	if (document.HasMember(key))
	{
		document.RemoveMember(key);
	}
	document.AddMember(key,object,allocator);
}

CKJsonModelVector CKJsonModel::getArrayChildByKey(const char* key)
{
    CKJsonModelVector vector;
    if (!document.HasMember(key))
	{
		return vector;
	}
	else
	{
		if (document[key].GetType()!=rapidjson::Type::kArrayType)
		{
			CCAssert(false,"getArrayChildByKey type error ");
			return vector;
		}
        
        __Array* array = this->getForeignArray(key);
        Ref* obj = nullptr;
        CCARRAY_FOREACH(array,obj) {
            vector.pushBack(dynamic_cast<CKJsonModel*>(obj));
        }
		
		return vector;
	}
	
	return vector;
}

void CKJsonModel::addArrayChild(std::string key, CKJsonModelVector& data)
{
	this->addArrayChild(key.c_str(),data);
}

void CKJsonModel::addArrayChild(const char* key, CKJsonModelVector& data)
{
    {
        __Array* array = __Array::create();
        for (const auto& child : data)
        {
            array->addObject(child);
        }
        this->setForeignArray(key, array);
    }
    
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value array(rapidjson::kArrayType);

	bool haveMember = document.HasMember(key);

	for (const auto& child : data)
	{
        rapidjson::Value object(rapidjson::kObjectType);
        
        rapidjson::Document::AllocatorType& allocator = child->document.GetAllocator();
        for (auto it = child->document.MemberonBegin(); it !=  child->document.MemberonEnd(); ++it)
        {
            object.AddMember((*it).name,(*it).value,allocator);
        }
        
		array.PushBack(object,allocator);
	}

	if (haveMember)
	{
		document.RemoveMember(key);
	}

	document.AddMember(key,array,allocator);
}

bool CKJsonModel::removeChild(std::string key)
{
	return this->removeChild(key.c_str());
}

bool CKJsonModel::removeChild(const char* key)
{
	this->removeValue(key);

	for (auto it = document.MemberonBegin(); it !=  document.MemberonEnd(); ++it)
	{
		if ((*it).name.GetString() == key)
		{
			document.RemoveMember((*it).name.GetString());

			return true;
		}
	}

	return false;
}
