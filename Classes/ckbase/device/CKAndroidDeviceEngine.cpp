#include "CKAndroidDeviceEngine.h"
#include "platform/android/jni/JniHelper.h"

#define  CKGAMEHELP_CLASS_NAME "org/cocos2dx/cpp/CKGameHelper"

CKAndroidDeviceEngine::CKAndroidDeviceEngine() {

}

CKAndroidDeviceEngine::~CKAndroidDeviceEngine() {

}

std::string CKAndroidDeviceEngine::getDeviceId()
{
	std::string ret("");

	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CKGAMEHELP_CLASS_NAME, "getDeviceId", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		ret = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);

		return ret;
	}

	return "0000";
}

void CKAndroidDeviceEngine::showNetworkSettings()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CKGAMEHELP_CLASS_NAME, "showNetworkSettings", "()V")) {
		t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}