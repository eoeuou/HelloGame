#ifndef CKRATINGENGINE_H_
#define CKRATINGENGINE_H_

#include "CKCommon.h"

class CKRatingListener{
public:
	virtual ~CKRatingListener(){};
	virtual void onRatingSuccess(const std::string& id){};
	virtual void onRatingFail(const std::string& id,const std::string& error){};
};

class CKRatingEngine: public cocos2d::Ref{
private:
	CC_SYNTHESIZE(std::string,m_key,Key);
	CC_SYNTHESIZE(CKRatingListener*,m_listener,Listener);
protected:
	CKRatingEngine();
public:
	virtual ~CKRatingEngine();

	virtual bool rate(const char* appId) = 0;

	CK_SINGLETON_METHOD(CKRatingEngine,s_sharedEngine,sharedEngine);
};

#endif /* CKRATINGENGINE_H_ */
