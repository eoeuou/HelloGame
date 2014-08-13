#ifndef __CKCOLORITEM_H__
#define __CKCOLORITEM_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

#define GAME_HORIZONTAL 10
#define GAME_VERTICAL 8

#define MAKE_PROPSTYPE_1_SUM 1 //���ɵ�������1������

/*Ԫ�����ͣ���ɫ��*/
typedef enum __ColorItemType
{
	CKITEM_COLOR_BLUE,
	CKITEM_COLOR_GREEN,
	CKITEM_COLOR_RED,
	CKITEM_COLOR_YELLOW,
	CKITEM_COLOR_ORANGE,
	CKITEM_COLOR_NONE
}CKColorItemType;

/*Ԫ��״̬*/
typedef enum __ColorItemStatus
{
	CKITEM_STATUS_MISS,
	CKITEM_STATUS_NONE
}CKColorItemStatus;

/*��������*/
typedef enum __ColorItemPropsType
{
	CKITEM_PROPSTYPE_1,
	CKITEM_PROPSTYPE_2,
	CKITEM_PROPSTYPE_NONE
}CKColorItemPropsType;

class CKColorItem : public cocos2d::CCLayer
{
private:
	CC_SYNTHESIZE_READONLY(Sprite*,m_bgSprite,BgSprite);
	CC_SYNTHESIZE_READONLY(bool,m_bIsSelected,BIsSelected);
	CC_SYNTHESIZE_READONLY(CKColorItemType,m_colorItemType,ColorItemType);
	CC_SYNTHESIZE_READONLY(CKColorItemStatus,m_colorItemStatus,ColorItemStatus);
	CC_SYNTHESIZE_READONLY(CKColorItemPropsType,m_colorItemPropsType,ColorItemPropsType);

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
	// Qualifier: ������ɫ����
	// Parameter: CKColorItemType type
	//************************************
	void setItemType(CKColorItemType type);

	//************************************
	// Method:    randomItemType
	// FullName:  CKColorItem::randomItemType
	// Access:    public 
	// Returns:   void
	// Qualifier: �����ɫ
	//************************************
	void randomItemType();

	//************************************
	// Method:    changeItemIndex
	// FullName:  CKColorItem::changeItemIndex
	// Access:    public 
	// Returns:   void
	// Qualifier: �ı�ԭʼIndex
	// Parameter: int index
	//************************************
	void changeItemIndex(int index);

	//************************************
	// Method:    onItemSelected
	// FullName:  CKColorItem::onItemSelected
	// Access:    public 
	// Returns:   void
	// Qualifier: ��Ԫ�ر�ѡ��
	//************************************
	void onItemSelected();

	//************************************
	// Method:    onItemuUnSelected
	// FullName:  CKColorItem::onItemuUnSelected
	// Access:    public 
	// Returns:   void
	// Qualifier: ��Ԫ��ʧȥ����
	//************************************
	void onItemuUnSelected();

	//************************************
	// Method:    runRotateAction
	// FullName:  CKColorItem::runRotateAction
	// Access:    public 
	// Returns:   void
	// Qualifier: ������ת����
	//************************************
	void runRotateAction();

	//************************************
	// Method:    stopRotateAction
	// FullName:  CKColorItem::stopRotateAction
	// Access:    public 
	// Returns:   void
	// Qualifier: ֹͣ��ת����
	//************************************
	void stopRotateAction();

	//************************************
	// Method:    runMissAction
	// FullName:  CKColorItem::runMissAction
	// Access:    public 
	// Returns:   void
	// Qualifier: ��ʧ����
	// Parameter: CallFunc * func
	//************************************
	void runMissAction(CallFunc* func = nullptr,float delay = 0);

	//************************************
	// Method:    isItemTypeEqual
	// FullName:  CKColorItem::isItemTypeEqual
	// Access:    public 
	// Returns:   bool
	// Qualifier: �ж�����Ԫ���Ƿ�һ��
	// Parameter: CKColorItem * item
	//************************************
	bool isItemTypeEqual(CKColorItem* item);

	//************************************
	// Method:    isItemMiss
	// FullName:  CKColorItem::isItemMiss
	// Access:    public 
	// Returns:   bool
	// Qualifier: item�Ƿ�Ϊ��ʧ״̬
	//************************************
	bool isItemMiss();

	//************************************
	// Method:    isItemNeedMove
	// FullName:  CKColorItem::isItemNeedMove
	// Access:    public 
	// Returns:   bool
	// Qualifier: item�Ƿ���Ҫ�ƶ�
	//************************************
	bool isItemNeedMove();

	//************************************
	// Method:    runMoveAction
	// FullName:  CKColorItem::runMoveAction
	// Access:    public 
	// Returns:   void
	// Qualifier: �ƶ�����
	// Parameter: CallFunc * func
	//************************************
	void runMoveAction(CallFunc* func = nullptr);

	//************************************
	// Method:    changeItemPropsType
	// FullName:  CKColorItem::changeItemPropsType
	// Access:    public 
	// Returns:   void
	// Qualifier: �ı�Item��������
	// Parameter: CKColorItemPropsType type
	//************************************
	void changeItemPropsType(CKColorItemPropsType type);

	//************************************
	// Method:    isItemPropsTypeNone
	// FullName:  CKColorItem::isItemPropsTypeNone
	// Access:    public 
	// Returns:   bool
	// Qualifier: Item�Ƿ�Ϊ��������
	//************************************
	bool isItemPropsType();
};
#endif // __CKCOLORITEM_H__