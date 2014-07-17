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

	//向队列中添加url    
	if (!addUrl(_data))
	{
		//进入这里证明队列已满    
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
		URLController::getInstance()->openUrl(strUrl,this);
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
	bool isSucceed = model->getIsSucceed();
	if (m_bIsDoingShakeHands)
	{
		if (isSucceed)
		{
			if (checkShakeHandsData())
			{
				wrapper::showToast("握手成功!");
				next();
			}			
		}
		else
		{
			log("与服务器连接中断!");
			wrapper::showToast("与服务器连接中断(无签名 utf-8可以显示汉语) Server connection is broken!");
			exit();
		}		
	}
	else if (isSucceed)
	{
		//处理数据,加解密处理等

		URLRequestListener* listener = m_urlData->getCurUrlData()->m_listener;
		if (listener)
		{
			listener->urlRequestCallback(model);

			m_urlData->removeCurRUrlData();
		}		

		m_bIsRunning = false;
		//发送下一个请求
		next();
	}
	else
	{
		retry();
	}
}