#include "CKManager.h"

CK_SINGLETON_METHOD_INIT(CKManager,s_singleInstance);

CKManager::CKManager(void)
{

}

CKManager::~CKManager(void)
{
	
}

void CKManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKManager::init()
{
	return true;
}