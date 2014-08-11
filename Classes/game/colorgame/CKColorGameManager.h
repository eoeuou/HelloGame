#ifndef __CKCOLORGAMEMANAGER_H__
#define __CKCOLORGAMEMANAGER_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKColorGameLayer.h"

USING_NS_CC;

using namespace std;

typedef Map<int,CKColorItem*> CKColorItemMap;
typedef Vector<CKColorItem*> CKColorItemVector;

class CKColorGameManager
{
private:
	CC_SYNTHESIZE_READONLY(CKColorItemMap,m_colorItems,ColorItems);

	CC_SYNTHESIZE_READONLY(Size,m_colorItemSize,ColorItemSize);

	CC_SYNTHESIZE_READONLY(CKColorItemVector,m_selectedItems,SelectedItems);

	CC_SYNTHESIZE_READONLY(CKColorGameLayer*,m_colorGameLayer,ColorGameLayer);

	CKColorGameManager(void);

	CKColorItem* m_items[GAME_HORIZONTAL][GAME_VERTICAL];
public:

	~CKColorGameManager(void);

	CK_SINGLETON_METHOD_LAZY(CKColorGameManager,s_singleInstance,Instance);

    static void destroyInstance();

private:

	bool init();

	//************************************
	// Method:    initGameItems
	// FullName:  CKColorGameManager::initGameItems
	// Access:    private 
	// Returns:   void
	// Qualifier: 初始化元素
	//************************************
	void initGameItems();

	//************************************
	// Method:    getItemByIndex
	// FullName:  CKColorGameManager::getItemByIndex
	// Access:    private 
	// Returns:   CKColorItem*
	// Qualifier: 通过index获得元素
	// Parameter: int index
	//************************************
	CKColorItem* getItemByIndex(int index);

	//************************************
	// Method:    getItemByPosition
	// FullName:  CKColorGameManager::getItemByPosition
	// Access:    private 
	// Returns:   CKColorItem*
	// Qualifier: 通过坐标获取元素
	// Parameter: int x
	// Parameter: int y
	//************************************
	CKColorItem* getItemByPosition(int x, int y);

	//************************************
	// Method:    getIndexByPosition
	// FullName:  CKColorGameManager::getIndexByPosition
	// Access:    private 
	// Returns:   int
	// Qualifier: 通过坐标获取Index
	// Parameter: int x
	// Parameter: int y
	//************************************
	int getIndexByPosition(int x, int y);

	//************************************
	// Method:    checkBoundingItems
	// FullName:  CKColorGameManager::checkBoundingItems
	// Access:    private 
	// Returns:   void
	// Qualifier: 检查四周的元素颜色并旋转
	// Parameter: int x
	// Parameter: int y
	//************************************
	void checkBoundingItems(int x, int y);

	//************************************
	// Method:    cleanupAllItemsAction
	// FullName:  CKColorGameManager::cleanupAllItemsAction
	// Access:    private 
	// Returns:   void
	// Qualifier: 停止所有元素动画
	//************************************
	void cleanupAllItemsAction();

	//************************************
	// Method:    allSelectedItemsRotateAction
	// FullName:  CKColorGameManager::allSelectedItemsRotateAction
	// Access:    private 
	// Returns:   void
	// Qualifier: 所有周边相同颜色元素旋转
	//************************************
	void allSelectedItemsRotateAction();

	//************************************
	// Method:    allSelectedItemsMissAction
	// FullName:  CKColorGameManager::allSelectedItemsMissAction
	// Access:    private 
	// Returns:   void
	// Qualifier: 移除所有旋转动画的元素
	//************************************
	void allSelectedItemsMissAction();

	void allUnMissItemAction();

	//************************************
	// Method:    onSelectColorItem
	// FullName:  CKColorGameManager::onSelectColorItem
	// Access:    private 
	// Returns:   void
	// Qualifier: 当坐标（x,y）被选中时
	// Parameter: int x
	// Parameter: int y
	//************************************
	void onSelectColorItem(int x , int y);

	//************************************
	// Method:    changeItemPosition
	// FullName:  CKColorGameManager::changeItemPosition
	// Access:    private 
	// Returns:   void
	// Qualifier: 切换Item位置，从fromIndex到toIndex
	// Parameter: int fromIndex
	// Parameter: int toIndex
	//************************************
	void changeItemPosition(int fromIndex , int toIndex);

	//************************************
	// Method:    adjustItemsPosition
	// FullName:  CKColorGameManager::adjustItemsPosition
	// Access:    private 
	// Returns:   void
	// Qualifier: 调整所有Item位置
	//************************************
	void adjustItemsPosition();
	
	//************************************
	// Method:    getMaxHoriValue
	// FullName:  CKColorGameManager::getMaxHoriValue
	// Access:    private 
	// Returns:   int
	// Qualifier: 水平方向没有消失的最大值
	//************************************
	int getMaxHoriValue();
	//************************************
	// Method:    isNeedHoriAdjust
	// FullName:  CKColorGameManager::isNeedHoriAdjust
	// Access:    private 
	// Returns:   bool
	// Qualifier: 水平方向是否需要调整
	//************************************
	bool isNeedHoriAdjust();

	//************************************
	// Method:    isLevelEnd
	// FullName:  CKColorGameManager::isLevelEnd
	// Access:    private 
	// Returns:   bool
	// Qualifier: 当前等级是否结束
	//************************************
	bool isLevelEnd();
};

#endif // __CKCOLORGAMEMANAGER_H__