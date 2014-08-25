#ifndef __CKCommon_H__
#define __CKCommon_H__

#include "cocos2d.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocos-ext.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace cocostudio;
using namespace CocosDenshion;

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
public: virtual void set##funName(varType& var){ this->setValue(varName,Value(var));}\
public: virtual varType get##funName(void) const { return this->getValue(varName).asString();}

#define CK_SYNTHESIZE_MODEL_INTEGER(varType,varName, funName)\
public: virtual void set##funName(varType& var){ this->setValue(varName,Value(var));}\
public: virtual varType get##funName(void) const { return this->getValue(varName).asInt();}

#define CK_SYNTHESIZE_MODEL_BOOLEAN(varType,varName, funName)\
public: virtual void set##funName(varType& var){ this->setValue(varName,Value(var));}\
public: virtual varType get##funName(void) const { return this->getValue(varName).asBool();}

#define CK_SYNTHESIZE_MODEL_FLOAT(varType,varName, funName)\
public: virtual void set##funName(varType& var){ this->setValue(varName,Value(var));}\
public: virtual varType get##funName(void) const { return this->getValue(varName).asFloat();}

#define CK_SYNTHESIZE_MODEL_DOUBLE(varType,varName, funName)\
public: virtual void set##funName(varType& var){ this->setValue(varName,Value(var));}\
public: virtual varType get##funName(void) const { return this->getValue(varName).asDouble();}

//CKJSONMODEL 变量返回值
#define CK_SYNTHESIZE_JSONMODEL_STRING(varType,varName, funName)\
public: varType get##funName(void) { return (*this)[varName].GetString();}

#define CK_SYNTHESIZE_JSONMODEL_INTEGER(varType,varName, funName)\
public: varType get##funName(void) { return (*this)[varName].GetInt();}

#define CK_SYNTHESIZE_JSONMODEL_BOOLEAN(varType,varName, funName)\
public: varType get##funName(void) { return (*this)[varName].GetBool();}

#define CK_SYNTHESIZE_JSONMODEL_FLOAT(varType,varName, funName)\
public: varType get##funName(void) { return (*this)[varName].GetDouble();}

#define CK_SYNTHESIZE_JSONMODEL_DOUBLE(varType,varName, funName)\
public: varType get##funName(void) { return (*this)[varName].GetDouble();}

//convert somethine
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
{\
    const char* value = DICTOOL->getStringValue_json(doc,key.c_str());\
	model->setValue(key.c_str(),Value(value));\
	log("key=%s,value=%s",key.c_str(),value);\
	log("info=%s",model->getInfo().c_str());\
}\

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

cocos2d::Point nodeLeftPoint(Node* node);
cocos2d::Point nodeRightPoint(Node* node);
cocos2d::Point nodeTopPoint(Node* node);
cocos2d::Point nodeBottomPoint(Node* node);
cocos2d::Point nodeCenterPoint(Node* node);
cocos2d::Point nodeLeftTopPoint(Node* node);
cocos2d::Point nodeRightTopPoint(Node* node);
cocos2d::Point nodeLeftBottomPoint(Node* node);
cocos2d::Point nodeRightBottomPoint(Node* node);

/* */
std::string base64_encode(const char* data, int data_len);
/* */ 
std::string base64_decode(const char *data, int data_len);

#define CKFontSize TITLE_FONT_SIZE
#define CKFontName "Marker Felt"
#define CKFontNamePath "fonts/Marker Felt.ttf"

#endif // __CKCommon_H__