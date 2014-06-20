#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"

#include "ckbase/CKModel.h"
#include "CKDialog.h"

#include "CKGameDataManager.h"
#include "FightScene.h"
#include "device/CKDeviceEngine.h"
#include "network/CKHttpUtils.h"
#include "CKGameManager.h"
#include "CKNotificationEngine.h"
#include "wrapper/CKWrapper.h"

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

static HelloWorld* m_hello = NULL;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	m_hello = this;
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

	this->setColor(ccc3(0,0,0));
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	
	CKModel* child = CKModel::create();
	child->setValue("name",Value("childName"));

	CKModel* model = CKModel::create();
	model->setValue("child",Value(child->getValue("name")));
	int key = model->getValue("key").asInt();
	CCLog("%s",model->getInfo().c_str());

	addTestLabel();
	return true;
}


typedef struct _Controller{
	const char *test_name;
	std::function<void()> callback;
} Controller;

Controller g_aTestNames[] = {
	{"loadGameData",[=](){CKGameDataManager::getInstance()->loadGameData();}},
	{ "FightScene", [=]() { m_hello->showFightScene();} },
	{ "questionTest", [=]() { m_hello->questionTest();} },
	{ "httpTest", [=]() { m_hello->httpTest();} },
	{ "NotificationTest", [=]() { m_hello->NotificationTest();} },
	{
		"Dialog",[=](){
			CKDialog::show<CKDialog>(m_hello,getChildrenMaxZorder(m_hello));
			//this->addChild(CKDialog::create(),100);
		}
	},
	{"CKLoadingDialog",[=](){CKDialog::show<CKLoadingDialog>(m_hello,getChildrenMaxZorder(m_hello));}},
	{"Toast",[=](){wrapper::showToast("11111111111");}},
	{"UID",[=](){wrapper::showToast(wrapper::getUID().c_str());}},
	{"IMSI",[=](){wrapper::showToast(wrapper::getIMSI().c_str());}},
	{"PhoneNum",[=](){
		const char * p = wrapper::getPhoneNum().c_str();
		wrapper::showToast(p);
	}},
};

static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);
#define LINE_SPACE          40
static Point s_tCurPos = Point::ZERO;

void HelloWorld::addTestLabel()
{	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	TTFConfig ttfConfig("fonts/arial.ttf", 24);
	_itemMenu = Menu::create();

	for (int i = 0; i < g_testCount; ++i)
	{		
		auto label = LabelTTF::create( g_aTestNames[i].test_name,"Arial", 24);
		auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::menuCallback, this));
		_itemMenu->addChild(menuItem, i + 10000);		
		menuItem->setPosition( Point( visibleSize.width/2, (visibleSize.height - (i + 1) * LINE_SPACE) ));				
	}	
	
	_itemMenu->setContentSize(Size(visibleSize.width, (g_testCount + 1) * (LINE_SPACE)));
	_itemMenu->setPosition(Point::ZERO);
	_itemMenu->setColor(ccc3(255,255,0));
	addChild(_itemMenu,100);

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event  *event)
{
	_beginPos = touch->getLocation();
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event  *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto touchLocation = touch->getLocation();    
	float nMoveY = touchLocation.y - _beginPos.y;

	auto curPos  = _itemMenu->getPosition();
	auto nextPos = Point(curPos.x, curPos.y + nMoveY);

	if (nextPos.y < 0.0f)
	{
		_itemMenu->setPosition(Point::ZERO);
		return;
	}

	if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - visibleSize.height))
	{
		_itemMenu->setPosition(Point(0, ((g_testCount + 1)* LINE_SPACE - visibleSize.height)));
		return;
	}

	_itemMenu->setPosition(nextPos);
	_beginPos = touchLocation;
	s_tCurPos   = nextPos;
}

void HelloWorld::onMouseScroll(Event *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto mouseEvent = static_cast<EventMouse*>(event);
	float nMoveY = mouseEvent->getScrollY() * 6;

	auto curPos  = _itemMenu->getPosition();
	auto nextPos = Point(curPos.x, curPos.y + nMoveY);

	if (nextPos.y < 0.0f)
	{
		_itemMenu->setPosition(Point::ZERO);
		return;
	}

	if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - visibleSize.height))
	{
		_itemMenu->setPosition(Point(0, ((g_testCount + 1)* LINE_SPACE - visibleSize.height)));
		return;
	}

	_itemMenu->setPosition(nextPos);
	s_tCurPos   = nextPos;
}

void HelloWorld::menuCallback(cocos2d::Ref* pSender)
{
	auto menuItem = static_cast<MenuItem *>(pSender);
	int idx = menuItem->getLocalZOrder() - 10000;
	g_aTestNames[idx].callback();
}

void HelloWorld::onExit()
{
	CCLayer::onExit();
	CKGameManager::destroyInstance();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//CKHttpUtils::getInstance()->destroyInstance();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void HelloWorld::showFightScene()
{
	CCScene * newscene = FightScene::create();
	CCDirector::sharedDirector()->replaceScene(newscene); 
}

CKModel* HelloWorld::getQuestionByIndex(int index)
{
	CKModel* questionsModel = CKGameDataManager::getInstance()->getQuestionsModel();
	__Array* questions = questionsModel->getForeignArray("questions");
	int sum = questions->count();
	if (index<sum)
	{
		return dynamic_cast<CKModel*>(questions->objectAtIndex(index));
	}	
	return NULL;
}

void HelloWorld::questionTest()
{
	CKGameDataManager::getInstance()->loadQuestionsData();
	CKModel* question = getQuestionByIndex(0);
	std::string id = question->getValue("id").asString();
	std::string right = question->getValue("right").asString();

	const CKModel* answers = question->getForeignProperty("answers");
	std::string a = answers->getValue("a").asString();
	std::string b = answers->getValue("b").asString();
	std::string c = answers->getValue("c").asString();
	std::string d = answers->getValue("d").asString();
}
void HelloWorld::httpTest()
{
	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName = writablePath+"external.txt";
	/*CKHttpUtils::getInstance()->getFile("http://httpbin.org/ip",fileName.c_str(),[](CKModel* model){
		CCLog("getFile_end:result=%s,path=%s",model->getValue("result").asString(),model->getValue("path").asString());
	});*/
	/*
	CKHttpUtils::getInstance()->getText("http://tarenaapptest.herokuapp.com/?echostr=1",[](CKModel* model){
		CCLog("getText_end:result=%s,path=%s",model->getValue("result").asString(),model->getValue("path").asString());
	});
	*/
	/*CKHttpUtils::getInstance()->getText("http://127.0.0.1:8000",[](CKModel* model){
	});*/
	//CKHttpUtils::getInstance()->post("http://tarenaapptest.herokuapp.com/login");
	//CKHttpUtils::getInstance()->post("http://httpbin.org/post","username=112",STD_FUN_MODEL_NULL);
}

void HelloWorld::NotificationTest()
{
	CKNotificationEngine* engine = CKNotificationEngine::sharedEngine();
	CKNotification notification;
	notification.id = 1;
	notification.title = "title";
	notification.message = "message";
	notification.url = "http://www.baidu.com/";
	engine->show(notification);
}