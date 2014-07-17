#ifndef __URLMANAGER_H__
#define __URLMANAGER_H__

#include "cocos2d.h"
#include "URLData.h"
#include "URLController.h"

USING_NS_CC;

using namespace std;

class URLManager : public URLRequestListener
{
public:

    static URLManager* getInstance();

    static void destroyInstance();
	
	bool init();
	
	virtual void URLRequestCallback(CKHttpModel* model);

private:
	URLManager(void);
	
	~URLManager(void);
	
	//向队列中添加url
	bool addUrl(requestURLData _data);
	
	void start();

	void next();

	//生成与服务器的握手操作
	std::string shakeHandsUrl();

private:
    static URLManager* s_singleInstance;		

	//用于存储url
	CC_SYNTHESIZE_READONLY(URLData*,m_urlData,URLData);
	//是否需要与服务器握手
	CC_SYNTHESIZE_READONLY(bool,m_bNeedShakeHands,BNeedShakeHands);
	//是否正在与服务器握手
	CC_SYNTHESIZE_READONLY(bool,m_bIsDoingShakeHands,BDoingShakeHands);
	//是否正在访问url
	CC_SYNTHESIZE_READONLY(bool,m_bIsRunning,BIsRunning)

	//正在访问的url
	//CC_SYNTHESIZE_READONLY(std::string,,)

};

#endif // __URLMANAGER_H__