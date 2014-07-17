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

void URLController::openUrl(std::string url,std::function<void(CKHttpModel* model)> callback)
{
	m_strUrl = url;

	CKHttpUtils::getInstance()->getText(url.c_str(),callback);

}