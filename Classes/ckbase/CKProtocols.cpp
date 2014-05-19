#include "CKProtocols.h"

bool PropertyProtocol::getBooleanProperty(const char* key, bool defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->compare("true") == 0;
	}

	return defaultValue;
}

int PropertyProtocol::getIntProperty(const char* key, int defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->intValue();
	}

	return defaultValue;
}

float PropertyProtocol::getFloatProperty(const char* key, float defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->floatValue();
	}

	return defaultValue;
}

string PropertyProtocol::getStringProperty(const char* key, const char* defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->getCString();
	}

	return defaultValue;
}

void PropertyProtocol::setProperty(const char* key, float value)
{
	__String* result = __String::create(CCString::createWithFormat("%f",value)->getCString());
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::setProperty(const char* key, bool value)
{
	__String* result = __String::create(value ? "true" : "false");
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::setProperty(const char* key, const char* value)
{
	__String* result = __String::create(value);
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::setProperty(const char* key, int value)
{
	__String* result = __String::create(CCString::createWithFormat("%d",value)->getCString());
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::removeProperty(const char* key)
{
	m_propertyDic->removeObjectForKey(key);
}

bool PropertyProtocol::hasProperty(const char* key)
{
	return m_propertyDic->objectForKey(key)!=NULL;
}

void PropertyProtocol::clear()
{
	m_propertyDic->removeAllObjects();
}