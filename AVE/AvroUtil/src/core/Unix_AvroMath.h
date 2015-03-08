#ifndef AVRO_UTIL_UNIX_MATH_H
#define AVRO_UTIL_UNIX_MATH_H
#ifdef A_UNX

// SSE intrinsic inverse square root of float
glob INLINEFORCE F32 SqrtInv(F32 f){
	lscope const VF32 three = _mm_set_ss(3.0f);
	lscope const VF32 half = _mm_set_ss(0.5f);
	VF32 Y0, X0, Temp;
	F32 temp;

	Y0 = _mm_set_ss(f);
	X0 = _mm_rsqrt_ss(Y0); // 1/sqrt estimate (12bits)

	// Newton-Raphson iteration (X1 = 0.5*X0*(3-(Y*X0)*X0))
	Temp = _mm_mul_ss(_mm_mul_ss(Y0, X0), X0);  // (Y*X0)*X0
	Temp = _mm_sub_ss(three, Temp);				// (3-(Y*X0)*X0
	Temp = _mm_mul_ss(X0, Temp);				// X0*(3-(Y*X0)*X0)
	Temp = _mm_mul_ss(half, Temp);              // 0.5*X0*(3-(Y*X0)*X0)
	_mm_store_ss(&temp, Temp);
	return temp;
}

#endif
#endif