#ifndef __CKCOLORITEM_H__
#define __CKCOLORITEM_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

#define GAME_HORIZONTAL 10
#define GAME_VERTICAL 8

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
	CC_SYNTHESIZE(int,m_toItemIndex,ToItemIndex);

protected:
	CKColorItem();
public:
	~CKColorItem();

	static CKColorItem* create(int itemIndex) 
	{ 
		CKColorItem *pRet = new CKColorItem(); 
		if (pRet && pRet->init(itemIndex)) 
		{
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}
	
	virtual bool init(int itemIndex);

	//************************************
	// Method:    setItemType
	// FullName:  CKColorItem::setItemType
	// Access:    public 
	// Returns:   void
	// Qualifier: 设置颜色类型
	// Parameter: CKColorItemType type
	//************************************
	void setItemType(CKColorItemType type);

	//************************************
	// Method:    randomItemType
	// FullName:  CKColorItem::randomItemType
	// Access:    public 
	// Returns:   void
	// Qualifier: 随机颜色
	//************************************
	void randomItemType();

	//************************************
	// Method:    changeItemIndex
	// FullName:  CKColorItem::changeItemIndex
	// Access:    public 
	// Returns:   void
	// Qualifier: 改变原始Index
	// Parameter: int index
	//************************************
	void changeItemIndex(int index);

	//************************************
	// Method:    onItemSelected
	// FullName:  CKColorItem::onItemSelected
	// Access:    public 
	// Returns:   void
	// Qualifier: 当元素被选中
	//************************************
	void onItemSelected();

	//************************************
	// Method:    onItemuUnSelected
	// FullName:  CKColorItem::onItemuUnSelected
	// Access:    public 
	// Returns:   void
	// Qualifier: 当元素失去焦点
	//************************************
	void onItemuUnSelected();

	//************************************
	// Method:    runRotateAction
	// FullName:  CKColorItem::runRotateAction
	// Access:    public 
	// Returns:   void
	// Qualifier: 运行旋转动画
	//************************************
	void runRotateAction();

	//************************************
	// Method:    stopRotateAction
	// FullName:  CKColorItem::stopRotateAction
	// Access:    public 
	// Returns:   void
	// Qualifier: 停止旋转动画
	//************************************
	void stopRotateAction();

	//************************************
	// Method:    runMissAction
	// FullName:  CKColorItem::runMissAction
	// Access:    public 
	// Returns:   void
	// Qualifier: 消失动画
	// Parameter: CallFunc * func
	//************************************
	void runMissAction(CallFunc* func = nullptr,float delay = 0);

	//************************************
	// Method:    isItemTypeEqual
	// FullName:  CKColorItem::isItemTypeEqual
	// Access:    public 
	// Returns:   bool
	// Qualifier: 判断两个元素是否一致
	// Parameter: CKColorItem * item
	//************************************
	bool isItemTypeEqual(CKColorItem* item);

	//************************************
	// Method:    isItemMiss
	// FullName:  CKColorItem::isItemMiss
	// Access:    public 
	// Returns:   bool
	// Qualifier: item是否为消失状态
	//************************************
	bool isItemMiss();

	//************************************
	// Method:    isItemNeedMove
	// FullName:  CKColorItem::isItemNeedMove
	// Access:    public 
	// Returns:   bool
	// Qualifier: item是否需要移动
	//************************************
	bool isItemNeedMove();

	//************************************
	// Method:    runMoveAction
	// FullName:  CKColorItem::runMoveAction
	// Access:    public 
	// Returns:   void
	// Qualifier: 移动动画
	// Parameter: CallFunc * func
	//************************************
	void runMoveAction(CallFunc* func = nullptr);
};
#endif // __CKCOLORITEM_H__