#ifndef CKANDROIDPAYENGINE_H_
#define CKANDROIDPAYENGINE_H_

#include "CKPayEngine.h"

class CKAndroidPayEngine: public CKPayEngine {
public:
	CKAndroidPayEngine();

	virtual ~CKAndroidPayEngine();

	virtual bool pay(const std::string& id,int money);
};

#endif /* CKANDROIDPAYENGINE_H_ */
