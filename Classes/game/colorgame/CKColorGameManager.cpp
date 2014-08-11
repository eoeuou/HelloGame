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
	m_colorItemSize = CKColorItem::create()->getContentSize();

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
	for (int i = 0; i < GAME_VERTICAL; i++)
	{
		for (int j = 0;j < GAME_HORIZONTAL; j++)
		{
			CKColorItem* item = CKColorItem::create();
			m_colorGameLayer->addChild(item);
			item->setPosition(ccp(j*m_colorItemSize.width + m_colorItemSize.width/2.0f,
				i*m_colorItemSize.height + m_colorItemSize.height/2.0f));

			int index = j+i*GAME_HORIZONTAL;
			log("index=%d",index);
			m_colorItems.insert(index,item);
			item->changeItemIndex(index);
		}
	}

	for (const auto& child : m_colorItems)
	{
		log("index=%d",child.second->getItemIndex());
	}
}

CKColorItem* CKColorGameManager::getItemByIndex(int index)
{
	int size = m_colorItems.size();
	bool result = index>=0&&index<size;
	assert(result,"wrong index");
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
		if (!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(right,y);
		}
	}

	//check to left
	int left = x - 1;
	if (left >= 0)
	{
		CKColorItem* item = getItemByPosition(left,y);
		if (!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(left,y);
		}
	}

	//check to top
	int top = y + 1;
	if (top < GAME_VERTICAL)
	{
		CKColorItem* item = getItemByPosition(x,top);
		if (!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
		{
			checkBoundingItems(x,top);
		}
	}

	//check to bottom
	int bottom = y - 1;
	if (bottom >= 0)
	{
		CKColorItem* item = getItemByPosition(x,bottom);
		if (!item->getBIsSelected()&&item->isItemTypeEqual(curItem))
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
		[&](){
			log("xxxxxxxxxx");
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

void CKColorGameManager::onSelectColorItem(int x , int y)
{
	CKColorItem* curItem = getItemByPosition(x,y);
	if (curItem->getBIsSelected())
	{
		allSelectedItemsMissAction();
	}
	else
	{
		cleanupAllItemsAction();
		checkBoundingItems(x,y);
		allSelectedItemsRotateAction();
	}
}