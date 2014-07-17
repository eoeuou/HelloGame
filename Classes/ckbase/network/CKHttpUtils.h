#ifndef __CKHTTPUTILS_H__
#define __CKHTTPUTILS_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "CKCommon.h"
#include "CKDialog.h"
#include "CKHttpModel.h"

USING_NS_CC;
using namespace cocos2d::network;

using namespace std;

struct CKNetStruct
{
	std::string name;
	std::function<void(CKHttpModel* model)> callback;
	CKLoadingDialog* m_loadingDialog;

	CKNetStruct(std::string name,
		std::function<void(CKHttpModel* model)> callback)
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
			m_loadingDialog = nullptr;
		}
	}
};

class CKHttpUtils : public cocos2d::Ref
{
public:
	CK_SINGLETON_METHOD_LAZY(CKHttpUtils,s_singleInstance,Instance);	

	static void destroyInstance();

	bool init();

	void setTimeOutInformation(int _timeoutForConnect = 30,int _timeoutForRead = 60);

	//************************************
	// Method:    getText
	// FullName:  CKHttpUtils::getText
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char * url
	// Parameter: std::function<void
	// Parameter: CKHttpModel * model ӵ������ [content������] [path�������ַ] [statusCode������״̬��] [isSucceed: ���سɹ�ʧ��]
	// Parameter: > callback �ص�����
	//************************************
	void getText(const char* url,std::function<void(CKHttpModel* model)> callback);
	void getText(const char* url);

	//************************************
	// Method:    getFile
	// FullName:  CKHttpUtils::getFile
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char * url
	// Parameter: const char * localpath ����·��
	// Parameter: std::function<void
	// Parameter: CKHttpModel * model ӵ������ [content������] [path�������ַ] [statusCode������״̬��] [isSucceed: ���سɹ�ʧ��]
	// Parameter: > callback �ص�����
	//************************************
	void getFile(const char* url,const char* localpath,std::function<void(CKHttpModel* model)> callback);
	void getFile(const char* url,const char* localpath);

	//************************************
	// Method:    post
	// FullName:  CKHttpUtils::post
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char * url
	// Parameter: std::function<void
	// Parameter: CKHttpModel * model ӵ������ [content������] [path�������ַ] [statusCode������״̬��] [isSucceed: ���سɹ�ʧ��]
	// Parameter: > callback
	//************************************
	void post(const char* url,const char* postData,std::function<void(CKHttpModel* model)> callback);
	void post(const char* url,const char* postData);
protected:
	CKHttpUtils(void);

	~CKHttpUtils(void);
	
	void onGetTextCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	void onGetFileCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	void onPostCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	std::string httpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response,CKHttpModel* callbackModel);

private:
};

#endif // __CKHTTPUTILS_H__