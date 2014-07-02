#ifndef __URLMANAGER_H__
#define __URLMANAGER_H__

#include "cocos2d.h"
#include "URLData.h"

USING_NS_CC;

using namespace std;

class URLManager
{
public:

    static URLManager* getInstance();

    static void destroyInstance();
	
	bool init();

	//发送请求    
	void requestData(URLRequestType action, JsonData *j_data ,URLRequestDelegate* delegate, void* extraInfo = NULL);
			
private:
	URLManager(void);
	
	~URLManager(void);
	
	//向队列中添加url
	bool addUrl(requestURLData _data);
	

private:
    static URLManager* s_singleInstance;
		

	//用于存储url
	CC_SYNTHESIZE_READONLY(URLData*,m_urlData,URLData);
	//是否需要与服务器握手
	CC_SYNTHESIZE_READONLY(bool,m_bNeedShakeHands,BNeedShakeHands);
	//是否正在与服务器握手
	CC_SYNTHESIZE_READONLY(bool,m_bisDoingShakeHands,BDoingShakeHands);
	//是否正在访问url
	CC_SYNTHESIZE_READONLY(bool,m_bIsRunning,BIsRunning)

	//正在访问的url
	//CC_SYNTHESIZE_READONLY(std::string,,)
};

#endif // __URLMANAGER_H__