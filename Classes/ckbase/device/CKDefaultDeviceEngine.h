#ifndef CKDEFAULTDEVICEENGINE_H_
#define CKDEFAULTDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKDefaultDeviceEngine: public CKDeviceEngine {
public:
	CKDefaultDeviceEngine();

	virtual ~CKDefaultDeviceEngine();

	virtual bool initDevice();

	virtual std::string getDeviceId(){ return "default";}
};

#endif /* CKDEFAULTDEVICEENGINE_H_ */
