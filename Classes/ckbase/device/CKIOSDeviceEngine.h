#ifndef KIOSDEVICEENGINE_H_
#define CKIOSDEVICEENGINE_H_

#include "CKDeviceEngine.h"

class CKIOSDeviceEngine: public CKDeviceEngine {
public:
	CKIOSDeviceEngine();
	virtual ~CKIOSDeviceEngine();
	
	virtual std::string getIMSI(){ return ""; }
	virtual std::string getPhoneNum(){ return ""; }
	virtual std::string getDeviceId(){ return "";}
    
	virtual void showNetworkSettings(){};
    
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

#endif /* CKIOSDEVICEENGINE_H_ */
