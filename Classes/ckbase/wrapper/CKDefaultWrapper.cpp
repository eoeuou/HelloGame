#include "CKWrapper.h"

NS_WP_BGN

void showToast(const char* msg)
{
	if (strcmp(msg,"")==0)
	{
		msg = "empty";
	}
	
	auto label = LabelTTF::create(msg,"Arial", 24);

	auto scene = Director::getInstance()->getRunningScene();

	auto size = scene->getContentSize();

	int zOrder = getChildrenMaxZorder(scene);

	scene->addChild(label,zOrder);

	label->setPosition(ccp(size.width/2,label->getContentSize().height*2));

	label->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1.0f),CCRemoveSelf::create(true)));
}

std::string getUID(){ return CKDeviceEngine::sharedEngine()->getDeviceId();}
std::string getIMSI(){ return CKDeviceEngine::sharedEngine()->getIMSI();}
std::string getPhoneNum(){ return CKDeviceEngine::sharedEngine()->getPhoneNum();}
NS_WP_END