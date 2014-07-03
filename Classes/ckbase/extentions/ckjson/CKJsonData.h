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
	CKJsonData* child = new CKJsonData();
	(*child)["name"] = 12;
	(*child)["age"] =12*20;

	CKJsonData* data = new CKJsonData();
	(*data)["id"] = 1;	
	(*data)["image"] = "image_path";
	data->addChild("stu",child);
	log("%s",data->getJsonString());
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
	// Method:    addChild
	// FullName:  CKJsonData::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array
	// Parameter: const char * key
	// Parameter: CKJsonData * data
	//************************************
	void addChild(const char* key, CKJsonData* data);

	//************************************
	// Method:    addChild
	// FullName:  CKJsonData::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array
	// Parameter: int key
	// Parameter: CKJsonData * data
	//************************************
	void addChild(int key, CKJsonData* data);

	//************************************
	// Method:    addChild
	// FullName:  CKJsonData::addChild
	// Access:    public 
	// Returns:   void
	// Qualifier: this is used to add array
	// Parameter: std::string key
	// Parameter: CKJsonData * data
	//************************************
	void addChild(std::string key, CKJsonData* data);
};

#endif // __CKJSONDATA_H__