#ifndef CKDEVICEENGINE_H_
#define CKDEVICEENGINE_H_

#include "CKCommon.h"

typedef enum __NetworkStatusType
{
	n_STATUS_DEFAULT = -1,
	n_STATUS_FAILURE = 0,
	n_STATUS_WIFI = 1,
	n_STATUS_MOBILE = 2,
	n_STATUS_UNKNOW = 5
}NetworkStatusType;

class CKDeviceEngine: public cocos2d::Ref
{
private:

protected:
	CKDeviceEngine();
public:
	virtual ~CKDeviceEngine();

	// ===========================================================
	// DeviceInformation
	// ===========================================================
	virtual std::string getIMSI() = 0;
	virtual std::string getPhoneNum() = 0;
	virtual std::string getDeviceId() = 0;

	virtual void showNetworkSettings() = 0;

	virtual std::string getPackageName() = 0;
	virtual std::string getVersionName() = 0;
	virtual int getVersionCode() = 0;

	virtual int getNetworkStatusCode() = 0;

	virtual bool isNetworkAvailable()
	{
		int ret = CKDeviceEngine::sharedEngine()->getNetworkStatusCode();
		return (ret!=n_STATUS_DEFAULT && ret!=n_STATUS_FAILURE);
	}

	virtual NetworkStatusType getCurNetworkStatusType()
	{
		NetworkStatusType status = NetworkStatusType::n_STATUS_DEFAULT;
		int ret = CKDeviceEngine::sharedEngine()->getNetworkStatusCode();
		switch (ret)
		{
		case n_STATUS_DEFAULT:
			status = n_STATUS_DEFAULT;
			break;
		case n_STATUS_FAILURE:
			status = n_STATUS_FAILURE;
			break;
		case n_STATUS_WIFI:
			status = n_STATUS_WIFI;
			break;
		case n_STATUS_MOBILE:
			status = n_STATUS_MOBILE;
			break;
		case n_STATUS_UNKNOW:
			status = n_STATUS_UNKNOW;
			break;
		default:
			break;
		}
		return status;
	}

	// ===========================================================
	// DeviceInformation
	// ===========================================================

	// ===========================================================
	// MemorySize
	// ===========================================================
	virtual std::string getAvailableInternalMemorySize() = 0;
	virtual std::string getTotalInternalMemorySize() = 0;
	virtual std::string getAvailableExternalMemorySize() = 0;
	virtual std::string getTotalExternalMemorySize() = 0;
	virtual std::string getUsedExternalMemorySize() = 0;

	virtual std::string getDeviceMemorySizeInfo(){
		return	"AvailableInternalMemorySize:"+getAvailableInternalMemorySize()+
			"\nTotalInternalMemorySize:"+getTotalInternalMemorySize()+
			"\nAvailableExternalMemorySize:"+getAvailableExternalMemorySize()+
			"\nTotalExternalMemorySize:"+getTotalExternalMemorySize()+
			"\nUsedExternalMemorySize:"+getUsedExternalMemorySize();
	};
	// ===========================================================
	// MemorySize
	// ===========================================================

	CK_SINGLETON_METHOD(CKDeviceEngine,s_sharedEngine,sharedEngine);
};

#endif /* CKDEVICEENGINE_H_ */
