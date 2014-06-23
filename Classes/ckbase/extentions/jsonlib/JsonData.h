//
//  JsonData.h
//  ApparkTest
//
//  Created by wangxin on 13-4-2.
//
//

#ifndef __ApparkTest__JsonData__
#define __ApparkTest__JsonData__

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include "JsonNode.h"
#include "ckHashMap.h"
#include "JsonException.h"

using namespace std;

class JsonData {
    
    
public:
    
    /**
     * 从另一个jsonnode中克隆数据
     * @param 被克隆的jsonnode
     */
    void operator=(JsonData & _jdata);
                            
    /**
     * 解析json字符串  
     * @param 需要被解析的字符串 
     */
    virtual void operator<<(const unsigned char *)  throw(JsonException);
    
    /**
     * 解析json字符串  
     * @param 需要被解析的字符串 
     */
    virtual void operator<<(std::string str) throw(JsonException);

	virtual void operator<<(JsonNode&);
    /**
     * 解析json字符串 
     * @param 需要被解析的字符串 
     */
    virtual void operator<<(const char*) throw(JsonException);
    
    /**
     * 解析json字符串  
     * @param 需要被解析的字符串 
     */
    virtual void decode(string) throw(JsonException);
    /**
     * 解析json字符串  
     * @param 需要被解析的字符串 
     */
    virtual void decode(const char*) throw(JsonException);
    /**
     * 解析json字符串  
     * @param 需要被解析的字符串 
     */
    virtual void decode(const unsigned char*) throw(JsonException);
    /** 
     * 编码json对象 
     * @param 输出的字符串 
     */
    virtual void encode(string &);
    /**
     * 编码json对象 
     * @param 输出的字符串 
     */
    virtual void encode(char* &);
    /**
     * 编码json对象 
     * @param 输出的字符串 
     */
    virtual void encodeUnsigned(unsigned char* &);
    /**
     * 编码json对象 
     * @param 输出的字符串 
     */
    virtual void operator>>(string &);
    /**
     * 编码json对象 
     * @param 输出的字符串 
     */
    virtual void operator>>(char* &);
    /**
     * 编码json对象 
     * @param 输出的字符串 
     */
    virtual void operator>>(unsigned char* &);
    /**
     * 编码json对象 
     * @param 输出的字符串 
     */
    
    std::string toString();
    
    JsonData();
    ~JsonData();
    /**
     * 获取以数组为存储结构的json子节点的JsonNode 
     * @param 数字key 
     */
    JsonNode& operator[](int);
    /**
     * 获取以键值对为存储结构的json子节点的JsonNode 
     * @param 字符串key 
     */
    JsonNode& operator[](string);
    /**
     * 获取以键值对为存储结构的json子节点的JsonNode 
     * @param 字符串key 
     */
    JsonNode& operator[](const char *);
    /**
     * 获得第一层子节点的个数 
     */
    size_t size();
    /**
     * 判断字符串是否是json字符串
     */
    bool isJson(std::string json_str);
    
    bool isJson(char * c_str);
    /**
     * 获得根节点的key 
     */
    vector<string> getKeys();
    
    virtual void clear();
private:
    static const int ONE_STRING_DEFAULT_LENGTH  = 50;
    string lostStrValue;
    string lostStrKey;
    bool lostIsKey;
    bool lostVstart;
    bool lostIsString;
    
    JsonNode* _m_root;
    stack<JsonNode*> _m_stack;
    stack<string> _m_key_stack;
    /**
     * 错误处理，打印错误文字，截断解码 
     */
    JsonException formatError(const unsigned char *);
    virtual void addNode(JsonNode & node,const char* value);
};

#endif /* defined(__ApparkTest__JsonData__) */
