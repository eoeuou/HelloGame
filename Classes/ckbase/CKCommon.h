#ifndef __CKCommon_H__
#define __CKCommon_H__

#include "cocos2d.h"
#include "editor-support\cocostudio\DictionaryHelper.h"
#include "cocos-ext.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace cocostudio;


//////////////////////////////////////////////////////////////////////////
#define STD_FUN_NULL [](){}

//////////////////////////////////////////////////////////////////////////

#define CK_SINGLETON_METHOD(className,sharedObject,methodName) \
protected:\
	static className* sharedObject;\
public:\
	static className* methodName(){\
		assert(sharedObject);\
		return sharedObject;\
	}\

#define CK_SINGLETON_METHOD_LAZY(className,sharedObject,methodName) \
protected:\
	static className* sharedObject;\
public:\
	static className* get##methodName(){\
		if(!sharedObject){\
			sharedObject = new className();\
			sharedObject->init();\
		}\
		return sharedObject;\
	}\

#define CK_INIT_STATIC_FIELD(className,fieldName,fieldType,fieldValue)\
fieldType className::fieldName = fieldValue

#define CK_INIT_STATIC_FIELD_WITH_NULL(className,fieldName,fieldType)\
CK_INIT_STATIC_FIELD(className,fieldName,fieldType,NULL)

#define CK_SINGLETON_METHOD_INIT(className,fieldName)\
CK_INIT_STATIC_FIELD(className,fieldName,className*,NULL)

//CKMODEL变量返回值
#define CK_SYNTHESIZE_MODEL_STRING(varType,varName, funName)\
public: virtual varType get##funName(void) const { return this->getValue(varName).asString();}

#define CK_SYNTHESIZE_MODEL_INTEGER(varType,varName, funName)\
public: virtual varType get##funName(void) const { return this->getValue(varName).asInt();}

#define CK_SYNTHESIZE_MODEL_BOOLEAN(varType,varName, funName)\
public: virtual varType get##funName(void) const { return this->getValue(varName).asBool();}

#define CK_SYNTHESIZE_MODEL_FLOAT(varType,varName, funName)\
public: virtual varType get##funName(void) const { return this->getValue(varName).asFloat();}

#define CK_SYNTHESIZE_MODEL_DOUBLE(varType,varName, funName)\
public: virtual varType get##funName(void) const { return this->getValue(varName).asDouble();}

const char* intToString(const int value);
const char* longToString(const long value);
const char* floatToString(const float value);
const char* doubleToString(const double value);

std::string GBKToUTF8(const std::string& strGBK);
std::wstring UTF8ToUnicode(const char* putf8);
std::string UnicodeToUTF8(const wchar_t* putf8);

//about json begin
#define CONVERT_VALUE_MODEL(key,model,doc) \
	if(!model)\
{\
	return;\
}\
	const char* value = DICTOOL->getStringValue_json(doc,key.c_str());\
	model->setValue(key.c_str(),Value(value));\
	CCLog("key=%s,value=%s",key.c_str(),value);\
	CCLog("info=%s",model->getInfo().c_str());\

//************************************
// Method:    parseJsonFileToDocument
// FullName:  parseJsonFileToDocument
// Access:    public 
// Returns:   bool
// Qualifier:  将json文件解析为document
// Parameter: const std::string & fileName
// Parameter: rapidjson::Document & doc
//************************************
bool parseJsonFileToDocument(const std::string &fileName, rapidjson::Document &doc);

//************************************
// Method:    parseJsonStrToDocument
// FullName:  parseJsonStrToDocument
// Access:    public 
// Returns:   bool
// Qualifier: 将json字符串解析为document
// Parameter: const std::string & jsonStr
// Parameter: rapidjson::Document & doc
//************************************
bool parseJsonStrToDocument(const std::string &jsonStr, rapidjson::Document &doc);
//about json end

//************************************
// Method:    writeFileData
// FullName:  writeFileData
// Access:    public 
// Returns:   bool
// Qualifier: 写入本地文件
// Parameter: const char * localPath
// Parameter: const char * fileData
//************************************
bool writeFileData(const char * localPath, const char * fileData);

//************************************
// Method:    getChildrenMaxZorder
// FullName:  getChildrenMaxZorder
// Access:    public 
// Returns:   int
// Qualifier:  获取Node节点的孩子节点中最大的order
// Parameter: Node * parent
//************************************
int getChildrenMaxZorder(Node* parent);

/* */ 
std::string base64_encode(const char* data, int data_len);
/* */ 
std::string base64_decode(const char *data, int data_len);

#endif // __CKCommon_H__