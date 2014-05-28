#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"

#include "ckbase/CKModel.h"
#include "CKDialog.h"

#include "CKGameDataManager.h"
#include "FightScene.h"
#include "device/CKDeviceEngine.h"
#include "network/CKHttpUtils.h"

USING_NS_CC;
using namespace cocostudio;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	std::string id = CKDeviceEngine::sharedEngine()->getDeviceId();
		
	label->setString(id);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);



	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
		
	//CKDialog::show<CKDialog>(this,100);

	CKDialog::show<CKLoadingDialog>(this,200);

	//this->addChild(CKDialog::create(),100);
	
	questionTest();

	httpTest();

	return true;
}

void HelloWorld::onExit()
{
	CCLayer::onExit();
	CKHttpUtils::destroyInstance();
	CKGameDataManager::destroyInstance();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	//showFightScene();

	CKHttpUtils::getInstance()->destroyInstance();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void HelloWorld::showFightScene()
{
	CCScene * newscene  = FightScene::create();
	CCDirector::sharedDirector()->replaceScene(newscene); 
}

CKModel* HelloWorld::getQuestionByIndex(int index)
{
	CKModel* questionsModel = CKGameDataManager::getInstance()->getQuestionsModel();
	__Array* questions = questionsModel->getForeignArray("questions");
	int sum = questions->count();
	if (index<sum)
	{
		return (CKModel*)questions->getObjectAtIndex(index);
	}	
	return NULL;
}

void HelloWorld::questionTest()
{
	CKGameDataManager::getInstance()->loadQuestionsData();
	CKModel* question = getQuestionByIndex(0);
	std::string id = question->getStringProperty("id");
	std::string right = question->getStringProperty("right");

	CKModel* answers = question->getForeignProperty("answers");
	std::string a = answers->getStringProperty("a");
	std::string b = answers->getStringProperty("b");
	std::string c = answers->getStringProperty("c");
	std::string d = answers->getStringProperty("d");
}

void HelloWorld::httpTest()
{
	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName = writablePath+"external.txt";
	CKHttpUtils::getInstance()->getFile("http://httpbin.org/ip",fileName.c_str());
}
