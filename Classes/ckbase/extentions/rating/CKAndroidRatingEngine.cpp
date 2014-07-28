#include "CKAndroidRatingEngine.h"
#include "platform/android/jni/JniHelper.h"

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
	JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "rating", "(Ljava/lang/String;I)Z")) 
	{
        jstring stringArg = t.env->NewStringUTF(appId);
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return false;
}
