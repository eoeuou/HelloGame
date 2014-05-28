#ifndef __CKHTTPUTILS_H__
#define __CKHTTPUTILS_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "CKCommon.h"

USING_NS_CC;
using namespace cocos2d::network;

using namespace std;

class CKHttpUtils : public cocos2d::Ref
{
public:
	CK_SINGLETON_METHOD_LAZY(CKHttpUtils,s_singleInstance,Instance);

	std::string getText(const char* url);

	void getFile(const char* url,const char* localpath);

	std::string download(const char* url,const string& filename);

protected:
	CKHttpUtils(void);

	~CKHttpUtils(void);
	
	void onGetTextCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	void onGetFileCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	std::string httpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:

};

#endif // __CKHTTPUTILS_H__