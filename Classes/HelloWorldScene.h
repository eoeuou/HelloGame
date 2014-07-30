#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKModel.h"
#include "URLData.h"

class HelloWorld : public cocos2d::Layer , public URLRequestListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void addTestLabel();

	void menuCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touches, Event  *event);
	void onTouchMoved(Touch* touches, Event  *event);

	void onMouseScroll(Event *event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
	void showFightScene();

	CKModel* getQuestionByIndex(int index);

	void questionTest();

	void httpTest();

	void NotificationTest();

	void messageboxTest();

	virtual void onExit();

	virtual void urlRequestCallback(CKHttpModel* model);

	void drawTest();
private:
	Point _beginPos;
	Menu* _itemMenu;
};

#endif // __HELLOWORLD_SCENE_H__
