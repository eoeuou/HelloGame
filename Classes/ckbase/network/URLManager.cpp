#include "URLManager.h"

URLManager* URLManager::s_singleInstance = nullptr;

URLManager::URLManager(void)
	:m_urlData(NULL),
	m_bNeedShakeHands(true),
	m_bisDoingShakeHands(false),
	m_bIsRunning(false)
{

}

URLManager::~URLManager(void)
{
	
}

URLManager* URLManager::getInstance()
{
    if (! s_singleInstance)
    {
        s_singleInstance = new URLManager();
		s_singleInstance->init();
    }

    return s_singleInstance;
}

void URLManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool URLManager::init()
{
	return true;
}

void URLManager::requestData(URLRequestType action, CKJsonModel *j_data ,URLRequestDelegate* delegate, void* extraInfo)
{
	requestURLData data;
	data.action = action;
	data.delegate = delegate;
	data.extraInfo = extraInfo;
	data.j_data = j_data;
	data.picURL = "";

	if (!addUrl(data))
	{
		delegate->URLRequestErrorCallback(data.action,-1,extraInfo);
	}	
}

bool URLManager::addUrl(requestURLData _data)
{
	if (!m_urlData->add(_data))
	{
		return false;
	}
	if (m_bNeedShakeHands && !m_bisDoingShakeHands)
	{
		m_bIsRunning = true;
		m_bisDoingShakeHands = true;
		
		return true;
	}
	if (!m_bIsRunning)
	{
		//START();
	}
	return true;
}