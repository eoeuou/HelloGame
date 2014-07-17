#include "URLData.h"


URLData::URLData(void):
	m_addIndex(0)
{
	clear();
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
	if (m_rUrlData[m_addIndex].m_listener == NULL)
	{
		m_rUrlData[m_addIndex] = urlData;
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
	
	return generateURL(m_rUrlData[m_getIndex].m_action);
}

std::string URLData::getCurUrl()
{
	if (m_rUrlData[m_getIndex].m_listener == nullptr)
	{
		return "";
	}
	
	return generateURL(m_rUrlData[m_getIndex].m_action);
}

requestURLData* URLData::getCurUrlData()
{
	return &m_rUrlData[m_getIndex];
}

void URLData::removeCurRUrlData()
{
	m_rUrlData[m_getIndex].clear();
}

void URLData::clear()
{
	for (int i = 0; i < MAX_URL_NUM; i++)
	{
		m_rUrlData[i].m_listener = nullptr;
		CC_SAFE_DELETE(m_rUrlData[i].m_jsonModel);
	}
	m_addIndex = 0;
	m_getIndex = MAX_URL_NUM - 1;
}

bool URLData::isEmpty()
{
	for (int i = 0; i < MAX_URL_NUM; i++)
	{
		if (m_rUrlData[i].m_listener != NULL)
		{
			return false;
		}
	}
	return true;
}


std::string URLData::generateURL(URLRequestType type)
{
	return "http://tarenaapptest.herokuapp.com/?echostr=1";
}