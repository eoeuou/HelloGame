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

const char* CKJsonData::getJsonString()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	m_document.Accept(writer);

	auto out = buffer.GetString();
	log("getJsonString: %s", out);
	
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
	rapidjson::Document::AllocatorType& allocator = m_document.GetAllocator();
	rapidjson::Value object(rapidjson::kObjectType);

	for (auto it = data->getJsonDocument().MemberonBegin(); it !=  data->getJsonDocument().MemberonEnd(); ++it)
	{		
		object.AddMember((*it).name,(*it).value,allocator);
	}
	array.PushBack(object,allocator);

	if (!hasRapidJsonMember(key))
	{
		m_document.AddMember(key,array,allocator);		
	}else
	{
		m_document[key] = array;
	}
}
