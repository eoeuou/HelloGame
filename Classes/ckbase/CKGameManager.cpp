#include "CKGameManager.h"
#include "CKGameDataManager.h"
#include "network/CKHttpUtils.h"

CK_SINGLETON_METHOD_INIT(CKGameManager,s_singleInstance);

CKGameManager::CKGameManager(void)
{

}

CKGameManager::~CKGameManager(void)
{
	
}

void CKGameManager::destroyInstance()
{
	CKHttpUtils::destroyInstance();
	CKGameDataManager::destroyInstance();

    CC_SAFE_DELETE(s_singleInstance);
}

bool CKGameManager::init()
{
	CKConstants::init();
	return true;
}