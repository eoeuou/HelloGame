﻿#include "CKDefaultRatingEngine.h"
#include "CKWrapper.h"

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
	CCLOG("CKDefaultRatingEngine::rating %s\n",appId);
	wrapper::openUrl("http://www.baidu.com/");
	if (m_listener)
	{
		m_listener->onRatingSuccess(appId);
	}
	
	return false;
}
