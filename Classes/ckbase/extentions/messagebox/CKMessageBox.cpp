#include "CKMessageBox.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#	include "CKIOSMessageBox.h"
#	define	CKPlatformMessageBox CKIOSMessageBox
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#	include "CKAndroidMessageBox.h"
#	define	CKPlatformMessageBox CKAndroidMessageBox
#endif

#ifndef CKPlatformMessageBox
#	include "CKDefaultMessageBox.h"
#	define	CKPlatformMessageBox CKDefaultMessageBox
#endif

CKMessageBox* CKMessageBox::s_messageBox = NULL;

CKMessageBox::CKMessageBox()
	:m_title(""),
	m_message(""),
	m_messageBoxListener(NULL)
{

}

CKMessageBox::~CKMessageBox()
{

}

void CKMessageBox::onButtonClick(int which)
{
	if (m_messageBoxListener)
	{
		m_messageBoxListener->onButtonClick(this,which);
	}
	if (m_msgBoxCallback)
	{
		m_msgBoxCallback(this,which);
	}	
}

CKMessageBox* CKMessageBox::create(const char* title,const char* message)
{
	if(s_messageBox==NULL){
		s_messageBox = new CKPlatformMessageBox();
	}

	s_messageBox->setTitle(title);
	s_messageBox->setMessage(message);

	s_messageBox->create();

	return s_messageBox;
}

void CKMessageBox::dispatchButtonClick(int which)
{
	s_messageBox->onButtonClick(which);
}
