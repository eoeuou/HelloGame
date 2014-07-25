#include "CKAndroidPayEngine.h"
#include "platform/android/jni/JniHelper.h"

#define  CK_JAVA_CLASS_NAME "org/cocos2dx/ckbase/CKGameHelper"

CKAndroidPayEngine::CKAndroidPayEngine()
{

}

CKAndroidPayEngine::~CKAndroidPayEngine()
{

}

bool CKAndroidPayEngine::pay(const std::string& id,int money)
{
	CCLog("CKAndroidPayEngine::pay %d for %s\n",money,id.c_str());
	JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "pay", "(Ljava/lang/String;I)Z")) 
	{
        jstring stringArg = t.env->NewStringUTF(id.c_str());
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg, money);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return false;
}
