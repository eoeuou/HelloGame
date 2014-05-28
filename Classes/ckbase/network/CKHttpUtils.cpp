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
	CC_SAFE_RELEASE(s_singleInstance);
}

std::string CKHttpUtils::getText(const char* url) {

	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName = writablePath+"external.txt";
	char szBuf[100] = "Hello Cocos2d-x!";
	FILE* fp = fopen(fileName.c_str(), "wb");
	if (fp)
	{
		size_t ret = fwrite(szBuf, 1, strlen(szBuf), fp);
		CCASSERT(ret != 0, "fwrite function returned zero value");
		fclose(fp);
		if (ret != 0)
			log("Writing file to writable path succeed.");
	}

	return "";
}

void CKHttpUtils::onGetTextCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	std::string res = httpRequestCompleted(sender,response);
}

void CKHttpUtils::getFile(const char* url,const char* localpath)
{
	HttpRequest* request = new HttpRequest();

	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(CKHttpUtils::onGetFileCompleted));
	request->setTag("GET test2");

	HttpClient::getInstance()->send(request);

	request->release();
}

void CKHttpUtils::onGetFileCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{	
	log("over");	
	std::string res = httpRequestCompleted(sender,response);

	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName = writablePath+"external.txt";
	writeFileData(fileName.c_str(),res.c_str());
}

std::string CKHttpUtils::download(const char* url,const string& filename)
{	
	return "";
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