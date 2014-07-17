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

string URLData::getNextUrl()
{
	if (isEmpty())
	{
		return "";
	}

	m_getIndex>=(MAX_URL_NUM-1)?m_getIndex=0:m_getIndex++;
	
	return generateURL(m_urlData[m_getIndex].action);
}

std::string URLData::getCurUrl()
{
	if (m_urlData[m_getIndex].delegate == nullptr)
	{
		return "";
	}
	
	return generateURL(m_urlData[m_getIndex].action);
}

requestURLData* URLData::getCurUrlData()
{
	return &m_urlData[m_getIndex];
}

void URLData::clear()
{
	for (int i = 0; i < MAX_URL_NUM; i++)
	{
		m_urlData[i].delegate = nullptr;
		CC_SAFE_DELETE(m_urlData[i].j_data);
	}
	m_addIndex = 0;
	m_getIndex = MAX_URL_NUM - 1;
}

bool URLData::isEmpty()
{
	for (int i = 0; i < MAX_URL_NUM; i++)
	{
		if (m_urlData[i].delegate != NULL)
		{
			return false;
		}
	}
	return true;
}


std::string URLData::generateURL(URLRequestType type)
{
	return "";
}