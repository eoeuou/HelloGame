#ifndef __CKSEQUENCELAYER_H__
#define __CKSEQUENCELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKSequenceLayer:public cocos2d::Layer
{
private:
	CC_SYNTHESIZE(CCLayerColor*,m_landLayerA,LandLayerA);
	CC_SYNTHESIZE(CCLayerColor*,m_landLayerB,LandLayerB);
public:
	CREATE_FUNC(CKSequenceLayer);

	void startScrollLand();

	void stopScrollLand();
protected:
	CKSequenceLayer(void);
	
	~CKSequenceLayer(void);

	virtual bool init();  

	void scrollLand(float dt);


};

#endif // __CKSEQUENCELAYER_H__