#include "CKWrapper.h"
#include "platform/android/jni/JniHelper.h"

#define CKGAMEHELP_CLASS_NAME "org/cocos2dx/ckbase/Wrapper"

NS_WP_BGN

void showToast(const char* msg)
{
	log("CKAndroidNotificationEngine::show\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,CKGAMEHELP_CLASS_NAME, "showToast", "(Ljava/lang/String;)V")) {
		jstring message = t.env->NewStringUTF(msg);

		t.env->CallStaticVoidMethod(t.classID, t.methodID,message);
		t.env->DeleteLocalRef(t.classID);
	}
}

std::string getUID(){ return CKDeviceEngine::sharedEngine()->getDeviceId();}
std::string getIMSI(){ return CKDeviceEngine::sharedEngine()->getIMSI();}
std::string getPhoneNum(){ return CKDeviceEngine::sharedEngine()->getPhoneNum();}

NS_WP_END