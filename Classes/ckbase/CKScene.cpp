#include "CKScene.h"
#include "CKGameDataManager.h"
#include "CKPayEngine.h"
#include "CKDialog.h"

CKScene::CKScene(void)
{
}


CKScene::~CKScene(void)
{
	
}

bool CKScene::init()
{
	bool ret = Scene::init();	
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height-200));

    // add the label as a child to this layer
    this->addChild(label, 1);
		
	CKGameDataManager::getInstance()->loadGameData();

	CKPayEngine::sharedEngine()->pay("1",100);

	this->addChild(CKDialog::create());
	return ret;
}
