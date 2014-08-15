#ifndef __CKCOLORGAMELAYER_H__
#define __CKCOLORGAMELAYER_H__

#include "cocos2d.h"
#include "CKProtocols.h"
#include "CKColorItem.h"

USING_NS_CC;

using namespace std;

class CKColorGameLayer : public cocos2d::LayerColor ,public CKTouchMoveProtocol ,public CKTouchProtocol
{
private:

	std::function<void(int,int)> m_onSelectColorItemFunc;

	CC_SYNTHESIZE(Size,m_colorItemSize,ColorItemSize);
	
	CKColorGameLayer();

public:
	~CKColorGameLayer();

	static CKColorGameLayer * create(const Color4B& color,std::function<void(int,int)> onSelectFunc,Size size)
	{
		CKColorGameLayer * layer = new CKColorGameLayer();
		layer->m_onSelectColorItemFunc = onSelectFunc;

		if( layer && layer->initWithColor(color,size.width,size.height))
		{
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	CKColorItem* initColorItemByPos(int x, int y);

	virtual void onExit() override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	void changeTouchStatus(bool touchable);
private:
	bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);

};

#endif // __CKCOLORGAMELAYER_H__