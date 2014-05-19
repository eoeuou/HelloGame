#ifndef __CKCommon_H__
#define __CKCommon_H__

#include "cocos2d.h"
#include "editor-support\cocostudio\DictionaryHelper.h"

USING_NS_CC;
using namespace std;
using namespace cocostudio;

const char* intToString(const int value);
const char* longToString(const long value);
const char* floatToString(const float value);
const char* doubleToString(const double value);

std::string GBKToUTF8(const std::string& strGBK);

std::wstring UTF8ToUnicode(const char* putf8);

std::string UnicodeToUTF8(const wchar_t* putf8);


bool parseJsonToDocument(const std::string &fileName, rapidjson::Document &doc);

#endif // __CKCommon_H__