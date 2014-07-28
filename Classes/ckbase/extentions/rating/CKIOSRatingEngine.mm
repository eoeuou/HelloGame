#include "CKIOSRatingEngine.h"

CKIOSRatingEngine::CKIOSRatingEngine()
{

}

CKIOSRatingEngine::~CKIOSRatingEngine()
{

}

bool CKIOSRatingEngine::rating(const std::string& id,int money)
{
	CCLOG("CKIOSRatingEngine::rating %d for %s\n",money,id.c_str());
	return false;
}
