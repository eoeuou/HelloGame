#include "CKPayEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#	include "CKIOSPayEngine.h"
#	define	CKPlatformPayEngine CKIOSPayEngine
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#	include "CKAndroidPayEngine.h"
#	define	CKPlatformPayEngine CKAndroidPayEngine
#endif

#ifndef CKPlatformPayEngine
#	include "CKDefaultPayEngine.h"
#	define	CKPlatformPayEngine CKDefaultPayEngine
#endif

CK_INIT_STATIC_FIELD(CKPayEngine,s_sharedEngine,CKPayEngine*,new CKPlatformPayEngine());

CKPayEngine::CKPayEngine():m_listener(NULL)
{

}

CKPayEngine::~CKPayEngine()
{

}