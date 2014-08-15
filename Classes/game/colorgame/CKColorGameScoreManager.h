#ifndef __CKCOLORGAMESCOREMANAGER_H__
#define __CKCOLORGAMESCOREMANAGER_H__

#include "cocos2d.h"
#include "CKCommon.h"

USING_NS_CC;

using namespace std;

class CKColorGameScoreManager
{
private:
	CKColorGameScoreManager(void);
	
	~CKColorGameScoreManager(void);
	
public:

	CK_SINGLETON_METHOD_LAZY(CKColorGameScoreManager,s_singleInstance,Instance);

    static void destroyInstance();
	
	bool init();

	/*添加分数标签*/
	void addScoreLabelToScene();
};

#endif // __CKCOLORGAMESCOREMANAGER_H__