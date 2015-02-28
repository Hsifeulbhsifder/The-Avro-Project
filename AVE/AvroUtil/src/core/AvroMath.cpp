#include "AU_stdafx.h" //must be first statement
#include "AvroMath.h"

I32 factorial(I32 n){
	return (n > 1) ? factorial(n-1) : 1;
}

F32 lerp(F32 a, F32 b, F32 alpha){
	return a + (b - a) * alpha; //(1 - alpha) * a + alpha * b;
}