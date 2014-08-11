#include "CKColorGameLayer.h"

CKColorItem::CKColorItem():
	m_bgSprite(nullptr),
	m_bIsSelected(false),
	m_colorItemType(CKColorItemType::CKITEM_COLOR_NONE),
	m_colorItemStatus(CKColorItemStatus::CKITEM_STATUS_NONE),
	m_itemIndex(-1)
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
