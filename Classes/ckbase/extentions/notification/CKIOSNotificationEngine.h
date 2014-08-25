#ifndef KIOSNOTIFICATIONENGINE_H_
#define CKIOSNOTIFICATIONENGINE_H_

#include "CKNotificationEngine.h"

class CKIOSNotificationEngine: public CKNotificationEngine {
public:
	CKIOSNotificationEngine();
	virtual ~CKIOSNotificationEngine();

	virtual void show(CKNotification& notification);
    
	virtual void cancel(CKNotification& notification);

};

#endif /* CKIOSNOTIFICATIONENGINE_H_ */
