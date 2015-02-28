#ifndef AVRO_MATH_H
#define AVRO_MATH_H
#include "avro_typedefs.h"

#ifdef AVRO_DEBUG
#elif AVRO_PROFILE
#elif AVRO_RELEASE
#elif AVRO_PRODUCTION
#endif

#ifdef A_W32
#include "win32_AvroMath.h"
#endif

//CONSTANTS
#define PI (3.1415926535897932f)
#define E  (2.71828182845904523526f)
#define EZERO (1.e-8f)
#define EPSILON (1.e-4f)


//FUNCTIONS
namespace ave{
	template<class T>
	INLINEFORCE static T Square(const T a){
		return a*a;
	}

	INLINEFORCE static F32 Sqrt(const F32 value){ return sqrtf(value); }

	INLINEFORCE static F32 Abs(const F32 value){
		return fabsf(value);
	}

	template<class T>
	INLINEFORCE static T Max(const T a, const T b){
		return (a >= b) ? a : b;
	}

	template<class T>
	INLINEFORCE static T Min(const T a, const T b){
		return (a <= b) ? a : b;
	}

	template<class T>
	INLINEFORCE static T Clamp(const T a, const T min, const T max){
		return a<min ? min : a>max ? a : max;
	}

	I32 factorial(I32 n);
	F32 lerp(F32 a, F32 b, F32 alpha);
}
#endif