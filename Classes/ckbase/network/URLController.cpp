#include "URLController.h"

CK_SINGLETON_METHOD_INIT(URLController,s_singleInstance);

URLController::URLController(void):
	m_urlRequestListener(nullptr)
{

}

URLController::~URLController(void)
{
	
}

void URLController::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool URLController::init()
{
	return true;
}

void URLController::openUrl(std::string url, URLRequestListener* urlRequestListener)
{
	m_strUrl = url;
	m_urlRequestListener = urlRequestListener;	

	CKHttpUtils::getInstance()->getText(url.c_str(),[this](CKHttpModel* model){
		if (m_urlRequestListener)
		{
			m_urlRequestListener->urlRequestCallback(model);
		}		
	});

}