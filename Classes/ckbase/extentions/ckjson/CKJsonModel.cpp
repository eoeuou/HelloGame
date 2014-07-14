#include "CKJsonModel.h"

CKJsonModel::CKJsonModel(void):
	m_objMap(nullptr),
	m_arrayMap(nullptr)
{
}


CKJsonModel::~CKJsonModel(void)
{
	
}

bool CKJsonModel::init()
{
	this->SetObject();
	
	return true;
}

int CKJsonModel::size()
{
	int result = 0;
	for (auto it = this->MemberonBegin(); it !=  this->MemberonEnd(); ++it)
	{		
		result++;
	}
	return result;
}

void CKJsonModel::clear()
{
	std::vector<string> values = getKeys();
	for (auto it = values.begin(); it !=  values.end(); ++it)
	{
		(*this).RemoveMember((*it).c_str());
	}		
}

std::vector<std::string> CKJsonModel::getKeys()
{
	std::vector<string> values;
	for (auto it = (*this).MemberonBegin(); it !=  (*this).MemberonEnd(); ++it)
	{
		values.push_back((*it).name.GetString());
	}	
	return values;
}

void CKJsonModel::logJsonString()
{
	log("%s",getJsonString().c_str());
}

std::string CKJsonModel::getJsonString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	(*this).Accept(writer);

	const char* out = buffer.GetString();

	return out;
}

rapidjson::Value& CKJsonModel::operator[]( int key )
{
	return this->operator[](intToString(key));
}

rapidjson::Value& CKJsonModel::operator[]( string key )
{
	return this->operator[](key.c_str());
}

rapidjson::Value& CKJsonModel::operator[]( const char* key )
{
	if (!HasMember(key))
	{
		rapidjson::Document::AllocatorType& allocator = (*this).GetAllocator();
		(*this).AddMember(key,"",allocator);		
		(*this)[key] = "default";
	}

	return rapidjson::Value::operator[](key);	
}

rapidjson::Value& CKJsonModel::convertToRapidJsonValue()
{
	rapidjson::Document::AllocatorType& allocator = (*this).GetAllocator();
	rapidjson::Value* object = new rapidjson::Value(rapidjson::kObjectType);

	for (auto it = this->MemberonBegin(); it !=  this->MemberonEnd(); ++it)
	{		
		CCAssert((*it).name.GetType() == rapidjson::kStringType,"data maybe added");

		rapidjson::Type vtype = (*it).value.GetType();
		if (vtype == rapidjson::kObjectType)
		{
			log("");
		}
		
		(*object).AddMember((*it).name,(*it).value,allocator);
	}

	return *object;
}

CKJsonModel* CKJsonModel::getObjectChildByKey(const char* key)
{	
	if (m_objMap)
	{
		return (*m_objMap)[key];
	}

	return nullptr;	
}

void CKJsonModel::recordToObjMap(const char* key, CKJsonModel* data)
{
	if (!m_objMap)
	{
		m_objMap = new CKJsonModelMap();
	}		
	(*m_objMap)[key] = data;
}

void CKJsonModel::addObjectChild(int key, CKJsonModel* data)
{
	this->addObjectChild(intToString(key),data);
}

void CKJsonModel::addObjectChild(std::string key, CKJsonModel* data)
{
	this->addObjectChild(key.c_str(),data);
}

void CKJsonModel::addObjectChild(const char* key, CKJsonModel* data)
{
	rapidjson::Document::AllocatorType& allocator = (*this).GetAllocator();
	rapidjson::Value& object = data->convertToRapidJsonValue();

	if (!HasMember(key))
	{
		(*this).AddMember(key,object,allocator);	

		recordToObjMap(key,data);
	}
	else
	{
		(*this)[key] = object;
	}
}

int CKJsonModel::getArrayChildCount()
{
	if (m_arrayMap)
	{
		return m_arrayMap->size();
	}

	return 0;	
}

CKJsonModelVector* CKJsonModel::getArrayChildByKey(const char* key)
{
	if (m_arrayMap)
	{
		return (*m_arrayMap)[key];
	}

	return nullptr;	
}

void CKJsonModel::recordToArrayMap(const char* key, CKJsonModel* data)
{
	if (!m_arrayMap)
	{
		m_arrayMap = new CKJsonModelVectorMap();
	}
	CKJsonModelVector* vector = (*m_arrayMap)[key];

	if (vector)
	{
		for (auto it = vector->begin(); it != vector->end(); ++it)
		{
			CCAssert((*it) != data,"data maybe added");	
			if ((*it) == data)
			{
				return;
			}			
		}
	}
	else
	{
		vector = new CKJsonModelVector();
		(*m_arrayMap)[key] = vector;
	}

	(*vector).push_back(data);
}

void CKJsonModel::addArrayChild(int key, CKJsonModel* data)
{
	this->addArrayChild(intToString(key),data);
}

void CKJsonModel::addArrayChild(std::string key, CKJsonModel* data)
{
	this->addArrayChild(key.c_str(),data);
}

void CKJsonModel::addArrayChild(const char* key, CKJsonModel* data)
{
	recordToArrayMap(key,data);	

	rapidjson::Value array(rapidjson::kArrayType);	

	bool haveMember = HasMember(key);

	if (haveMember)
	{
		for (auto it = this->MemberonBegin(); it !=  this->MemberonEnd(); ++it)
		{
			if ((*it).name.GetString() == key)
			{
				CCASSERT((*it).value.GetType() == rapidjson::kArrayType,"this key is not for array before");
				array = (*it).value;
				break;
			}
		}
	}	

	rapidjson::Document::AllocatorType& allocator = this->GetAllocator();
	rapidjson::Value& object = data->convertToRapidJsonValue();
	array.PushBack(object,allocator);

	if (!haveMember)
	{
		this->AddMember(key,array,allocator);			
	}
	else
	{
		(*this)[key] = array;
	}
}

bool CKJsonModel::removeChild(int key)
{
	return this->removeChild(intToString(key));
}

bool CKJsonModel::removeChild(std::string key)
{
	return this->removeChild(key.c_str());
}

bool CKJsonModel::removeChild(const char* key)
{
	for (auto it = this->MemberonBegin(); it !=  this->MemberonEnd(); ++it)
	{
		if ((*it).name.GetString() == key)
		{
			this->RemoveMember((*it).name.GetString());

			return true;
		}
	}

	return false;
}
