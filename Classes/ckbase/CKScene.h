#ifndef __CKSCENE_H__
#define __CKSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CKScene:public cocos2d::Scene
{
public:
	CREATE_FUNC(CKScene);
			
protected:
	CKScene(void);
	
	~CKScene(void);

	virtual bool init() override;  

	/**
     * add your sprite to this scene
     */
	virtual void initScene(){}

	/**
     * pause your scene
     */
	virtual void pauseScene(){}
	
	/**
     * resume your scene
     */
	virtual void resumeScene(){}

};

#endif // __CKSCENE_H__