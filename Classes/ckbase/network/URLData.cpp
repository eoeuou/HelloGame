#include "URLData.h"

URLData::URLData(void):
	m_addIndex(0)
{
}


URLData::~URLData(void)
{
	
}

bool URLData::init()
{
	
	return true;
}


bool URLData::add(requestURLData urlData)
{
	if (m_urlData[m_addIndex].delegate == NULL)
	{
		m_urlData[m_addIndex] = urlData;
	}
	else
	{
		return false;
	}

	m_addIndex = (m_addIndex >= (MAX_URL_NUM-1))?0:m_addIndex+1;
	
	return true;
}