#ifndef __CKJSONMODEL_H__
#define __CKJSONMODEL_H__

#include "cocos2d.h"
#include "CKCommon.h"
#include "CKModel.h"

USING_NS_CC;
using namespace std;

class CKJsonModel;

typedef std::vector<CKJsonModel*> CKJsonModelVector;
typedef std::unordered_map<std::string, CKJsonModel*> CKJsonModelMap;
typedef std::unordered_map<std::string, CKJsonModelVector*> CKJsonModelVectorMap;

class CKJsonModel:public CKModel , public rapidjson::Document
{
public:
	//CREATE_FUNC(CKJsonModel);
	static CKJsonModel* create() 
	{ 
		CKJsonModel *pRet = new CKJsonModel(); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			//pRet->retain();
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}
	
	~CKJsonModel(void);

protected:
	CKJsonModel(void);

	virtual bool init();  	

private:

	CKJsonModelMap* m_objMap;

	CKJsonModelVectorMap* m_arrayMap;

	void recordToObjMap(const char* key, CKJsonModel* data);

	void recordToArrayMap(const char* key, CKJsonModel* data);
public:
	//************************************
	// Method:    size
	// FullName:  CKJsonModel::size
	// Access:    public 
	// Returns:   int
	// Qualifier: get the root keys size
	//************************************
	int size();

	//************************************
	// Method:    clear
	// FullName:  CKJsonModel::clear
	// Access:    public 
	// Returns:   void
	// Qualifier:  clear all data
	//************************************
	void clear();

	//************************************
	// Method:    getKeys
	// FullName:  CKJsonModel::getKeys
	// Access:    public 
	// Returns:   std::vector<std::string>
	// Qualifier:  get the root keys
	//************************************
	std::vector<std::string> getKeys();

	//************************************
	// Method:    logJsonString
	// FullName:  CKJsonModel::logJsonString
	// Access:    public 
	// Returns:   void
	// Qualifier: log the Json string
	//************************************
	void logJsonString();

	//************************************
	// Method:    getJsonString
	// FullName:  CKJsonModel::getJsonString
	// Access:    public 
	// Returns:   std::string
	// Qualifier: get the Json string
	//************************************
	std::string getJsonString();

	rapidjson::Value& operator[](int key);

	rapidjson::Value& operator[](string key);

	rapidjson::Value& operator[](const char* key);

	//************************************
	// Method:    convertToRapidJsonValue
	// FullName:  CKJsonModel::convertToRapidJsonValue
	// Access:    public 
	// Returns:   rapidjson::Value&
	// Qualifier: 将CKJsonModel转化为rapidjson::Value对象
	//************************************
	rapidjson::Value& convertToRapidJsonValue();

	//************************************
	// Method:    getObjectChildByKey
	// FullName:  CKJsonModel::getObjectChildByKey
	// Access:    public 
	// Returns:   CKJsonModel*
	// Qualifier:
	// Parameter: const char * key
	//************************************
	CKJsonModel* getObjectChildByKey(const char* key);

	//************************************
	// Method:    addObjectChild
	// FullName:  CKJsonModel::addObjectChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add object child
	// Parameter: int key
	// Parameter: CKJsonModel * data
	//************************************
	void addObjectChild(int key, CKJsonModel* data);

	//************************************
	// Method:    addObjectChild
	// FullName:  CKJsonModel::addObjectChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add object child
	// Parameter: std::string key
	// Parameter: CKJsonModel * data
	//************************************
	void addObjectChild(std::string key, CKJsonModel* data);
	
	//************************************
	// Method:    addObject
	// FullName:  CKJsonModel::addObject
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add object child
	// Parameter: const char * key
	// Parameter: CKJsonModel * data
	//************************************
	void addObjectChild(const char* key, CKJsonModel* data);

	int getArrayChildCount();

	//************************************
	// Method:    getArrayChildByKey
	// FullName:  CKJsonModel::getArrayChildByKey
	// Access:    public 
	// Returns:   CKJsonModelVector*
	// Qualifier:
	// Parameter: const char * key
	//************************************
	CKJsonModelVector* getArrayChildByKey(const char* key);

	//************************************
	// Method:    addChild
	// FullName:  CKJsonModel::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array child
	// Parameter: int key
	// Parameter: CKJsonModel * data
	//************************************
	void addArrayChild(int key, CKJsonModel* data);

	//************************************
	// Method:    addChild
	// FullName:  CKJsonModel::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array child
	// Parameter: std::string key
	// Parameter: CKJsonModel * data
	//************************************
	void addArrayChild(std::string key, CKJsonModel* data);	

	//************************************
	// Method:    addChild
	// FullName:  CKJsonModel::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array child
	// Parameter: const char * key
	// Parameter: CKJsonModel * data
	//************************************
	void addArrayChild(const char* key, CKJsonModel* data);
	
	//************************************
	// Method:    removeChild
	// FullName:  CKJsonModel::removeChild
	// Access:    public 
	// Returns:   bool
	// Qualifier: remove child by key
	// Parameter: int key
	//************************************
	bool removeChild(int key);

	//************************************
	// Method:    removeChild
	// FullName:  CKJsonModel::removeChild
	// Access:    public 
	// Returns:   bool
	// Qualifier: remove child by key
	// Parameter: std::string key
	//************************************
	bool removeChild(std::string key);

	//************************************
	// Method:    removeChild
	// FullName:  CKJsonModel::removeChild
	// Access:    public 
	// Returns:   bool
	// Qualifier: remove child by key
	// Parameter: const char * key
	//************************************
	bool removeChild(const char* key);	

};

#endif // __CKJSONMODEL_H__