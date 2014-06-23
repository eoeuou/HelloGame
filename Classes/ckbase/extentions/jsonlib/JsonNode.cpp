//
//  JsonNode.cpp
//  ApparkTest
//
//  Created by wangxin on 13-4-2. 
//
//

#include "JsonNode.h"
JsonNode * JsonNode::_s_empty_node = NULL;
JsonNode::JsonNode(){
    //_m_data = NULL;
    m_value_type = NIL;
    _m_data_length = 0;
    str_node_name = "";
    is_coded = false;
    _m_parentNode = NULL;
    _parent_key = "";
    _parent_index = -1;
}
JsonNode::JsonNode(void*){
    JsonNode();
}
JsonNode::~JsonNode(){
    // 如果是键值对数据，则便利键值对递归析构所有子节点 
    if (m_value_type == HASH_MAP) {
        hash_map<string, JsonNode*>::iterator _it = _m_data.h->begin();
        while (_it != _m_data.h->end()) {
            if (_it->second != NULL) {
                delete _it->second;
            }
            ++_it;
        }
        delete _m_data.h;
        _m_data.h = NULL;
    }
    // 如果是数组数据，则遍历析构所有子节点 
    else if (m_value_type == VECTOR){
        for (int i=0; i<_m_data.v->size();++i) {
            delete (*_m_data.v)[i];
        }
        delete _m_data.v;
        _m_data.v = NULL;
    }
    // 如果是字符串数据，则释放字符串 
    else if (m_value_type == STRING){
        free(_m_data.c);
    }
    
}

bool JsonNode::isEmpty(){
    // 判断空 只要判断这个节点内是否有数据操作 
    if (m_value_type == NIL) {
        return true;
    }
    else{
        return false;
    }
}

bool JsonNode::hasChild(string str){
    bool res = false;
    if (m_value_type == HASH_MAP && _m_data.h->find(str) != _m_data.h->end()) {
        res = true;
    }
    return res;
}

bool JsonNode::hasChild(const char* c_str){
    string str = c_str;
    return hasChild(str);
}

bool JsonNode::hasChild(int index){
    bool res = false;
    if (m_value_type == VECTOR && (*_m_data.v)[index] != NULL) {
        res = true;
    }
    return res;
}

bool JsonNode::hasChild(){
    bool res = false;
    // 只有键值对和数组数据才会有子节点，只要所以判断他们的长度来确定是否有子节点 
    if ( (m_value_type == HASH_MAP && _m_data.h->size() > 0) || ( m_value_type == VECTOR && _m_data.v->size() > 0)) {
        res = true;
    }
    return res;
}
int JsonNode::getIntValue(int def){
    int res = def;
    // 整形数据直接返回，小数和长整型进行类型转换，其他类型数据返回初始值 
    if (m_value_type == INT) {
        res = _m_data.i;
    }
    else if (m_value_type == FLOAT){
        res = (int)_m_data.f;
    }
    else if(m_value_type == DOUBLE){
        res = (int)_m_data.d;
    }
    else if(m_value_type == LONG){
        res = (int)_m_data.l;
    }
    else if(m_value_type == STRING){
        res = 0;
        int x = 1;
        size_t l = strlen(_m_data.c);
        for(int i=(int)l-1;i>=0;--i){
            if(_m_data.c[i]  >= 48 && _m_data.c[i] <= 57){
                res += (_m_data.c[i]-48)*x;
                x *= 10;
            }
            else{
                res = def;
                break;
            }
        }
        
    }
    return res;
}

int JsonNode::getIntValue(){
    return getIntValue(0);
}

vector<string> JsonNode::getKeysArr(){
    vector<string> vec;
    if (m_value_type == HASH_MAP) {
        hash_map<string,JsonNode*>::iterator _it = _m_data.h->begin();
        while (_it != _m_data.h->end()) {
            vec.push_back(_it->first);
            ++_it;
        }
    }
    return vec;
}

JsonNode * JsonNode::getParentNode(){
    return _m_parentNode;
}

long JsonNode::getLongValue(){
    long res = 0l;
    // 整形数据直接返回，小数和长整型进行类型转换，其他类型数据返回初始值 
    if (m_value_type == LONG) {
        res = _m_data.l;
    }
    else if (m_value_type == FLOAT){
        res = (long)_m_data.f;
    }
    else if(m_value_type == DOUBLE){
        res = (long)_m_data.d;
    }

    else if (m_value_type == INT){
        res = (long)_m_data.i;
    }
    return res;
}

size_t JsonNode::size(){
    size_t size = 1;
    // 键值对数据和书组数据获得真实长度，其他数据长度始终为1 
    if (m_value_type == HASH_MAP) {
        size = _m_data.h->size();
    }
    else if (m_value_type == VECTOR){
        size = _m_data.v->size();
    }
    else if (m_value_type == NIL){
        size = 0;
    }
    return size;
}

void JsonNode::clear(){
    // 清空键值对数据和数组数据 
    if (m_value_type == HASH_MAP) {
        _m_data.h->clear();
    }
    else if (m_value_type == VECTOR){
        _m_data.v->clear();
    }
}

bool JsonNode::getBoolValue(bool b){
    bool res = b;
    // 真假值直接返回，整形，长整形，进行数据转换，字符串判断字符内容为任意形式的true则为真，否则为假 
    if (m_value_type == BOOLEAN) {
        res = _m_data.b;
    }
    else if (m_value_type == INT){
        res = (bool)_m_data.i;
    }
    else if (m_value_type == LONG){
        res = (bool)_m_data.l;
    }
    else if (m_value_type == STRING){
        if (strcmp(c_str_2_low(_m_data.c), "true") == 0) {
            res = true;
        }
        else{
            res = false;
        }
    }
    return res;
}

vector<int> &JsonNode::getBaseIntArray(){
    // 获得基础数组，将JsonNode的vector解释成int[] 
    vector<int>* vec = new vector<int>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getIntValue());
        }
    }
    return *vec;
}
vector<float> &JsonNode::getBaseFlaotArray(){
    // 获得基础数组，将JsonNode的vector解释成float[] 
    vector<float>* vec = new vector<float>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getFloatValue());
        }
    }
    return *vec;
}
vector<long> &JsonNode::getBaseLongArray(){
    // 获得基础数组，将JsonNode的vector解释成long[] 
    vector<long>* vec = new vector<long>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getLongValue());
        }
    }
    return *vec;
}
vector<bool> &JsonNode::getBaseBoolArray(){
    // 获得基础数组，将JsonNode的vector解释成bool[] 
    vector<bool>* vec = new vector<bool>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getBoolValue());
        }
    }
    return *vec;
}
vector<double> &JsonNode::getBaseDoubleArray(){
    // 获得基础数组，将JsonNode的vector解释成Double[] 
    vector<double>* vec = new vector<double>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getDoubleValue());
        }
    }
    return *vec;
}
vector<string> &JsonNode::getBaseStringArray(){
    // 获得基础数组，将JsonNode的vector解释成string[] 
    vector<string>* vec = new vector<string>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getStringValue());
        }
    }
    return *vec;
}
vector<char*> &JsonNode::getBaseCStrArray(){
    // 获得基础数组，将JsonNode的vector解释成char*[] 
    vector<char*>* vec = new vector<char*>();
    if (m_value_type == VECTOR) {
        for (int i = 0; i < this->size(); ++i) {
            vec->push_back((*this)[i].getCharptrValue());
        }
    }
    return *vec;
}

bool JsonNode::isNull(){
    // 等于空节点或者节点为定义数据 为真 
    if (m_value_type == NIL) {
        return true;
    }
    else{
        return false;
    }
}

bool JsonNode::getBoolValue(){
    return getBoolValue(false);
}

double JsonNode::getDoubleValue(){
    return getDoubleValue(0.0);
}

double JsonNode::getDoubleValue(double d){
    double res = d;
    // 强制转换点精度浮点数 整形 长整型 其他数据返货默认值 
    if (m_value_type == DOUBLE) {
        res = _m_data.d;
    }
    else if (m_value_type == FLOAT){
        res = (double)_m_data.f;
    }
    else if (m_value_type == INT){
        res = (double)_m_data.i;
    }
    else if (m_value_type == LONG){
        res = (double)_m_data.l;
    }
    return res;
}

float JsonNode::getFloatValue(){
    return getFloatValue(0.0f);
}

float JsonNode::getFloatValue(float f){
    float res = f;
    // 强制转换双精度浮点数 整形 长整型 其他数据返货默认值 
    if (m_value_type == FLOAT) {
        res = _m_data.f;
    }
    else if (m_value_type == DOUBLE){
        res = (float)_m_data.d;
    }
    else if (m_value_type == INT){
        res = (float)_m_data.i;
    }
    else if (m_value_type == LONG){
        res = (float)_m_data.l;
    }
    return res;
}

string JsonNode::getStringValue(const char * c_str){
    string res = c_str;
    char* tmp = NULL;
    char* format_str = NULL;
    if (m_value_type == STRING) {
        if (_m_data.c != NULL && strlen(_m_data.c) > 0) {
            res = _m_data.c;
        }
    }
    else if (m_value_type == HASH_MAP){
        res = "HASH_MAP";
    }
    else if (m_value_type == VECTOR){
        res = "ARRAY";
    }
    else if (m_value_type == BOOLEAN){
        if (_m_data.b == true) {
            res = "TRUE";
        }
        else{
            res = "FALSE";
        }
    }
    else{
        tmp = (char*)malloc(20);
        format_str = (char*)malloc(4);
        memset(tmp, 0, 20);
        memset(format_str, 0, 3);
        if (m_value_type == INT) {
            sprintf(format_str, "%s","%d");
            sprintf(tmp, format_str,_m_data.i);
        }
        else if (m_value_type == LONG){
            sprintf(format_str, "%s","%ld");
            sprintf(tmp, format_str,_m_data.l);
        }
        else if (m_value_type == FLOAT){
            sprintf(format_str, "%s","%f");
            sprintf(tmp, format_str,_m_data.f);
        }
        else if (m_value_type == DOUBLE){
            sprintf(format_str, "%s","%f");
            sprintf(tmp, format_str,_m_data.d);
        }
        res = tmp;
        free(tmp);
        free(format_str);
        tmp = NULL;
        format_str = NULL;
    }
    return res;
}

string JsonNode::getStringValue(string str){
    return getStringValue(str.c_str());
}

string JsonNode::getStringValue(){
    return getStringValue("");
}


char* JsonNode::getCharptrValue(const char * _c){
    const char * c_c_str = getStringValue(_c).c_str();
    int size = strlen(c_c_str)+1;
    char * c_str = (char*)malloc(size);
    memset(c_str, 0, size);
    sprintf(c_str, "%s",c_c_str);
    return c_str;
}

char* JsonNode::getCharptrValue(){
    return getCharptrValue("");
}



bool JsonNode::operator==(const JsonNode & node){
    bool res = false;
    if (m_value_type == node.m_value_type) {
        // 数字判断值，对象判断指针，字符串判断字 
        switch (m_value_type) {
            case STRING:
                if (strcmp(_m_data.c, node._m_data.c) == 0) {
                    res = true;
                }
                break;
            case INT:
                if (_m_data.i == node._m_data.i) {
                    res = true;
                }
                break;
            case DOUBLE:
                if (_m_data.d == node._m_data.d) {
                    res = true;
                }
                break;
            case LONG:
                if (_m_data.l == node._m_data.l) {
                    res =true;
                }
                break;
            case FLOAT:
                if (_m_data.f == node._m_data.f) {
                    res = true;
                }
                break;
            case HASH_MAP:
                if (_m_data.h == node._m_data.h) {
                    res = true;
                }
                break;
            case VECTOR:
                if (_m_data.v == node._m_data.v) {
                    res = true;
                }
                break;
            default:
                break;
        }
    }
    return res;
}

string JsonNode::getNodeName(){
    return str_node_name;
}

void JsonNode::setNodeName(string str){
    this->str_node_name = this->str_node_name + "::" + str;
    if (m_value_type == HASH_MAP) {
        hash_map<string, JsonNode*>::iterator _it = _m_data.h->begin();
        while (_it != _m_data.h->end()) {
            _it->second->setNodeName(str);
            ++_it;
        }
    }
    else if (m_value_type == VECTOR){
        for (int i=0; i<_m_data.v->size();++i) {
            (*_m_data.v)[i]->setNodeName(str);
        }
    }
}

void JsonNode::addChild(JsonNode *node,string key){
    if (m_value_type == HASH_MAP) {
        node->_m_parentNode = this;
        node->_parent_key = key;
        (*_m_data.h)[key]=node;
    }
}

void JsonNode::addChild( JsonNode *node, int index){
    if (m_value_type == VECTOR) {
        node->_m_parentNode = this;
        node->_parent_index = this->size();
        if (index < _m_data.v->size()) {
            _m_data.v->push_back(_m_data.v->at(_m_data.v->size()-1));
            for (int i = _m_data.v->size(); i > index; --i) {
                (*_m_data.v)[i]->_parent_index = i-1;
                (*_m_data.v)[i] = (*_m_data.v)[i-1];
            }
            node->_parent_index = index;
            (*_m_data.v)[index] =  node;
        }
        else{
            _m_data.v->push_back(node);
        }
    }
}

void JsonNode::addChild(JsonNode *node){
    if (m_value_type == VECTOR) {
        node->_m_parentNode = this;
        node->_parent_index = this->size();
        _m_data.v->push_back(node);
    }
}
JsonNode & JsonNode::operator[](const char * c){
    string str;
    str = c;
    return operator[](str);
}

JsonNode & JsonNode::operator[](string str){
    if (m_value_type == NIL){
        m_value_type = HASH_MAP;
        _m_data.h = new hash_map<string,JsonNode*>();
    }
    if (m_value_type == HASH_MAP) {
        if (_m_data.h->find(str) == _m_data.h->end()) {
            JsonNode * e_node = new JsonNode();
            this->addChild(e_node, str);
        }
        return *(*_m_data.h)[str];
    }
    return  *emptyNode();
    
}

std::string JsonNode::toString()
{   
    std::string res_str = "";
    if (m_value_type == VECTOR) {
        res_str += "[";
        for(int i=0 ;i < _m_data.v->size() ; ++i){
            if(i != 0){
                res_str+=",";
            }
            res_str+=(*_m_data.v)[i]->toString();
            
        }
        res_str += "]";
    }
    else if (m_value_type == HASH_MAP){
        res_str +="{";
        hash_map<string,JsonNode*>::iterator _it = _m_data.h->begin();
        while (_it != _m_data.h->end()) {
            if(_it != _m_data.h->begin()){
                res_str+=",";
            }
            res_str+="\"";
            res_str+=_it->first;
            res_str+="\"";
            res_str+=":";
            res_str+=_it->second->toString();
            ++_it;
        }
        res_str+="}";
    }
    else{
        if(m_value_type == STRING){
            res_str+="\"";
        }
        res_str+=this->getStringValue("");
        if(m_value_type == STRING){
            res_str+="\"";
        }
    }
    return res_str;
}


JsonNode * JsonNode::emptyNode(){
    if (_s_empty_node == NULL) {
        _s_empty_node = new JsonNode();
    }
    return _s_empty_node;
}

JsonNode & JsonNode::operator[](int key){
    if (m_value_type == NIL) {
        m_value_type = VECTOR;
        _m_data.v = new vector<JsonNode*>();
    }
    if (m_value_type == VECTOR) {
        if (_m_data.v->size() <= key) {
            JsonNode * e_node = new JsonNode();
            this->addChild(e_node);
        }
        return *(*_m_data.v)[key];
    }
    
    
    
//	else
//		if(m_value_type == HASH_MAP){
//		char str[4];
//		memset(str, 0, 4);
//        sprintf(str, "%d\0",key);
//		
//		return this->operator[](str);
//	}
    return *emptyNode();
    
}

void JsonNode::operator=(vector<JsonNode*> * _data){
    m_value_type = VECTOR;
    _m_data.v = _data;
}

vector<string> JsonNode::getKeys(){
    vector<string> keys;
    if(m_value_type == HASH_MAP){
        hash_map<string,JsonNode*>::iterator _it;
        _it = _m_data.h->begin();
        while (_it != _m_data.h->end()) {
            keys.push_back(_it->first);
            _it++;
        }
    }
    return keys;
}
void JsonNode::operator=(hash_map<string, JsonNode *> * _data){
    m_value_type = HASH_MAP;
    _m_data.h = _data;
}

void JsonNode::operator=(bool _data){
    m_value_type = BOOLEAN;
    _m_data.b = _data;
}

void JsonNode::operator=(int _data){
    m_value_type = INT;
    _m_data.i = _data;
}


void JsonNode::operator=(long _data){
    m_value_type = LONG;
    _m_data.l = _data;
}


void JsonNode::operator=(float _data){
    m_value_type = FLOAT;
    _m_data.f= _data;
}

void JsonNode::operator=(double _data){
    m_value_type = DOUBLE;
    _m_data.d = _data;
}

void JsonNode::operator=(const char * _data){
    m_value_type = STRING;
    int size = strlen(_data)+1;
    _m_data.c = (char*)malloc(size);
    memset(_m_data.c, 0, size);
    memcpy(_m_data.c, _data, size-1);
}

void JsonNode::operator=(string _data){
    m_value_type = STRING;
    (*this)=_data.c_str();
}