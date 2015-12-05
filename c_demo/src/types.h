/*
 Copyright (c) 20115 richard.hmm

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
/**
 * @file common.h
 * @brief  common data types defintion
 * @author Copyright (C) 2015 Richard.hmm  <sunhyx@gmail.com>
 */

#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

typedef unsigned char Bool;
#ifndef TRUE
#define TRUE			1
#endif
#ifndef FALSE
#define FALSE			0
#endif

#ifndef NULL
#define NULL			((void *)0)
#endif

typedef char INT8;
typedef short INT16;
typedef long INT32;
typedef long long INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;
typedef unsigned long long UINT64;

typedef float FLOAT32;
typedef double FLOAT64;

// attribute
#define __UNUSED        __attribute__ ((unused))
#define __PACKED        __attribute__ ((packed))
#define __ALIGNED(n)    __attribute__ ((aligned(n))
#define __WEAK          __attribute__((weak))

#endif // COMMON_TYPES_H_
