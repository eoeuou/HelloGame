#include "CKColorGameScene.h"
#include "CKColorGameManager.h"

CKColorGameScene::CKColorGameScene(void)
{
}

CKColorGameScene::~CKColorGameScene(void)
{
	
}

bool CKColorGameScene::init()
{	
	CKScene::init();

	addKeyBackEvent(this);
	//addTouchEvent();

	return true;
}

void CKColorGameScene::onEnter()
{
	CKScene::onEnter();
	CKColorGameManager::getInstance();
}

void CKColorGameScene::onExit()
{
	removeKeyBackEvent(this);
	CKColorGameManager::destroyInstance();
	CKScene::onExit();
}

bool CKColorGameScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	CKScene::onTouchBegan(touch,unused_event);

	CKColorItem* item = CKColorItem::create();
	this->addChild(item);
	item->setPosition(touch->getLocation());
	item->randomItemType();
	return true;
}

void CKColorGameScene::onTouchMoved( Touch *touch, Event *unused_event )
{

}

void CKColorGameScene::onTouchEnded( Touch *touch, Event *unused_event )
{

}

void CKColorGameScene::onTouchCancelled( Touch *touch, Event *unused_event )
{

}