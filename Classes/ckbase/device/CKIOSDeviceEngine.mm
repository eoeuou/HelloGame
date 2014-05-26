#include "CKIOSDeviceEngine.h"

CKIOSDeviceEngine::CKIOSDeviceEngine() {

}

CKIOSDeviceEngine::~CKIOSDeviceEngine() {

}

bool CKIOSDeviceEngine::device(const std::string& id,int money){
	CCLOG("CKIOSDeviceEngine::device %d for %s\n",money,id.c_str());
	return false;
}
