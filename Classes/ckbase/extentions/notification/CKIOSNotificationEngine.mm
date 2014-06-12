#include "CKIOSNotificationEngine.h"

CKIOSNotificationEngine::CKIOSNotificationEngine() {

}

CKIOSNotificationEngine::~CKIOSNotificationEngine() {

}

bool CKIOSNotificationEngine::notification(const std::string& id,int money){
	CCLOG("CKIOSNotificationEngine::notification %d for %s\n",money,id.c_str());
	return false;
}
