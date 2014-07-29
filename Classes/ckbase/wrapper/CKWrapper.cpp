#include "CKWrapper.h"

NS_WP_BGN

std::string getUID(){ return CKDeviceEngine::sharedEngine()->getDeviceId();}
std::string getIMSI(){ return CKDeviceEngine::sharedEngine()->getIMSI();}
std::string getPhoneNum(){ return CKDeviceEngine::sharedEngine()->getPhoneNum();}
bool isNetworkAvailable(){ return CKDeviceEngine::sharedEngine()->isNetworkAvailable();}

NS_WP_END