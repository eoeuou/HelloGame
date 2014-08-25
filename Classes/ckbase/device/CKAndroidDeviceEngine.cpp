#include "CKAndroidDeviceEngine.h"
#include "platform/android/jni/JniHelper.h"

#define  CK_JAVA_CLASS_NAME "org/cocos2dx/ckbase/CKGameHelper"

CKAndroidDeviceEngine::CKAndroidDeviceEngine()
{

}

CKAndroidDeviceEngine::~CKAndroidDeviceEngine()
{

}

std::string getStringByJniMethod(const char* className, const char* methodName)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, className, methodName, "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		std::string ret = JniHelper::jstring2string(str);

		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(str);

		return ret;
	}

	char buf[256];
	sprintf(buf, "JniMethod Wrong : %s", methodName);
	CCAssert(false,buf);
	return "";
}

int getIntegerByJniMethod(const char* className, const char* methodName)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, className, methodName, "()I")) {
		jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);

		return ret;
	}

	char buf[256];
	sprintf(buf, "JniMethod Wrong : %s", methodName);
	CCAssert(false,buf);

	return -1;
}

std::string CKAndroidDeviceEngine::getIMSI()
{
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getImsiNumber").c_str();
}

std::string CKAndroidDeviceEngine::getPhoneNum()
{
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getPhoneNumber").c_str();
}

std::string  CKAndroidDeviceEngine::getDeviceId()
{
	std::string ret = getStringByJniMethod(CK_JAVA_CLASS_NAME,"getDeviceId");

	return ret==""?"0000":ret.c_str();
}

void CKAndroidDeviceEngine::showNetworkSettings()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "showNetworkSettings", "()V")) {
		t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

std::string CKAndroidDeviceEngine::getPackageName()
{ 
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getPackageName");
}

std::string CKAndroidDeviceEngine::getVersionName()
{
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getVersionName");
}

int CKAndroidDeviceEngine::getVersionCode()
{
	return getIntegerByJniMethod(CK_JAVA_CLASS_NAME,"getVersionCode");
}

int CKAndroidDeviceEngine::getNetworkStatusCode()
{
	return getIntegerByJniMethod(CK_JAVA_CLASS_NAME, "getNetworkStatusCode");
}

std::string CKAndroidDeviceEngine::getAvailableInternalMemorySize()
{ 
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getAvailableInternalMemorySize");
}

std::string CKAndroidDeviceEngine::getTotalInternalMemorySize()
{ 
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getTotalInternalMemorySize");
}

std::string CKAndroidDeviceEngine::getAvailableExternalMemorySize()
{
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getAvailableExternalMemorySize");
}

std::string CKAndroidDeviceEngine::getTotalExternalMemorySize()
{ 
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getTotalExternalMemorySize");
}

std::string CKAndroidDeviceEngine::getUsedExternalMemorySize()
{
	return getStringByJniMethod(CK_JAVA_CLASS_NAME,"getUsedExternalMemorySize");
}
