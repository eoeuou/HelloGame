#ifndef __CKDIALOG_H__
#define __CKDIALOG_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKDialog:public cocos2d::LayerColor
{
private:
	CC_SYNTHESIZE_READONLY(MenuItemImage*,m_closeItem,CloseItem);
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

	void addCloseItem();

	void removeCloseItem();
protected:
	CKDialog(void);
	
	~CKDialog(void);

	virtual bool init();  

};

class CKLoadingDialog : public CKDialog
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

class CKInfoDialog : public CKDialog
{
private:
	CC_SYNTHESIZE_READONLY(LabelTTF*,m_infoLabel,InfoLabel);

public:
	CREATE_FUNC(CKInfoDialog);

	virtual bool init() override;

	void setInfoLableString(std::string info);
protected:

	CKInfoDialog():m_infoLabel(nullptr){}

	~CKInfoDialog(){}

};
#endif // __CKDIALOG_H__