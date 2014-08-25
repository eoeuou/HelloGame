#ifndef CKANDROIDRATINGENGINE_H_
#define CKANDROIDRATINGENGINE_H_

#include "CKRatingEngine.h"

class CKAndroidRatingEngine: public CKRatingEngine {
public:
	CKAndroidRatingEngine();

	virtual ~CKAndroidRatingEngine();

	virtual bool rate(const char* appId);
};

#endif /* CKANDROIDRATINGENGINE_H_ */
