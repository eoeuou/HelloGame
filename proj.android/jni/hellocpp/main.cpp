#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "CKCommon.h"
#include "CKNotificationEngine.h"
#include "CKHttpUtils.h"
#include "org_cocos2dx_ckbase_CKNotification.h"
#include "org_cocos2dx_ckbase_CKGameHelper.h"
#include "org_cocos2dx_ckbase_utils_CKNotificationService.h"
#include "org_cocos2dx_ckbase_CKMessageBox.h"
#include "CKMessageBox.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
}
/*
 * Class:     org_cocos2dx_ckbase_CKNotification
 * Method:    dispatchRecieveNotification
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_cocos2dx_ckbase_CKNotification_dispatchRecieveNotification
  (JNIEnv * env, jclass obj, jint id, jstring title, jstring message, jstring url)
{
	CKNotification notification;
	notification.id = id;
	notification.title = JniHelper::jstring2string(title);
	notification.message = JniHelper::jstring2string(message);
	if(url!=NULL){
		notification.url = JniHelper::jstring2string(url);
	}

	CKNotificationEngine::sharedEngine()->dispatchRecieveNotification(notification);
}

/*
 * Class:     org_cocos2dx_ckbase_CKNotification
 * Method:    dispatchClickNotification
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_cocos2dx_ckbase_CKNotification_dispatchClickNotification
  (JNIEnv * env, jclass obj, jint id)
{
	CKNotificationEngine::sharedEngine()->dispatchClickNotification(id);
}

/*
 * Class:     org_cocos2dx_ckbase_CKGameHelper
 * Method:    httpUtilsGetText
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_cocos2dx_ckbase_CKGameHelper_httpUtilsGetText
  (JNIEnv *env, jclass obj, jstring url)
{
	std::string path = JniHelper::jstring2string(url);
	CKHttpUtils::getInstance()->getText(path.c_str());
	return env->NewStringUTF("");
}
/*
 * Class:     org_cocos2dx_ckbase_CKMessageBox
 * Method:    onNativeButtonClick
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_cocos2dx_ckbase_CKMessageBox_onNativeButtonClick
  (JNIEnv *env, jclass obj, jint which)
{
	CKMessageBox::dispatchButtonClick(which);
}
