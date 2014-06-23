//
//  main.cpp
//  test_cpp
//
//  Created by wangxin on 13-9-2.
//  Copyright (c) 2013年 wangxin. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "JsonData.h"
#include <strstream>
using namespace std;

int main(int argc, const char * argv[])
{
    string str = "{\"state\":1,\"data\":{\"un\":\"Ccc\",\"coco\":\"13621025230\",\"ph\":\"\",\"tkn\":\"e2b921ad60160ed7a626c8d2eddaa8b5ea6a44bd9e9a8710055084c3bc1fbdbb\",\"ava\":\"\ \"}}";
//    JsonData j_data;
//    j_data<<str;
//    cout << j_data["status"].getIntValue() << endl;
//    vector<string> vec =  j_data["opponent"].getKeys();
//    for (int i = 0; i < vec.size(); ++i) {
//        cout << i << ":" << vec[i] << endl;
//    }
//    
//    cout << "toString:" << j_data.toString() << endl;
//    string st1r1 ;
//    j_data>>st1r1;
//    cout << ">>" << st1r1 << endl;
//    printf("%d\n",'0');
//    printf("%d\n",'1');
//    printf("%d\n",'2');
//    printf("%d\n",'3');
//    printf("%d\n",'4');
//    printf("%d\n",'5');
//    printf("%d\n",'6');
//    printf("%d\n",'7');
//    printf("%d\n",'8');
//    printf("%d\n",'9');
//    JsonNode n;
//    n = "1234a";
//    int i = n.getIntValue();
//    printf("%d\n",i);
//    string str = "{\"status\":\"a\",\"opponent\":[1,2,3]}";
    JsonData j_data;
    j_data<<str;
//    cout << j_data["data"]["ph"].getStringValue() << endl;
//    cout << j_data.toString() << endl;
    JsonData j_data2;
//    j_data2.operator=(j_data);
    j_data2 = j_data;
    j_data2 << j_data.toString();
    cout << j_data.toString() << endl;
    cout << j_data2.toString() << endl;
    
}

