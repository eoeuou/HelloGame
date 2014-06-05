#include "CKManager.h"

//CK_SINGLETON_METHOD_INIT(CKManager,s_singleInstance);
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
		s_singleInstance->init();
    }

    return s_singleInstance;
}

void CKManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKManager::init()
{
	return true;
}