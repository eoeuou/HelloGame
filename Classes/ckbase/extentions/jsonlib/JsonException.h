//
//  JsonException.h
//  JsonLib
//  Json 解析异常 
//  Created by wangxin on 13-4-10.
//  Copyright (c) 2013年 wangxin. All rights reserved. 
//

#ifndef __JsonLib__JsonException__
#define __JsonLib__JsonException__

#include <iostream>
#include <exception>
#include <string>
using namespace std;

class JsonException :exception {
    
public:
    ~JsonException() throw();
    JsonException(const char*);
    const char* what() const throw();
private:
    string error_msg;
};

#endif /* defined(__JsonLib__JsonException__) */
