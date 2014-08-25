#ifndef CKPAYENGINE_H_
#define CKPAYENGINE_H_

#include "CKCommon.h"
#include "CKModel.h"

/*商品信息*/
class CKProductInfoModel : public CKModel
{
public:
	CREATE_FUNC(CKProductInfoModel);

	CK_SYNTHESIZE_MODEL_STRING(std::string,"productId",ProductId);
	CK_SYNTHESIZE_MODEL_FLOAT(float,"rice",Price);

};

class CKPayListener{
public:
	virtual ~CKPayListener(){};
	virtual void onPaySuccess(const std::string& id){};
	virtual void onPayFail(const std::string& id,const std::string& error){};
};

class CKPayEngine: public cocos2d::Ref{
private:
	CC_SYNTHESIZE(std::string,m_key,Key);
	CC_SYNTHESIZE(CKPayListener*,m_listener,Listener);
protected:
	CKPayEngine();
public:
	virtual ~CKPayEngine();

	virtual bool pay(const std::string& id,int money) = 0;

	CK_SINGLETON_METHOD(CKPayEngine,s_sharedEngine,sharedEngine);
};

#endif /* CKPAYENGINE_H_ */
