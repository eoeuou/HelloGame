#ifndef __CKGAMEMANAGER_H__
#define __CKGAMEMANAGER_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKConstants.h"

USING_NS_CC;

using namespace std;

class CKGameManager
{
public:

	CK_SINGLETON_METHOD_LAZY(CKGameManager,s_singleInstance,Instance);

	static void destroyInstance();

	bool init();
			
private:
	CKGameManager(void);
	
	~CKGameManager(void);

};

#endif // __CKGAMEMANAGER_H__