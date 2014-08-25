#ifndef CKDEFAULTMESSAGEBOXENGINE_H_
#define CKDEFAULTMESSAGEBOXENGINE_H_

#include "CKMessageBox.h"

class CKDefaultMessageBox: public CKMessageBox {
protected:

	virtual bool create();
public:
	CKDefaultMessageBox();

	virtual ~CKDefaultMessageBox();

	virtual void setButtonText(int which,const char* text);

	virtual void show();

	virtual void hide();
};

#endif /* CKDEFAULTMESSAGEBOXENGINE_H_ */
