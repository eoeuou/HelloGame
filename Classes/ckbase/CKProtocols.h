#ifndef __CKProtocols_H__
#define __CKProtocols_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "EventDef.h"

USING_NS_CC;

using namespace std;

class PropertyProtocol
{	
private:
	ValueMap        _valueDict;

protected:
	PropertyProtocol(){}
    virtual ~PropertyProtocol() {}

public:
	/** returns the value of a given key as a double */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;

	/** sets a new key/value pair  in the configuration dictionary */
	void setValue(const std::string& key, const Value& value);

	/** returns the Configuration info */
	std::string getInfo() const;
};

class SceneProtocol
{
protected:	
	//oncreate onstart onresume onpause onstop ondestory

	//************************************
	// Method:    add your sprite to this scene
	// FullName:  SceneProtocol::initScene
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	//************************************
	virtual void initScene() = 0;

	//************************************
	// Method:    pause your scene
	// FullName:  SceneProtocol::pauseScene
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	//************************************
	virtual void pauseScene() = 0;
	
	//************************************
	// Method:    resume your scene
	// FullName:  SceneProtocol::resumeScene
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	//************************************
	virtual void resumeScene() = 0;
};

/************************************************************************/
/* Node的点击事件（EventListenerTouchOneByOne）、KeyBack事件                                                                     */
/************************************************************************/
class CKTouchProtocol
{
private:
	CC_SYNTHESIZE(EventListenerKeyboard*,m_eventListenerKeyboard,EventListenerKeyboard);

	CC_SYNTHESIZE(EventListener*,m_touchListener,TouchListener);

	CC_SYNTHESIZE_READONLY(bool,m_touchable,Touchable);
protected:

	CKTouchProtocol();

	~CKTouchProtocol();

	virtual void addKeyBackEvent(Node* node, std::function<void(EventKeyboard::KeyCode, Event*)> onKeyReleased = nullptr);
	virtual void removeKeyBackEvent(Node* node);

	virtual void addTouchEvent(EventDispatcher* dispatch = nullptr);
	virtual void removeTouchEvent(EventDispatcher* dispatch = nullptr);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
};

/************************************************************************/
/* Node的拖动事件                                                                     */
/************************************************************************/
class CKTouchMoveProtocol
{
private:
	EventListenerTouchOneByOne* m_eventListener;
	Node* m_node;
protected:

	CKTouchMoveProtocol():m_node(nullptr){};

	~CKTouchMoveProtocol(){};

	virtual void addTouchMoveEvent(Node* node)
	{
		m_node = node;
		m_eventListener = EventListenerTouchOneByOne::create();
		m_eventListener->setSwallowTouches(true);

		m_eventListener->onTouchBegan = [=](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());

            cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			cocos2d::Size s = target->getContentSize();
			cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
				log("sprite ...Position...x = %f, y = %f \n...Anchor...x = %f, y = %f", m_node->getPositionX(),m_node->getPositionY(),m_node->getAnchorPoint().x,m_node->getAnchorPoint().y);
				target->setOpacity(180);
				return true;
			}
			return false;
		};

		m_eventListener->onTouchMoved = [](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			target->setPosition(target->getPosition() + touch->getDelta());
		};

		m_eventListener->onTouchEnded = [=](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			log("sprite onTouchesEnded.. ");
			target->setOpacity(255);
			log("sprite ...Position...x = %f, y = %f \n...Anchor...x = %f, y = %f", m_node->getPositionX(),m_node->getPositionY(),m_node->getAnchorPoint().x,m_node->getAnchorPoint().y);
		};

		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_eventListener, node);
	}

	virtual void removeTouchMoveEvent(Node* node)
	{
		if (m_eventListener)
		{
			node->getEventDispatcher()->removeEventListener(m_eventListener);
		}
	}

};
#endif // __CKProtocols_H__