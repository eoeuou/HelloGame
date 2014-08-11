#ifndef __CKCOLORITEM_H__
#define __CKCOLORITEM_H__

#include "cocos2d.h"

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
	CC_SYNTHESIZE_READONLY(Sprite*,m_bgSprite,BgSprite);
	CC_SYNTHESIZE_READONLY(bool,m_bIsSelected,BIsSelected);
	CC_SYNTHESIZE_READONLY(CKColorItemType,m_colorItemType,ColorItemType);
	CC_SYNTHESIZE_READONLY(CKColorItemStatus,m_colorItemStatus,CKColorItemStatus);

	CC_SYNTHESIZE_READONLY(int,m_itemIndex,ItemIndex);
protected:
	CKColorItem();
public:
	~CKColorItem();

	CREATE_FUNC(CKColorItem);
	
	virtual bool init();

	void setItemType(CKColorItemType type);

	void randomItemType();

	void changeItemIndex(int index)
	{
		m_itemIndex = index;
	}

	void onItemSelected()
	{
		this->m_bIsSelected = true;
	}

	void runRotateAction()
	{
		this->runAction(CCRepeatForever::create(CCRotateBy::create(3,360)));
	}

	void stopRotateAction()
	{
		m_bIsSelected = false;
		this->setRotation(0);
		this->cleanup();
	}

	void runMissAction(CallFunc* func = nullptr)
	{
		CallFunc* changeStatus = CallFunc::create(
			// lambda
			[&](){
				this->m_colorItemStatus = CKColorItemStatus::CKITEM_STATUS_MISS;
		}  );

		if (func != nullptr)
		{
			this->runAction(CCSequence::create(Blink::create(0.3f,3),Hide::create(),changeStatus,func,NULL));
		}
		else
		{
			this->runAction(CCSequence::create(Blink::create(0.3f,3),Hide::create(),changeStatus,NULL));
		}
	}

	bool isItemTypeEqual(CKColorItem* item)
	{
		return this->getColorItemType()==item->getColorItemType();
	}
};
#endif // __CKCOLORITEM_H__