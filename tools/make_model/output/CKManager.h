#ifndef __CKMANAGER_H__
#define __CKMANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKManager:public cocos2d::Ref
{
public:
	CREATE_FUNC(CKManager);
			
protected:
	CKManager(void);
	
	~CKManager(void);

	virtual bool init();  

};

#endif // __CKMANAGER_H__