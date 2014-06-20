#ifndef CKDEVICEENGINE_H_
#define CKDEVICEENGINE_H_

#include "CKCommon.h"

class CKDeviceEngine: public cocos2d::Ref
{
private:

protected:
	CKDeviceEngine();
public:
	virtual ~CKDeviceEngine();

	virtual std::string getIMSI() = 0;
	virtual std::string getPhoneNum() = 0;
	virtual std::string getDeviceId() = 0;

	virtual void showNetworkSettings() = 0;

	CK_SINGLETON_METHOD(CKDeviceEngine,s_sharedEngine,sharedEngine);
};

#endif /* CKDEVICEENGINE_H_ */
