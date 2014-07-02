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

	const char* getJsonString();
	
	bool hasRapidJsonMember(const char* key);
	
    rapidjson::Value& operator[](int key);

    rapidjson::Value& operator[](string key);

	rapidjson::Value& operator[](const char* key);

	void addChild(const char* key, CKJsonData* data);
};

#endif // __CKJSONDATA_H__