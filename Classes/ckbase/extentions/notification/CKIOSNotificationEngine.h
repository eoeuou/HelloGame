#ifndef KIOSNOTIFICATIONENGINE_H_
#define CKIOSNOTIFICATIONENGINE_H_

#include "CKNotificationEngine.h"

class CKIOSNotificationEngine: public CKNotificationEngine {
public:
	CKIOSNotificationEngine();
	virtual ~CKIOSNotificationEngine();

	virtual bool notification(const std::string& id,int money);
};

#endif /* CKIOSNOTIFICATIONENGINE_H_ */
