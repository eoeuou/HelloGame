#include "DrawScene.h"

#define AnimalSpeed 50.0f

DrawScene::DrawScene(void):
	m_ckSequenceLayer(NULL),
	m_drawNode(NULL),
	m_animal(NULL)
{
}

DrawScene::~DrawScene(void)
{
	
}

bool DrawScene::init()
{	
	addKeyBackEvent(this);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(DrawScene::menuCloseCallback, this));

	closeItem->setPosition(Point(closeItem->getContentSize().width/2 ,closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	return true;
}

void DrawScene::menuCloseCallback(Ref* pSender)
{
	if (m_drawNode)
	{
		m_drawNode->clear();
	}	
}

void DrawScene::onEnter()
{
	CKScene::onEnter();

	addTouchEvent();

	this->schedule(schedule_selector(DrawScene::sceneUpdate));
	
	auto size = Director::getInstance()->getWinSize();
	m_startPoint = ccp(size.width/2,size.height/2);
	m_curPoint = m_startPoint;
	m_directionPoint = ccp(1,0);

	m_ckSequenceLayer = CKSequenceLayer::create();
	addChild(m_ckSequenceLayer,-1);
	m_ckSequenceLayer->changeScrollVector(m_directionPoint*LandSpeed_DIS);
	m_ckSequenceLayer->startScrollLand();

	m_drawNode = DrawNode::create();
	m_ckSequenceLayer->addChild(m_drawNode, 10);
	m_drawNode->drawDot(m_curPoint,10,Color4F(0, 0, 0, 1));

	m_animal = LabelTTF::create("Hello World", "Arial", 24);
	addChild(m_animal,11);
	m_animal->setPosition(ccp(size.width,size.height/2));
	m_animal->runAction(CCMoveTo::create(4.0f,ccp(0,size.height/2)));
}

void DrawScene::onExit()
{
	this->unschedule(schedule_selector(DrawScene::sceneUpdate));
	removeTouchEvent();
	CKScene::onExit();
}

bool DrawScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	CCPoint touchPoint = touch->getLocation();
	float angle = ccpToAngle(ccpSub(touchPoint,m_startPoint));
	m_directionPoint = Point::forAngle(angle);

	//m_ckSequenceLayer->pauseScrollLand();
	m_ckSequenceLayer->changeScrollVector(m_directionPoint*LandSpeed_DIS);

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
	//m_ckSequenceLayer->resumeScrollLand();
}

void DrawScene::onTouchCancelled( Touch *touch, Event *unused_event )
{

}

static int num = 1;
void DrawScene::sceneUpdate( float dt )
{
	m_curPoint += m_directionPoint;
	//log("%f,%f,%f",m_directionPoint.x,m_directionPoint.y,dt);
	log("%d",num++);
	m_drawNode->drawDot(m_curPoint,2,Color4F(0.5, 1, 0.8, 1));
}

void DrawScene::drawLine()
{
}
