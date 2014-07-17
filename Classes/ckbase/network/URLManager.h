#ifndef __URLMANAGER_H__
#define __URLMANAGER_H__

#include "cocos2d.h"
#include "URLData.h"
#include "URLController.h"
#include "CKHttpModel.h"

USING_NS_CC;

using namespace std;

class URLManager
{
public:

    static URLManager* getInstance();

    static void destroyInstance();
	
	bool init();
	
	void requestData(URLRequestType action, CKJsonModel *model ,URLRequestListener* listener, void* extraInfo = nullptr);

	void urlRequestCallback(CKHttpModel* model);

private:
	URLManager(void);
	
	~URLManager(void);
	
	//����������url
	bool addUrl(requestURLData _data);

	void openUrl(std::string url);
		
	void start();
	
	void next();

	void retry();

	void exit();

	//����������������ֲ���
	std::string shakeHandsUrl();

	//У�������������������    
	bool checkShakeHandsData();

private:
    static URLManager* s_singleInstance;		

	//���ڴ洢url
	CC_SYNTHESIZE_READONLY(URLData*,m_urlData,URLData);
	//�Ƿ���Ҫ�����������
	CC_SYNTHESIZE_READONLY(bool,m_bNeedShakeHands,BNeedShakeHands);
	//�Ƿ����������������
	CC_SYNTHESIZE_READONLY(bool,m_bIsDoingShakeHands,BDoingShakeHands);
	//�Ƿ����ڷ���url
	CC_SYNTHESIZE_READONLY(bool,m_bIsRunning,BIsRunning);
	//���ԵĴ���     
	CC_SYNTHESIZE_READONLY(int,m_iRetryTimes,IRetryTimes);

	//���ڷ��ʵ�url
	//CC_SYNTHESIZE_READONLY(std::string,,)

};

#endif // __URLMANAGER_H__