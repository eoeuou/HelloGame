#include "CKColorGameManager.h"

CK_SINGLETON_METHOD_INIT(CKColorGameManager,s_singleInstance);

CKColorGameManager::CKColorGameManager(void)
{

}

CKColorGameManager::~CKColorGameManager(void)
{
	
}

void CKColorGameManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKColorGameManager::init()
{
	return true;
}