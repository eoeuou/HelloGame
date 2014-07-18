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
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
	HttpClient::destroyInstance();
#endif
	CC_SAFE_RELEASE_NULL(s_singleInstance);
}

bool CKHttpUtils::init()
{
	//setTimeOutInformation(1,1);
	return true;
}

void CKHttpUtils::setTimeOutInformation(int _timeoutForConnect,int _timeoutForRead)
{
	HttpClient::getInstance()->setTimeoutForConnect(_timeoutForConnect);
	HttpClient::getInstance()->setTimeoutForRead(_timeoutForRead);
}

std::string CKHttpUtils::httpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response,CKHttpModel* callbackModel)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
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
	
	callbackModel->setValue("statusCode",Value((int)statusCode));
	callbackModel->setValue("isSucceed",Value(response->isSucceed()));
	
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
#endif
	return "";
}

void CKHttpUtils::getText(const char* url,std::function<void(CKHttpModel* model)> callback) 
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
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
#endif
}

void CKHttpUtils::getText(const char* url) 
{
	getText(url,STD_FUN_CKHTTPMODEL_NULL);
}

void CKHttpUtils::onGetTextCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
	CKNetStruct* sInfo = static_cast<CKNetStruct*>(response->getHttpRequest()->getUserData());
	CCASSERT(sInfo,"sInfo is empty");
	const char* name = sInfo->name.c_str();
	log("getTextName=%s",name);

	CKHttpModel* model = CKHttpModel::create();

	std::string res = httpRequestCompleted(sender,response,model);	
	model->setValue("content",Value(res.c_str()));
	
	sInfo->callback(model);
	sInfo->hideLoadingDialog();
	CC_SAFE_DELETE(sInfo);
#endif
}

void CKHttpUtils::getFile(const char* url,const char* localpath,std::function<void(CKHttpModel* model)> callback)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
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
#endif
}
void CKHttpUtils::getFile(const char* url,const char* localpath)
{
	getFile(url,localpath,STD_FUN_CKHTTPMODEL_NULL);
}

void CKHttpUtils::onGetFileCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{		
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
	CKNetStruct* sInfo = static_cast<CKNetStruct*>(response->getHttpRequest()->getUserData());
	CCASSERT(sInfo,"sInfo is empty");
	const char* path = sInfo->name.c_str();
	log("getTextName=%s",path);

	CKHttpModel* model = CKHttpModel::create();
	
	std::string res = httpRequestCompleted(sender,response,model);
	writeFileData(path,res.c_str());
	model->setValue("content",Value(res.c_str()));
	model->setValue("path",Value(path));

	sInfo->callback(model);
	sInfo->hideLoadingDialog();
	CC_SAFE_DELETE(sInfo);
#endif
}

void CKHttpUtils::post(const char* url,const char* postData,std::function<void(CKHttpModel* model)> callback)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
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
#endif
}

void CKHttpUtils::post(const char* url,const char* postData)
{
	post(url,postData,STD_FUN_CKHTTPMODEL_NULL);
}

void CKHttpUtils::onPostCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
	CKNetStruct* sInfo = static_cast<CKNetStruct*>(response->getHttpRequest()->getUserData());
	CCASSERT(sInfo,"sInfo is empty");
	
	CKHttpModel* model = CKHttpModel::create();

	std::string res = httpRequestCompleted(sender,response,model);
	log("%s",res.c_str());
	model->setValue("content",Value(res.c_str()));

	sInfo->callback(model);
	sInfo->hideLoadingDialog();
	CC_SAFE_DELETE(sInfo);
#endif
}