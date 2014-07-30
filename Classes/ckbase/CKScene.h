#ifndef __CKSCENE_H__
#define __CKSCENE_H__

#include "cocos2d.h"
#include "CKProtocols.h"

USING_NS_CC;

using namespace std;

class CKScene: public cocos2d::Scene, public SceneProtocol, public CKTouchProtocol
{
private:

public:
	CREATE_FUNC(CKScene);
			
protected:
	CKScene(void);
	
	~CKScene(void);

	virtual bool init() override;  

	virtual void initScene();

	virtual void pauseScene();

	virtual void resumeScene();

};

#endif // __CKSCENE_H__