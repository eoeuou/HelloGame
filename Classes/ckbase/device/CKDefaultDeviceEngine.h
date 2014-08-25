#ifndef CKDEFAULTDEVICEENGINE_H_
#define CKDEFAULTDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKDefaultDeviceEngine: public CKDeviceEngine 
{
public:
	CKDefaultDeviceEngine();

	virtual ~CKDefaultDeviceEngine();

	virtual std::string getIMSI(){ return ""; }
	virtual std::string getPhoneNum(){ return ""; }
	virtual std::string getDeviceId();

	virtual void showNetworkSettings();

	virtual std::string getPackageName(){ return "";}
	virtual std::string getVersionName() { return "";}
	virtual int getVersionCode() { return 0;}

	virtual int getNetworkStatusCode(){ return -1;}

	virtual std::string getAvailableInternalMemorySize(){return "";}
	virtual std::string getTotalInternalMemorySize(){return "";}
	virtual std::string getAvailableExternalMemorySize(){return "";}
	virtual std::string getTotalExternalMemorySize(){return "";}
	virtual std::string getUsedExternalMemorySize(){return "";}
};

#endif /* CKDEFAULTDEVICEENGINE_H_ */
