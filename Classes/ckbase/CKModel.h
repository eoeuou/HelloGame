#ifndef __CKMODEL_H__
#define __CKMODEL_H__

#include "cocos2d.h"
#include "CKProtocols.h"

USING_NS_CC;

using namespace std;

enum ModelType
{
	NONE,
	VALUEMAP,
	DICTIONARY
};

class CKModel : public cocos2d::Ref, public PropertyProtocol
{
private:
	__Dictionary* m_propertyDic;
	
public:
	CREATE_FUNC(CKModel);

	__Dictionary* getPropertyDic(){return m_propertyDic;}

	void setForeignProperty(const char* key,CKModel* value);

	CKModel* getForeignProperty(const char* key,CKModel* defaultValue = nullptr);

	void setForeignArray(const char* key,__Array* value);

	__Array* getForeignArray(const char* key,__Array* defaultValue = nullptr);

	void setForeignDic(const char* key,__Dictionary* value);

	__Dictionary* getForeignDic(const char* key,__Dictionary* defaultValue = nullptr);

	virtual bool removeValue(const char* key) override;

	virtual bool hasValue(const char* key) override;

	virtual int size() override;

	virtual void clear() override;
	
	ModelType getModelTypeByKey(const char* key);

	virtual std::string getInfo() const;

protected:
	CKModel(void);

	~CKModel(void);

	virtual bool init();

};
#endif // __CKMODEL_H__