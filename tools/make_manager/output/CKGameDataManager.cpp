#include "CKGameDataManager.h"

CKGameDataManager* CKGameDataManager::s_singleInstance = nullptr;

CKGameDataManager::CKGameDataManager(void)
{
}


CKGameDataManager::~CKGameDataManager(void)
{
	
}

CKGameDataManager* CKGameDataManager::getInstance()
{
    if (! s_singleInstance)
    {
        s_singleInstance = new CKGameDataManager();
    }

    return s_singleInstance;
}

void CKGameDataManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}
