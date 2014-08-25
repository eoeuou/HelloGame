#ifndef KIOSPAYENGINE_H_
#define CKIOSPAYENGINE_H_

#include "CKPayEngine.h"

class CKIOSPayEngine: public CKPayEngine {
public:
	CKIOSPayEngine();
	virtual ~CKIOSPayEngine();

	virtual bool pay(const std::string& id,int money);
};

#endif /* CKIOSPAYENGINE_H_ */
