#include "CKJsonHelper.h"

CK_SINGLETON_METHOD_INIT(CKJsonHelper,s_singleInstance);

CKJsonHelper::CKJsonHelper(void)
{

}

CKJsonHelper::~CKJsonHelper(void)
{
	
}

void CKJsonHelper::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKJsonHelper::init()
{
	return true;
}