#include "CKColorGameScene.h"
#include "CKColorGameLayer.h"

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

	Size s = Director::getInstance()->getWinSize();
	Color4B colorA = Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255);
	CKColorGameLayer* m_ckColorGameLayer =  CKColorGameLayer::create(colorA);
	m_ckColorGameLayer->setPosition(ccp(s.width/2.0f,m_ckColorGameLayer->getContentSize().height/2));
	addChild(m_ckColorGameLayer,-1);

	return true;
}

void CKColorGameScene::onEnter()
{
	CKScene::onEnter();
}

void CKColorGameScene::onExit()
{
	removeKeyBackEvent(this);
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