#ifndef AVRO_PREPROCESSOR_H
#define AVRO_PREPROCESSOR_H

#include "avro_typedefs.h"
#include "Platform.h"
#include <iostream>


#ifdef A_W32
#include <windows.h>
#include "win32_Platform.h"
#endif

#ifdef AVRO_DEBUG
#define CHECK_NAN 1
#define AVRO_ASSERT(expr, strmessage) if(expr){} \
		else{ \
			char buffer [512]; \
			sprintf_s(buffer, sizeof(buffer), "%s Failed Assertion at: %s ln:%d :: %s\n", \
			(#expr), __FILE__, __LINE__, (strmessage));\
			OutputDebugStringA(buffer);\
			AvroDebugBreak();\
		} 
				
#elif AVRO_PROFILE
#define AVRO_ASSERT(expr, strmessage) if((expr)){}else{ \
			char buffer [512]; \
			sprintf_s(buffer, sizeof(buffer), "%s Failed Assertion at: %s ln:%d :: %s\n", \
			(#expr), __FILE__, __LINE__, (strmessage));\
			OutputDebugStringA(buffer);\
			AvroDebugBreak();\\
}  

#elif AVRO_RELEASE
#define AVRO_ASSERT(expr, strmessage){}
#elif AVRO_PRODUCTION
#define AVRO_ASSERT(expr, strmessage){}
#endif




#endif