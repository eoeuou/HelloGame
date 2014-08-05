#include "GUIScene.h"

GUIScene::GUIScene(void)
{
}

GUIScene::~GUIScene(void)
{
	
}

bool GUIScene::init()
{	
	CKScene::init();

	addKeyBackEvent(this);
	
	Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("SampleChangeEquip/SampleChangeEquip_1.ExportJson"));
	layout->setScale(2);
	this->addChild(layout);
	
	Layout* root = static_cast<Layout*>(layout->getChildByName("ImageView"));
	Button* button = static_cast<Button*>(Helper::seekWidgetByName(root, "closebutton"));
	button->addTouchEventListener(this, toucheventselector(GUIScene::touchEvent));
	
	return true;
}

void GUIScene::touchEvent(Ref* pSender, TouchEventType type)
{
	Button* button = static_cast<Button*>(pSender);
	if (button)
	{
		bool visible = button->isVisible();
		button->setVisible(false);
	}
}

void GUIScene::onEnter()
{
	CKScene::onEnter();
}

void GUIScene::onExit()
{
	removeKeyBackEvent(this);
	CKScene::onExit();
}
