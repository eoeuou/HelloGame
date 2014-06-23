//
//  JsonNode.h
//  ApparkTest
//
//  Created by wangxin on 13-4-2.
//
//

#ifndef __ApparkTest__JsonNode__
#define __ApparkTest__JsonNode__

using namespace std;
#include <iostream>

#include "ckHashMap.h"
#include "CStrUtils.h"

#include <string>
#include <stdio.h>
#include <vector>
#include <stack>

class JsonNode{
public:
    enum VALUE_TYPE{   
        INT, // 整形 
        LONG, // 长整形 
        FLOAT, // 浮点数 
        DOUBLE, // 双精度浮点数  
        VECTOR, // 数组  
        HASH_MAP, // 键值对  
        STRING, // 字符串 
        BOOLEAN, // 对错值 
        NIL = 999,
    };
    
    VALUE_TYPE m_value_type; // 数据类型 
    
    JsonNode();
    JsonNode(void*);
    ~JsonNode();
    // 获得节点内数据个数，只对数组和键值对对象有效 
    size_t size(); 
    // 清空节点内数据 
    void clear();
    // 获得以键值对为储存模式的子节点 
    JsonNode& operator[](const char*);
    // 获得以键值对为存储模式的子节点 
    JsonNode& operator[](string);
    // 获得以数组模式储存的子节点 
    JsonNode& operator[](int);
    
    // 获得以键值对为储存模式的子节点 
    JsonNode getChild(string);
    // 获得以数组模式储存的子节点 
    JsonNode getChild(int);
    // 添加以数组模式存储的数据的子节点到制定的索引位置上 
    void addChild(JsonNode * node,int index);
    // 添加以数组模式储存的数据的子节点，到数组末尾 
    void addChild(JsonNode * node);
    // 添加以键值对模式储存的数据的子节点 
    void addChild(JsonNode * node,string key); 
    // 比较两个节点是否相等
    bool operator==(const JsonNode &);
    // 将整个键值对组赋值给节点 
    void operator=(hash_map<string, JsonNode*>*);
    // 将整个数组对象赋值给节点 
    void operator=(vector<JsonNode*>*);
    // 将整形赋值给节点 
    void operator=(int);
    // 将长整形赋值给节点 
    void operator=(long);
    // 将小数赋值给节点 
    void operator=(float);
    // 将双精度浮点数赋值给节点 
    void operator=(double); 
    // 将字符串赋值给节点 
    void operator=(const char*);
    // 将对错值赋值给节点 
    void operator=(bool);
    // 将字符串赋值给节点  
    void operator=(string);
    // 判断节点是不是空 
    bool isEmpty();
    // 判断节点是否有子节点 
    bool hasChild();
    // 判断节点是不是有str名称的子节点 
    bool hasChild(string str);
    // 判断节点是不是有c_str名称的子节点 
    bool hasChild(const char* c_str);
    // 判断节点是不是有index索引的子节点 
    bool hasChild(int index);
    vector<string> getKeys();
    
    vector<int> &getBaseIntArray();
    vector<float> &getBaseFlaotArray();
    vector<long> &getBaseLongArray();
    vector<bool> &getBaseBoolArray();
    vector<double> &getBaseDoubleArray();
    vector<string> &getBaseStringArray();
    vector<char*> &getBaseCStrArray();
     
    bool isNull(); // 判断节点是不是不存在 
    bool getBoolValue(); 
    bool getBoolValue(bool); // 默认值 
    int getIntValue();
    int getIntValue(int); // 默认值 
    long getLongValue();
    long getLongValue(long); // 默认值 
    float getFloatValue();
    float getFloatValue(float); // 默认值 
    double getDoubleValue();
    double getDoubleValue(double); // 默认值 
    char* getCharptrValue();
    char* getCharptrValue(const char*); // 默认值 
    string getStringValue();
    string getStringValue(const char*); // 默认值 
    string getStringValue(string); // 默认值  
    vector<string> getKeysArr();
    void setNodeName(string);
    string getNodeName();
    JsonNode * getParentNode(); // 获得父节点 
    bool is_coded;
    static JsonNode * emptyNode(); // 获得空节点 
    /**
     * 将json节点解析成字符串 
     */
    std::string toString();
private:
    union U_data {
        float                           f;
        double                          d;
        int                             i;
        long                            l;
        char *                          c;
        bool                            b;
        hash_map<string, JsonNode*>*    h;
        vector<JsonNode*>*              v;
    };
    
    JsonNode * addMeToParent();
    JsonNode * _m_parentNode; // 父节点 
    string str_node_name; // 节点名称 
    int _m_data_length; // 数据大小 
    U_data _m_data; // 数据值 
    string _parent_key; // 父节点中的自己的key 
    int _parent_index; // 父节点中自己的索引 
    static JsonNode * _s_empty_node; // 空节点 
    
};


#endif /* defined(__ApparkTest__JsonNode__) */
