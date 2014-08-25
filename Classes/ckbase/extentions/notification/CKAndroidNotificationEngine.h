#ifndef CKANDROIDNOTIFICATIONENGINE_H_
#define CKANDROIDNOTIFICATIONENGINE_H_

#include "CKNotificationEngine.h"

class CKAndroidNotificationEngine: public CKNotificationEngine {
public:
	CKAndroidNotificationEngine();

	virtual ~CKAndroidNotificationEngine();

	virtual void show(CKNotification& notification);

	virtual void cancel(CKNotification& notification);

};

#endif /* CKANDROIDNOTIFICATIONENGINE_H_ */
