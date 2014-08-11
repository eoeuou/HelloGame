#include "CKSequenceLayer.h"

bool CKLandLayer::initWithColor(const Color4B& color, GLfloat width, GLfloat height)
{
	bool ret = LayerColor::initWithColor(color,width,height);

	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode);
	return ret;
}

void CKLandLayer::drawDotUpdate(float dt,Point prePoint,Point curPoint)
{
	m_drawNode->drawSegment(prePoint,curPoint,10,Color4F(0.5, 1, 0.8, 1));
}

CKSequenceLayer::CKSequenceLayer(void):
	m_scrollType(CKScrollType::CKSCROLL_DIR_BOTH),
	m_scrollDirection(Point::ZERO),
	m_scrollSpeed(LandSpeed),
	m_landLayerA(nullptr),
	m_landLayerB(nullptr),
	m_landLayerC(nullptr),
	m_landLayerD(nullptr),
	m_bIsPauseScrollLand(false),
	m_curLandLayer(nullptr)
{
	m_landLayers.clear();
}


CKSequenceLayer::~CKSequenceLayer(void)
{
	
}

void CKSequenceLayer::changeScrollDirection(Point direction)
{
	//CCAssert(m_scrollType == CKScrollType::CKSCROLL_DIR_BOTH,"wrong msg");
	m_scrollDirection = direction*m_scrollSpeed;
}

void CKSequenceLayer::changeScrollSpeed(float speed)
{
	Point direction = m_scrollDirection/m_scrollSpeed;
	m_scrollSpeed = speed;
	changeScrollDirection(direction);
}

bool CKSequenceLayer::init()
{
	m_landLayers.clear();
	Size s = Director::getInstance()->getWinSize();
	Color4B colorA = Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255);
	Color4B colorB = Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255);

	m_landLayerA = CKLandLayer::create(Color4B::RED, s.width, s.height);
	m_landLayerA->setTag(1);
	m_landLayerB = CKLandLayer::create(Color4B::BLUE, s.width, s.height);
	m_landLayerB->setTag(2);

	if (m_scrollType == CKScrollType::CKSCROLL_DIR_HORIZONTAL)
	{
		m_landLayerA->setAnchorPoint(Point::ZERO);
		m_landLayerA->setPosition(Point::ZERO);

		m_landLayerB->setAnchorPoint(Point::ZERO);
		m_landLayerB->setPosition(s.width,0);

		m_scrollDirection = ccp(m_scrollSpeed,0);

		this->setContentSize(CCSize(s.width*2,s.height));
	}
	else if (m_scrollType == CKScrollType::CKSCROLL_DIR_VERTICAL)
	{
		m_landLayerA->setAnchorPoint(Point::ZERO);
		m_landLayerA->setPosition(Point::ZERO);

		m_landLayerB->setAnchorPoint(Point::ZERO);
		m_landLayerB->setPosition(0,s.height);

		m_scrollDirection = ccp(0,m_scrollSpeed);

		this->setContentSize(CCSize(s.width,s.height*2));
	}
	else
	{
		m_landLayerC = CKLandLayer::create(Color4B::GREEN, s.width, s.height);
		m_landLayerC->setTag(3);
		m_landLayerD = CKLandLayer::create(Color4B::ORANGE, s.width, s.height);
		m_landLayerD->setTag(4);

		m_landLayerA->setAnchorPoint(Point::ZERO);
		m_landLayerA->setPosition(Point::ZERO);

		m_landLayerB->setAnchorPoint(Point::ZERO);
		m_landLayerB->setPosition(-s.width,0);
		
		m_landLayerC->setAnchorPoint(Point::ZERO);
		m_landLayerC->setPosition(-s.width,-s.height);

		m_landLayerD->setAnchorPoint(Point::ZERO);
		m_landLayerD->setPosition(0,-s.height);

		addChild(m_landLayerC);
		addChild(m_landLayerD);
		m_landLayers.pushBack(m_landLayerC);
		m_landLayers.pushBack(m_landLayerD);

		m_scrollDirection = ccp(m_scrollSpeed,m_scrollSpeed);

		this->setContentSize(CCSize(s.width*2,s.height*2));
	}

	addChild(m_landLayerA);
	addChild(m_landLayerB);
	m_landLayers.pushBack(m_landLayerA);
	m_landLayers.pushBack(m_landLayerB);
	
	/*Color3B color = ccc3(CCRANDOM_0_1()*255,CCRANDOM_0_1()*255,CCRANDOM_0_1()*255);
	for (const auto& child : m_landLayers)
	{
		child->setColor(color);
	}*/
	return true;
}
static int num = 1;
void CKSequenceLayer::scrollLand(float dt)
{
	if (m_bIsPauseScrollLand)
	{
		return;
	}
	CCScene* scene = Director::getInstance()->getRunningScene();
	Point point = scene->convertToWorldSpace(m_startPoint);

	for (const auto& child : m_landLayers)
	{
		if (child->getBoundingBox().containsPoint(point))
		{
			Point curPoint = child->convertToNodeSpace(point);
			if (m_curLandLayer!=child)
			{
				if (m_curLandLayer)
				{
					m_curLandLayer->getParent()->reorderChild(m_curLandLayer,-1);
				}
				m_curLandLayer = child;
				m_prePoint = curPoint;
			}

			child->drawDotUpdate(dt,m_prePoint,curPoint);
			m_prePoint = curPoint;
			log("%d",num++);
			break;
		}
	}
	
	if (m_scrollType == CKScrollType::CKSCROLL_DIR_HORIZONTAL)
	{
		horizontalScroll();
	}
	else if (m_scrollType == CKScrollType::CKSCROLL_DIR_VERTICAL)
	{
		verticalScroll();
	}
	else
	{
		bothScroll();
	}
}

void CKSequenceLayer::horizontalScroll()
{
	//log("%f,%f,%f",m_landLayerA->getPositionX(),m_landLayerB->getPositionX(),m_landLayerA->getPositionX()-m_landLayerB->getPositionX());
		
	for (const auto& child : m_landLayers)
	{
		child->setPositionX(child->getPositionX() + m_scrollDirection.x);
		resetLandLayerHorizontal(child);
	}
}

void CKSequenceLayer::verticalScroll()
{
	//log("%f,%f,%f",m_landLayerA->getPositionY(),m_landLayerB->getPositionY(),m_landLayerA->getPositionY()-m_landLayerB->getPositionY());
		
	for (const auto& child : m_landLayers)
	{
		child->setPositionY(child->getPositionY() + m_scrollDirection.y);
		resetLandLayerVertical(child);
	}
}

void CKSequenceLayer::bothScroll()
{
	//log("X:%f,%f,%f,%f",m_landLayerA->getPositionX(),m_landLayerB->getPositionX(),m_landLayerC->getPositionX(),m_landLayerB->getPositionX());
	//log("Y:%f,%f,%f,%f",m_landLayerA->getPositionY(),m_landLayerB->getPositionY(),m_landLayerC->getPositionY(),m_landLayerB->getPositionY());

	for (const auto& child : m_landLayers)
	{
		child->setPosition(child->getPosition() + m_scrollDirection);
		resetLandLayerVertical(child);
		resetLandLayerHorizontal(child);
	}
}

void CKSequenceLayer::startScrollLand()
{
	resumeScrollLand();
	stopScrollLand();
	schedule(schedule_selector(CKSequenceLayer::scrollLand));
}

void CKSequenceLayer::stopScrollLand()
{
	unschedule(schedule_selector(CKSequenceLayer::scrollLand));
}

void CKSequenceLayer::pauseScrollLand()
{
	m_bIsPauseScrollLand = true;
	for (const auto& child : m_landLayers)
	{
		child->addTouchEvent();
	}
}

void CKSequenceLayer::resumeScrollLand()
{
	m_bIsPauseScrollLand = false;
	for (const auto& child : m_landLayers)
	{
		child->removeTouchEvent();
	}
}

bool CKSequenceLayer::resetLandLayerHorizontal(Layer* landLayer)
{
	float width = Director::getInstance()->getWinSize().width;
	if(landLayer->getPositionX() <= -width) 
	{
		landLayer->setPositionX(landLayer->getPositionX() + 2*width);
		log("reset:%d,to right",landLayer->getTag());
		return true;
	}
	else if(landLayer->getPositionX() >= width) 
	{
		landLayer->setPositionX(landLayer->getPositionX() - 2*width);
		log("reset:%d,to left",landLayer->getTag());
		return true;
	}
	return false;
}

bool CKSequenceLayer::resetLandLayerVertical(Layer* landLayer)
{
	float height = Director::getInstance()->getWinSize().height;
	if(landLayer->getPositionY() <= -height) 
	{
		landLayer->setPositionY(landLayer->getPositionY() + 2*height);
		return true;
	}
	else if(landLayer->getPositionY() >= height) 
	{
		landLayer->setPositionY(landLayer->getPositionY() - 2*height);
		return true;
	}
	return false;
}
