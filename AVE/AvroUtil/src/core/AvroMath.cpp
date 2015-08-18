#include "AU_stdafx.h" //must be first statement
#include "AvroMath.h"
#include <math.h>

I32 AU::Factorial(I32 n){
	return (n > 1) ? Factorial(n-1) : 1;
}

F32 AU::Lerp(F32 a, F32 b, F32 alpha){
	return a + (b - a) * alpha; //(1 - alpha) * a + alpha * b;
}

F32 AU::Sin(F32 x)
{
	return sinf(x);
}

F32 AU::Cos(F32 x)
{
	return cosf(x);
}
