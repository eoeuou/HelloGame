/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_cocos2dx_ckbase_utils_CKNotificationService */

#ifndef _Included_org_cocos2dx_ckbase_utils_CKNotificationService
#define _Included_org_cocos2dx_ckbase_utils_CKNotificationService
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_cocos2dx_ckbase_utils_CKNotificationService
 * Method:    getUserToken
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_cocos2dx_ckbase_utils_CKNotificationService_getUserToken
  (JNIEnv *, jobject);

/*
 * Class:     org_cocos2dx_ckbase_utils_CKNotificationService
 * Method:    onRecievedNotification
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_cocos2dx_ckbase_utils_CKNotificationService_onRecievedNotification
  (JNIEnv *, jobject, jint, jstring, jstring, jstring);

/*
 * Class:     org_cocos2dx_ckbase_utils_CKNotificationService
 * Method:    onClickedNotification
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_cocos2dx_ckbase_utils_CKNotificationService_onClickedNotification
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
