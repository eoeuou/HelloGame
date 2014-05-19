#include "CKProtocols.h"

bool PropertyProtocol::getBooleanProperty(string key, bool defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->compare("true") == 0;
	}

	return defaultValue;
}

int PropertyProtocol::getIntProperty(string key, int defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->intValue();
	}

	return defaultValue;
}

float PropertyProtocol::getFloatProperty(string key, float defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->floatValue();
	}

	return defaultValue;
}

string PropertyProtocol::getStringProperty(string key, const char* defaultValue)
{
	__String* pStr = dynamic_cast<__String*>(m_propertyDic->objectForKey(key));
	if(pStr)
	{
		return pStr->getCString();
	}

	return defaultValue;
}

void PropertyProtocol::setProperty(string key, float value)
{
	__String* result = __String::create(CCString::createWithFormat("%f",value)->getCString());
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::setProperty(string key, bool value)
{
	__String* result = __String::create(value ? "true" : "false");
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::setProperty(string key, const char* value)
{
	__String* result = __String::create(value);
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}

void PropertyProtocol::setProperty(string key, int value)
{
	__String* result = __String::create(CCString::createWithFormat("%d",value)->getCString());
	m_propertyDic->removeObjectForKey(key);
	m_propertyDic->setObject(result,key);
}