#ifndef __CKDIALOG_H__
#define __CKDIALOG_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKDialog:public cocos2d::LayerColor
{
public:
	CREATE_FUNC(CKDialog);
				
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 	
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);

	void onCloseCallback(cocos2d::Ref* pSender);

	virtual void close();

	template<class T> static T* show(Node* parent,int localZOrder) {
		T* dialog = T::create();

		if(dialog){
			dialog->setVisible(true);
			if(parent){
				parent->addChild(dialog,localZOrder);
			}
		}

		return dialog;
	};

	void testBtnAdd();
protected:
	CKDialog(void);
	
	~CKDialog(void);

	virtual bool init();  

};

class  CKLoadingDialog : public CKDialog
{
private:
	CC_SYNTHESIZE_READONLY(Sprite*,m_loadingSprite,LoadingSprite);

public:
	CREATE_FUNC(CKLoadingDialog);

	virtual bool init() override;

	virtual void close() override;

protected:

	CKLoadingDialog():m_loadingSprite(nullptr){}

	~CKLoadingDialog(){}

};
#endif // __CKDIALOG_H__