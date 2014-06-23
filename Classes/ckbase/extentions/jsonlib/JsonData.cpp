//
//  JsonData.cpp
//  ApparkTest
//
//  Created by wangxin on 13-4-2.
//
//

#include "JsonData.h"


void JsonData::operator=(JsonData & _jdata){
    this->clear();
    this->operator<<(_jdata.toString());
}

JsonData::JsonData(){
    lostStrValue = "";
    lostStrKey = "";
    lostIsKey = false;
    lostIsString = false;
    lostVstart = true;
    // 初始化根节点为数组模式，子节点0为真正的根节点，并将根节点压入节点栈 
    _m_root = new JsonNode();
    vector<JsonNode*> * vec = new vector<JsonNode*>();
    (*_m_root) = vec;
    _m_root->setNodeName("__super_root_");
    _m_stack.push(_m_root);
}

void JsonData::clear(){
    delete _m_root;
    _m_root = NULL;
    // 清空压栈数据 
    while(_m_stack.size() > 0){
        _m_stack.pop();
    }
    
    while(_m_key_stack.size() > 0){
        _m_key_stack.pop();
    }
    
    lostStrValue = "";
    lostStrKey = "";
    lostIsKey = false;
    lostIsString = false;
    lostVstart = true;
    // 初始化根节点为数组模式，子节点0为真正的根节点，并将根节点压入节点栈 
    _m_root = new JsonNode();
    vector<JsonNode*> * vec = new vector<JsonNode*>();
    (*_m_root) = vec;
    _m_root->setNodeName("__super_root_");
    _m_stack.push(_m_root);

}



JsonData::~JsonData(){
    delete _m_root;
    _m_root = NULL;
    // 清空压栈数据 
    while(_m_stack.size() > 0){
        _m_stack.pop();
    }
    
    while(_m_key_stack.size() > 0){
        _m_key_stack.pop();
    }
}

JsonNode & JsonData::operator[](int i){
    return (*_m_root)[0][i];
}

JsonNode & JsonData::operator[](string key){
    return (*_m_root)[0][key];
}

JsonNode & JsonData::operator[](const char * c_str){
    string str = c_str;
    return this->operator[](str);
}

void JsonData::addNode(JsonNode &node, const char *value){
    JsonNode::VALUE_TYPE type = JsonNode::LONG;
    long _int_v = 0;
    long _tmp_int_v = 0;
    double _double_v = 0.0;
    bool isFloat = false;
    const char* _t_str = value;
    double d_p = 1;
    int flag = 1;
    if (*value == '-') {
        flag = -1;
        ++value;
    }
    if (*value == '\0' || ( *value == '0' && *(value+1) != '.' )) { // 优先处理空字符串 如果数字的第一位是0 则处理为字符串 
        type = JsonNode::STRING;
    }
    else{
        while (*value != '\0') {
            if (*value < 58 && *value > 47) {
                if (!isFloat) {
                    _tmp_int_v = _int_v;
                    _int_v = _int_v*10;
                    _int_v += *value - 48;
                    if (_int_v < _tmp_int_v) { // 添加一个新数字后反而比没添加的小 则表示 数字已经越界 
                        type = JsonNode::STRING;
                        break;
                    }
                }
                else{
                    d_p = d_p * 0.1;
                    _double_v += d_p * (*value -48 );
                }
            }
            else if (*value == '.'){
                if (!isFloat) {
                    type = JsonNode::DOUBLE;
                    isFloat = true;
                }
                else{
                    type = JsonNode::STRING;
                    break;
                }
            }
            else{
                type = JsonNode::STRING;
                break;
            }
            ++value;
        }
    }
    
    if (type == JsonNode::STRING) {
        node=_t_str;
    }
    else{
        if (_double_v > 0.0) {
            _double_v = _int_v + _double_v;
            if (_double_v != (float)_double_v) {
                node = _double_v * flag;
            }
            else{
                node = (float)_double_v * flag;
            }
        }
        else{
            if (_int_v != (int)_int_v){
                node = _int_v * flag;
            }
            else{
                node  = (int) _int_v * flag;
            }
        }
    }
}

void JsonData::decode(string str) throw(JsonException){
    decode(str.c_str());
}
void JsonData::decode(const char * c_str) throw(JsonException){
    decode((const unsigned char *) c_str);
}
void JsonData::operator<<(const char* c) throw(JsonException){
    operator<<((const unsigned char *) c);
}
void JsonData::operator<<(JsonNode & node){
	_m_root->addChild(&node);
}
void JsonData::operator<<(const unsigned char * c) throw(JsonException){
    decode(c);
}

void JsonData::operator<<(std::string str) throw(JsonException)
{
    this->operator<<(str.c_str());
}

bool JsonData::isJson(std::string json_str){
    return isJson(json_str.c_str());
}

bool JsonData::isJson(char *c_str){
    if (!c_str) {
        return false;
    }
    bool res = false;
    size_t length = strlen(c_str);
    int start = 0;
//    printf("length:%ld:%d/(%d,%d)||%d/(%d,%d)\n",length,c_str[0],'{','[',c_str[length-1],'}',']');
    while (c_str[start] <= 32  && start<length) { // 32 is space and char befor 32 is Unmeaningful char
        start++;
    }
    while (c_str[length-1] <= 32 && length > start) { // 32 is space and char befor 32 is Unmeaningful char
        length--;
    }
    if((length - start > 2)&&((c_str[start] == '{' && c_str[length-1] == '}')||(c_str[start] == '[' && c_str[length-1] == ']'))){
        res = true;
    }
    return res;
}
void JsonData::decode(const unsigned char * uc) throw(JsonException){
    if(isJson((char*)uc) != true){
        return;
    }
    const unsigned char * c = uc;
    string str_key = lostStrKey; // 将上次遗留的字符串赋值  
    string str_value = lostStrValue;
    bool isKey = lostIsKey; // true 是key false 是value 
    bool isString = lostIsString;
    bool v_start = lostVstart; // 判断现在是在读（字符/数字）还是（数组/对象） true是字符，false是对象 在（对象/数组）结束的时候设置成false，在(对象/数组)结束后的第一个","处设置成true 
    while (*c != '\0') {
//        cout << *c << endl;
        switch (*c) {
            case '[': // 数组开始 
            {
                isKey = false;
                JsonNode * node = NULL;
                node= new JsonNode();
                
                vector<JsonNode*> *vec = new vector<JsonNode*>();
                (*node)=vec;
                _m_stack.push(node);
                break;
            }
            case '{': // 对象开始 
            {
                isKey = true;
                JsonNode * node = new JsonNode();
                hash_map<string, JsonNode  *> * map = new hash_map<string, JsonNode*>();
                (*node)=map;
                _m_stack.push(node);
                break;
            }
            case ']': // 数组结束 
            {
                bool old_vstart = v_start;
                v_start = false;
                // 结束接收一个数据 并存入node中 
                JsonNode * child= _m_stack.top();
                _m_stack.pop();
                // 仅当不是紧跟对象数组结束处理的处理才进行字符处理 
                if (old_vstart == true && str_value.size() > 0) {
                    
                    JsonNode * child_value = new JsonNode();
                    addNode((*child_value), str_value.c_str());
                    char c[4];
                    memset(c, 0, 4);
                    sprintf(c, "%zd",child->size());
                    string n_name = c;
                    child_value->setNodeName(n_name);
                    // 如果是数组 直接写入父节点 
                    child->addChild(child_value);
                }
                
                str_value = ""; // 清空 value 
                // 结束数组 
                // 将当前操作的对象加入Josn对象中 
                JsonNode * parent = _m_stack.top();
                if (parent->m_value_type == JsonNode::HASH_MAP) {
                    string _str_key = _m_key_stack.top();
                    
                    parent->addChild(child,_str_key);
                    child->setNodeName(_str_key);
                    _m_key_stack.pop();
                    isKey = true;
                }
                else if ( parent->m_value_type == JsonNode::VECTOR){
                    char c[4];
                    memset(c, 0, 4);
                    sprintf(c, "%zd",parent->size());
                    parent->addChild(child);
                    string n_name = c;
                    child->setNodeName(n_name);
                }
                break;
                
            }
            case '}': // 对象结束 
            {
                bool old_vstart = v_start;
                v_start = false;
                // 结束接收一个数据 并存入node中 
                JsonNode * child= _m_stack.top();
                _m_stack.pop();
                if (isKey && v_start == true) { // 如果是key 则表示JSON错误 v_start 为true表示刚完成一（数组/对象的解析)忽略格式检查 
                    //throw formatError(c);
                }
                else{ // 如果是value结束 则将数据写入父节点中 
                    // 只当不是紧跟一个这一个对象/数组结束的结束才会处理字符属性 
                    bool char_ok = false;
                    bool is_nullchar = false;
                    if (str_value.size() > 0) {
                        char_ok = true;
                    }
                    else{
                        const unsigned char* _c = c-1;
                        while ( *_c < 32) {
                            if ( _c <= uc) {
                                break;
                            }
                            _c--;
                        }
                        if ( _c > uc && *_c == '"') {
                            char_ok = true;
                            is_nullchar = true;
                        }
                    }
                    if (old_vstart == true&& char_ok) {
                        string _str_key = _m_key_stack.top();
                        JsonNode * child_value = new JsonNode();
                        addNode((*child_value), str_value.c_str());
                        child->addChild(child_value,_str_key);
                        child_value->setNodeName(_str_key);
                        str_value = ""; // 清空 value 
                        
                        _m_key_stack.pop();
                    }
                }
                
                
                
                // 结束对象 
                // 将当前操作的对象加入Josn对象中 
                JsonNode * parent = _m_stack.top();
                if (parent->m_value_type == JsonNode::HASH_MAP) {
//                    if(_m_key_stack.size() > 0){
                        string _str_key = _m_key_stack.top();
                        parent->addChild(child,_str_key);
                        child->setNodeName(_str_key);
                        _m_key_stack.pop();
                        isKey = true;
//                    }
                }
                else if ( parent->m_value_type == JsonNode::VECTOR){
                    char c[4];
                    memset(c, 0, 4);
                    sprintf(c, "%zd",parent->size());
                    string n_name = c;
                    parent->addChild(child);
                    child->setNodeName(n_name);
                    
                }
                break;
            }
            case ',': // , 表示一个数据的开始和结束 
            {
                // 不处理字符串中的,号 
                if (isString) {
                    if (isKey) {
                        str_key += (*c);
                    }
                    else{
                        str_value += (*c);
                    }
                    break;
                }
                // 只当这个在写入的时字符的时候将现在的字符进行处理，因为对象/数组在解析结束的时候已经进行了处理了 
                if (v_start) {
                    // 结束接收一个数据 并存入node中 
                    JsonNode * child= _m_stack.top();
                    JsonNode * child_value = new JsonNode();
                    addNode((*child_value), str_value.c_str());
                    if (child->m_value_type == JsonNode::HASH_MAP) { // 如果是对象，则判断是key还是Value 
                        isKey = true;
                        string _str_key = _m_key_stack.top();
                        child->addChild(child_value,_str_key);
                        child_value->setNodeName(_str_key);
                        _m_key_stack.pop();
                    }
                    else if (child->m_value_type == JsonNode::VECTOR){ // 如果是数组 直接写入父节点 
                        char c[4];
                        memset(c, 0, 4);
                        sprintf(c, "%zd",child->size());
                        child->addChild(child_value);
                        string n_name = c;
                        child_value->setNodeName(n_name);
                    }
                    str_value = ""; // 清空 value 
                }
                else{// 表示对象处理已经完成 
                    v_start = true;
                    
                }
                break;
            }
            case ':':
            {
                if (isString) {
                    if (isKey) {
                        str_key += (*c);
                    }
                    else{
                        str_value += (*c);
                    }
                    break;
                }
                if (isKey == true) { // : 表示前面是key后面是value 
                    isKey = false;
                    _m_key_stack.push(str_key);
                    str_key = "";
                }
                else{
                   //throw formatError(c);
                }
                break;
            }
            case '\'':
            case '"':
            {
                if (isString == false) {
                    isString = true;
                }
                else{
                    isString = false;
                }
                break;
            }
            case ' ': // 忽略空白区 
            case '\r':
            case '\f':
            case '\n':
            case '\t':
            case '\v':
//                if (isString != true && !isKey)  // 只忽略字符串外的空白
                break;

            default:
            {
                if (isKey) {
                    str_key += (*c);
                }
                else{
                    str_value += (*c);
                }
                break;
            }
        }
        ++c;
    }
    lostStrKey = str_key;
    lostStrValue = str_value;
    lostIsKey = isKey;
    lostIsString = isString;
    lostVstart = v_start;
}

void JsonData::operator>>(string & str){
//    encode(str); // 2013-9-2 使用递归模式解析json对象
    str = this->toString();
}

void JsonData::operator>>(char *& c_str){
//    encode(c_str);// 2013-9-2 使用递归模式解析json对象
    string str = this->toString();
    c_str = (char*)malloc(str.length()+1);
    memset(c_str, 0, str.length()+1);
    memcpy(c_str, str.c_str(), str.length());
}

void JsonData::operator>>(unsigned char *& uc_str){
//    encodeUnsigned(uc_str);// 2013-9-2 使用递归模式解析json对象
    string str = this->toString();
    uc_str = (unsigned char*)malloc(str.length()+1);
    memset(uc_str, 0, str.length()+1);
    memcpy(uc_str, str.c_str(), str.length());
}

void JsonData::encode(string & str){
    char * c_str;
    encode(c_str);
    str = c_str;
}

void JsonData::encode(char * & c_str){
    unsigned char *& uc_str = (unsigned char *&)c_str;
    encodeUnsigned(uc_str);
}

void JsonData::encodeUnsigned(unsigned char *& c_str){
    string json_str = "";
    // 清空堆栈内容 
    while (!_m_stack.empty()) {
        _m_stack.pop();
    }
    while (!_m_key_stack.empty()) {
        _m_key_stack.pop();
    }
    _m_stack.push(&(*_m_root)[0]);

    JsonNode * c_node;
    while (!_m_stack.empty()) {
        c_node = _m_stack.top();
        if (c_node->size() == 0) {
            continue;
        }
        
        switch (c_node->m_value_type) {
            case JsonNode::INT:
            case JsonNode::LONG:
            case JsonNode::FLOAT:
            case JsonNode::DOUBLE:
            case JsonNode::BOOLEAN:
            case JsonNode::STRING:
                if (c_node->getParentNode()->m_value_type == JsonNode::HASH_MAP) {
                    json_str += "\"";
                    json_str += _m_key_stack.top();
                    
                    json_str += "\"";
                    _m_key_stack.pop();
                    json_str += ":";
                }
                json_str += "\"";
                json_str += c_node->getStringValue();
                json_str += "\"";
                _m_stack.pop();
                
                if (!_m_stack.top()->is_coded) {
                    json_str += ",";
                }
                break;
            case JsonNode::VECTOR:
                if (!c_node->is_coded) {
                    if (c_node->getParentNode()->m_value_type == JsonNode::HASH_MAP) {
                        json_str += "\"";
                        json_str += _m_key_stack.top();
                        
                        json_str += "\"";
                        _m_key_stack.pop();
                        json_str += ":";
                    }
                    json_str += "[";
                    // 将所以子节点加入到压栈中 
                    for (int i = c_node->size()-1; i>=0; --i) {
                        (*c_node)[i].is_coded = false;
                        _m_stack.push(&(*c_node)[i]);
                    }
                    c_node->is_coded = true;
                }
                else{
                    c_node->is_coded = false;
                    json_str += "]";
                    if (!_m_stack.empty()) {
                        _m_stack.pop();
                                
                        if (!_m_stack.empty()&&_m_stack.top()->is_coded != true) {
                            json_str += ",";
                        }
                    }
                }
                break;
            case JsonNode::HASH_MAP:
                if (c_node->getParentNode()->m_value_type == JsonNode::HASH_MAP /*&& _m_key_stack.size() >0*/) {
                    json_str += "\"";
                    json_str += _m_key_stack.top();
                    
                    json_str += "\"";
                    _m_key_stack.pop();
                    json_str += ":";
                }
                if (!c_node->is_coded) {
                    
                    json_str += "{";
                    vector<string> keys = c_node->getKeysArr();
                    for (int i = keys.size() -1; i >= 0; --i) {
                        (*c_node)[keys[i]].is_coded = false;
                        _m_key_stack.push(keys[i]);
                        
                        _m_stack.push(&(*c_node)[keys[i]]);
                    }
                    c_node->is_coded = true;
                }
                else{
                    c_node->is_coded = false;
                    json_str += "}";
                    
                    if (!_m_stack.empty()) {
                        _m_stack.pop();
                        if (!_m_stack.empty()&&_m_stack.top()->is_coded != true) {
                            json_str += ",";
                        }
                    }
                }
                break;
            default:
                _m_stack.pop();
                break;
        }
        
    }
    c_str = (unsigned char *)malloc(json_str.length()+1);
    memset(c_str, 0, json_str.length());
    sprintf((char*)c_str, "%s",json_str.c_str());
}

size_t JsonData::size()
{
    return (*_m_root)[0].size();
}

vector<string> JsonData::getKeys(){
    return (*_m_root)[0].getKeys();
}

std::string JsonData::toString(){
    return (*_m_root)[0].toString();
}

JsonException JsonData::formatError(const unsigned char * err_str){
    cout << "json format is error" <<err_str <<endl;
    return JsonException((const char*)err_str);
    //exit(0);
}