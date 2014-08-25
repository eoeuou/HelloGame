#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"

#include "CKDialog.h"
#include "VisibleRect.h"

#include "CKGameDataManager.h"
#include "FightScene.h"
#include "CKDeviceEngine.h"
#include "CKHttpUtils.h"
#include "CKGameManager.h"
#include "CKNotificationEngine.h"
#include "CKWrapper.h"
#include "CKJsonHelper.h"
#include "CKJsonModel.h"
#include "URLManager.h"
#include "CKDeviceEngine.h"
#include "CKMessageBox.h"
#include "CKRatingEngine.h"
#include "DrawScene.h"
#include "GUIScene.h"
#include "CKColorGameScene.h"

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
	Size sceneSize = Director::getInstance()->getWinSize();
	Size sizeInPixels = Director::getInstance()->getWinSizeInPixels();

	log("visibleSize.width=%f,visibleSize.height=%f",visibleSize.width,visibleSize.height);
	log("origin.x=%f,origin.y=%f",origin.x,origin.y);
	log("sceneSize.width=%f,sceneSize.height=%f",sceneSize.width,sceneSize.height);
	log("sizeInPixels.width=%f,sizeInPixels.height=%f",sizeInPixels.width,sizeInPixels.height);

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
	//this->addChild(label, 1);

	this->setColor(Color3B(0,0,0));
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	addTestLabel();

	return true;
}


typedef struct _Controller{
	const char *test_name;
	std::function<void()> callback;
} Controller;

Controller g_aTestNames[] = {
	{ "json", [=]() { m_hello->jsonTest();} },
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
	{"XiaoChu",[=](){
		Scene * newscene = CKColorGameScene::create();
		Director::getInstance()->pushScene(newscene); 
	}},
	{"CKLoadingDialog",[=](){CKDialog::show<CKLoadingDialog>(m_hello,getChildrenMaxZorder(m_hello));}},
	{"Toast",[=](){wrapper::showToast("11111111111");}},
	{"UID",[=](){wrapper::showToast(wrapper::getUID().c_str());}},
	{"IMSI",[=](){wrapper::showToast(wrapper::getIMSI().c_str());}},
	{"PhoneNum",[=](){
		std::string phone = wrapper::getPhoneNum();
		wrapper::showToast(phone.c_str());
	}},	
	{"ParseJson",[=](){		
		CKJsonHelper::getInstance()->parseJsonToJsonModel("jsondata/data2.json",nullptr,true);
		wrapper::showToast("see log");
	}},
	{"DrawTest",[=](){
		m_hello->drawTest();
	}},
	{"CKModelTest",[=](){
		m_hello->ckmodelTest();
	}},	
	{"CKJsonModel",[=](){
        m_hello->ckjsonTest();
		wrapper::showToast("xx");
	}},
	{"DeviceMemorySize",[=](){
		CKInfoDialog* dialog = CKDialog::show<CKInfoDialog>(m_hello,getChildrenMaxZorder(m_hello));
		dialog->setInfoLableString(CKDeviceEngine::sharedEngine()->getDeviceMemorySizeInfo());
	}},	
	{"CurNetworkStatus",[=](){
		NetworkStatusType status = CKDeviceEngine::sharedEngine()->getCurNetworkStatusType();
		wrapper::showToast(intToString(status));
	}},	
	{"Messagebox",[=](){
		m_hello->messageboxTest();
	}},	
	{"Rate",[=](){
		CKRatingEngine::sharedEngine()->rate("");
		wrapper::showToast("empty");
	}},
	{"cocostudioUITest",[=](){
		Scene * newscene = GUIScene::create();
		Director::getInstance()->pushScene(newscene); 
	}},
	{"empty",[=](){
		wrapper::showToast("empty");
	}},	
};

static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);
#define LINE_SPACE          40
static Point s_tCurPos = Point::ZERO;

void HelloWorld::addTestLabel()
{
	TTFConfig ttfConfig("fonts/arial.ttf", 24);
	_itemMenu = Menu::create();

	for (int i = 0; i < g_testCount; ++i)
	{		
		auto label = LabelTTF::create( g_aTestNames[i].test_name,"Arial", 24);
		auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::menuCallback, this));
		_itemMenu->addChild(menuItem, i + 10000);
		menuItem->setPosition( Point( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
	}	
	
	_itemMenu->setContentSize(Size(VisibleRect::getVisibleRect().size.width, (g_testCount + 1) * (LINE_SPACE)));
	_itemMenu->setPosition(s_tCurPos);
	_itemMenu->setColor(Color3B(255,255,0));
	addChild(_itemMenu,100);
	log("w:%f,h:%f",_itemMenu->getContentSize().width,_itemMenu->getContentSize().height);

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
	auto particle1 = ParticleSystemQuad::create("colorgame/light1.plist");
	addChild(particle1,10);
	particle1->setPosition(_beginPos);
	particle1->setAngle(90);

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
	Scene * newscene = FightScene::create();
	Director::getInstance()->pushScene(newscene); 
}

CKModel* HelloWorld::getQuestionByIndex(int index)
{
	CKModel* questionsModel = CKGameDataManager::getInstance()->getQuestionsModel();
	__Array* questions = questionsModel->getForeignArray("questions");
	int sum = questions->count();
	if (index<sum)
	{
		return dynamic_cast<CKModel*>(questions->getObjectAtIndex(index));
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

void HelloWorld::ckmodelTest()
{
	CKModel* model = CKModel::create();
	model->setValue("k1",Value("v1"));
	model->setValue("k2",Value(2014));
	int size=  model->size();
	int k2 = model->getValue("k2").asInt();

	CKModel* child = CKModel::create();
	child->setValue("name",Value("zhangsan"));

	model->setForeignProperty("child",child);
	std::string str = child->getInfo();

	child = model->getForeignProperty("child");
	str = child->getInfo();

	log("%s",str.c_str());

}

void HelloWorld::ckjsonTest()
{/*
	//key-value
	CKJsonModel* root = CKJsonModel::create();
	root->addChild("root",Value("rootValue"));
	root->addChild("rootInt",Value(20));
	root->logJsonString();

	//key-object
	CKJsonModel* object = CKJsonModel::create();
	object->addChild("string",Value("string"));
	object->addChild("int1",Value(150));
	object->addChild("int2",Value(1510));
	object->addChild("bool",Value(false));
	object->addChild("float",Value(12.01));
	object->logJsonString();

	root->addObjectChild("object",object);
	root->logJsonString();

	//key-array
	CKJsonModelVector vector;

	for (int i = 0; i<10;i++)
	{
		CKJsonModel* child = CKJsonModel::create();
		child->addChild("i=",Value(i));
		vector.pushBack(child);
	}
	root->addArrayChild("array",vector);
	root->logJsonString();
	object->logJsonString();
	root->logJsonString();

	log("");

	//get key--value
	std::string rootValue = root->getChildByKey("root").asString();
	int rootInt = root->getChildByKey("rootInt").asInt();

	//get object
	CKJsonModel* object1 = root->getObjectChildByKey("object");
	object1->logJsonString();
	int i1 = object1->getChildByKey("int1").asInt();
	int i2 = object1->getChildByKey("int2").asInt();
	int test = object1->getChildByKey("test").asInt();
	string s = object1->getChildByKey("string").asString();
	bool b = object1->getChildByKey("bool").asBool();
	float f = object1->getChildByKey("float").asFloat();
	//get array

	CKJsonModelVector vector1 = root->getArrayChildByKey("array");
	int size = vector1.size();
	for (auto& child : vector1)
	{
		child->logJsonString();
	}
	
	log("end");*/
}

void HelloWorld::httpTest()
{
	/*std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName = writablePath+"external.txt";
	CKHttpUtils::getInstance()->getFile("http://httpbin.org/ip",fileName.c_str(),[](CKHttpModel* model){
		log("getFile_end:result=%s,path=%s",model->getValue("result").asString(),model->getValue("path").asString());
	});*/
		
// 	CKHttpUtils::getInstance()->getText("http://tarenaapptest.herokuapp.com/?echostr=1",[](CKHttpModel* model){
// 		bool isSucceed = model->getIsSucceed();
// 		int code = model->getStatusCode();
// 		log("getText_end:result=%s,path=%s",model->getValue("result").asString().c_str(),model->getValue("path").asString().c_str());
// 	});

	CKJsonModel* model = CKJsonModel::create();
	URLManager::getInstance()->requestData(k_BATTLE_WORLD_RANK_LIST,model,this);
		
	/*CKHttpUtils::getInstance()->getText("http://127.0.0.1:8000",[](CKHttpModel* model){
	});*/
	//CKHttpUtils::getInstance()->post("http://tarenaapptest.herokuapp.com/login");
	//CKHttpUtils::getInstance()->post("http://httpbin.org/post","username=112",STD_FUN_CKHTTPMODEL_NULL);
}

void HelloWorld::urlRequestCallback(CKHttpModel* model)
{
	static int i = 1;
	log("i=%d,isSucceed=%s",i++,model->getIsSucceed()?"true":"false");
	wrapper::showToast(model->getContent().c_str());

	std::string abc = "xxxxxxxxxxxx";
	model->setContent(abc);
	std::string a = model->getContent();
	log("%s",a.c_str());
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

void HelloWorld::messageboxTest()
{
	const char* title = "title";
	const char* message = "message";
	CKMessageBox* msg = CKMessageBox::create(title,message);
	msg->setButtonText(CKMessageBox::BUTTON_POSITIVE,"Ok");
	msg->setButtonText(CKMessageBox::BUTTON_NEGATIVE,"Cancel");

	msg->setMsgBoxCallback([](CKMessageBox* box,int which){
		char buf[256] = {0};
		sprintf(buf, "msgBoxCallBack:which = %d", which);
		wrapper::showToast(buf);
	});
	msg->show();

	//msg->dispatchButtonClick(-1);
}

void HelloWorld::drawTest()
{
	Scene * newscene = DrawScene::create();
	Director::getInstance()->pushScene(newscene);
}

void HelloWorld::jsonTest()
{
	auto path =FileUtils::getInstance()->getWritablePath();
	log("%s", path.c_str());
	path.append("myhero.json");

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("id", 1, allocator);
	object.AddMember("name", "豹儿", allocator);
	object.AddMember("name", "豹儿1", allocator);
	object.AddMember("age", "3年", allocator);
	object.AddMember("low", true, allocator);
	array.PushBack(object, allocator);

	document.AddMember("propety", "PLAYER-TO", allocator);
	document.AddMember("player", array, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	FILE* file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}

	//{"key":1,"child":{"id":12},"stu":[{"name":12,"age":240},{"name":2,"age":40}]}
	//{"propety":"PLAYER-TO","player":[{"id":1,"name":"豹儿","age":"3年","low":true}]} 
}