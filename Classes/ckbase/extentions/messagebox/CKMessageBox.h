#ifndef CKMESSAGEBOXENGINE_H_
#define CKMESSAGEBOXENGINE_H_

#include "CKCommon.h"

class CKMessageBox;

class CKMessageBoxListener{
public:
	virtual ~CKMessageBoxListener(){};
	virtual void onButtonClick(CKMessageBox* box,int which){};
};

class CKMessageBox: public cocos2d::Ref{
public:
	static const int BUTTON_POSITIVE = -1;
	static const int BUTTON_NEGATIVE = -2;
	static const int BUTTON_NEUTRAL = -3;

private:
	CC_SYNTHESIZE(std::string,m_title,Title);
	CC_SYNTHESIZE(std::string,m_message,Message);
	CC_SYNTHESIZE(CKMessageBoxListener*,m_messageBoxListener,MessageBoxListener);
	CC_SYNTHESIZE(std::function<void(CKMessageBox* box,int which)>,m_msgBoxCallback,MsgBoxCallback);
	
	static CKMessageBox* s_messageBox;
protected:
	CKMessageBox();

	virtual bool create() = 0;

	virtual void onButtonClick(int which);
public:
	virtual ~CKMessageBox();

	static CKMessageBox* create(const char* title,const char* message);

	static void dispatchButtonClick(int which);

	virtual void setButtonText(int which,const char* text) = 0 ;

	virtual void show() = 0;

	virtual void hide() = 0;

};

#endif /* CKMESSAGEBOXENGINE_H_ */
