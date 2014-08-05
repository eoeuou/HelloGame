#ifndef __GUIScene_H__
#define __GUIScene_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CKScene.h"
#include "UILayout.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace std;

class GUIScene : public CKScene
{
private:

public:
	CREATE_FUNC(GUIScene);

protected:
	GUIScene(void);
	
	~GUIScene(void);

	virtual bool init();  

public:

	virtual void onEnter() override;
	virtual void onExit() override;

	void touchEvent(Ref* pSender, TouchEventType type);
};

#endif // __GUIScene_H__