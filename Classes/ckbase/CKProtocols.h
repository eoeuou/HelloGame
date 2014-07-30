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

class CKTouchProtocol
{
private:
	CC_SYNTHESIZE(EventListenerKeyboard*,m_eventListenerKeyboard,EventListenerKeyboard);

	CC_SYNTHESIZE(EventListener*,m_touchListener,TouchListener);
protected:

	CKTouchProtocol();

	~CKTouchProtocol();

	virtual void addKeyBackEvent(Node* node, std::function<void(EventKeyboard::KeyCode, Event*)> onKeyReleased = nullptr);
	virtual void removeKeyBackEvent(Node* node);

	virtual void addTouchEvent();
	virtual void removeTouchEvent();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif // __CKProtocols_H__