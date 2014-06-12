#include "CKNotificationEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#	include "CKIOSNotificationEngine.h"
#	define	CKPlatformNotificationEngine CKIOSNotificationEngine
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#	include "CKAndroidNotificationEngine.h"
#	define	CKPlatformNotificationEngine CKAndroidNotificationEngine
#endif

#ifndef CKPlatformNotificationEngine
#	include "CKDefaultNotificationEngine.h"
#	define	CKPlatformNotificationEngine CKDefaultNotificationEngine
#endif

CK_INIT_STATIC_FIELD(CKNotificationEngine,s_sharedEngine,CKNotificationEngine*,new CKPlatformNotificationEngine());

CKNotificationEngine::CKNotificationEngine():m_listener(NULL) 
{

}

CKNotificationEngine::~CKNotificationEngine() 
{

}

void CKNotificationEngine::dispatchRecieveNotification(CKNotification& notification)
{
	if(m_listener){
		m_listener->onRecievedNotification(notification);
	}
}

void CKNotificationEngine::dispatchClickNotification(int id)
{
	if(m_listener){
		m_listener->onClickNotification(id);
	}
}
