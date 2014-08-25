#include "CKModel.h"

CKModel::CKModel(void)
	:PropertyProtocol()
	,m_propertyDic(__Dictionary::create())
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

void CKModel::setForeignDic(const char* key,__Dictionary* value)
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

__Dictionary* CKModel::getForeignDic(const char* key,__Dictionary* defaultValue)
{
	CCAssert(m_propertyDic,"dic init error");
	if (m_propertyDic->objectForKey(key))
	{
		__Dictionary* result = dynamic_cast<__Dictionary*>(m_propertyDic->objectForKey(key));
		if(result)
		{
			return result;
		}
	}
	return defaultValue;
}

bool CKModel::removeValue(const char* key)
{
	if (getModelTypeByKey(key) != ModelType::NONE)
	{
		if (PropertyProtocol::hasValue(key))
		{
			return PropertyProtocol::removeValue(key);
		}
		else if (m_propertyDic->objectForKey(key) != nullptr)
		{
			m_propertyDic->removeObjectForKey(key);
			return true;
		}
	}
	return false;
}

bool CKModel::hasValue(const char* key)
{
	bool res1 = PropertyProtocol::hasValue(key);
	
	bool res2 = (m_propertyDic->objectForKey(key) != nullptr);
	
	return res1||res2;
}

int CKModel::size()
{
	return PropertyProtocol::size() + m_propertyDic->count();
}

void CKModel::clear()
{
	PropertyProtocol::clear();
	m_propertyDic->removeAllObjects();
}

ModelType CKModel::getModelTypeByKey(const char* key)
{
	if (PropertyProtocol::hasValue(key))
	{
		return ModelType::VALUEMAP;
	}
	else if (m_propertyDic->objectForKey(key) != nullptr)
	{
		return ModelType::DICTIONARY;
	}

	return ModelType::NONE;
}

std::string CKModel::getInfo() const
{
	if (m_propertyDic->count()>0)
	{
		CCAssert(false,"to do!");
	}
	
	return PropertyProtocol::getInfo();
}
