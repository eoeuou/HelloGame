#ifndef CKANDROIDDEVICEENGINE_H_
#define CKANDROIDDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKAndroidDeviceEngine: public CKDeviceEngine {
public:
	CKAndroidDeviceEngine();

	virtual ~CKAndroidDeviceEngine();
	
	virtual std::string getDeviceId();

	virtual void showNetworkSettings();

};

#endif /* CKANDROIDDEVICEENGINE_H_ */
