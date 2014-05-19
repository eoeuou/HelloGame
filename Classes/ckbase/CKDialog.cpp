#include "CKDialog.h"

CKDialog::CKDialog(void)
{
}


CKDialog::~CKDialog(void)
{
	
}

bool CKDialog::init()
{	  
    Size s = Director::getInstance()->getWinSize();
	initWithColor(Color4B(0,0,0,200), s.width, s.height);

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
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2-200 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	
	setTouchEnabled(true);
	setTouchMode(cocos2d::CCTouch::DispatchMode::ONE_BY_ONE);
	return true;
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
	this->removeFromParent();
}