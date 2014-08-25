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
	ValueMap        m_valueMap;

protected:
	PropertyProtocol(){m_valueMap.clear();}
    virtual ~PropertyProtocol() {m_valueMap.clear();}

public:
    ValueMap& getValueMap(){return m_valueMap;}

	/** returns the value of a given key*/
	const Value& getValue(const char* key, const Value& defaultValue = Value::Null) const;

	/** sets a new key/value pair  in the configuration dictionary */
	void setValue(const char* key, const Value& value);
	
	/** remove the value of a given key */
	virtual bool removeValue(const char* key);

	/** weather have the value of a given key */
	virtual bool hasValue(const char* key);
	
	virtual int size();

	virtual void clear();
	/** returns the Configuration info */
	virtual std::string getInfo() const;

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
public:
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)    
	static CKTouchMoveProtocol* create(Node* node,bool isResetPos,float colorA)
	{
		CKTouchMoveProtocol* p = new CKTouchMoveProtocol();
		p->m_bIsResetPos = isResetPos;
		p->addTouchMoveEvent(node);
        
        if (node->getParent()) {
            
            p->m_colorlayer = LayerColor::create(Color4B(200,0,0,colorA));
            p->m_colorlayer->ignoreAnchorPointForPosition(false);
            p->m_colorlayer->setContentSize(node->getContentSize());
            p->m_colorlayer->setPosition(node->getPosition());
            p->m_colorlayer->setAnchorPoint(node->getAnchorPoint());
            node->getParent()->addChild(p->m_colorlayer,1000);
        }

		return p;
	}
#endif

private:
	EventListenerTouchOneByOne* m_eventListener;
	Node* m_node;
	bool m_bIsResetPos;

    cocos2d::Point m_oriPos;
    LayerColor* m_colorlayer;

protected:
	CKTouchMoveProtocol():m_eventListener(nullptr),m_node(nullptr),m_bIsResetPos(false),m_colorlayer(nullptr){};

	~CKTouchMoveProtocol(){};

	virtual void addTouchMoveEvent(Node* node)
	{
		m_node = node;
		m_eventListener = EventListenerTouchOneByOne::create();
		m_eventListener->setSwallowTouches(true);

		m_eventListener->onTouchBegan = [=](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());

			m_oriPos = target->getPosition();
            cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			cocos2d::Size s = target->getContentSize();
			cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
				//log("sprite ...Position...x = %f, y = %f \n...Anchor...x = %f, y = %f", m_node->getPositionX(),m_node->getPositionY(),m_node->getAnchorPoint().x,m_node->getAnchorPoint().y);
				target->setOpacity(180);
				return true;
			}
			return false;
		};

		m_eventListener->onTouchMoved = [this](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			target->setPosition(target->getPosition() + touch->getDelta());
            if(m_colorlayer)
            {
                m_colorlayer->setPosition(target->getPosition());
            }
		};

		m_eventListener->onTouchEnded = [=](Touch* touch, Event* event){
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			log("sprite onTouchesEnded.. ");
			target->setOpacity(255);
			log("sprite ...Position...x = %f, y = %f \n...Anchor...x = %f, y = %f", m_node->getPositionX(),m_node->getPositionY(),m_node->getAnchorPoint().x,m_node->getAnchorPoint().y);
			if (m_bIsResetPos)
			{
				target->setPosition(m_oriPos);
			}
            if(m_colorlayer)
            {
                m_colorlayer->setPosition(target->getPosition());
            }
		};

		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_eventListener, node);
        // todo verify
        //node->getEventDispatcher()->addEventListenerWithFixedPriority(m_eventListener,1);
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