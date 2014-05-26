#ifndef KIOSDEVICEENGINE_H_
#define CKIOSDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKIOSDeviceEngine: public CKDeviceEngine {
public:
	CKIOSDeviceEngine();
	virtual ~CKIOSDeviceEngine();

	virtual bool device(const std::string& id,int money);
};

#endif /* CKIOSDEVICEENGINE_H_ */
