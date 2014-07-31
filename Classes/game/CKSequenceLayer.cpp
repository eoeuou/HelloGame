#include "CKSequenceLayer.h"

CKSequenceLayer::CKSequenceLayer(void):
	m_scrollDirection(CKScrollDirection::CKSCROLL_DIR_BOTH),
	m_scrollVector(Point::ZERO),
	m_landLayerA(nullptr),
	m_landLayerB(nullptr),
	m_landLayerC(nullptr),
	m_landLayerD(nullptr),
	m_bIsPauseScrollLand(false)
{
}


CKSequenceLayer::~CKSequenceLayer(void)
{
	
}

void CKSequenceLayer::changeScrollVector(CCPoint scrollVector)
{
	//CCAssert(m_scrollDirection == CKScrollDirection::CKSCROLL_DIR_BOTH,"wrong msg");
	m_scrollVector = scrollVector;
}

bool CKSequenceLayer::init()
{
	Size s = Director::getInstance()->getWinSize();
	Color4B colorA = Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255);
	Color4B colorB = Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255);

	m_landLayerA = CCLayerColor::create(Color4B::BLUE, s.width, s.height);
	m_landLayerB = CCLayerColor::create(Color4B::GREEN, s.width, s.height);
	
	if (m_scrollDirection == CKScrollDirection::CKSCROLL_DIR_HORIZONTAL)
	{
		m_landLayerA->setAnchorPoint(Point::ZERO);
		m_landLayerA->setPosition(Point::ZERO);

		m_landLayerB->setAnchorPoint(Point::ZERO);
		m_landLayerB->setPosition(s.width,0);

		m_scrollVector = ccp(LandSpeed_DIS,0);

		this->setContentSize(CCSize(s.width*2,s.height));
	}
	else if (m_scrollDirection == CKScrollDirection::CKSCROLL_DIR_VERTICAL)
	{
		m_landLayerA->setAnchorPoint(Point::ZERO);
		m_landLayerA->setPosition(Point::ZERO);

		m_landLayerB->setAnchorPoint(Point::ZERO);
		m_landLayerB->setPosition(0,s.height);

		m_scrollVector = ccp(0,LandSpeed_DIS);

		this->setContentSize(CCSize(s.width,s.height*2));
	}
	else
	{
		m_landLayerC = CCLayerColor::create(Color4B::RED, s.width, s.height);
		m_landLayerD = CCLayerColor::create(Color4B::ORANGE, s.width, s.height);

		m_landLayerA->setAnchorPoint(Point::ZERO);
		m_landLayerA->setPosition(Point::ZERO);

		m_landLayerB->setAnchorPoint(Point::ZERO);
		m_landLayerB->setPosition(-s.width,0);
		
		m_landLayerC->setAnchorPoint(Point::ZERO);
		m_landLayerC->setPosition(-s.width,-s.height);

		m_landLayerD->setAnchorPoint(Point::ZERO);
		m_landLayerD->setPosition(0,-s.height);

		addChild(m_landLayerC, 0);
		addChild(m_landLayerD, 0);

		m_scrollVector = ccp(LandSpeed_DIS,LandSpeed_DIS);

		this->setContentSize(CCSize(s.width*2,s.height*2));
	}

	addChild(m_landLayerA, 0);
	addChild(m_landLayerB, 0);
	
	return true;
}

void CKSequenceLayer::scrollLand(float dt)
{
	if (m_bIsPauseScrollLand)
	{
		return;
	}
	
	if (m_scrollDirection == CKScrollDirection::CKSCROLL_DIR_HORIZONTAL)
	{
		horizontalScroll();
	}
	else if (m_scrollDirection == CKScrollDirection::CKSCROLL_DIR_VERTICAL)
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
	log("%f,%f,%f",m_landLayerA->getPositionX(),m_landLayerB->getPositionX(),m_landLayerA->getPositionX()-m_landLayerB->getPositionX());

	m_landLayerA->setPositionX(m_landLayerA->getPositionX() + m_scrollVector.x);
	m_landLayerB->setPositionX(m_landLayerB->getPositionX() + m_scrollVector.x);
	
	resetLandLayerVertical(m_landLayerA);
	resetLandLayerVertical(m_landLayerB);
}

void CKSequenceLayer::verticalScroll()
{
	log("%f,%f,%f",m_landLayerA->getPositionY(),m_landLayerB->getPositionY(),m_landLayerA->getPositionY()-m_landLayerB->getPositionY());

	m_landLayerA->setPositionY(m_landLayerA->getPositionY() + m_scrollVector.y);
	m_landLayerB->setPositionY(m_landLayerB->getPositionY() + m_scrollVector.y);
	
	resetLandLayerHorizontal(m_landLayerA);
	resetLandLayerHorizontal(m_landLayerB);
}

void CKSequenceLayer::bothScroll()
{
	log("X:%f,%f,%f,%f",m_landLayerA->getPositionX(),m_landLayerB->getPositionX(),m_landLayerC->getPositionX(),m_landLayerB->getPositionX());
	log("Y:%f,%f,%f,%f",m_landLayerA->getPositionY(),m_landLayerB->getPositionY(),m_landLayerC->getPositionY(),m_landLayerB->getPositionY());
	m_landLayerA->setPosition(m_landLayerA->getPosition() + m_scrollVector);
	m_landLayerB->setPosition(m_landLayerB->getPosition() + m_scrollVector);
	m_landLayerC->setPosition(m_landLayerC->getPosition() + m_scrollVector);
	m_landLayerD->setPosition(m_landLayerD->getPosition() + m_scrollVector);

	resetLandLayerVertical(m_landLayerA);
	resetLandLayerVertical(m_landLayerB);
	resetLandLayerVertical(m_landLayerC);
	resetLandLayerVertical(m_landLayerD);

	resetLandLayerHorizontal(m_landLayerA);
	resetLandLayerHorizontal(m_landLayerB);
	resetLandLayerHorizontal(m_landLayerC);
	resetLandLayerHorizontal(m_landLayerD);
}

void CKSequenceLayer::startScrollLand()
{
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
}

void CKSequenceLayer::resumeScrollLand()
{
	m_bIsPauseScrollLand = false;
}

bool CKSequenceLayer::resetLandLayerVertical(Layer* landLayer)
{
	float width = Director::getInstance()->getWinSize().width;
	if(landLayer->getPositionX() <= -width) 
	{
		landLayer->setPositionX(landLayer->getPositionX() + 2*width);
		return true;
	}
	else if(landLayer->getPositionX() >= width) 
	{
		landLayer->setPositionX(landLayer->getPositionX() - 2*width);
		return true;
	}
	return false;
}

bool CKSequenceLayer::resetLandLayerHorizontal(Layer* landLayer)
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
