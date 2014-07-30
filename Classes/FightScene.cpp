#include "FightScene.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
FightScene::FightScene(void)
{
}


FightScene::~FightScene(void)
{
	
}

bool FightScene::init()
{
	CCNode *pNode = SceneReader::getInstance()->createNodeWithSceneFile("publish/FightScene.json"); 
	this->addChild(pNode, 0, 1); 

	addKeyBackEvent(this);
	return true;
}

void FightScene::onEnter()
{
	CKScene::onEnter();
	sendEvent(TRIGGEREVENT_ENTERSCENE);

	addTouchEvent();

	this->schedule(schedule_selector(FightScene::gameLogic));
}

void FightScene::onExit()
{
	sendEvent(TRIGGEREVENT_LEAVESCENE);
	this->unschedule(schedule_selector(FightScene::gameLogic));
	removeTouchEvent();
	CKScene::onExit();
}

bool FightScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	CKScene::onTouchBegan(touch,unused_event);
	sendEvent(TRIGGEREVENT_TOUCHBEGAN);
	return true;
}

void FightScene::onTouchMoved( Touch *touch, Event *unused_event )
{
	sendEvent(TRIGGEREVENT_TOUCHMOVED);
}

void FightScene::onTouchEnded( Touch *touch, Event *unused_event )
{
	sendEvent(TRIGGEREVENT_TOUCHENDED);
}

void FightScene::onTouchCancelled( Touch *touch, Event *unused_event )
{
	sendEvent(TRIGGEREVENT_TOUCHCANCELLED);
}

void FightScene::gameLogic( float dt )
{
	sendEvent(TRIGGEREVENT_UPDATESCENE);
}
