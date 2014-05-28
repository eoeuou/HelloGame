#ifndef __CKHTTPUTILS_H__
#define __CKHTTPUTILS_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "CKCommon.h"
#include "CKDialog.h"

USING_NS_CC;
using namespace cocos2d::network;

using namespace std;

class CKHttpUtils : public cocos2d::Ref
{
public:
	CK_SINGLETON_METHOD_LAZY(CKHttpUtils,s_singleInstance,Instance);	

	static void destroyInstance();

	bool init();

	//************************************
	// Method:    getText
	// FullName:  CKHttpUtils::getText
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char * url
	// Parameter: std::function<void
	// Parameter: CKModel * model modelӵ��result��path���ԣ��������ݺͱ����ַ
	// Parameter: > callback �ص�����
	//************************************
	void getText(const char* url,std::function<void(CKModel* model)> callback);

	//************************************
	// Method:    getFile
	// FullName:  CKHttpUtils::getFile
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char * url
	// Parameter: const char * localpath ����·��
	// Parameter: std::function<void
	// Parameter: CKModel * model   modelӵ��result��path���ԣ��������ݺͱ����ַ
	// Parameter: > callback �ص�����
	//************************************
	void getFile(const char* url,const char* localpath,std::function<void(CKModel* model)> callback);

protected:
	CKHttpUtils(void);

	~CKHttpUtils(void);
	
	void onGetTextCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	void onGetFileCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	std::string httpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:
};

#endif // __CKHTTPUTILS_H__