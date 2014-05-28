#include "CKDialog.h"

CKDialog::CKDialog(void)
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

		//test closebtn
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		auto label = LabelTTF::create("Dialog", "Arial", 24);

		// position the label on the center of the screen
		label->setPosition(Point(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - label->getContentSize().height-220));

		// add the label as a child to this layer
		this->addChild(label, 1);

		auto closeItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(CKDialog::onCloseCallback, this));

		closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2,
			origin.y + visibleSize.height - closeItem->getContentSize().height/2));

		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu, 1);
		//test closebtn

		setTouchMode(cocos2d::CCTouch::DispatchMode::ONE_BY_ONE);
		setTouchEnabled(true);

		bRet = true;
	} while (0);	

	return bRet;
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

		Size visibleSize = Director::getInstance()->getVisibleSize();

		m_loadingSprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));

		m_loadingSprite->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));

		this->addChild(m_loadingSprite);

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
