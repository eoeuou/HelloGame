#include "CKAndroidNotificationEngine.h"
#include "platform/android/jni/JniHelper.h"

#define CKGAMEHELP_CLASS_NAME "org/cocos2dx/cpp/ckbase/CKNotification"

CKAndroidNotificationEngine::CKAndroidNotificationEngine()
{

}

CKAndroidNotificationEngine::~CKAndroidNotificationEngine()
{

}

void CKAndroidNotificationEngine::show(CKNotification& notification)
{
	log("CKAndroidNotificationEngine::show\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,CKGAMEHELP_CLASS_NAME, "showNotification", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring title = t.env->NewStringUTF(notification.title.c_str());
		jstring message = t.env->NewStringUTF(notification.message.c_str());
		jstring url = t.env->NewStringUTF(notification.url.c_str());

		t.env->CallStaticVoidMethod(t.classID, t.methodID,notification.id,title,message,url);
		t.env->DeleteLocalRef(t.classID);
	}
}

void CKAndroidNotificationEngine::cancel(CKNotification& notification)
{
	log("CKAndroidNotificationEngine::cancel\n");
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,CKGAMEHELP_CLASS_NAME, "cancelNotification", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID,notification.id);

		t.env->DeleteLocalRef(t.classID);
	}
}