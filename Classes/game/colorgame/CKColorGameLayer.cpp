#include "CKColorGameLayer.h"

CKColorItem::CKColorItem():
	m_bgSprite(nullptr),
	m_bIsRotated(false),
	m_colorItemType(CKColorItemType::CKITEM_COLOR_NONE),
	m_colorItemStatus(CKColorItemStatus::CKITEM_STATUS_NONE)
{

}

CKColorItem::~CKColorItem()
{

}

bool CKColorItem::init()
{
	this->ignoreAnchorPointForPosition(false);
	m_bgSprite = Sprite::create("item.png");
	CCSize size = m_bgSprite->getContentSize();
	this->setContentSize(size);
	this->addChild(m_bgSprite);
	m_bgSprite->setPosition(ccp(size.width/2,size.height/2));
	randomItemType();
	return true;
}

void CKColorItem::setItemType(CKColorItemType type)
{	
	if (m_bgSprite)
	{
		Color3B color;
		switch (type)
		{
		case CKColorItemType::CKITEM_COLOR_BLUE:
			color = Color3B::BLUE;
			break;
		case CKColorItemType::CKITEM_COLOR_GREEN:
			color = Color3B::GREEN;
			break;
		case CKColorItemType::CKITEM_COLOR_RED:
			color = Color3B::RED;
			break;
		case CKColorItemType::CKITEM_COLOR_YELLOW:
			color = Color3B::YELLOW;
			break;
		case CKColorItemType::CKITEM_COLOR_ORANGE:
			color = Color3B::ORANGE;
			break;
		default:
			CCAssert(false,"type wrong!");
			break;
		}
		m_bgSprite->setColor(color);
		m_colorItemType = type;
	}
}

void CKColorItem::randomItemType()
{
	int number = CKITEM_COLOR_NONE;
	int ret = rand()%number;
	setItemType((CKColorItemType)ret);
}


CKColorGameLayer::CKColorGameLayer()
{
	m_colorItems.clear();
	m_colorItemSize = Size(0,0);
}

CKColorGameLayer::~CKColorGameLayer()
{
}

bool CKColorGameLayer::initWithColor(const Color4B& color)
{
	CKColorItem* item = CKColorItem::create();
	m_colorItemSize = item->getContentSize();

	int width = GAME_HORIZONTAL*m_colorItemSize.width;
	int height = GAME_VERTICAL*m_colorItemSize.height;

	bool ret = LayerColor::initWithColor(color,width,height);
	this->ignoreAnchorPointForPosition(false);

	//this->addTouchMoveEvent(this);
	this->addTouchEvent();

	initGameItems();
	return ret;
}

void CKColorGameLayer::initGameItems()
{
	m_colorItems.clear();
	m_rotateColorItems.clear();

	int sum = GAME_HORIZONTAL*GAME_VERTICAL;
	for (int i = 0; i < GAME_VERTICAL; i++)
	{
		for (int j = 0;j < GAME_HORIZONTAL; j++)
		{
			CKColorItem* item = CKColorItem::create();
			this->addChild(item);
			item->setPosition(ccp(j*m_colorItemSize.width + m_colorItemSize.width/2.0f,
				i*m_colorItemSize.height + m_colorItemSize.height/2.0f));
			m_colorItems.pushBack(item);
		}
	}
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
		CKColorItem* curItem = m_colorItems.at(x + y * GAME_HORIZONTAL);
		if (curItem->getBIsRotated())
		{
			removeAllRotateColorItems();
		}
		else
		{
			m_rotateColorItems.clear();
			cleanupAllItemsAction();
			checkBoundingItems(x,y);
		}
		return true;
	}

	return false;
}

void CKColorGameLayer::onTouchMoved( Touch *touch, Event *unused_event )
{
	CCPoint prePoint = touch->getPreviousLocation();
	CCPoint curPoint = touch->getLocation();
}

void CKColorGameLayer::onTouchEnded( Touch *touch, Event *unused_event )
{
}

void CKColorGameLayer::onTouchCancelled( Touch *touch, Event *unused_event )
{

}

void CKColorGameLayer::checkBoundingItems(int x, int y)
{
	log("checkBoundingItems... x = %d, y = %d", x, y);
	int cur = x + y * GAME_HORIZONTAL;

	CKColorItem* curItem = m_colorItems.at(cur);
	if (curItem->getBIsRotated())
	{
		return;
	}
	curItem->runRotateAction();
	if (m_rotateColorItems.contains(curItem))
	{
		CCAssert(false,"add wrong!");
	}	
	m_rotateColorItems.pushBack(curItem);
	//check to right
	int right = x + 1;
	if (right < GAME_HORIZONTAL)
	{
		int index = right + y * GAME_HORIZONTAL;
		CKColorItem* item = m_colorItems.at(index);
		log("index=%d,cur=%d",index,cur);
		if (!item->getBIsRotated()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(right,y);
		}
	}
	
	//check to left
	int left = x - 1;
	if (left >= 0)
	{
		int index = left + y * GAME_HORIZONTAL;
		CKColorItem* item = m_colorItems.at(index);
		log("index=%d,cur=%d",index,cur);
		if (!item->getBIsRotated()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(left,y);
		}
	}

	//check to top
	int top = y + 1;
	if (top < GAME_VERTICAL)
	{
		int index = x + top * GAME_HORIZONTAL;
		CKColorItem* item = m_colorItems.at(index);
		log("index=%d,cur=%d",index,cur);
		if (!item->getBIsRotated()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(x,top);
		}
	}
	//check to bottom
	int bottom = y - 1;
	if (bottom >= 0)
	{
		int index = x + bottom * GAME_HORIZONTAL;
		CKColorItem* item = m_colorItems.at(index);
		log("index=%d,cur=%d",index,cur);
		if (!item->getBIsRotated()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(x,bottom);
		}
	}
}

void CKColorGameLayer::cleanupAllItemsAction()
{
	for (const auto& child : m_colorItems)
	{
		child->stopRotateAction();
	}
}

void CKColorGameLayer::removeAllRotateColorItems()
{
	for (const auto& child : m_rotateColorItems)
	{
		child->runMissAction();
	}
	m_rotateColorItems.clear();
}