#ifndef CKDEFAULTPAYENGINE_H_
#define CKDEFAULTPAYENGINE_H_

#include "CKPayEngine.h"

class CKDefaultPayEngine: public CKPayEngine {
public:
	CKDefaultPayEngine();

	virtual ~CKDefaultPayEngine();

	virtual bool pay(const std::string& id,int money);
};

#endif /* CKDEFAULTPAYENGINE_H_ */
