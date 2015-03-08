#ifndef AVRO_UTIL_VECTOR_MATH_H
#define AVRO_UTIL_VECTOR_MATH_H
#include "avro_typedefs.h"
#include "Avro_Preprocessor.h"
#include "AvroMath.h"
#include "AvroUtil.h"


namespace AU{

	struct V2;
	struct V3;
	struct V4;
	struct Q4;
	struct M33;
	struct M43;
	struct M44;

	/************************************************************************/
	/*	Two-Dimensional Vector                                              */
	/************************************************************************/
	// Structure for 2 dimensional vector
	struct V2{

		F32 x;
		F32 y;

		glob const V2 ZERO;
		glob const V2 UNIT;
		glob const V2 X_AXIS;
		glob const V2 Y_AXIS;

		INLINEFORCE V2(){} // default ctor: (0,0)
		INLINEFORCE explicit V2(F32 s); //scalar ctor
		INLINEFORCE V2(F32 x, F32 y); //defined ctor: (x,y)
		INLINEFORCE V2(const V2& v); //copy ctor: (v.x,v.y)
		INLINEFORCE V2(V2&& v); //move ctor: (v.x, v.y)

		INLINEFORCE V2 operator=(const V2& v);// copy assignment
		INLINEFORCE V2 operator=(V2&& s); // move assignment

		INLINEFORCE V2 operator+(const V2& v) const; // vector addition
		INLINEFORCE V2 operator+(F32 s) const; // scalar addition

		INLINEFORCE V2 operator-(const V2& v) const; //vector subtraction
		INLINEFORCE V2 operator-(F32 s) const; //scalar subtraction

		INLINEFORCE V2 operator*(const V2& v) const; //vector multiplication
		INLINEFORCE V2 operator*(F32 s) const; //scalar multiplication

		INLINEFORCE V2 operator/(const V2& v) const; //vector division
		INLINEFORCE V2 operator/(F32 s) const; //scalar division

		INLINEFORCE F32 operator|(const V2& v) const; //dot product
		INLINEFORCE F32 operator^(const V2& v) const; //cross product

		INLINEFORCE B8 operator==(const V2& v) const; //vector equality check
		INLINEFORCE B8 operator==(F32 s) const; //scalar comparison
		INLINEFORCE B8 operator!= (const V2& v) const; //vector inequality check
		INLINEFORCE B8 operator!= (F32 s) const; //scalar inequality check
		INLINEFORCE B8 operator<(const V2& v) const; //vector less-than comparison
		INLINEFORCE B8 operator<(F32 s) const; //scalar less-than comparison
		INLINEFORCE B8 operator>(const V2& v) const; //vector more-than comparison
		INLINEFORCE B8 operator>(F32 s) const; //scalar more-than comparison
		INLINEFORCE B8 operator<=(const V2& v) const; //vector less-than-equals comparison
		INLINEFORCE B8 operator<=(F32 s) const; //scalar less-than-equals comparison
		INLINEFORCE B8 operator>=(const V2& v) const; //vector more-than-equals comparison
		INLINEFORCE B8 operator>=(F32 s) const; //scalar more-than-equals comparison

		INLINEFORCE V2 operator-() const; //negate the vector

		INLINEFORCE V2 operator+=(const V2& v); //vector self-addition
		INLINEFORCE V2 operator+=(F32 s); //scalar self-addition

		INLINEFORCE V2 operator-=(const V2& v); //vector self-subtraction
		INLINEFORCE V2 operator-=(F32 s); //scalar self-subtraction

		INLINEFORCE V2 operator*=(const V2& v); //vector self-multiplication
		INLINEFORCE V2 operator*=(F32 s); //scalar self-multiplication

		INLINEFORCE V2 operator/=(const V2& v); //vector self-division
		INLINEFORCE V2 operator/=(F32 s); //scalar self-division

		INLINEFORCE V2 operator%(F32 tolerance) const; //Normalize with tolerance
		INLINEFORCE V2 operator%=(const V2& v); // Normalization assignment

		INLINEFORCE F32 operator~() const; //euclidean length squared

		INLINEFORCE V2 operator++(); //doubles vector magnitude, chained return
		INLINEFORCE V2 operator--(); //half of vector magnitude, chained return

		INLINEFORCE F32& operator[](U32 index); // gets specific component reference
		INLINEFORCE F32 operator[](U32 index) const; // gets specific component copy

		INLINEFORCE glob F32 Dot(const V2& a, const V2& b); //global dot product
		INLINEFORCE glob F32 Dist2(const V2& a, const V2& b); //global distance squared function
		INLINEFORCE glob F32 Dist(const V2& a, const V2& b); //global distance function
		INLINEFORCE glob F32 Cross(const V2& a, const V2& b); //global cross product

		INLINEFORCE B8 Equals(const V2& v, F32 tolerance) const; //fuzzy equality test

		INLINEFORCE V2 Set(F32 x, F32 y); //set components, chained return

		INLINEFORCE F32 Max() const; // gets max component
		INLINEFORCE F32 Min() const; // gets min component

		INLINEFORCE F32 AbsMax() const; // gets absolute max component
		INLINEFORCE F32 AbsMin() const; // gets absolute min component

		INLINEFORCE F32 Len() const; // euclidean length
		INLINEFORCE F32 Len2() const; // euclidean length squared

		INLINEFORCE V2 SafeNormalize(F32 tolerance = EZERO) const; //safe normalization

		INLINEFORCE V2 Nor(F32 tolerance = EZERO); // self-normalization, chained return

		INLINEFORCE B8 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		INLINEFORCE B8 IsZero() const; //check if absolutely zero

		INLINEFORCE V2 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

#if CHECK_NAN
		INLINEFORCE void CheckNan() const{
			AVRO_ASSERT(!HasNaN(), "V2 contains NaN");
		}
#else
		INLINEFORCE void CheckNaN() const{}
#endif

		INLINEFORCE B8 HasNaN() const{
			return (IsNaN(x) || IsNaN(y) || !IsFinite(x) || !IsFinite(y));
		}
	};


	//Functions

	INLINEFORCE V2::V2(F32 s):x(s), y(s){}
	INLINEFORCE V2::V2(F32 x, F32 y) : x(x), y(y){}
	INLINEFORCE V2::V2(const V2& v) : x(v.x), y(v.y){}
	INLINEFORCE V2::V2(V2&& v) : x(v.x), y(v.y){
		v.x = 0;
		v.y = 0;
	}

	INLINEFORCE V2 V2::operator=(const V2& rhs){
		x = rhs.x;
		y = rhs.y;
	}

	INLINEFORCE V2 V2::operator=(V2&& rhs){
		x = rhs.x;
		y = rhs.y;
		x = 0;
		y = 0;
	}

	INLINEFORCE V2 V2::operator+(const V2& v) const{
		return V2(x + v.x, y + v.y);
	}

	INLINEFORCE V2 V2::operator+(F32 s) const{
		return V2(x + s, y + s);
	}

	INLINEFORCE V2 V2::operator-(const V2& v) const{
		return V2(x - v.x, y - v.y);
	}

	INLINEFORCE V2 V2::operator-(F32 s) const{
		return V2(x - s, y - s);
	}
	INLINEFORCE V2 V2::operator*(const V2& v) const{
		return V2(x * v.x, y * v.y);
	}

	INLINEFORCE V2 V2::operator*(F32 s) const{
		return V2(x * s, y * s);
	}
	INLINEFORCE V2 V2::operator/(const V2& v) const{
		return V2(x / v.x, y / v.y);
	}

	INLINEFORCE V2 V2::operator/(F32 s) const{
		const F32 scale = 1.f / s;
		return V2(x * s, y * s);
	}

	//multiplication in opposite order
	INLINEFORCE V2 operator*(F32 scl, const V2& v){
		return v * scl;
	}

	INLINEFORCE F32 V2::operator|(const V2& v) const{
		return x*v.x + y*v.y;
	}

	INLINEFORCE F32 V2::operator^(const V2& v) const{
		return x*v.y - y*v.x;
	}

	INLINEFORCE F32 V2::Dot(const V2& a, const V2& b){
		return a | b;
	}

	INLINEFORCE F32 V2::Cross(const V2& a, const V2& b){
		return a ^ b;
	}

	INLINEFORCE F32 V2::Dist2(const V2& a, const V2& b){
		return Square(b.x - a.x) + Square(b.y - a.y);
	}

	INLINEFORCE F32 V2::Dist(const V2& a, const V2& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE B8 V2::operator==(const V2& v) const{
		return x == v.x && y == v.y;
	}

	INLINEFORCE B8 V2::operator!=(const V2& v) const{
		return x != v.x || y != v.y;
	}

	INLINEFORCE B8 V2::operator<(const V2& v) const{
		return x < v.x && y < v.y;
	}

	INLINEFORCE B8 V2::operator>(const V2& v) const{
		return x > v.x && y > v.y;
	}

	INLINEFORCE B8 V2::operator<=(const V2& v) const{
		return x <= v.x && y <= v.y;
	}

	INLINEFORCE B8 V2::operator>=(const V2& v) const{
		return x >= v.x && y >= v.y;
	}

	INLINEFORCE B8 V2::Equals(const V2& v, F32 tolerance) const{
		return Abs(x - v.x) < tolerance && Abs(y - v.y) < tolerance;
	}

	INLINEFORCE V2 V2::operator-() const{
		return V2(-x, -y);
	}

	INLINEFORCE V2 V2::operator+=(const V2& v){
		x += v.x; y += v.y;
		return *this;
	}

	INLINEFORCE V2 V2::operator+=(F32 s){
		x += s; y += s;
		return *this;
	}

	INLINEFORCE V2 V2::operator-=(const V2& v){
		x -= v.x; y -= v.y;
		return *this;
	}

	INLINEFORCE V2 V2::operator-=(F32 s){
		x -= s; y -= s;
		return *this;
	}

	INLINEFORCE V2 V2::operator*=(const V2& v){
		x *= v.x; y *= v.y;
		return *this;
	}

	INLINEFORCE V2 V2::operator*=(F32 s){
		x *= s; y *= s;
		return *this;
	}

	INLINEFORCE V2 V2::operator/=(const V2& v){
		x /= v.x; y /= v.y;
		return *this;
	}

	INLINEFORCE V2 V2::operator/=(F32 s){
		const F32 r = 1.f / s;
		x *= r; y *= r;
		return *this;
	}

	INLINEFORCE F32& V2::operator[](U32 index){
		AVRO_ASSERT(index >= 0 && index <= 2, index + "out of bounds, for V2");
		return (index == 0 ? x : y);
	}

	INLINEFORCE F32 V2::operator[](U32 index) const{
		AVRO_ASSERT(index >= 0 && index <= 2, index + "out of bounds, for V2");
		return (index == 0 ? x : y);
	}

	INLINEFORCE V2 V2::operator%(F32 tolerance) const{
		const F32 squaredSum = x*x + y*y;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			return V2(x*scl, y*scl);
		}
		return V2(0.f, 0.f);
	}

	INLINEFORCE V2 V2::operator%=(const V2& v){
		return v % EZERO;
	}

	INLINEFORCE F32 V2::operator~() const{
		return x*x + y*y;
	}

	INLINEFORCE V2 V2::operator++(){
		x *= 2.f;
		y *= 2.f;
		return *this;
	}

	INLINEFORCE V2 V2::operator--(){
		x *= 0.5f;
		y *= 0.5f;
		return *this;
	}

	INLINEFORCE V2 V2::Set(F32 x, F32 y){
		this->x = x;
		this->y = y;
		return *this;
	}

	INLINEFORCE F32 V2::Max() const{
		return AU::Max(x, y);
	}

	INLINEFORCE F32 V2::Min() const{
		return AU::Min(x, y);
	}

	INLINEFORCE F32 V2::AbsMax() const{
		return AU::Max(Abs(x), Abs(y));
	}

	INLINEFORCE F32 V2::AbsMin() const{
		return AU::Min(Abs(x), Abs(y));
	}

	INLINEFORCE F32 V2::Len() const{
		return Sqrt(x*x + y*y);
	}

	INLINEFORCE F32 V2::Len2() const{
		return x*x + y*y;
	}

	INLINEFORCE V2 V2::SafeNormalize(F32 tolerance) const{
		const F32 squaredSum = x*x + y*y;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			return V2(x*scl, y*scl);
		}
		return V2(0.f, 0.f);
	}

	INLINEFORCE V2 V2::Nor(F32 tolerance){
		const F32 squareSum = x*x + y*y;
		if (squareSum > tolerance)
		{
			const float scl = SqrtInv(squareSum);
			x *= scl;
			y *= scl;
			return *this;
		}
		x = 0.0f;
		y = 0.0f;
		return *this;
	}

	INLINEFORCE B8 V2::IsEpsilonZero(F32 tolerance) const{
		return Abs(x) < tolerance && Abs(y) < tolerance;
	}

	INLINEFORCE B8 V2::IsZero() const{
		return x == 0.f && y == 0.f;
	}

	INLINEFORCE V2 V2::Clamp(F32 min, F32 max) const{
		return V2(AU::Clamp(x, min, max), AU::Clamp(y, min, max));
	}

	INLINEFORCE glob U64 HashV2(const V2& value){
		U64 result = 17;
		result = 31 * result + HashF32(value.x);
		result = 31 * result + HashF32(value.y);
		return result;
	}

	/************************************************************************/
	/* Three-Dimensional Vector                                             */
	/************************************************************************/

	struct V3{

		F32 x;
		F32 y;
		F32 z;

		glob const V3 ZERO;
		glob const V3 UNIT;
		glob const V3 X_AXIS;
		glob const V3 Y_AXIS;
		glob const V3 Z_AXIS;


		INLINEFORCE V3(){} //Default ctor
		INLINEFORCE explicit V3(F32 s); //Scalar ctor
		INLINEFORCE V3(F32 x, F32 y, F32 z); //Defined ctor
		INLINEFORCE V3(const V3& rhs); //Copy ctor
		INLINEFORCE V3(const V2& rhs); //Copy ctor from V2
		INLINEFORCE V3(V3&& rhs); //Move ctor
		INLINEFORCE V3(V2&& rhs); //Move ctor from V2

		INLINEFORCE V3 operator=(const V3& rhs); //copy assignment operator
		INLINEFORCE V3 operator=(const V2& rhs); //copy assignment operator from V2
		INLINEFORCE V3 operator=(V3&& rhs); //move assignment operator
		INLINEFORCE V3 operator=(V2&& rhs); //move assignment operator from V2

		INLINEFORCE V3 operator+(const V3& v) const; //V3 addition
		INLINEFORCE V3 operator+(const V2& v) const; //V2 addition
		INLINEFORCE V3 operator+(F32 s) const; //Scalar addition

		INLINEFORCE V3 operator-(const V3& v) const; //V3 subtraction
		INLINEFORCE V3 operator-(const V2& v) const; //V2 subtraction
		INLINEFORCE V3 operator-(F32 s) const; //Scalar subtraction

		INLINEFORCE V3 operator*(const V3& v) const; //V3 multiplication
		INLINEFORCE V3 operator*(const V2& v) const; //V2 multiplication
		INLINEFORCE V3 operator*(F32 s) const; //Scalar multiplication

		INLINEFORCE V3 operator/(const V3& v) const; //V3 division
		INLINEFORCE V3 operator/(const V2& v) const; //V2 division
		INLINEFORCE V3 operator/(F32 s) const; //Scalar division

		INLINEFORCE F32 operator|(const V3& v) const; //V3 dot product
		INLINEFORCE F32 operator|(const V2& v) const; //V2 dot product

		INLINEFORCE V3 operator^(const V3& v) const; //V3 cross product
		INLINEFORCE V3 operator^(const V2& v) const; //V2 cross product

		INLINEFORCE B8 operator==(const V3& v) const; //vector equality check
		INLINEFORCE B8 operator==(F32 s) const; //scalar comparison
		INLINEFORCE B8 operator!= (const V3& v) const; //vector inequality check
		INLINEFORCE B8 operator!= (F32 s) const; //scalar inequality check
		INLINEFORCE B8 operator<(const V3& v) const; //vector less-than comparison
		INLINEFORCE B8 operator<(F32 s) const; //scalar less-than comparison
		INLINEFORCE B8 operator>(const V3& v) const; //vector more-than comparison
		INLINEFORCE B8 operator>(F32 s) const; //scalar more-than comparison
		INLINEFORCE B8 operator<=(const V3& v) const; //vector less-than-equals comparison
		INLINEFORCE B8 operator<=(F32 s) const; //scalar less-than-equals comparison
		INLINEFORCE B8 operator>=(const V3& v) const; //vector more-than-equals comparison
		INLINEFORCE B8 operator>=(F32 s) const; //scalar more-than-equals comparison

		INLINEFORCE V2 operator-() const; // Negate this vector

		INLINEFORCE V3 operator+=(const V3& v); //V3 self-addition
		INLINEFORCE V3 operator+=(const V2& v); //V2 self-addition
		INLINEFORCE V3 operator+=(F32 v); //Scalar self-addition

		INLINEFORCE V3 operator-=(const V3& v); //V3 self-subtraction
		INLINEFORCE V3 operator-=(const V2& v); //V2 self-subtraction
		INLINEFORCE V3 operator-=(F32 v); //Scalar self-subtraction

		INLINEFORCE V3 operator*=(const V3& v); //V3 self-multiplication
		INLINEFORCE V3 operator*=(const V2& v); //V2 self-multiplication
		INLINEFORCE V3 operator*=(F32 v); //Scalar self-multiplication

		INLINEFORCE V3 operator/=(const V3& v); //V3 self-division
		INLINEFORCE V3 operator/=(const V2& v); //V2 self-division
		INLINEFORCE V3 operator/=(F32 v); //Scalar self-division

		INLINEFORCE V3 operator%(F32 tolerance); //Normalize with tolerance
		INLINEFORCE V3 operator%=(const V3& v); //V3 self-normalization
		INLINEFORCE V3 operator%=(const V2& v); //V2 self-normalization

		INLINEFORCE F32 operator~() const; //euclidean length squared

		INLINEFORCE V3 operator++(); //doubles vector magnitude, chained return
		INLINEFORCE V3 operator--(); //half of vector magnitude, chained return

		INLINEFORCE F32& operator[](U32 index); // gets specific component reference
		INLINEFORCE F32 operator[](U32 index) const; // gets specific component copy

		INLINEFORCE glob F32 Dot(const V3& a, const V3& b); //global dot product
		INLINEFORCE glob F32 Dot(const V3& a, const V2& b); //global dot product
		INLINEFORCE glob F32 Dot(const V2& a, const V3& b); //global dot product

		INLINEFORCE glob F32 Dist(const V3& a, const V3& b); //global distance
		INLINEFORCE glob F32 Dist(const V3& a, const V2& b); //global distance
		INLINEFORCE glob F32 Dist(const V2& a, const V3& b); //global distance

		INLINEFORCE glob F32 Dist2(const V3& a, const V3& b); //global distance squared
		INLINEFORCE glob F32 Dist2(const V3& a, const V2& b); //global distance squared
		INLINEFORCE glob F32 Dist2(const V2& a, const V3& b); //global distance squared

		INLINEFORCE glob V3 Cross(const V3& a, const V3& b); //global cross product
		INLINEFORCE glob V3 Cross(const V3& a, const V2& b); //global cross product

		INLINEFORCE B8 Equals(const V3& v, F32 tolerance) const; //fuzzy equality test

		INLINEFORCE V2 Set(F32 x, F32 y); //set components, chained return

		INLINEFORCE F32 Max() const; // gets max component
		INLINEFORCE F32 Min() const; // gets min component

		INLINEFORCE F32 AbsMax() const; // gets absolute max component
		INLINEFORCE F32 AbsMin() const; // gets absolute min component

		INLINEFORCE F32 Len() const; // euclidean length
		INLINEFORCE F32 Len2() const; // euclidean length squared

		INLINEFORCE V3 SafeNormalize(F32 tolerance = EZERO) const; //safe normalization

		INLINEFORCE V3 Nor(F32 tolerance = EZERO); // self-normalization, chained return

		INLINEFORCE B8 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		INLINEFORCE B8 IsZero() const; //check if absolutely zero

		INLINEFORCE V3 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

		INLINEFORCE V2 XY() const; //Swizzles to V2(x,y)
		INLINEFORCE V2 YZ() const; //Swizzles to V2(y,z)
		INLINEFORCE V2 XZ() const; //Swizzles to V2(x,z)
		INLINEFORCE V2 YX() const; //Swizzles to V2(y,x)
		INLINEFORCE V2 ZY() const; //Swizzles to V2(z,y)
		INLINEFORCE V2 ZX() const; //Swizzles to V2(z,x)

#if CHECK_NAN
		INLINEFORCE void CheckNan() const{
			AVRO_ASSERT(!HasNaN(), "V3 contains NaN");
		}
#else
		INLINEFORCE void CheckNaN() const{}
#endif

		INLINEFORCE B8 HasNaN() const{
			return (IsNaN(x) || IsNaN(y) || IsNaN(z) || !IsFinite(x) || !IsFinite(y) || !IsFinite(z));
		}
	};





	/************************************************************************/
	/* Four-Dimensional Vector                                              */
	/************************************************************************/
	struct V4{
		F32 x;
		F32 y;
		F32 z;
		F32 w;
	};

	






	/************************************************************************/
	/* Quaternion                                                           */
	/************************************************************************/
	struct Q4{
		F32 x;
		F32 y;
		F32 z;
		F32 w;
	};






	/************************************************************************/
	/* Three-By-Three Matrix                                                */
	/************************************************************************/
	struct M33{
		F32 m[9];
	};


	




	/************************************************************************/
	/* Four-By-Three Matrix                                                 */
	/************************************************************************/
	struct M43{
		F32 m[12];
	};






	/************************************************************************/
	/* Four-By-Four Matrix                                                  */
	/************************************************************************/
	struct M44{
		F32 m[16];
	};








}

#endif