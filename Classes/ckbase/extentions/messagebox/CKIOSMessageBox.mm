#include "CKIOSMessageBox.h"

CKIOSMessageBox::CKIOSMessageBox()
{

}

CKIOSMessageBox::~CKIOSMessageBox()
{

}

bool CKIOSMessageBox::messagebox(const std::string& id,int money)
{
	CCLOG("CKIOSMessageBox::messagebox %d for %s\n",money,id.c_str());
	return false;
}
