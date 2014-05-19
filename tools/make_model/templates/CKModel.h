#ifndef __CKMODEL_H__
#define __CKMODEL_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKModel:public cocos2d::Ref
{
public:
	CREATE_FUNC(CKModel);
			
protected:
	CKModel(void);
	
	~CKModel(void);

	virtual bool init();  

};

#endif // __CKMODEL_H__