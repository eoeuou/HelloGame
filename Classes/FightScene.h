#ifndef __FIGHTSCENE_H__
#define __FIGHTSCENE_H__

#include "cocos2d.h"
#include "CKScene.h"

USING_NS_CC;

using namespace std;

class FightScene:public CKScene
{
private:

public:
	CREATE_FUNC(FightScene);
			
protected:
	FightScene(void);
	
	~FightScene(void);

	virtual bool init();  

public:

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override; 
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override; 
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override; 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;
		
	void gameLogic(float dt);

};

#endif // __FIGHTSCENE_H__