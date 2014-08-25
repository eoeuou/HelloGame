#ifndef CKDEFAULTNOTIFICATIONENGINE_H_
#define CKDEFAULTNOTIFICATIONENGINE_H_

#include "CKNotificationEngine.h"

class CKDefaultNotificationEngine: public CKNotificationEngine {
public:
	CKDefaultNotificationEngine();

	virtual ~CKDefaultNotificationEngine();

	virtual void show(CKNotification& notification){};

	virtual void cancel(CKNotification& notification){};

};

#endif /* CKDEFAULTNOTIFICATIONENGINE_H_ */
