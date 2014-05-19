#include "CKDefaultPayEngine.h"

CKDefaultPayEngine::CKDefaultPayEngine() {

}

CKDefaultPayEngine::~CKDefaultPayEngine() {

}

bool CKDefaultPayEngine::pay(const std::string& id,int money){
	CCLOG("CKDefaultPayEngine::pay %d for %s\n",money,id.c_str());
	return false;
}
