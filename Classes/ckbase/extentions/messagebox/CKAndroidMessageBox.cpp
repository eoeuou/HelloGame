#include "CKAndroidMessageBox.h"
#include "platform/android/jni/JniHelper.h"

#define  CK_JAVA_CLASS_NAME "org/cocos2dx/ckbase/CKMessageBox"

CKAndroidMessageBox::CKAndroidMessageBox()
{

}

CKAndroidMessageBox::~CKAndroidMessageBox()
{

}

bool CKAndroidMessageBox::create()
{
	CCLog("CKAndroidMessageBox::create\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "createDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) 
	{
		jstring titleArg = t.env->NewStringUTF(m_title.c_str());
		jstring messageArg = t.env->NewStringUTF(m_message.c_str());
		jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, titleArg, messageArg);

		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(titleArg);
		t.env->DeleteLocalRef(messageArg);
		return true;
	}

	return false;
}

void CKAndroidMessageBox::setButtonText(int which,const char* text)
{
	CCLog("CKAndroidMessageBox::messagebox %d for %s\n",which,text);
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "setDialogButton", "(ILjava/lang/String;)V")) 
	{
		jstring textArg = t.env->NewStringUTF(text);
		jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, which, textArg);

		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(textArg);
	}
}

void CKAndroidMessageBox::show()
{
	CCLog("CKAndroidMessageBox::show\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "showDialog", "()V")) 
	{
		jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);
	}
}

void CKAndroidMessageBox::hide()
{
	CCLog("CKAndroidMessageBox::hide\n");
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CK_JAVA_CLASS_NAME, "hideDialog", "()V")) 
	{
		jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);
	}
}