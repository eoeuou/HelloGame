#include "URLManager.h"

#define MAX_RETRY_TIMES 1

URLManager* URLManager::s_singleInstance = nullptr;

URLManager::URLManager(void)
	:m_urlData(NULL),
	m_bNeedShakeHands(true),
	m_bIsDoingShakeHands(false),
	m_bIsRunning(false),
	m_iRetryTimes(0)
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
	m_urlData = URLData::create();
	m_urlData->retain();
	return true;
}

void URLManager::requestData(URLRequestType action, CKJsonModel *model ,URLRequestListener* listener, void* extraInfo)
{
	requestURLData _data;
	_data.m_action = action;
	_data.m_listener = listener;
	_data.m_jsonModel = model;
	_data.m_picURL = "";
	_data.m_extraInfo = extraInfo;

	//����������url    
	if (!addUrl(_data))
	{
		//��������֤����������    
		CKHttpModel* httpModel = CKHttpModel::create();
		httpModel->initModelData(false,-1,"","",NULL);
		_data.m_listener->urlRequestCallback(httpModel);
	}
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
		std::string url = shakeHandsUrl();
		openUrl(url);
		return true;
	}
	if (!m_bIsRunning)
	{
		start();
	}
	return true;
}

void URLManager::openUrl(std::string url)
{
	URLController::getInstance()->openUrl(url,[this](CKHttpModel* model){
		
		bool isSucceed = model->getIsSucceed();
		if (m_bIsDoingShakeHands)
		{
			if (isSucceed)
			{
				if (checkShakeHandsData())
				{
					wrapper::showToast("���ֳɹ�!");
					next();
				}			
			}
			else
			{
				log("������������ж�!");
				wrapper::showToast("������������ж�(��ǩ�� utf-8������ʾ����) Server connection is broken!");
				exit();
			}		
		}
		else if (isSucceed)
		{
			//��������,�ӽ��ܴ����

			URLRequestListener* listener = m_urlData->getCurUrlData()->m_listener;
			if (listener)
			{
				listener->urlRequestCallback(model);

				m_urlData->removeCurRUrlData();
			}		

			m_bIsRunning = false;
			//������һ������
			next();
		}
		else
		{
			retry();
		}
		
	});
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
		std::string url = shakeHandsUrl();
		openUrl(url);
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
	openUrl(strUrl);
}

void URLManager::retry()
{
	if (m_iRetryTimes >= MAX_RETRY_TIMES)
	{

	}
	else
	{
		m_iRetryTimes++;
		std::string strUrl = m_urlData->getCurUrl();
		m_bIsRunning = true;
		openUrl(strUrl);
	}	
}

void URLManager::exit()
{
	m_bIsRunning = false;
	m_bNeedShakeHands = true;
	m_bIsDoingShakeHands = false;
	m_iRetryTimes = 0;
}

std::string URLManager::shakeHandsUrl()
{
	return "http://httpbin.org/ip";
}

bool URLManager::checkShakeHandsData()
{
	bool result = false;

	bool isRight = true;
	if (isRight)
	{
		result = true;
		m_bNeedShakeHands = false;
		m_bIsDoingShakeHands = false;
	}
	else
	{
		m_bNeedShakeHands = true;
		m_bIsDoingShakeHands = false;
	}


	return result;
}

void URLManager::urlRequestCallback(CKHttpModel* model)
{
}