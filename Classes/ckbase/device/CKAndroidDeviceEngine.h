#ifndef CKANDROIDDEVICEENGINE_H_
#define CKANDROIDDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKAndroidDeviceEngine: public CKDeviceEngine {
public:
	CKAndroidDeviceEngine();

	virtual ~CKAndroidDeviceEngine();

	virtual bool initDevice();

	virtual std::string getDeviceId();

};

#endif /* CKANDROIDDEVICEENGINE_H_ */
