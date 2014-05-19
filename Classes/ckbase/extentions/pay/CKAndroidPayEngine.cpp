#include "CKAndroidPayEngine.h"

CKAndroidPayEngine::CKAndroidPayEngine() {

}

CKAndroidPayEngine::~CKAndroidPayEngine() {

}

bool CKAndroidPayEngine::pay(const std::string& id,int money){
	CCLog("CKAndroidPayEngine::pay %d for %s\n",money,id.c_str());
	return false;
}
