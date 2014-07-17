#include "URLManager.h"

URLManager* URLManager::s_singleInstance = nullptr;

URLManager::URLManager(void)
	:m_urlData(NULL),
	m_bNeedShakeHands(true),
	m_bIsDoingShakeHands(false),
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

bool URLManager::addUrl(requestURLData _data)
{
	if (!m_urlData->add(_data))
	{
		return false;
	}
	if (m_bNeedShakeHands && !m_bIsDoingShakeHands)
	{
		m_bIsRunning = true;
		m_bIsDoingShakeHands = true;
		URLController::getInstance()->openUrl(shakeHandsUrl(),this);
		return true;
	}
	if (!m_bIsRunning)
	{
		start();
	}
	return true;
}

void URLManager::start()
{
	if (m_bIsRunning)
	{
		return;
	}

	if (m_bNeedShakeHands && !m_bIsDoingShakeHands)
	{
		m_bIsRunning = true;
		m_bIsDoingShakeHands = true;
		URLController::getInstance()->openUrl(shakeHandsUrl(),this);
		return;
	}
	next();
}

void URLManager::next()
{
	std::string strUrl = m_urlData->getNextUrl();
	if (strUrl == "")
	{
		m_bIsRunning = false;
		return;
	}

	m_bIsRunning = true;
	URLController::getInstance()->openUrl(strUrl,this);
}

std::string URLManager::shakeHandsUrl()
{
	return "";
}

void URLManager::URLRequestCallback(CKHttpModel* model)
{
	if (m_bIsDoingShakeHands)
	{

	}
	else
	{

	}
	
	next();
}