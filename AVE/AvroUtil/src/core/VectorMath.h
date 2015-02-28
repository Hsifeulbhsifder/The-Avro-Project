#ifndef AVRO_UTIL_VECTOR_MATH_H
#define AVRO_UTIL_VECTOR_MATH_H
#include "avro_typedefs.h"
#include "Avro_Preprocessor.h"
#include "AvroMath.h"


namespace ave{

	/************************************************************************/
	/*	Two-Dimensional Vector                                              */
	/************************************************************************/
	// Structure for 2 dimensional vector
	struct V2{

		F32 x;
		F32 y;

		glob const V2 ZERO;
		glob const V2 UNIT;

		INLINEFORCE V2(){} // default ctor: (0,0)
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

		B8 operator==(const V2& v) const; //vector equality check
		B8 operator==(F32 s) const; //scalar comparison
		B8 operator!= (const V2& v) const; //vector inequality check
		B8 operator!= (F32 s) const; //scalar inequality check
		B8 operator<(const V2& v) const; //vector less-than comparison
		B8 operator<(F32 s) const; //scalar less-than comparison
		B8 operator>(const V2& v) const; //vector more-than comparison
		B8 operator>(F32 s) const; //scalar more-than comparison
		B8 operator<=(const V2& v) const; //vector less-than-equals comparison
		B8 operator<=(F32 s) const; //scalar less-than-equals comparison
		B8 operator>=(const V2& v) const; //vector more-than-equals comparison
		B8 operator>=(F32 s) const; //scalar more-than-equals comparison

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

		F32& operator[](I32 index); // gets specific component reference
		F32 operator[](I32 index) const; // gets specific component copy

		INLINEFORCE glob F32 Dot(const V2& a, const V2& b); //static dot product
		INLINEFORCE glob F32 Dist2(const V2& a, const V2& b); //static distance squared function
		INLINEFORCE glob F32 Dist(const V2& a, const V2& b); //static distance function
		INLINEFORCE glob F32 Cross(const V2& a, const V2& b); //static cross product

		B8 Equals(const V2& v, F32 tolerance) const; //fuzzy equality test

		INLINEFORCE V2 Set(F32 x, F32 y); //set components, chained return

		F32 Max() const; // gets max component
		F32 Min() const; // gets min component

		F32 AbsMax() const; // gets absolute max component
		F32 AbsMin() const; // gets absolute min component

		INLINEFORCE F32 Len() const; // euclidean length
		INLINEFORCE F32 Len2() const; // euclidean length squared

		V2 SafeNormalize(F32 tolerance = EZERO) const; //safe normalization

		V2 Nor(F32 tolerance = EZERO); // self-normalization, chained return

		B8 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		B8 IsZero() const; //check if absolutely zero

		V2 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

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

	INLINEFORCE  V2::V2(F32 x, F32 y) : x(x), y(y){}
	INLINEFORCE  V2::V2(const V2& v) : x(v.x), y(v.y){}
	INLINEFORCE  V2::V2(V2&& v) : x(v.x), y(v.y){
		v.x = 0;
		v.y = 0;
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

	INLINEFORCE F32& V2::operator[](I32 index){
		AVRO_ASSERT(index >= 0 && index <= 2, index + "out of bounds, for V2");
		return (index == 0 ? x : y);
	}

	INLINEFORCE F32 V2::operator[](I32 index) const{
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
		return ave::Max(x, y);
	}

	INLINEFORCE F32 V2::Min() const{
		return ave::Min(x, y);
	}

	INLINEFORCE F32 V2::AbsMax() const{
		return ave::Max(Abs(x), Abs(y));
	}

	INLINEFORCE F32 V2::AbsMin() const{
		return ave::Min(Abs(x), Abs(y));
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
		return V2(ave::Clamp(x, min, max), ave::Clamp(y, min, max));
	}

}

#endif