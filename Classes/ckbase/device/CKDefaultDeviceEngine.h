#ifndef CKDEFAULTDEVICEENGINE_H_
#define CKDEFAULTDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKDefaultDeviceEngine: public CKDeviceEngine {
public:
	CKDefaultDeviceEngine();

	virtual ~CKDefaultDeviceEngine();

	virtual std::string getDeviceId(){ return "default";}

	virtual void showNetworkSettings(){}
};

#endif /* CKDEFAULTDEVICEENGINE_H_ */
