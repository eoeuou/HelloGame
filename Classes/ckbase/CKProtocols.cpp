﻿#include "CKProtocols.h"
//
// generic getters for properties
//
const Value& PropertyProtocol::getValue(const char* key, const Value& defaultValue) const
{
	auto iter = m_valueMap.find(key);
	if (iter != m_valueMap.cend())
		return m_valueMap.at(key);
	return defaultValue;
}

void PropertyProtocol::setValue(const char* key, const Value& value)
{
	m_valueMap[key] = value;
}

bool PropertyProtocol::removeValue(const char* key)
{
	auto iter = m_valueMap.find(key);
	if (iter != m_valueMap.cend())
	{
		m_valueMap.erase(iter);
		return true;
	}
	return false;
}

bool PropertyProtocol::hasValue(const char* key)
{
	auto iter = m_valueMap.find(key);
	if (iter != m_valueMap.cend())
		return true;
	return false;
}

int PropertyProtocol::size()
{
	return m_valueMap.size();
}

void PropertyProtocol::clear()
{
	m_valueMap.clear();
}

std::string PropertyProtocol::getInfo() const
{
	// Dump
	Value forDump = Value(m_valueMap);
	return forDump.getDescription();
}

CKTouchProtocol::CKTouchProtocol():
	m_eventListenerKeyboard(nullptr),
	m_touchListener(nullptr),
	m_touchable(false)
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
				Director::getInstance()->popScene();
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

void CKTouchProtocol::addTouchEvent(EventDispatcher* dispatch)
{
	m_touchable = true;
	if (dispatch == nullptr)
	{
		dispatch = Director::getInstance()->getEventDispatcher();
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CKTouchProtocol::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(CKTouchProtocol::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(CKTouchProtocol::onTouchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(CKTouchProtocol::onTouchCancelled,this);
	dispatch->addEventListenerWithFixedPriority(listener,1);
	m_touchListener = listener;
}

void CKTouchProtocol::removeTouchEvent(EventDispatcher* dispatch)
{
	m_touchable = false;
	if (dispatch == nullptr)
	{
		dispatch = Director::getInstance()->getEventDispatcher();
	}
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