#include "CKDefaultRatingEngine.h"

CKDefaultRatingEngine::CKDefaultRatingEngine()
{

}

CKDefaultRatingEngine::~CKDefaultRatingEngine()
{

}

bool CKDefaultRatingEngine::rate(const char* appId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	//http://www.cnblogs.com/cracker/archive/2012/07/12/windowsphone_Launchers.html
	MarketplaceReviewTask marketplaceReviewTask = new MarketplaceReviewTask();
	marketplaceReviewTask.Show();
#endif
	CCLOG("CKDefaultRatingEngine::rating %d for %s\n",appId);

	if (m_listener)
	{
		m_listener->onRatingSuccess(appId);
	}
	
	return false;
}
