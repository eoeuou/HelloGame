#ifndef __CKJSONMODEL_H__
#define __CKJSONMODEL_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKModel.h"

USING_NS_CC;
using namespace std;

class CKJsonModel;

typedef Vector<CKJsonModel*> CKJsonModelVector;
typedef Map<std::string, CKJsonModel*> CKJsonModelMap;

//{"propety":"PLAYER-TO",
//"abcdef":{"id":1,"name":"豹儿","age":"3年","low":true},
//"player":[{"id":1,"name":"豹儿","age":"3年","low":true},{"id":1,"name":"豹儿","age":"3年","low":true}]} 

class CKJsonModel : public CKModel
{
public:
	CREATE_FUNC(CKJsonModel);
	
	~CKJsonModel(void);

protected:
	CKJsonModel(void);

	virtual bool init();

private:

	rapidjson::Document document;
	
public:
	virtual int size() override;

	virtual void clear() override;

	void logJsonString();

	std::string getJsonString();

	bool hasChild(const char* key);

	const Value& getChildByKey(const char* key);

	void addChild(std::string key, Value& value);

	void addChild(const char* key, Value& value);

	CKJsonModel* getObjectChildByKey(const char* key);

	void addObjectChild(std::string key, CKJsonModel* data);
	
	void addObjectChild(const char* key, CKJsonModel* data);

	CKJsonModelVector getArrayChildByKey(const char* key);

	void addArrayChild(std::string key, CKJsonModelVector& data);

	void addArrayChild(const char* key, CKJsonModelVector& data);

	bool removeChild(std::string key);

	bool removeChild(const char* key);

};

#endif // __CKJSONMODEL_H__