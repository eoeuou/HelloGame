#include "CKWrapper.h"
#include "platform/android/jni/JniHelper.h"

#define CK_JAVA_CLASS_NAME "org/cocos2dx/ckbase/Wrapper"

NS_WP_BGN

void showToast(const char* msg)
{
	log("showToast\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,CK_JAVA_CLASS_NAME, "showToast", "(Ljava/lang/String;)V")) {
		jstring message = t.env->NewStringUTF(msg);

		t.env->CallStaticVoidMethod(t.classID, t.methodID,message);
		t.env->DeleteLocalRef(t.classID);
	}
}

void openUrl(const char* url)
{
	log("openUrl\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,CK_JAVA_CLASS_NAME, "openUrl", "(Ljava/lang/String;)V")) {
		jstring message = t.env->NewStringUTF(url);

		t.env->CallStaticVoidMethod(t.classID, t.methodID,message);
		t.env->DeleteLocalRef(t.classID);
	}
}

NS_WP_END