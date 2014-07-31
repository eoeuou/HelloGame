#ifndef __CKSEQUENCELAYER_H__
#define __CKSEQUENCELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;
typedef enum __ScrollDirection
{
	CKSCROLL_DIR_VERTICAL,
	CKSCROLL_DIR_HORIZONTAL,
	CKSCROLL_DIR_BOTH
}CKScrollDirection;

#define LandSpeed_DIS 5.0f

class CKSequenceLayer:public cocos2d::Layer
{
private:
	CC_SYNTHESIZE(CKScrollDirection,m_scrollDirection,ScrollDirection);

	CC_SYNTHESIZE(Point,m_scrollVector,ScrollVector);

	CC_SYNTHESIZE(CCLayerColor*,m_landLayerA,LandLayerA);
	CC_SYNTHESIZE(CCLayerColor*,m_landLayerB,LandLayerB);
	CC_SYNTHESIZE(CCLayerColor*,m_landLayerC,LandLayerC);
	CC_SYNTHESIZE(CCLayerColor*,m_landLayerD,LandLayerD);

	CC_SYNTHESIZE(bool,m_bIsPauseScrollLand,BIsPauseScrollLand);

	CCPoint m_positionDelta;
public:
	CREATE_FUNC(CKSequenceLayer);

	void startScrollLand();

	void stopScrollLand();

	void pauseScrollLand();

	void resumeScrollLand();

	void changeScrollVector(CCPoint scrollVector);
protected:
	CKSequenceLayer(void);
	
	~CKSequenceLayer(void);

	virtual bool init();  

	void scrollLand(float dt);

	void horizontalScroll();

	void verticalScroll();

	void bothScroll();
	
	bool resetLandLayerVertical(Layer* landLayer);

	bool resetLandLayerHorizontal(Layer* landLayer);

};

#endif // __CKSEQUENCELAYER_H__