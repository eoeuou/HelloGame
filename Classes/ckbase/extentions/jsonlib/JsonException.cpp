//
//  JsonException.cpp
//  JsonLib
//
//  Created by wangxin on 13-4-10.
//  Copyright (c) 2013年 wangxin. All rights reserved. 
//

#include "JsonException.h"

JsonException::JsonException(const char* c_str){
    this->error_msg = c_str;
}
JsonException::~JsonException() throw(){
    error_msg.clear();
}
const char* JsonException::what() const throw(){
    return error_msg.c_str();
}