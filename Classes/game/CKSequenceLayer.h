#ifndef __CKSEQUENCELAYER_H__
#define __CKSEQUENCELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;
typedef enum __ScrollType
{
	CKSCROLL_DIR_VERTICAL,
	CKSCROLL_DIR_HORIZONTAL,
	CKSCROLL_DIR_BOTH
}CKScrollType;

#define LandSpeed_DIS 3.0f

class CKLandLayer:public cocos2d::CCLayerColor
{
private:
	CC_SYNTHESIZE_READONLY(DrawNode*, m_drawNode, DrawNode);
protected:
	CKLandLayer():
		m_drawNode(nullptr)
	{
	};

public:
	~CKLandLayer(){};

	static CKLandLayer * create(const Color4B& color, GLfloat width, GLfloat height)
	{
		CKLandLayer * layer = new CKLandLayer();
		if( layer && layer->initWithColor(color,width,height))
		{
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);

	void drawDotUpdate(float dt,CCPoint drawPoint);
};

class CKSequenceLayer:public cocos2d::Layer
{
private:
	CC_SYNTHESIZE(CKScrollType,m_scrollType,ScrollType);

	CC_SYNTHESIZE(Point,m_scrollDirection,ScrollDirection);
	CC_SYNTHESIZE(float,m_scrollSpeed,ScrollSpeed);

	CC_SYNTHESIZE(CKLandLayer*,m_landLayerA,LandLayerA);
	CC_SYNTHESIZE(CKLandLayer*,m_landLayerB,LandLayerB);
	CC_SYNTHESIZE(CKLandLayer*,m_landLayerC,LandLayerC);
	CC_SYNTHESIZE(CKLandLayer*,m_landLayerD,LandLayerD);

	CC_SYNTHESIZE(Vector<CKLandLayer*>,m_landLayers,LandLayers);

	CC_SYNTHESIZE(bool,m_bIsPauseScrollLand,BIsPauseScrollLand);

	CCPoint m_positionDelta;
public:
	CREATE_FUNC(CKSequenceLayer);

	void startScrollLand();

	void stopScrollLand();

	void pauseScrollLand();

	void resumeScrollLand();

	void changeScrollDirection(CCPoint direction);
protected:
	CKSequenceLayer(void);

	~CKSequenceLayer(void);

	virtual bool init();  

	void scrollLand(float dt);

	void horizontalScroll();

	void verticalScroll();

	void bothScroll();

	bool resetLandLayerHorizontal(Layer* landLayer);

	bool resetLandLayerVertical(Layer* landLayer);

};

#endif // __CKSEQUENCELAYER_H__