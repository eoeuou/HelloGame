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
	
	//向队列中添加url
	bool addUrl(requestURLData _data);

	void openUrl(std::string url);
		
	void start();
	
	void next();

	void retry();

	void exit();

	//生成与服务器的握手操作
	std::string shakeHandsUrl();

	//校验服务器返回握手数据    
	bool checkShakeHandsData();

private:
    static URLManager* s_singleInstance;		

	//用于存储url
	CC_SYNTHESIZE_READONLY(URLData*,m_urlData,URLData);
	//是否需要与服务器握手
	CC_SYNTHESIZE_READONLY(bool,m_bNeedShakeHands,BNeedShakeHands);
	//是否正在与服务器握手
	CC_SYNTHESIZE_READONLY(bool,m_bIsDoingShakeHands,BDoingShakeHands);
	//是否正在访问url
	CC_SYNTHESIZE_READONLY(bool,m_bIsRunning,BIsRunning);
	//重试的次数     
	CC_SYNTHESIZE_READONLY(int,m_iRetryTimes,IRetryTimes);

	//正在访问的url
	//CC_SYNTHESIZE_READONLY(std::string,,)

};

#endif // __URLMANAGER_H__