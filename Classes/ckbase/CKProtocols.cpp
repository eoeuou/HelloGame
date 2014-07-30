#include "CKProtocols.h"
//
// generic getters for properties
//
const Value& PropertyProtocol::getValue(const std::string& key, const Value& defaultValue) const
{
	auto iter = _valueDict.find(key);
	if (iter != _valueDict.cend())
		return _valueDict.at(key);
	return defaultValue;
}

void PropertyProtocol::setValue(const std::string& key, const Value& value)
{
	_valueDict[key] = value;
}

std::string PropertyProtocol::getInfo() const
{
	// Dump
	Value forDump = Value(_valueDict);
	return forDump.getDescription();
}

CKTouchProtocol::CKTouchProtocol():
	m_eventListenerKeyboard(nullptr),
	m_touchListener(nullptr)
{

}

CKTouchProtocol::~CKTouchProtocol()
{

}

void CKTouchProtocol::addKeyBackEvent(Node* node, std::function<void(EventKeyboard::KeyCode, Event*)> onKeyReleased)
{
	m_eventListenerKeyboard = EventListenerKeyboard::create();
	if (onKeyReleased == nullptr)
	{
		onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
		{
			if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
			{
				CCDirector::sharedDirector()->popScene();
			}
		};
	}
	m_eventListenerKeyboard->onKeyReleased = onKeyReleased;

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_eventListenerKeyboard,node);
}

void CKTouchProtocol::removeKeyBackEvent(Node* node)
{
	node->getEventDispatcher()->removeEventListener(m_eventListenerKeyboard);
}

void CKTouchProtocol::addTouchEvent()
{
	auto dispatch = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CKTouchProtocol::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(CKTouchProtocol::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(CKTouchProtocol::onTouchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(CKTouchProtocol::onTouchCancelled,this);
	dispatch->addEventListenerWithFixedPriority(listener,1);
	m_touchListener = listener;
}

void CKTouchProtocol::removeTouchEvent()
{
	auto dispatch = Director::getInstance()->getEventDispatcher();
	dispatch->removeEventListener(m_touchListener);
}

bool CKTouchProtocol::onTouchBegan( Touch *touch, Event *unused_event )
{
	return true;
}

void CKTouchProtocol::onTouchMoved( Touch *touch, Event *unused_event )
{

}

void CKTouchProtocol::onTouchEnded( Touch *touch, Event *unused_event )
{

}

void CKTouchProtocol::onTouchCancelled( Touch *touch, Event *unused_event )
{

}