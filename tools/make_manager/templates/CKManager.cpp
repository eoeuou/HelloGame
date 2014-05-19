#include "CKManager.h"

CKManager* CKManager::s_singleInstance = nullptr;

CKManager::CKManager(void)
{

}

CKManager::~CKManager(void)
{
	
}

CKManager* CKManager::getInstance()
{
    if (! s_singleInstance)
    {
        s_singleInstance = new CKManager();
    }

    return s_singleInstance;
}

void CKManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}
