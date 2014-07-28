#ifndef KIOSRATINGENGINE_H_
#define CKIOSRATINGENGINE_H_

#include "CKRatingEngine.h"

class CKIOSRatingEngine: public CKRatingEngine {
public:
	CKIOSRatingEngine();
	virtual ~CKIOSRatingEngine();

	virtual bool rating(const std::string& id,int money);
};

#endif /* CKIOSRATINGENGINE_H_ */
