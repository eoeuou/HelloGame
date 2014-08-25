#ifndef __CKCONSTANTS_H_
#define __CKCONSTANTS_H_

#include "CKCommon.h"

class CKConstants {
public:
	static const char* USER_LOGIN_URL;
	static const char* GET_USER_SETTINGS_URL;
	static const char* CHECK_OVERDUE_URL;

	static bool init();
};


#endif /* __CKCONSTANTS_H_ */
