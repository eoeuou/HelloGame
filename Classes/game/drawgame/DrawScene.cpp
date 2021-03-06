#include "DrawScene.h"

#define AnimalSpeed 50.0f

DrawScene::DrawScene(void):
	m_ckSequenceLayer(NULL),
	m_drawNode(NULL)
{
}

DrawScene::~DrawScene(void)
{
	
}

bool DrawScene::init()
{	
	CKScene::init();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		[this](Ref* pSender){
			if (!m_ckSequenceLayer->getBIsPauseScrollLand())
			{
				m_ckSequenceLayer->pauseScrollLand();
			}
			else
			{
				m_ckSequenceLayer->resumeScrollLand();
			}
	});

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	auto speedItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		[this](Ref* pSender){
			m_ckSequenceLayer->changeScrollSpeed(m_ckSequenceLayer->getScrollSpeed() + 10.5f);
	});

	speedItem->setPosition(Point(origin.x + visibleSize.width - speedItem->getContentSize().width/2 ,
		origin.y + visibleSize.height - speedItem->getContentSize().height/2));


	auto menu = Menu::create(closeItem, speedItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 100);

	addKeyBackEvent(this);

	return true;
}

void DrawScene::onEnter()
{
	CKScene::onEnter();

	addTouchEvent();

	//this->schedule(schedule_selector(DrawScene::sceneUpdate));
	
	auto size = Director::getInstance()->getWinSize();
	m_startPoint = ccp(size.width/2,size.height/2);
	m_directionPoint = ccp(CCRANDOM_MINUS1_1(),CCRANDOM_MINUS1_1());

	m_ckSequenceLayer = CKSequenceLayer::create();
	addChild(m_ckSequenceLayer,-1);
	m_ckSequenceLayer->setStartPoint(m_startPoint);
	m_ckSequenceLayer->setPrePoint(m_startPoint);
	m_ckSequenceLayer->changeScrollDirection(m_directionPoint);
	m_ckSequenceLayer->startScrollLand();

	m_drawNode = DrawNode::create();
	addChild(m_drawNode, 10);
	m_drawNode->drawDot(m_startPoint,10,Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
}

void DrawScene::onExit()
{
	this->unschedule(schedule_selector(DrawScene::sceneUpdate));
	removeTouchEvent();
	CKScene::onExit();
}

bool DrawScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	Point touchPoint = touch->getLocation();
	float angle = ccpToAngle(ccpSub(touchPoint,m_startPoint));
	m_directionPoint = Point::forAngle(angle);

	m_ckSequenceLayer->changeScrollDirection(-m_directionPoint);

	return true;
}

void DrawScene::onTouchMoved( Touch *touch, Event *unused_event )
{
	Point prePoint = touch->getPreviousLocation();
	Point curPoint = touch->getLocation();
	//m_drawNode->drawSegment(prePoint, curPoint, 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
}

void DrawScene::onTouchEnded( Touch *touch, Event *unused_event )
{
}

void DrawScene::onTouchCancelled( Touch *touch, Event *unused_event )
{

}

void DrawScene::sceneUpdate( float dt )
{
}

void DrawScene::drawLine()
{
}
