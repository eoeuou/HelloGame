#include "CKRatingEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#	include "CKIOSRatingEngine.h"
#	define	CKPlatformRatingEngine CKIOSRatingEngine
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#	include "CKAndroidRatingEngine.h"
#	define	CKPlatformRatingEngine CKAndroidRatingEngine
#endif

#ifndef CKPlatformRatingEngine
#	include "CKDefaultRatingEngine.h"
#	define	CKPlatformRatingEngine CKDefaultRatingEngine
#endif

CK_INIT_STATIC_FIELD(CKRatingEngine,s_sharedEngine,CKRatingEngine*,new CKPlatformRatingEngine());

CKRatingEngine::CKRatingEngine():m_listener(NULL)
{

}

CKRatingEngine::~CKRatingEngine()
{

}