#ifndef CKANDROIDDEVICEENGINE_H_
#define CKANDROIDDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKAndroidDeviceEngine: public CKDeviceEngine 
{
public:
	CKAndroidDeviceEngine();

	virtual ~CKAndroidDeviceEngine();

	virtual std::string getIMSI();
	virtual std::string getPhoneNum();
	virtual std::string getDeviceId();

	virtual void showNetworkSettings();

	virtual std::string getPackageName();
	virtual std::string getVersionName();
	virtual int getVersionCode();
	virtual int getNetworkStatusCode();
	
	virtual std::string getAvailableInternalMemorySize();
	virtual std::string getTotalInternalMemorySize();
	virtual std::string getAvailableExternalMemorySize();
	virtual std::string getTotalExternalMemorySize();
	virtual std::string getUsedExternalMemorySize();
};

#endif /* CKANDROIDDEVICEENGINE_H_ */
