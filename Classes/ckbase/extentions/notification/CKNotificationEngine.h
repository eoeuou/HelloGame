#ifndef CKNOTIFICATIONENGINE_H_
#define CKNOTIFICATIONENGINE_H_

#include "CKCommon.h"

typedef struct _CKNotification{
public:
	int id;
	std::string title;
	std::string message;
	std::string url;
	std::string icon;

	_CKNotification():id(1){

	}

	_CKNotification(int id,std::string& title,std::string& message,std::string& url):id(id),title(title),message(message),url(url){

	}

}CKNotification;

class CKNotificationListener{
public:
	virtual ~CKNotificationListener(){};

	virtual bool onRecievedNotification(CKNotification& notification){return false;};

	virtual void onClickNotification(int id){};
};

class CKNotificationEngine: public cocos2d::Ref{
private:
	CC_SYNTHESIZE(std::string,m_key,Key);
	CC_SYNTHESIZE(CKNotificationListener*,m_listener,Listener);
protected:
	CKNotificationEngine();
public:
	virtual ~CKNotificationEngine();

	virtual void dispatchRecieveNotification(CKNotification& notification);

	virtual void dispatchClickNotification(int id);

	virtual void show(CKNotification& notification) = 0 ;

	virtual void cancel(CKNotification& notification) = 0 ;

	CK_SINGLETON_METHOD(CKNotificationEngine,s_sharedEngine,sharedEngine);
};

#endif /* CKNOTIFICATIONENGINE_H_ */
