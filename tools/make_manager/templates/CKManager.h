#ifndef __CKMANAGER_H__
#define __CKMANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKManager
{
public:

	//CK_SINGLETON_METHOD_LAZY(CKManager,s_singleInstance,Instance);

    static CKManager* getInstance();

    static void destroyInstance();
	
	bool init();
			
private:
	CKManager(void);
	
	~CKManager(void);
	
    static CKManager* s_singleInstance;

};

#endif // __CKMANAGER_H__