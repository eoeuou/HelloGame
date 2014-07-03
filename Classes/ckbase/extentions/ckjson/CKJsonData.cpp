#include "CKJsonData.h"

CKJsonData::CKJsonData(void)
{
	m_document.SetObject();
	rapidjson::Document::AllocatorType& allocator = m_document.GetAllocator();
	
}

CKJsonData::~CKJsonData(void)
{
	
}

rapidjson::Document& CKJsonData::getJsonDocument()
{
	return m_document;
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
	}

	return m_document[key];
}

void CKJsonData::addChild(const char* key, CKJsonData* data)
{
	rapidjson::Value array(rapidjson::kArrayType);	

	if (hasRapidJsonMember(key))
	{
		for (auto it = m_document.MemberonBegin(); it !=  m_document.MemberonEnd(); ++it)
		{		
			rapidjson::Type t= (*it).name.GetType();
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

	m_document.AddMember(key,array,allocator);	
}

void CKJsonData::addChild(int key, CKJsonData* data)
{
	this->addChild(intToString(key),data);
}

void CKJsonData::addChild(std::string key, CKJsonData* data)
{
	this->addChild(key.c_str(),data);
}