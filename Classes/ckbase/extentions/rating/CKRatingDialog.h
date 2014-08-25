#ifndef __CKRATINGDIALOG_H__
#define __CKRATINGDIALOG_H__

#include "cocos2d.h"
#include "CKDialog.h"

USING_NS_CC;

using namespace std;

class CKRatingDialog : public CKDialog
{
public:
	CREATE_FUNC(CKRatingDialog);
			
protected:
	CKRatingDialog(void);
	
	~CKRatingDialog(void);

	virtual bool init() override;  

};

#endif // __CKRATINGDIALOG_H__