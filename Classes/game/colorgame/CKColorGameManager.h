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
	// Qualifier: ��ʼ��Ԫ��
	//************************************
	void initGameItems();

	//************************************
	// Method:    getItemByIndex
	// FullName:  CKColorGameManager::getItemByIndex
	// Access:    private 
	// Returns:   CKColorItem*
	// Qualifier: ͨ��index���Ԫ��
	// Parameter: int index
	//************************************
	CKColorItem* getItemByIndex(int index);

	//************************************
	// Method:    getItemByPosition
	// FullName:  CKColorGameManager::getItemByPosition
	// Access:    private 
	// Returns:   CKColorItem*
	// Qualifier: ͨ�������ȡԪ��
	// Parameter: int x
	// Parameter: int y
	//************************************
	CKColorItem* getItemByPosition(int x, int y);

	//************************************
	// Method:    getIndexByPosition
	// FullName:  CKColorGameManager::getIndexByPosition
	// Access:    private 
	// Returns:   int
	// Qualifier: ͨ�������ȡIndex
	// Parameter: int x
	// Parameter: int y
	//************************************
	int getIndexByPosition(int x, int y);

	//************************************
	// Method:    checkBoundingItems
	// FullName:  CKColorGameManager::checkBoundingItems
	// Access:    private 
	// Returns:   void
	// Qualifier: ������ܵ�Ԫ����ɫ����ת
	// Parameter: int x
	// Parameter: int y
	//************************************
	void checkBoundingItems(int x, int y);

	//************************************
	// Method:    cleanupAllItemsAction
	// FullName:  CKColorGameManager::cleanupAllItemsAction
	// Access:    private 
	// Returns:   void
	// Qualifier: ֹͣ����Ԫ�ض���
	//************************************
	void cleanupAllItemsAction();

	//************************************
	// Method:    allSelectedItemsRotateAction
	// FullName:  CKColorGameManager::allSelectedItemsRotateAction
	// Access:    private 
	// Returns:   void
	// Qualifier: �����ܱ���ͬ��ɫԪ����ת
	//************************************
	void allSelectedItemsRotateAction();

	//************************************
	// Method:    allSelectedItemsMissAction
	// FullName:  CKColorGameManager::allSelectedItemsMissAction
	// Access:    private 
	// Returns:   void
	// Qualifier: �Ƴ�������ת������Ԫ��
	//************************************
	void allSelectedItemsMissAction();

	void allUnMissItemAction();

	//************************************
	// Method:    onSelectColorItem
	// FullName:  CKColorGameManager::onSelectColorItem
	// Access:    private 
	// Returns:   void
	// Qualifier: �����꣨x,y����ѡ��ʱ
	// Parameter: int x
	// Parameter: int y
	//************************************
	void onSelectColorItem(int x , int y);

	//************************************
	// Method:    changeItemPosition
	// FullName:  CKColorGameManager::changeItemPosition
	// Access:    private 
	// Returns:   void
	// Qualifier: �л�Itemλ�ã���fromIndex��toIndex
	// Parameter: int fromIndex
	// Parameter: int toIndex
	//************************************
	void changeItemPosition(int fromIndex , int toIndex);

	//************************************
	// Method:    adjustItemsPosition
	// FullName:  CKColorGameManager::adjustItemsPosition
	// Access:    private 
	// Returns:   void
	// Qualifier: ��������Itemλ��
	//************************************
	void adjustItemsPosition();
	
	//************************************
	// Method:    getMaxHoriValue
	// FullName:  CKColorGameManager::getMaxHoriValue
	// Access:    private 
	// Returns:   int
	// Qualifier: ˮƽ����û����ʧ�����ֵ
	//************************************
	int getMaxHoriValue();
	//************************************
	// Method:    isNeedHoriAdjust
	// FullName:  CKColorGameManager::isNeedHoriAdjust
	// Access:    private 
	// Returns:   bool
	// Qualifier: ˮƽ�����Ƿ���Ҫ����
	//************************************
	bool isNeedHoriAdjust();

	//************************************
	// Method:    isLevelEnd
	// FullName:  CKColorGameManager::isLevelEnd
	// Access:    private 
	// Returns:   bool
	// Qualifier: ��ǰ�ȼ��Ƿ����
	//************************************
	bool isLevelEnd();
};

#endif // __CKCOLORGAMEMANAGER_H__