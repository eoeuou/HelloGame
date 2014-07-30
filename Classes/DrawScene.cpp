#include "DrawScene.h"
#include "game/CKSequenceLayer.h"

#define AnimalSpeed 50.0f

DrawScene::DrawScene(void)
	:m_animal(NULL)
{
}


DrawScene::~DrawScene(void)
{
	
}

bool DrawScene::init()
{	
	addKeyBackEvent(this);
	return true;
}

void DrawScene::onEnter()
{
	CKScene::onEnter();

	addTouchEvent();

	this->schedule(schedule_selector(DrawScene::gameLogic));

	CKSequenceLayer* layer = CKSequenceLayer::create();
	
	addChild(layer,100);

	layer->startScrollLand();

	auto s = Director::getInstance()->getWinSize();

	m_drawNode = DrawNode::create();
	addChild(m_drawNode, 10);

	m_toPoint = ccp(s.width,s.height);
	m_startPoint = ccp(200,200);
	
	m_animal = LabelTTF::create("Hello World", "Arial", 24);
	this->addChild(m_animal);
	m_animal->setPosition(m_startPoint);

	float dis = ccpDistance(m_animal->getPosition(),m_toPoint);
	float time = dis/AnimalSpeed;
	m_animal->runAction(CCMoveTo::create(time,m_toPoint));
}

void DrawScene::onExit()
{
	this->unschedule(schedule_selector(DrawScene::gameLogic));
	removeTouchEvent();
	CKScene::onExit();
}

bool DrawScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	m_toPoint = touch->getLocation();
	m_animal->cleanup();
	float dis = ccpDistance(m_animal->getPosition(),m_toPoint);
	float time = dis/AnimalSpeed;
	m_animal->runAction(CCMoveTo::create(time,m_toPoint));

	return true;
}

void DrawScene::onTouchMoved( Touch *touch, Event *unused_event )
{
	CCPoint prePoint = touch->getPreviousLocation();
	CCPoint curPoint = touch->getLocation();
	m_drawNode->drawSegment(prePoint, curPoint, 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
}

void DrawScene::onTouchEnded( Touch *touch, Event *unused_event )
{

}

void DrawScene::onTouchCancelled( Touch *touch, Event *unused_event )
{

}

void DrawScene::gameLogic( float dt )
{
	auto s = Director::getInstance()->getWinSize();
	//m_drawNode->clear();
	//m_drawNode->drawSegment(m_startPoint, m_animal->getPosition(), 2, Color4F(0, 1, 0, 1));
	//m_drawNode->drawTriangle(Point(10, 10), Point(70, 30), Point(100, 140), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
	m_drawNode->drawDot(m_animal->getPosition(),2,Color4F(0, 1, 0, 1));
}

void DrawScene::drawLine()
{
}
