#include "CKAndroidDeviceEngine.h"
#include "platform/android/jni/JniHelper.h"

#define  CKGAMEHELP_CLASS_NAME "org/cocos2dx/ckbase/CKGameHelper"

CKAndroidDeviceEngine::CKAndroidDeviceEngine()
{

}

CKAndroidDeviceEngine::~CKAndroidDeviceEngine()
{

}

std::string getStringByJniMethod(const char* methodName)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CKGAMEHELP_CLASS_NAME, methodName, "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		std::string ret = JniHelper::jstring2string(str);

		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(str);

		return ret;
	}
	return "";
}

std::string CKAndroidDeviceEngine::getIMSI()
{
	return getStringByJniMethod("getImsiNumber").c_str();
}

std::string CKAndroidDeviceEngine::getPhoneNum()
{
	return getStringByJniMethod("getPhoneNumber").c_str();
}

std::string  CKAndroidDeviceEngine::getDeviceId()
{
	std::string ret = getStringByJniMethod("getDeviceId");

	return ret==""?"0000":ret.c_str();
}

void CKAndroidDeviceEngine::showNetworkSettings()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CKGAMEHELP_CLASS_NAME, "showNetworkSettings", "()V")) {
		t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}