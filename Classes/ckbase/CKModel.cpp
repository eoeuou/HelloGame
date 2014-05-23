#include "CKModel.h"

CKModel::CKModel(void)
{
}


CKModel::~CKModel(void)
{
	
}

bool CKModel::init()
{
	
	return true;
}
	
void CKModel::setForeignProperty(const char* key,CKModel* value)
{	
	if(value)
	{
		m_propertyDic->setObject(value,key);
	}
	else
	{
		m_propertyDic->removeObjectForKey(key);
	}
}

CKModel* CKModel::getForeignProperty(const char* key,CKModel* defaultValue)
{
	CCAssert(m_propertyDic,"dic init error");
	if (m_propertyDic->objectForKey(key))
	{
		CKModel* result = dynamic_cast<CKModel*>(m_propertyDic->objectForKey(key));
		if(result)
		{
			return result;
		}
	}
	return defaultValue;
}

void CKModel::setForeignArray(const char* key,__Array* value)
{	
	if(value)
	{
		m_propertyDic->setObject(value,key);
	}
	else
	{
		m_propertyDic->removeObjectForKey(key);
	}
}

__Array* CKModel::getForeignArray(const char* key,__Array* defaultValue)
{
	CCAssert(m_propertyDic,"dic init error");
	if (m_propertyDic->objectForKey(key))
	{
		__Array* result = dynamic_cast<__Array*>(m_propertyDic->objectForKey(key));
		if(result)
		{
			return result;
		}
	}
	return defaultValue;
}