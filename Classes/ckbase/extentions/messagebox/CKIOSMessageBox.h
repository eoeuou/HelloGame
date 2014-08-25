#ifndef KIOSMESSAGEBOXENGINE_H_
#define CKIOSMESSAGEBOXENGINE_H_

#include "CKMessageBox.h"

class CKIOSMessageBox: public CKMessageBox {
public:
	CKIOSMessageBox();
	virtual ~CKIOSMessageBox();
    
    virtual bool create(){ return false;}
    
	virtual void setButtonText(int which,const char* text){};
    
	virtual void show(){};
    
	virtual void hide(){};
};

#endif /* CKIOSMESSAGEBOXENGINE_H_ */
