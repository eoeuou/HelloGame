#include "CKIOSPayEngine.h"

CKIOSPayEngine::CKIOSPayEngine() {

}

CKIOSPayEngine::~CKIOSPayEngine() {

}

bool CKIOSPayEngine::pay(const std::string& id,int money){
	CCLOG("CKIOSPayEngine::pay %d for %s\n",money,id.c_str());
	return false;
}
