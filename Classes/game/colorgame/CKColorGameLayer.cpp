#include "CKColorGameLayer.h"

CKColorGameLayer::CKColorGameLayer()
{
}

CKColorGameLayer::~CKColorGameLayer()
{
}

bool CKColorGameLayer::initWithColor(const Color4B& color)
{
	int width = GAME_HORIZONTAL*m_colorItemSize.width;
	int height = GAME_VERTICAL*m_colorItemSize.height;

	bool ret = LayerColor::initWithColor(color,width,height);
	this->ignoreAnchorPointForPosition(false);

	//this->addTouchMoveEvent(this);
	this->addTouchEvent();

	return ret;
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