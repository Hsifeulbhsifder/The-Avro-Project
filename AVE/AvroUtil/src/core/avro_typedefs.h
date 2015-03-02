#ifndef AVRO_TYPE_DEFINITIONS_H
#define AVRO_TYPE_DEFINITIONS_H
#include "Platform.h"


#ifdef A_W32
#include <xmmintrin.h>
typedef unsigned __int8 B8;

typedef signed __int8 I8;
typedef signed __int16 I16;
typedef signed __int32 I32;
typedef signed __int64 I64;

typedef unsigned __int8 U8;
typedef unsigned __int16 U16;
typedef unsigned __int32 U32;
typedef unsigned __int64 U64;

typedef float F32;
typedef double F64;

typedef __m128 VF32;
#elif A_UNX

typedef unsigned __int8 B8;

typedef signed char			I8;
typedef signed short		I16;
typedef signed int			I32;
typedef signed long long	I64;

typedef unsigned char		U8;
typedef unsigned short		U16;
typedef unsigned int		U32;
typedef unsigned long long	U64;

typedef float				F32;
typedef double				F64;
//add SSE intrinsic
#endif

#define lscope static
#define glob static
#define intern static
#define scast static_cast
#define rcast reinterpret_cast

#endif