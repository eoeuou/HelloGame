#ifndef __CKMANAGER_H__
#define __CKMANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKManager
{
public:

    static CKManager* getInstance();

    static void destroyInstance();
			
private:
	CKManager(void);
	
	~CKManager(void);
	
    static CKManager* s_singleInstance;

};

#endif // __CKMANAGER_H__