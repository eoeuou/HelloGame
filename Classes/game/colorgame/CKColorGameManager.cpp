#include "CKColorGameManager.h"

CK_SINGLETON_METHOD_INIT(CKColorGameManager,s_singleInstance);

CKColorGameManager::CKColorGameManager(void):
	m_colorGameLayer(nullptr)
{
	m_colorItems.clear();
	m_colorItemSize = Size(0,0);
	m_selectedItems.clear();
}

CKColorGameManager::~CKColorGameManager(void)
{
	m_colorItems.clear();
	m_colorItemSize = Size(0,0);
	m_selectedItems.clear();
}

void CKColorGameManager::destroyInstance()
{
    CC_SAFE_DELETE(s_singleInstance);
}

bool CKColorGameManager::init()
{
	m_colorItemSize = CKColorItem::create(-1)->getContentSize();

	std::function<void(int,int)> func = [&](int x, int y){
		this->onSelectColorItem(x,y);
	};

	Color4B colorA = Color4B(CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, CCRANDOM_0_1()*255, 255);
	m_colorGameLayer = CKColorGameLayer::create(colorA,func,m_colorItemSize);

	CCScene* scene = Director::getInstance()->getRunningScene();
	scene->addChild(m_colorGameLayer,-1);

	Size winSize = Director::getInstance()->getWinSize();
	m_colorGameLayer->setPosition(ccp(winSize.width/2.0f,m_colorGameLayer->getContentSize().height/2));

	initGameItems();

	return true;
}

void CKColorGameManager::initGameItems()
{
	m_colorItems.clear();
	m_selectedItems.clear();

	int sum = GAME_HORIZONTAL*GAME_VERTICAL;
	for (int y = 0; y < GAME_VERTICAL; y++)
	{
		for (int x = 0; x < GAME_HORIZONTAL; x++)
		{
			int index = x+y*GAME_HORIZONTAL;

			CKColorItem* item = CKColorItem::create(index);
			m_colorGameLayer->addChild(item);
			item->setPosition(ccp(x*m_colorItemSize.width + m_colorItemSize.width/2.0f,
				y*m_colorItemSize.height + m_colorItemSize.height/2.0f));

			m_colorItems.insert(index,item);
		}
	}

	for (const auto& child : m_colorItems)
	{
		log("index=%d",child.second->getItemIndex());
	}
}

CKColorItem* CKColorGameManager::getItemByIndex(int index)
{
	CCAssert(index>=0,"wrong index");
	return m_colorItems.at(index);
}

CKColorItem* CKColorGameManager::getItemByPosition(int x, int y)
{
	return getItemByIndex(getIndexByPosition(x,y));
}

int CKColorGameManager::getIndexByPosition(int x, int y)
{
	return (x + y * GAME_HORIZONTAL);
}

void CKColorGameManager::checkBoundingItems(int x, int y)
{
	log("checkBoundingItems... x = %d, y = %d", x, y);
	int cur = x + y * GAME_HORIZONTAL;

	CKColorItem* curItem = getItemByPosition(x,y);
	if (curItem->getBIsSelected())
	{
		return;
	}
	curItem->onItemSelected();

	if (m_selectedItems.contains(curItem))
	{
		CCAssert(false,"add wrong!");
	}	
	m_selectedItems.pushBack(curItem);

	//check to right
	int right = x + 1;
	if (right < GAME_HORIZONTAL)
	{
		CKColorItem* item = getItemByPosition(right,y);
		if (!item->isItemMiss()&&!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(right,y);
		}
	}

	//check to left
	int left = x - 1;
	if (left >= 0)
	{
		CKColorItem* item = getItemByPosition(left,y);
		if (!item->isItemMiss()&&!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(left,y);
		}
	}

	//check to top
	int top = y + 1;
	if (top < GAME_VERTICAL)
	{
		CKColorItem* item = getItemByPosition(x,top);
		if (!item->isItemMiss()&&!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(x,top);
		}
	}

	//check to bottom
	int bottom = y - 1;
	if (bottom >= 0)
	{
		CKColorItem* item = getItemByPosition(x,bottom);
		if (!item->isItemMiss()&&!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(x,bottom);
		}
	}
}

void CKColorGameManager::cleanupAllItemsAction()
{
	m_selectedItems.clear();
	for (const auto& child : m_colorItems)
	{
		child.second->stopRotateAction();
	}
}

void CKColorGameManager::allSelectedItemsRotateAction()
{
	if (m_selectedItems.size() <= 1)
	{
		for (const auto& child : m_selectedItems)
		{
			child->onItemuUnSelected();
		}
		m_selectedItems.clear();
	}
	
	for (const auto& child : m_selectedItems)
	{
		child->runRotateAction();
	}
}

void CKColorGameManager::allSelectedItemsMissAction()
{
	CallFunc* func = CallFunc::create(
		// lambda
		[this](){
			adjustItemsPosition();
	}  );

	int size = m_selectedItems.size();
	int i = 0;
	for (const auto& child : m_selectedItems)
	{
		if (i++ == size-1)
		{
			child->runMissAction(func);
		}
		else
		{
			child->runMissAction();
		}
	}
	m_selectedItems.clear();
}

void CKColorGameManager::allUnMissItemAction()
{
	float delay = 0.1f;
	for (const auto& child : m_colorItems)
	{
		if (!child.second->isItemMiss())
		{
			delay += 0.3f;
			child.second->runMissAction(nullptr,delay);
		}
	}
}

void CKColorGameManager::onSelectColorItem(int x , int y)
{
	CKColorItem* curItem = getItemByPosition(x,y);
	if (curItem->getBIsSelected())
	{
		log("===================================================");
		allSelectedItemsMissAction();
	}
	else
	{
		cleanupAllItemsAction();
		checkBoundingItems(x,y);
		allSelectedItemsRotateAction();
	}
}

void CKColorGameManager::changeItemPosition(int fromIndex , int toIndex)
{
	CKColorItem* fromItem = getItemByIndex(fromIndex);
	CKColorItem* toItem = getItemByIndex(toIndex);
	fromItem->setToItemIndex(toIndex);

	m_colorItems.insert(fromIndex,toItem);
	m_colorItems.insert(toIndex,fromItem);
}

void CKColorGameManager::adjustItemsPosition()
{
	//竖直方向调整
	for (int y = 0; y < GAME_VERTICAL; y++)
	{
		for (int x = 0; x < GAME_HORIZONTAL; x++)
		{
			int tempVer = y;
			int index = getIndexByPosition(x,y);
			CKColorItem* item = getItemByIndex(index);
			CKColorItem* tempItem = item;
			if (!tempItem->isItemMiss())
			{
				continue;
			}
			else
			{
				while (tempItem->isItemMiss() && (tempVer < GAME_VERTICAL))
				{
					tempItem = getItemByPosition(x,tempVer);
					if (!tempItem->isItemMiss())
					{
						break;
					}
					++tempVer;
				}

				if (!tempItem->isItemMiss())
				{
					int tempIndex = getIndexByPosition(x,tempVer);
					changeItemPosition(tempIndex,index);
				}
			}
		}
	}
	//横向调整
	while (isNeedHoriAdjust())
	{
		int maxX = getMaxHoriValue();
		for (int x = 0; x <= maxX; ++x)
		{
			CKColorItem* item = getItemByPosition(x,0);
			if (item->isItemMiss())
			{
				for (int i = x; i < maxX; ++i)
				{
					for (int j = 0; j < GAME_VERTICAL; ++j)
					{
						int fromIndex = getIndexByPosition(i+1,j);
						CKColorItem* fromItem = getItemByIndex(fromIndex);
						if (fromItem->isItemMiss())
						{
							break;
						}
						int toIndex = getIndexByPosition(i,j);
						changeItemPosition(fromIndex,toIndex);
					}
				}
				break;
			}
		}
	}

	adjustItemsAction();

	if (isLevelEnd())
	{
		allUnMissItemAction();
	}

}

void CKColorGameManager::adjustItemsAction()
{
	CKColorItemVector items;
	for (const auto& child : m_colorItems)
	{
		if (!child.second->isItemMiss()&&child.second->isItemNeedMove())
		{
			items.pushBack(child.second);
		}
	}

	int size = items.size();
	if (size==0)
	{
		return;
	}

	changeGameLayerTouchStatus(false);

	CallFunc* func = CallFunc::create(
		// lambda
		[this](){
			changeGameLayerTouchStatus(true);
	}  );

	int i = 0;
	for (const auto& child : items)
	{
		if (i++ == size-1)
		{
			child->runMoveAction(func);
		}
		else
		{
			child->runMoveAction();
		}
	}
	items.clear();
}

int CKColorGameManager::getMaxHoriValue()
{
	int max = GAME_HORIZONTAL-1;
	while (max >= 0)
	{
		CKColorItem* item = getItemByPosition(max,0);
		if (!item->isItemMiss())
		{
			break;
		}
		--max;
	}

	return max;
}

bool CKColorGameManager::isNeedHoriAdjust()
{
	bool needHoriAdjust = false;
	bool haveHole = false;
	for (int x = 0; x < GAME_HORIZONTAL; ++x)
	{
		CKColorItem* item = getItemByPosition(x,0);
		if (item->isItemMiss())
		{
			haveHole = true;
		}
		else if (haveHole)
		{
			needHoriAdjust = true;
		}
	}
	return needHoriAdjust;
}


bool CKColorGameManager::isLevelEnd()
{
	for (int x = 0; x < GAME_HORIZONTAL; x++)
	{
		for (int y = 0; y < GAME_VERTICAL; y++)
		{
			CKColorItem* item = getItemByPosition(x,y);
			if (item->isItemMiss())
			{
				continue;
			}

			int right = x + 1;
			if (right < GAME_HORIZONTAL)
			{
				CKColorItem* tempItem = getItemByPosition(right,y);
				if (!tempItem->isItemMiss() && tempItem->isItemTypeEqual(item))
				{
					return false;
				}
			}

			int top = y + 1;
			if (top < GAME_VERTICAL)
			{
				CKColorItem* tempItem = getItemByPosition(x,top);
				if (!tempItem->isItemMiss() && tempItem->isItemTypeEqual(item))
				{
					return false;
				}
			}
		}
	}
	return true;
}


void CKColorGameManager::changeGameLayerTouchStatus(bool touchable)
{
	if (m_colorGameLayer)
	{
		m_colorGameLayer->changeTouchStatus(touchable);
	}
}