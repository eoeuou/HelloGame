#ifndef CKWRAPPER_H_
#define CKWRAPPER_H_

#include "CKCommon.h"
#include "CKDeviceEngine.h"

#define NS_WP_BGN	namespace wrapper {
#define NS_WP_END	}

namespace wrapper {
	
    //************************************
    // Method:    showToast
    // FullName:  wrapper::showToast
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: const char * msg
    //************************************
    void showToast(const char* msg);

	std::string getUID();
	std::string getIMSI();
	std::string getPhoneNum();
	bool isNetworkAvailable();
	

} // namespace wrapper

#endif /* CKWRAPPER_H_ */
