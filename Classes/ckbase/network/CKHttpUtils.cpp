#include "CKHttpUtils.h"

CK_SINGLETON_METHOD_INIT(CKHttpUtils,s_singleInstance);

CKHttpUtils::CKHttpUtils(void)
{
}


CKHttpUtils::~CKHttpUtils(void)
{
	
}

void CKHttpUtils::destroyInstance()
{
	HttpClient::destroyInstance();
	CC_SAFE_RELEASE_NULL(s_singleInstance);
}

bool CKHttpUtils::init()
{
	return true;
}

std::string CKHttpUtils::httpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	if (!response)
	{
		return "";
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag())) 
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %ld", statusCode);

	if (!response->isSucceed()) 
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return "";
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	std::string res(buffer->begin(),buffer->end()); 

	return res;
}

struct CKNetStruct
{
	std::string name;
	std::function<void(CKModel* model)> callback;
	CKLoadingDialog* m_loadingDialog;

	CKNetStruct(std::string name,
		std::function<void(CKModel* model)> callback)
	{
		this->name = name;
		this->callback = callback;
		m_loadingDialog = nullptr;
	}

	void showLoadingDialog()
	{
		Scene* curScene = CCDirector::getInstance()->getRunningScene();
		m_loadingDialog = CKDialog::show<CKLoadingDialog>(curScene,getChildrenMaxZorder(curScene));
	}

	void hideLoadingDialog()
	{
		if (m_loadingDialog)
		{
			m_loadingDialog->removeFromParent();
		}
	}
};

void CKHttpUtils::getText(const char* url,std::function<void(CKModel* model)> callback) 
{
	CKNetStruct* sInfo = new CKNetStruct("getTextName",callback);
	sInfo->showLoadingDialog();

	HttpRequest* request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(CKHttpUtils::onGetTextCompleted));
	request->setTag("getText");	
	request->setUserData(sInfo);

	HttpClient::getInstance()->send(request);
	request->release();
}

void CKHttpUtils::onGetTextCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	CKNetStruct* sInfo = static_cast<CKNetStruct*>(response->getHttpRequest()->getUserData());
	assert(sInfo,"sInfo is empty");
	const char* name = sInfo->name.c_str();
	log("getTextName=%s",name);

	std::string res = httpRequestCompleted(sender,response);

	CKModel* model = CKModel::create();
	model->setProperty("result",res.c_str());

	sInfo->callback(model);
	sInfo->hideLoadingDialog();
	CC_SAFE_DELETE(sInfo);
}

void CKHttpUtils::getFile(const char* url,const char* localpath,std::function<void(CKModel* model)> callback)
{
	CKNetStruct* sInfo = new CKNetStruct(localpath,callback);	
	sInfo->showLoadingDialog();

	HttpRequest* request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(CKHttpUtils::onGetFileCompleted));
	request->setTag("getFile");
	request->setUserData(sInfo);

	HttpClient::getInstance()->send(request);
	request->release();
}

void CKHttpUtils::onGetFileCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{		
	CKNetStruct* sInfo = static_cast<CKNetStruct*>(response->getHttpRequest()->getUserData());
	assert(sInfo,"sInfo is empty");
	const char* path = sInfo->name.c_str();
	log("getTextName=%s",path);
	
	std::string res = httpRequestCompleted(sender,response);
	writeFileData(path,res.c_str());

	CKModel* model = CKModel::create();
	model->setProperty("result",res.c_str());
	model->setProperty("path",path);

	sInfo->callback(model);
	sInfo->hideLoadingDialog();
	CC_SAFE_DELETE(sInfo);
}

void CKHttpUtils::post(const char* url,const char* postData,std::function<void(CKModel* model)> callback)
{
	CKNetStruct* sInfo = new CKNetStruct("postName",callback);	
	sInfo->showLoadingDialog();

	HttpRequest* request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(CKHttpUtils::onPostCompleted));
	request->setRequestData(postData, strlen(postData));
	request->setUserData(sInfo);

	request->setTag("POST test1");
	HttpClient::getInstance()->send(request);
	request->release();
}

void CKHttpUtils::onPostCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	CKNetStruct* sInfo = static_cast<CKNetStruct*>(response->getHttpRequest()->getUserData());
	assert(sInfo,"sInfo is empty");

	std::string res = httpRequestCompleted(sender,response);
	log("%s",res.c_str());

	CKModel* model = CKModel::create();
	model->setProperty("result",res.c_str());

	sInfo->callback(model);
	sInfo->hideLoadingDialog();
	CC_SAFE_DELETE(sInfo);
}