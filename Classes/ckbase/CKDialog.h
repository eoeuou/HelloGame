#ifndef __CKDIALOG_H__
#define __CKDIALOG_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKDialog:public cocos2d::Ref
{
public:
	CREATE_FUNC(CKDialog);
			
protected:
	CKDialog(void);
	
	~CKDialog(void);

	virtual bool init();  

};

#endif // __CKDIALOG_H__