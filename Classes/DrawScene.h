#ifndef __DrawScene_H__
#define __DrawScene_H__

#include "cocos2d.h"
#include "CKScene.h"
#include "game/CKSequenceLayer.h"

USING_NS_CC;

using namespace std;

class DrawScene : public CKScene
{
private:
	CKSequenceLayer* m_ckSequenceLayer;
	DrawNode* m_drawNode;

	CCPoint m_startPoint;
	CCPoint m_directionPoint;

public:
	CREATE_FUNC(DrawScene);
			
protected:
	DrawScene(void);
	
	~DrawScene(void);

	virtual bool init();  

public:

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override; 
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override; 
	virtual void onTouchEnded(Touch *touch, Event *unused_event) override; 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

	void sceneUpdate(float dt);

	void drawLine();
};

#endif // __DrawScene_H__