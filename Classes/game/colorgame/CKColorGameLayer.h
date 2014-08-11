#ifndef __CKCOLORGAMELAYER_H__
#define __CKCOLORGAMELAYER_H__

#include "cocos2d.h"
#include "CKProtocols.h"
#include "CKColorItem.h"

USING_NS_CC;

using namespace std;

#define GAME_HORIZONTAL 10
#define GAME_VERTICAL 8

class CKColorGameLayer : public cocos2d::LayerColor ,public CKTouchMoveProtocol ,public CKTouchProtocol
{
private:

	std::function<void(int,int)> m_onSelectColorItemFunc;

	CC_SYNTHESIZE_READONLY(Size,m_colorItemSize,ColorItemSize);
	
	CKColorGameLayer();

public:
	~CKColorGameLayer();

	static CKColorGameLayer * create(const Color4B& color,std::function<void(int,int)> func,Size itemSize)
	{
		CKColorGameLayer * layer = new CKColorGameLayer();
		layer->m_onSelectColorItemFunc = func;
		layer->m_colorItemSize = itemSize;

		if( layer && layer->initWithColor(color))
		{
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

private:
	bool initWithColor(const Color4B& color);

};

#endif // __CKCOLORGAMELAYER_H__