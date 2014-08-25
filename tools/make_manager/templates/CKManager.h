#ifndef __CKMANAGER_H__
#define __CKMANAGER_H__

#include "cocos2d.h"
#include "CKCommon.h"

USING_NS_CC;

using namespace std;

class CKManager
{
private:
	CKManager(void);
    
public:
	
	~CKManager(void);

	CK_SINGLETON_METHOD_LAZY(CKManager,s_singleInstance,Instance);

    static void destroyInstance();
	
	bool init();
};

#endif // __CKMANAGER_H__