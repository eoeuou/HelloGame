#include "CKDefaultDeviceEngine.h"
#include "CKWrapper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "platform\wp8-xaml\cpp\WP8DataManager.h"
#endif
CKDefaultDeviceEngine::CKDefaultDeviceEngine() 
{

}

CKDefaultDeviceEngine::~CKDefaultDeviceEngine() 
{

}

std::string CKDefaultDeviceEngine::getDeviceId()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	return cocos2d::WP8Tran::pstos(WP8DataHelper::sharedWP8DataManager()->GetUniqueID()).c_str();
#endif
	return "0000";
}

void CKDefaultDeviceEngine::showNetworkSettings()
{
	wrapper::showToast("This is win32");
}
