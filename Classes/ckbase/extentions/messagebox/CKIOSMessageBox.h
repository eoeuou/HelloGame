#ifndef KIOSMESSAGEBOXENGINE_H_
#define CKIOSMESSAGEBOXENGINE_H_

#include "CKMessageBox.h"

class CKIOSMessageBox: public CKMessageBox {
public:
	CKIOSMessageBox();
	virtual ~CKIOSMessageBox();

	virtual bool messagebox(const std::string& id,int money);
};

#endif /* CKIOSMESSAGEBOXENGINE_H_ */
