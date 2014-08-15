#include "CKColorGameScoreManager.h"

CK_SINGLETON_METHOD_INIT(CKColorGameScoreManager,s_singleInstance);

CKColorGameScoreManager::CKColorGameScoreManager(void)
{

}

CKColorGameScoreManager::~CKColorGameScoreManager(void)
{
	
}

void CKColorGameScoreManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKColorGameScoreManager::init()
{
	return true;
}

void CKColorGameScoreManager::addScoreLabelToScene()
{

}
