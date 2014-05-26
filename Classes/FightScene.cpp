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

	return true;
}

void FightScene::onEnter()
{
	CKScene::onEnter();
	sendEvent(TRIGGEREVENT_ENTERSCENE);

	auto dispatch = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(FightScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(FightScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(FightScene::onTouchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(FightScene::onTouchCancelled,this);
	dispatch->addEventListenerWithFixedPriority(listener,1);
	_touchListener = listener;


	this->schedule(schedule_selector(FightScene::gameLogic));
}

void FightScene::onExit()
{
	sendEvent(TRIGGEREVENT_LEAVESCENE);
	this->unschedule(schedule_selector(FightScene::gameLogic));
	auto dispatch = Director::getInstance()->getEventDispatcher();
	dispatch->removeEventListener(_touchListener);
	CKScene::onExit();
}

bool FightScene::onTouchBegan( Touch *touch, Event *unused_event )
{
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
