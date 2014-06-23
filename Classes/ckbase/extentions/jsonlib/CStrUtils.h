//
//  CStrUtils.h
//  JsonLib
//
//  Created by wangxin on 13-4-8.
//  Copyright (c) 2013年 wangxin. All rights reserved. 
//

#ifndef __JsonLib__CStrUtils__
#define __JsonLib__CStrUtils__

#include <iostream>
#include <string>
using namespace std;

// 转换字符串为大写 
char* c_str_2_up(const char*);
char* c_str_2_up(string);
string str_2_up(const char*);
string str_2_up(string);

 // 转换字符串为小写 
char* c_str_2_low(const char*);
char* c_str_2_low(string);
string str_2_low(const char*);
string str_2_low(string);

#endif /* defined(__JsonLib__CStrUtils__) */
