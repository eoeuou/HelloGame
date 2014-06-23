//
//  CStrUtils.cpp
//  JsonLib
//
//  Created by wangxin on 13-4-8.
//  Copyright (c) 2013年 wangxin. All rights reserved. 
//

#include "CStrUtils.h"
// 转换字符串为大写 
char* c_str_2_up(const char* c_ptr){
    int size = strlen(c_ptr);
    char * _c = (char*)malloc(size+1);
    memset(_c, 0, size+1);
    char * res_c = _c;
    if (c_ptr != NULL) {
        for (int i = 0 ; i < size; ++i) {
            if( *c_ptr >='a' && *c_ptr <= 'z'){
                *_c = *c_ptr - 32;
            }
            else{
                *_c = *c_ptr;
            }
            ++_c;
            ++c_ptr;
        }
    }
    return res_c;
}
char* c_str_2_up(string str){
    return c_str_2_up(str.c_str());
}
string str_2_up(const char* _c){
    char * p_c = c_str_2_up(_c);
    string str = p_c;
    free(p_c);
    return str;
}
string str_2_up(string str){
    char* c = c_str_2_up(str);
    str = c;
    free(c);
    return str;
}

// 转换字符串为小写 
char* c_str_2_low(const char* c_ptr){
    int size = strlen(c_ptr);
    char * _c = (char*)malloc(size+1);
    memset(_c, 0, size+1);
    char * res_c = _c;
    if (c_ptr != NULL) {
        for (int i = 0 ; i < size; ++i) {
            if( *c_ptr >='A' && *c_ptr <= 'Z'){
                *_c = (char)(*c_ptr + 32);            }
            else{
                *_c = *c_ptr;
            }
            ++_c;
            ++c_ptr;
        }
    }
    return res_c;
}
char* c_str_2_low(string str){
    return c_str_2_low(str.c_str());
}
string str_2_low(const char* _c){
    string str = "";
    char * p_c = c_str_2_low(_c);
    str = p_c;
    free(p_c);
    return str;
}
string str_2_low(string str){
    char* c = c_str_2_low(str);
    str = c;
    free(c);
    return str;
}