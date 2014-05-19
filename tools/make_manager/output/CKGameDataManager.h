#ifndef __CKGAMEDATAMANAGER_H__
#define __CKGAMEDATAMANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKGameDataManager
{
public:

    static CKGameDataManager* getInstance();

    static void destroyInstance();
			
private:
	CKGameDataManager(void);
	
	~CKGameDataManager(void);
	
    static CKGameDataManager* s_singleInstance;

};

#endif // __CKGAMEDATAMANAGER_H__