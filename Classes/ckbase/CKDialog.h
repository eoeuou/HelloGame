#ifndef __CKDIALOG_H__
#define __CKDIALOG_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKDialog:public cocos2d::LayerColor
{
public:
	CREATE_FUNC(CKDialog);
				
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 	
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);

	void onCloseCallback(cocos2d::Ref* pSender);
protected:
	CKDialog(void);
	
	~CKDialog(void);

	virtual bool init();  

};

#endif // __CKDIALOG_H__