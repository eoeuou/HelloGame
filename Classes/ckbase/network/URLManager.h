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

	//��������    
	void requestData(URLRequestType action, JsonData *j_data ,URLRequestDelegate* delegate, void* extraInfo = NULL);
			
private:
	URLManager(void);
	
	~URLManager(void);
	
	//����������url
	bool addUrl(requestURLData _data);
	

private:
    static URLManager* s_singleInstance;
		

	//���ڴ洢url
	CC_SYNTHESIZE_READONLY(URLData*,m_urlData,URLData);
	//�Ƿ���Ҫ�����������
	CC_SYNTHESIZE_READONLY(bool,m_bNeedShakeHands,BNeedShakeHands);
	//�Ƿ����������������
	CC_SYNTHESIZE_READONLY(bool,m_bisDoingShakeHands,BDoingShakeHands);
	//�Ƿ����ڷ���url
	CC_SYNTHESIZE_READONLY(bool,m_bIsRunning,BIsRunning)

	//���ڷ��ʵ�url
	//CC_SYNTHESIZE_READONLY(std::string,,)
};

#endif // __URLMANAGER_H__