#ifndef __CKProtocols_H__
#define __CKProtocols_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "trigger/EventDef.h"

USING_NS_CC;

using namespace std;

class PropertyProtocol
{	
private:
	CC_SYNTHESIZE(__Dictionary*,m_propertyDic,PropertyDic);

	ValueMap        _valueDict;
protected:
	PropertyProtocol():m_propertyDic(__Dictionary::create()){}
    virtual ~PropertyProtocol() {}

public:
	/*bool getBooleanProperty(const char* key, bool defaultValue = false);
	int getIntProperty(const char* key, int defaultValue = 0);
	float getFloatProperty(const char* key, float defaultValue = 0);
	string getStringProperty(const char* key, const char* defaultValue = "");

	void setProperty(const char* key, float value);
	void setProperty(const char* key, bool value);
	void setProperty(const char* key, const char* value);
	void setProperty(const char* key, int value);

	void removeProperty(const char* key);
	bool hasProperty(const char* key);

	void clear();

	__Array* allKeys(){ return m_propertyDic->allKeys();}
	string allKeysToString(){
		__Array* all = allKeys();
		Ref* key = nullptr;
		std::string result = "";
		int count = all->count();
		int i = 0;
		CCARRAY_FOREACH(all,key)
		{
			__String* v = dynamic_cast<__String*>(key);
			result.append(v->getCString());
			if(i++!=count-1)
			{
				result.append(":");
			}
		}
		return result;
	}*/

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

#endif // __CKProtocols_H__