#include "CKColorGameLayer.h"

CKColorGameLayer::CKColorGameLayer()
{
}

CKColorGameLayer::~CKColorGameLayer()
{
}

bool CKColorGameLayer::initWithColor(const Color4B& color, GLfloat width, GLfloat height)
{
	bool ret = LayerColor::initWithColor(color,width,height);

	this->ignoreAnchorPointForPosition(false);

	//this->addTouchMoveEvent(this);
	this->addTouchEvent();

	return ret;
}

CKColorItem* CKColorGameLayer::initColorItemByPos(int x, int y)
{
	int index = x+y*GAME_HORIZONTAL;

	CKColorItem* item = CKColorItem::create(index);

	float sacleX = m_colorItemSize.width/item->getContentSize().width;
	float sacleY = m_colorItemSize.height/item->getContentSize().height;
	item->setScale(sacleX,sacleY);
	item->setPosition(ccp(x*m_colorItemSize.width + m_colorItemSize.width/2.0f,
		y*m_colorItemSize.height + m_colorItemSize.height/2.0f));

	this->addChild(item);

	return item;
}

void CKColorGameLayer::onExit()
{
	LayerColor::onExit();
	this->removeTouchEvent();
}

bool CKColorGameLayer::onTouchBegan( Touch *touch, Event *unused_event )
{
	Point locationInNode = this->convertToNodeSpace(touch->getLocation());
	Size s = this->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode))
	{
		this->setOpacity(180);
		int x = locationInNode.x/m_colorItemSize.width;
		int y = locationInNode.y/m_colorItemSize.height;

		log("sprite began... x = %d, y = %d", x, y);
		if (m_onSelectColorItemFunc != nullptr)
		{
			m_onSelectColorItemFunc(x,y);
		}
		return true;
	}
	return false;
}

void CKColorGameLayer::onTouchMoved( Touch *touch, Event *unused_event )
{
	Point prePoint = touch->getPreviousLocation();
	Point curPoint = touch->getLocation();
}

void CKColorGameLayer::onTouchEnded( Touch *touch, Event *unused_event )
{
}

void CKColorGameLayer::onTouchCancelled( Touch *touch, Event *unused_event )
{
}

void CKColorGameLayer::changeTouchStatus(bool touchable)
{
	if (m_touchable == touchable)
	{
		return;
	}	
	if (touchable)
	{
		log("CKColorGameLayer touchable true");
		this->addTouchEvent(this->getEventDispatcher());
	}
	else
	{
		log("CKColorGameLayer touchable false");
		this->removeTouchEvent(this->getEventDispatcher());
	}
}