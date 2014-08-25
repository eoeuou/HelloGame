#ifndef CKWRAPPER_H_
#define CKWRAPPER_H_

#include "CKCommon.h"
#include "CKDeviceEngine.h"

#define NS_WP_BGN	namespace wrapper {
#define NS_WP_END	}

namespace wrapper {
	
    void showToast(const char* msg);
	void openUrl(const char* url);

	std::string getUID();
	std::string getIMSI();
	std::string getPhoneNum();
	bool isNetworkAvailable();	

	

} // namespace wrapper

#endif /* CKWRAPPER_H_ */
