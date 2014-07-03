#ifndef __CKJSONDATA_H__
#define __CKJSONDATA_H__

#include "cocos2d.h"
#include "CKCommon.h"

USING_NS_CC;

using namespace std;

class CKJsonData;

typedef std::vector<CKJsonData*> CKJsonDataVector;
typedef std::unordered_map<std::string, CKJsonData*> CKJsonDataMap;

/*
samples:
	CKJsonData* data = new CKJsonData();
	(*data)["id"] = 1;	
	(*data)["image"] = "image_path";

	CKJsonData* child = new CKJsonData();
	(*child)["name"] = 2;
	(*child)["age"] = 2*20;
	data->addArrayChild("stu",child);

	CKJsonData* child1 = new CKJsonData();
	(*child1)["name"] = 12;
	(*child1)["age"] =12*20;
	data->addArrayChild("stu",child1);

	CKJsonData* obj = new CKJsonData();
	(*obj)["name"] = 12;
	(*obj)["age"] =12*20;
	data->addObjectChild("stuobj",obj);

	data->logJsonString();
*/

class CKJsonData
{
private:
	rapidjson::Document m_document;

public:
	CKJsonData(void);
	
	~CKJsonData(void);

	rapidjson::Document& getJsonDocument();

	//************************************
	// Method:    size
	// FullName:  CKJsonData::size
	// Access:    public 
	// Returns:   int
	// Qualifier: get the root keys size
	//************************************
	int size();

	//************************************
	// Method:    clear
	// FullName:  CKJsonData::clear
	// Access:    public 
	// Returns:   void
	// Qualifier:  clear all data
	//************************************
	void clear();

	//************************************
	// Method:    getKeys
	// FullName:  CKJsonData::getKeys
	// Access:    public 
	// Returns:   std::vector<std::string>
	// Qualifier:  get the root keys
	//************************************
	std::vector<std::string> getKeys();

	//************************************
	// Method:    logJsonString
	// FullName:  CKJsonData::logJsonString
	// Access:    public 
	// Returns:   void
	// Qualifier: log the Json string
	//************************************
	void logJsonString();

	//************************************
	// Method:    getJsonString
	// FullName:  CKJsonData::getJsonString
	// Access:    public 
	// Returns:   std::string
	// Qualifier: get the Json string
	//************************************
	std::string getJsonString();
	
	//************************************
	// Method:    hasRapidJsonMember
	// FullName:  CKJsonData::hasRapidJsonMember
	// Access:    public 
	// Returns:   bool
	// Qualifier: find whether have the member by key 
	// Parameter: const char * key
	//************************************
	bool hasRapidJsonMember(const char* key);
	
    rapidjson::Value& operator[](int key);

    rapidjson::Value& operator[](string key);

	rapidjson::Value& operator[](const char* key);
	
	//************************************
	// Method:    addObjectChild
	// FullName:  CKJsonData::addObjectChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add object child
	// Parameter: int key
	// Parameter: CKJsonData * data
	//************************************
	void addObjectChild(int key, CKJsonData* data);

	//************************************
	// Method:    addObjectChild
	// FullName:  CKJsonData::addObjectChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add object child
	// Parameter: std::string key
	// Parameter: CKJsonData * data
	//************************************
	void addObjectChild(std::string key, CKJsonData* data);
	
	//************************************
	// Method:    addObject
	// FullName:  CKJsonData::addObject
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add object child
	// Parameter: const char * key
	// Parameter: CKJsonData * data
	//************************************
	void addObjectChild(const char* key, CKJsonData* data);

	//************************************
	// Method:    addChild
	// FullName:  CKJsonData::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array child
	// Parameter: int key
	// Parameter: CKJsonData * data
	//************************************
	void addArrayChild(int key, CKJsonData* data);

	//************************************
	// Method:    addChild
	// FullName:  CKJsonData::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array child
	// Parameter: std::string key
	// Parameter: CKJsonData * data
	//************************************
	void addArrayChild(std::string key, CKJsonData* data);	

	//************************************
	// Method:    addChild
	// FullName:  CKJsonData::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array child
	// Parameter: const char * key
	// Parameter: CKJsonData * data
	//************************************
	void addArrayChild(const char* key, CKJsonData* data);
	
	//************************************
	// Method:    removeChild
	// FullName:  CKJsonData::removeChild
	// Access:    public 
	// Returns:   bool
	// Qualifier: remove child by key
	// Parameter: int key
	//************************************
	bool removeChild(int key);

	//************************************
	// Method:    removeChild
	// FullName:  CKJsonData::removeChild
	// Access:    public 
	// Returns:   bool
	// Qualifier: remove child by key
	// Parameter: std::string key
	//************************************
	bool removeChild(std::string key);

	//************************************
	// Method:    removeChild
	// FullName:  CKJsonData::removeChild
	// Access:    public 
	// Returns:   bool
	// Qualifier: remove child by key
	// Parameter: const char * key
	//************************************
	bool removeChild(const char* key);	
};

#endif // __CKJSONDATA_H__