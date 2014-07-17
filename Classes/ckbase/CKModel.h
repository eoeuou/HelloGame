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

/*
以下结果均来自CKHttpUtils 返回值
[result：内容] [path：保存地址] [statusCode：返回状态码] [isSucceed: 返回成功失败]
*/
class CKHttpModel : public CKModel
{
public:
	CREATE_FUNC(CKHttpModel);

	bool getIsSucceed(){ return this->getValue("isSucceed").asBool(); };

	int getStatusCode(){ return this->getValue("statusCode").asInt(); };

	std::string getPath(){ return this->getValue("path").asString(); };

	std::string getResult(){ return this->getValue("result").asString(); };

protected:

	CKHttpModel(){}

	~CKHttpModel(){}

};
#endif // __CKMODEL_H__