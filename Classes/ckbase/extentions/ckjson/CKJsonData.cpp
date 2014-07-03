#include "CKJsonData.h"

CKJsonData::CKJsonData(void)
{
	m_document.SetObject();
}

CKJsonData::~CKJsonData(void)
{
	clear();
}

rapidjson::Document& CKJsonData::getJsonDocument()
{
	return m_document;
}

int CKJsonData::size()
{
	int result = 0;
	for (auto it = m_document.MemberonBegin(); it !=  m_document.MemberonEnd(); ++it)
	{		
		result++;
	}
	return result;
}

void CKJsonData::clear()
{
	std::vector<string> values = getKeys();
	for (auto it = values.begin(); it !=  values.end(); ++it)
	{
		m_document.RemoveMember((*it).c_str(););
	}		
}

std::vector<std::string> CKJsonData::getKeys()
{
	std::vector<string> values;
	for (auto it = m_document.MemberonBegin(); it !=  m_document.MemberonEnd(); ++it)
	{
		values.push_back((*it).name.GetString());
	}	
	return values;
}

void CKJsonData::logJsonString()
{
	log(getJsonString().c_str());
}

std::string CKJsonData::getJsonString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	m_document.Accept(writer);

	const char* out = buffer.GetString();
	
	return out;
}

bool CKJsonData::hasRapidJsonMember(const char* key)
{
	return m_document.HasMember(key);
}

rapidjson::Value& CKJsonData::operator[]( int key )
{
	return this->operator[](intToString(key));
}

rapidjson::Value& CKJsonData::operator[]( string key )
{
	return this->operator[](key.c_str());
}

rapidjson::Value& CKJsonData::operator[]( const char* key )
{
	if (!hasRapidJsonMember(key))
	{
		rapidjson::Document::AllocatorType& allocator = m_document.GetAllocator();
		m_document.AddMember(key,"",allocator);		
		m_document[key] = "default";
	}

	return m_document[key];
}

void CKJsonData::addObjectChild(int key, CKJsonData* data)
{
	this->addObjectChild(intToString(key),data);
}

void CKJsonData::addObjectChild(std::string key, CKJsonData* data)
{
	this->addObjectChild(key.c_str(),data);
}

void CKJsonData::addObjectChild(const char* key, CKJsonData* data)
{
	rapidjson::Document::AllocatorType& allocator = m_document.GetAllocator();
	rapidjson::Value object(rapidjson::kObjectType);

	for (auto it = data->getJsonDocument().MemberonBegin(); it !=  data->getJsonDocument().MemberonEnd(); ++it)
	{		
		object.AddMember((*it).name,(*it).value,allocator);
	}

	if (!hasRapidJsonMember(key))
	{
		m_document.AddMember(key,object,allocator);	
	}
	else
	{
		m_document[key] = object;
	}
}

void CKJsonData::addArrayChild(int key, CKJsonData* data)
{
	this->addArrayChild(intToString(key),data);
}

void CKJsonData::addArrayChild(std::string key, CKJsonData* data)
{
	this->addArrayChild(key.c_str(),data);
}

void CKJsonData::addArrayChild(const char* key, CKJsonData* data)
{
	rapidjson::Value array(rapidjson::kArrayType);	

	bool haveMember = hasRapidJsonMember(key);

	if (haveMember)
	{
		for (auto it = m_document.MemberonBegin(); it !=  m_document.MemberonEnd(); ++it)
		{
			if ((*it).name.GetString() == key)
			{
				CCASSERT((*it).value.GetType()==rapidjson::kArrayType,"this key is not for array before");
				array = (*it).value;
			}
		}
	}	

	rapidjson::Document::AllocatorType& allocator = m_document.GetAllocator();
	rapidjson::Value object(rapidjson::kObjectType);

	for (auto it = data->getJsonDocument().MemberonBegin(); it !=  data->getJsonDocument().MemberonEnd(); ++it)
	{		
		object.AddMember((*it).name,(*it).value,allocator);
	}
	array.PushBack(object,allocator);

	if (!haveMember)
	{
		m_document.AddMember(key,array,allocator);	
	}
	else
	{
		m_document[key] = array;
	}
}

bool CKJsonData::removeChild(int key)
{
	return this->removeChild(intToString(key));
}

bool CKJsonData::removeChild(std::string key)
{
	return this->removeChild(key.c_str());
}

bool CKJsonData::removeChild(const char* key)
{
	for (auto it = m_document.MemberonBegin(); it !=  m_document.MemberonEnd(); ++it)
	{
		if ((*it).name.GetString() == key)
		{
			m_document.RemoveMember((*it).name.GetString());

			return true;
		}
	}

	return false;
}
