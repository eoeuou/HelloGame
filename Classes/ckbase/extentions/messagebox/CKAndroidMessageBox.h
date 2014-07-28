#ifndef CKANDROIDMESSAGEBOXENGINE_H_
#define CKANDROIDMESSAGEBOXENGINE_H_

#include "CKMessageBox.h"

class CKAndroidMessageBox: public CKMessageBox {
protected:

	virtual bool create();

public:
	CKAndroidMessageBox();

	virtual ~CKAndroidMessageBox();

	virtual void setButtonText(int which,const char* text);

	virtual void show();

	virtual void hide();
};

#endif /* CKANDROIDMESSAGEBOXENGINE_H_ */
