#ifndef CKDEFAULTRATINGENGINE_H_
#define CKDEFAULTRATINGENGINE_H_

#include "CKRatingEngine.h"

class CKDefaultRatingEngine: public CKRatingEngine {
public:
	CKDefaultRatingEngine();

	virtual ~CKDefaultRatingEngine();

	virtual bool rate(const char* appId);
};

#endif /* CKDEFAULTRATINGENGINE_H_ */
