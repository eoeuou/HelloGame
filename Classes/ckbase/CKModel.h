#ifndef __CKMODEL_H__
#define __CKMODEL_H__

#include "cocos2d.h"
#include "CKProtocols.h"

USING_NS_CC;

using namespace std;

class CKModel:public cocos2d::Ref , public PropertyProtocol
{
private:
	CC_SYNTHESIZE_READONLY(__Dictionary*,m_propertyDic,PropertyDic);

public:
	CREATE_FUNC(CKModel);
	
	void setForeignProperty(const char* key,CKModel* value);

	CKModel* getForeignProperty(const char* key,CKModel* defaultValue = nullptr);

	void setForeignArray(const char* key,__Array* value);

	__Array* getForeignArray(const char* key,__Array* defaultValue = nullptr);		

	void setForeignDic(const char* key,__Dictionary* value);

	__Dictionary* getForeignDic(const char* key,__Dictionary* defaultValue = nullptr);

protected:
	CKModel(void);
	
	~CKModel(void);

	virtual bool init();  

};
#endif // __CKMODEL_H__