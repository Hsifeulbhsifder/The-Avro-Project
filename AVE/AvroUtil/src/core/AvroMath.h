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
#define TAU (6.2831853071795865f)
#define E (2.71828182845904523526f)
#define EZERO (1.0e-8f)
#define EPSILON (1.0e-4f)
#define ARCFINITY (3.402e+38f)
#define VECTOR_PROXIMITY_THRESHOLD (0.00002f)
#define VECTOR_PARALLEL_THRESHOLD (0.02f)
#define RAD_TO_DEG (57.2957795f)
#define DEG_TO_RAD (0.0174532925f)


//FUNCTIONS
namespace AU{

	INLINEFORCE glob F32 ToDeg(F32 rad){
		return rad * RAD_TO_DEG;
	}

	INLINEFORCE glob F32 ToRad(F32 deg){
		return deg * DEG_TO_RAD;
	}

	template<class T>
	INLINEFORCE glob T Sq(const T a){
		return a * a;
	}

	template<class T>
	INLINEFORCE glob T Cube(const T a){
		return a * a * a;
	}

	template<class T>
	INLINEFORCE glob T Quart(const T a){
		return a * a * a * a;
	}

	INLINEFORCE glob F32 Sqrt(const F32 value){ return sqrtf(value); }

	INLINEFORCE glob F32 Abs(const F32 value){
		return fabsf(value);
	}

	template<class T>
	INLINEFORCE glob T Max(const T a, const T b){
		return (a >= b) ? a : b;
	}

	template<class T>
	INLINEFORCE glob T Min(const T a, const T b){
		return (a <= b) ? a : b;
	}

	template<class T>
	INLINEFORCE glob T Clamp(const T a, const T min, const T max){
		return a<min ? min : a>max ? a : max;
	}

	INLINEFORCE glob F32 SelectF32(F32 comparand, F32 valueGreaterThanEqualsZero, F32 valueLesserThanZero){
		return comparand >= 0.f ? valueGreaterThanEqualsZero : valueLesserThanZero;
	}

	I32 Factorial(I32 n);
	F32 Lerp(F32 a, F32 b, F32 alpha);

	F32 Sin(F32 x);
	F32 Cos(F32 x);
}
#endif