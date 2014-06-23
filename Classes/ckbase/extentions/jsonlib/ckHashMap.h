//
//  ckHashMap.h
//  Appark get hash_map mod from VS or GNU cpp Compiler
//  根据不同编译器实现的hash_map名称不同，而进行自适应 
//  Created by Wangxin on 13-3-28.
//  Copyright (c) 2013年 Wangxin. All rights reserved. 
//

#ifndef Demo2_ckHashMap_h
#define Demo2_ckHashMap_h

#include <iostream>
using namespace std;

#if defined(_MSC_VER)
// 微软编译器实现的hash_map 
#include <hash_map>
using namespace stdext;
#else

#ifdef IOS_PLATFORM    
// 苹果上面可以用的hash_map (gcc标准库) 
#include <tr1/unordered_map>
using namespace std::tr1;
#define hash_map unordered_map
#endif

#ifndef IOS_PLATFORM
//安卓上的hash_map(gcc google 库) 
#include <hash_map>
using namespace std;
#endif

#endif


#endif
