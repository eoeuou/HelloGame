#include "CKColorGameLayer.h"

CKColorItem::CKColorItem():
	m_bgSprite(nullptr),
	m_bIsSelected(false),
	m_colorItemType(CKColorItemType::CKITEM_COLOR_NONE),
	m_colorItemStatus(CKColorItemStatus::CKITEM_STATUS_NONE),
	m_itemIndex(-1),
	m_toItemIndex(-1)
{

}

CKColorItem::~CKColorItem()
{

}

bool CKColorItem::init(int itemIndex)
{
	this->m_itemIndex = itemIndex;
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

void CKColorItem::changeItemIndex(int index)
{
	m_itemIndex = index;
}

void CKColorItem::onItemSelected()
{
	this->m_bIsSelected = true;
}

void CKColorItem::onItemuUnSelected()
{
	this->m_bIsSelected = false;
}

void CKColorItem::runRotateAction()
{
	this->runAction(CCRepeatForever::create(CCRotateBy::create(3,360)));
}

void CKColorItem::stopRotateAction()
{
	this->onItemuUnSelected();
	this->setRotation(0);
	this->cleanup();
}

void CKColorItem::runMissAction(CallFunc* func,float delay)
{
	CallFunc* changeStatus = CallFunc::create(
		// lambda
		[this](){
			this->m_colorItemStatus = CKColorItemStatus::CKITEM_STATUS_MISS;
	}  );


	if (func != nullptr)
	{
		this->runAction(CCSequence::create(DelayTime::create(delay),Blink::create(0.3f,3),Hide::create(),changeStatus,func,NULL));
	}
	else
	{
		this->runAction(CCSequence::create(DelayTime::create(delay),Blink::create(0.3f,3),Hide::create(),changeStatus,NULL));
	}
}

bool CKColorItem::isItemTypeEqual(CKColorItem* item)
{
	return this->getColorItemType()==item->getColorItemType();
}

bool CKColorItem::isItemMiss()
{
	return this->getCKColorItemStatus() == CKColorItemStatus::CKITEM_STATUS_MISS;
}

bool CKColorItem::isItemNeedMove()
{
	return m_toItemIndex != -1;
}

void CKColorItem::runMoveAction(CallFunc* func)
{
	if (m_toItemIndex==-1)
	{
		return ;
	}
	
	int nowX = m_itemIndex%GAME_HORIZONTAL;
	int nowY = m_itemIndex/GAME_HORIZONTAL;

	int toX = m_toItemIndex%GAME_HORIZONTAL;
	int toY = m_toItemIndex/GAME_HORIZONTAL;

	log("from:nowX=%d,nowY=%d to:toX=%d,toY=%d========from:m_itemIndex=%d to:toItemIndex=%d",nowX,nowY,toX,toY,m_itemIndex,m_toItemIndex);

	this->m_itemIndex = m_toItemIndex;

	CCSize size = this->getContentSize();
	CCPoint point = this->getPosition();
	point = ccpAdd(point,ccp(size.width*(toX-nowX),size.height*(toY-nowY)));

	float time = 0.3f;

	CallFunc* changeStatus = CallFunc::create(
		// lambda
		[this](){
			m_toItemIndex = -1;
	}  );

	if (func != nullptr)
	{
		this->runAction(CCSequence::create(EaseElasticInOut::create(CCMoveTo::create(time,point),0.1f),changeStatus,func,NULL));
	}
	else
	{
		this->runAction(CCSequence::create(EaseElasticInOut::create(CCMoveTo::create(time,point),0.1f),changeStatus,NULL));
	}
}