#include "CKDeviceEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#	include "CKIOSDeviceEngine.h"
#	define	CKPlatformDeviceEngine CKIOSDeviceEngine
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#	include "CKAndroidDeviceEngine.h"
#	define	CKPlatformDeviceEngine CKAndroidDeviceEngine
#endif

#ifndef CKPlatformDeviceEngine
#	include "CKDefaultDeviceEngine.h"
#	define	CKPlatformDeviceEngine CKDefaultDeviceEngine
#endif

CK_INIT_STATIC_FIELD(CKDeviceEngine,s_sharedEngine,CKDeviceEngine*,new CKPlatformDeviceEngine());

CKDeviceEngine::CKDeviceEngine()
{

}

CKDeviceEngine::~CKDeviceEngine() 
{

}