#include "CKDialog.h"

CKDialog::CKDialog(void)
	:m_closeItem(nullptr)
{
}


CKDialog::~CKDialog(void)
{
	
}

bool CKDialog::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!LayerColor::initWithColor(Color4B(0,0,0,200)));

		addCloseItem();

		setTouchMode(cocos2d::CCTouch::DispatchMode::ONE_BY_ONE);
		setTouchEnabled(true);

		bRet = true;
	} while (0);	

	return bRet;
}

void CKDialog::addCloseItem()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//addCloseItem
	m_closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CKDialog::onCloseCallback, this));

	m_closeItem->setPosition(Point(origin.x + visibleSize.width - m_closeItem->getContentSize().width/2,
		origin.y + visibleSize.height - m_closeItem->getContentSize().height/2));

	auto menu = Menu::create(m_closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void CKDialog::removeCloseItem()
{
	if (m_closeItem)
	{
		m_closeItem->removeFromParent();
	}	
}

bool CKDialog::onTouchBegan(Touch *touch, Event *unused_event)
{
	unused_event->stopPropagation();
    return false;
}

void CKDialog::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{	
	unused_event->stopPropagation();
}

void CKDialog::onCloseCallback(cocos2d::Ref* pSender)
{
	close();
}

void CKDialog::close()
{
	this->removeFromParent();
}

bool CKLoadingDialog::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CKDialog::init());

		m_loadingSprite = Sprite::create("loading.png");

		Scene* scene = Director::getInstance()->getRunningScene();

		m_loadingSprite->setPosition(Point(scene->getContentSize()/2));

		m_loadingSprite->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));

		this->addChild(m_loadingSprite);

		//removeCloseItem();

		bRet = true;
	} while (0);	

	return bRet;
}

void CKLoadingDialog::close()
{
	if (m_loadingSprite)
	{
		m_loadingSprite->cleanup();
	}
	
	CKDialog::close();
}

bool CKInfoDialog::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CKDialog::init());

		m_infoLabel = LabelTTF::create("Hello World", "Arial", 24);

		Scene* scene = Director::getInstance()->getRunningScene();

		m_infoLabel->setPosition(Point(scene->getContentSize()/2));

		this->addChild(m_infoLabel);

		bRet = true;
	} while (0);	

	return bRet;
}

void CKInfoDialog::setInfoLableString(std::string info)
{
	if (m_infoLabel)
	{
		m_infoLabel->setString(info);
	}
}