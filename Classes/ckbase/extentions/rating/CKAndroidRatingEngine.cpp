#include "CKAndroidRatingEngine.h"
#include "platform/android/jni/JniHelper.h"
#include "CKDeviceEngine.h"
#include "CKWrapper.h"

#define  CK_JAVA_CLASS_NAME "org/cocos2dx/ckbase/CKGameHelper"

CKAndroidRatingEngine::CKAndroidRatingEngine()
{

}

CKAndroidRatingEngine::~CKAndroidRatingEngine()
{

}

bool CKAndroidRatingEngine::rate(const char* appId)
{
	CCLog("CKAndroidRatingEngine::rating %s\n",appId);
	string appIdStr = CKDeviceEngine::sharedEngine()->getPackageName();
	appId = appIdStr.c_str();

	char url [1024] = {0};

	sprintf(url,"market://details?id==%s",appId);

	wrapper::openUrl(url);

    return true;
}
