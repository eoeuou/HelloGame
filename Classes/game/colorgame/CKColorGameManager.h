#ifndef __CKCOLORGAMEMANAGER_H__
#define __CKCOLORGAMEMANAGER_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKColorGameLayer.h"
#include "CKColorGameScene.h"

USING_NS_CC;

using namespace std;

class CKColorGameManager
{
private:
	CKColorGameManager(void);
	
	~CKColorGameManager(void);
	
public:

	CK_SINGLETON_METHOD_LAZY(CKColorGameManager,s_singleInstance,Instance);

    static void destroyInstance();
	
	bool init();
};

#endif // __CKCOLORGAMEMANAGER_H__