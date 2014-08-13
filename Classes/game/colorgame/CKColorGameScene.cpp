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

	auto nextItem = MenuItemFont::create("Back", [=](Ref* sender){
		CCDirector::sharedDirector()->popScene();
	});

	nextItem->setFontSizeObj(16);
	nextItem->setPosition(Point(100, 150));

	auto menu2 = Menu::create(nextItem, NULL);
	menu2->setPosition(Point(0, 0));
	menu2->setAnchorPoint(Point(0, 0));
	this->addChild(menu2,100);

	return true;
}

void CKColorGameScene::onEnter()
{
	CKScene::onEnter();
	CCNode::onEnter();
	CKColorGameManager::destroyInstance();
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

	CKColorItem* item = CKColorItem::create(1);
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