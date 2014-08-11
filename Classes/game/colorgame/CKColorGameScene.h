#ifndef __CKCOLORGAMESCENE_H__
#define __CKCOLORGAMESCENE_H__

#include "cocos2d.h"
#include "CKScene.h"

USING_NS_CC;
using namespace std;

class CKColorGameScene : public CKScene
{
private:

public:
	CREATE_FUNC(CKColorGameScene);

protected:
	CKColorGameScene(void);
	
	~CKColorGameScene(void);

	virtual bool init();  

public:

	virtual void onEnter() override;
	virtual void onExit() override;
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override; 
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override; 
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override; 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;
};

#endif // __CKCOLORGAMESCENE_H__