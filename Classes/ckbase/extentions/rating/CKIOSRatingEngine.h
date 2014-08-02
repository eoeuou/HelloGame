#ifndef KIOSRATINGENGINE_H_
#define CKIOSRATINGENGINE_H_

#include "CKRatingEngine.h"

class CKIOSRatingEngine: public CKRatingEngine {
public:
	CKIOSRatingEngine();
	virtual ~CKIOSRatingEngine();
    
	virtual bool rate(const char* appId){};
};

#endif /* CKIOSRATINGENGINE_H_ */
