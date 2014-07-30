#ifndef __DrawScene_H__
#define __DrawScene_H__

#include "cocos2d.h"
#include "CKScene.h"

USING_NS_CC;

using namespace std;

class DrawScene:public CKScene
{
private:
	DrawNode* m_drawNode;
	LabelTTF* m_animal;
	CCPoint m_startPoint;
	CCPoint m_curPoint;
	CCPoint m_toPoint;
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
		
	void gameLogic(float dt);

	void drawLine();

};

#endif // __DrawScene_H__