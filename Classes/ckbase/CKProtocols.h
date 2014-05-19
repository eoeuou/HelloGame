#ifndef __CKProtocols_H__
#define __CKProtocols_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class PropertyProtocol
{	
private:
	CC_SYNTHESIZE(__Dictionary*,m_propertyDic,PropertyDic);

protected:
	PropertyProtocol():m_propertyDic(__Dictionary::create()){}
    virtual ~PropertyProtocol() {}

public:
	bool getBooleanProperty(const char* key, bool defaultValue = false);
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
	}
};


#endif // __CKProtocols_H__