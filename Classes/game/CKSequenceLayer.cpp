#include "CKSequenceLayer.h"

#define LandSpeed_DIS 20.0f

CKSequenceLayer::CKSequenceLayer(void):
	m_landLayerA(nullptr),
	m_landLayerB(nullptr)
{
}


CKSequenceLayer::~CKSequenceLayer(void)
{
	
}

bool CKSequenceLayer::init()
{
	Size s = Director::getInstance()->getWinSize();
	m_landLayerA = CCLayerColor::create(Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255), s.width, s.height);
	m_landLayerB = CCLayerColor::create(Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255), s.width, s.height);
	
	this->m_landLayerA->setAnchorPoint(Point::ZERO);
	this->m_landLayerA->setPosition(Point::ZERO);
	this->addChild(this->m_landLayerA, 30);

	this->m_landLayerB->setAnchorPoint(Point::ZERO);
	this->m_landLayerB->setPosition(this->m_landLayerA->getContentSize().width,0);
	this->addChild(this->m_landLayerB, 30);
	
	return true;
}

void CKSequenceLayer::scrollLand(float dt)
{
	this->m_landLayerA->setPositionX(this->m_landLayerA->getPositionX() - LandSpeed_DIS);
	this->m_landLayerB->setPositionX(this->m_landLayerB->getPositionX() - LandSpeed_DIS);
	if(this->m_landLayerA->getPositionX() <= -this->m_landLayerA->getContentSize().width) 
	{
		this->m_landLayerA->setPositionX(this->m_landLayerA->getContentSize().width);
		Color3B color = m_landLayerA->getColor();
		color.r += 50;
		if (color.r>=255)
		{
			color.r = 0;
		}
		m_landLayerA->setColor(color);
	}
	else if (this->m_landLayerB->getPositionX() <= -this->m_landLayerA->getContentSize().width)
	{
		this->m_landLayerB->setPositionX(this->m_landLayerA->getContentSize().width);
		Color3B color = m_landLayerB->getColor();
		color.r += 50;
		if (color.r>=255)
		{
			color.r = 0;
		}
		m_landLayerB->setColor(color);
	}
}

void CKSequenceLayer::startScrollLand()
{
	stopScrollLand();
	this->schedule(schedule_selector(CKSequenceLayer::scrollLand), 0.01f);
}

void CKSequenceLayer::stopScrollLand()
{
	this->unschedule(schedule_selector(CKSequenceLayer::scrollLand));
}