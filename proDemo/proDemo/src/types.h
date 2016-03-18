
/** @file types.h
    @brief Data type definition
    @author Copyright (C) 2015 hmm
*/

#ifndef _TYPES_H_
#define _TYPES_H_

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

#define MWANS_ERROR -1
#define MWANS_OK     0
#define MWANS_WARN   1

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
#define __WEAK          __attribute__ ((weak))

#endif /* _TYPES_H_ */
