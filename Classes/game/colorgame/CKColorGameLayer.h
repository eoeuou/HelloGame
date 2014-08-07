#ifndef __CKCOLORGAMELAYER_H__
#define __CKCOLORGAMELAYER_H__

#include "cocos2d.h"
#include "CKProtocols.h"

USING_NS_CC;

using namespace std;

typedef enum __ColorItemType
{
	CKITEM_COLOR_BLUE,
	CKITEM_COLOR_GREEN,
	CKITEM_COLOR_RED,
	CKITEM_COLOR_YELLOW,
	CKITEM_COLOR_ORANGE,
	CKITEM_COLOR_NONE
}CKColorItemType;

typedef enum __ColorItemStatus
{
	CKITEM_STATUS_MISS,
	CKITEM_STATUS_NONE
}CKColorItemStatus;

class CKColorItem : public cocos2d::CCLayer
{
private:
	CC_SYNTHESIZE(Sprite*,m_bgSprite,BgSprite);
	CC_SYNTHESIZE(CKColorItemType,m_colorItemType,ColorItemType);
	CC_SYNTHESIZE(CKColorItemStatus,m_colorItemStatus,CKColorItemStatus);
protected:
	CKColorItem();
public:
	~CKColorItem();

	CREATE_FUNC(CKColorItem);
	
	virtual bool init();

	void setItemType(CKColorItemType type);

	void randomItemType();

	void runRotateAction()
	{
		this->runAction(CCRepeatForever::create(CCRotateBy::create(3,360)));
	}
	void stopRotateAction()
	{
		this->setRotation(0);
		this->cleanup();
	}

	bool isItemTypeEqual(CKColorItem* item)
	{
		return this->getColorItemType()==item->getColorItemType();
	}
};

typedef Vector<CKColorItem*> CKColorItems;

#define GAME_HORIZONTAL 10
#define GAME_VERTICAL 8

class CKColorGameLayer : public cocos2d::LayerColor ,public CKTouchMoveProtocol ,public CKTouchProtocol
{
private:
	CC_SYNTHESIZE_READONLY(CKColorItems,m_colorItems,ColorItems);

	CC_SYNTHESIZE_READONLY(Size,m_colorItemSize,ColorItemSize);

protected:

	CKColorGameLayer();

public:
	~CKColorGameLayer();

	static CKColorGameLayer * create(const Color4B& color)
	{
		CKColorGameLayer * layer = new CKColorGameLayer();
		if( layer && layer->initWithColor(color))
		{
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	bool initWithColor(const Color4B& color);

	void initGameItems();
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	void checkBoundingItems(int x, int y);

	void cleanupAllItems();
};

#endif // __CKCOLORGAMELAYER_H__