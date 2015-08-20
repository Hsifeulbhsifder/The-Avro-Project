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

		INLINEFORCE B32 operator==(const V2& v) const; //vector equality check
		INLINEFORCE B32 operator==(F32 s) const; //scalar comparison
		INLINEFORCE B32 operator!= (const V2& v) const; //vector inequality check
		INLINEFORCE B32 operator!= (F32 s) const; //scalar inequality check
		INLINEFORCE B32 operator<(const V2& v) const; //vector less-than comparison
		INLINEFORCE B32 operator<(F32 s) const; //scalar less-than comparison
		INLINEFORCE B32 operator>(const V2& v) const; //vector more-than comparison
		INLINEFORCE B32 operator>(F32 s) const; //scalar more-than comparison
		INLINEFORCE B32 operator<=(const V2& v) const; //vector less-than-equals comparison
		INLINEFORCE B32 operator<=(F32 s) const; //scalar less-than-equals comparison
		INLINEFORCE B32 operator>=(const V2& v) const; //vector more-than-equals comparison
		INLINEFORCE B32 operator>=(F32 s) const; //scalar more-than-equals comparison

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

		INLINEFORCE B32 Equals(const V2& v, F32 tolerance = EPSILON) const; //fuzzy equality test

		INLINEFORCE V2 Set(F32 x, F32 y); //set components, chained return

		INLINEFORCE F32 Max() const; // gets max component
		INLINEFORCE F32 Min() const; // gets min component

		INLINEFORCE F32 AbsMax() const; // gets absolute max component
		INLINEFORCE F32 AbsMin() const; // gets absolute min component

		INLINEFORCE F32 Len() const; // euclidean length
		INLINEFORCE F32 Len2() const; // euclidean length squared

		INLINEFORCE V2 SafeNormalize(F32 tolerance = EZERO) const; //safe normalization

		INLINEFORCE V2 Nor(F32 tolerance = EZERO); // self-normalization, chained return

		INLINEFORCE B32 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		INLINEFORCE B32 IsZero() const; //check if absolutely zero

		INLINEFORCE V2 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

#if CHECK_NAN
		INLINEFORCE void CheckNan() const{
			AVRO_ASSERT(!HasNaN(), "V2 contains NaN");
		}
#else
		INLINEFORCE void CheckNaN() const{}
#endif

		INLINEFORCE B32 HasNaN() const{
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
		return Sq(b.x - a.x) + Sq(b.y - a.y);
	}

	INLINEFORCE F32 V2::Dist(const V2& a, const V2& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE B32 V2::operator==(const V2& v) const{
		return x == v.x && y == v.y;
	}

	INLINEFORCE B32 V2::operator!=(const V2& v) const{
		return x != v.x || y != v.y;
	}

	INLINEFORCE B32 V2::operator<(const V2& v) const{
		return x < v.x && y < v.y;
	}

	INLINEFORCE B32 V2::operator>(const V2& v) const{
		return x > v.x && y > v.y;
	}

	INLINEFORCE B32 V2::operator<=(const V2& v) const{
		return x <= v.x && y <= v.y;
	}

	INLINEFORCE B32 V2::operator>=(const V2& v) const{
		return x >= v.x && y >= v.y;
	}

	INLINEFORCE B32 V2::Equals(const V2& v, F32 tolerance) const{
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
		*this = v % EZERO;
		return *this;
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

	INLINEFORCE B32 V2::IsEpsilonZero(F32 tolerance) const{
		return Abs(x) < tolerance && Abs(y) < tolerance;
	}

	INLINEFORCE B32 V2::IsZero() const{
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
		glob const V3 XY_AXIS;
		glob const V3 YZ_AXIS;
		glob const V3 XZ_AXIS;


		INLINEFORCE V3(){} //Default ctor
		INLINEFORCE explicit V3(F32 s); //Scalar ctor
		INLINEFORCE V3(F32 x, F32 y, F32 z); //Defined ctor
		INLINEFORCE V3(const V2& rhs, F32 z); //ctor from V2 and scalar
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

		INLINEFORCE B32 operator==(const V3& v) const; //vector equality check
		INLINEFORCE B32 operator==(F32 s) const; //scalar comparison
		INLINEFORCE B32 operator!= (const V3& v) const; //vector inequality check
		INLINEFORCE B32 operator!= (F32 s) const; //scalar inequality check
		INLINEFORCE B32 operator<(const V3& v) const; //vector less-than comparison
		INLINEFORCE B32 operator<(F32 s) const; //scalar less-than comparison
		INLINEFORCE B32 operator>(const V3& v) const; //vector more-than comparison
		INLINEFORCE B32 operator>(F32 s) const; //scalar more-than comparison
		INLINEFORCE B32 operator<=(const V3& v) const; //vector less-than-equals comparison
		INLINEFORCE B32 operator<=(F32 s) const; //scalar less-than-equals comparison
		INLINEFORCE B32 operator>=(const V3& v) const; //vector more-than-equals comparison
		INLINEFORCE B32 operator>=(F32 s) const; //scalar more-than-equals comparison

		INLINEFORCE V3 operator-() const; // Negate this vector

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

		INLINEFORCE V3 operator%(F32 tolerance) const; //Normalize with tolerance
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

		INLINEFORCE B32 Equals(const V3& v, F32 tolerance = EPSILON) const; //fuzzy equality test
		INLINEFORCE B32 AllComponentsEqual(F32 tolerance = EPSILON) const;

		INLINEFORCE V3 Set(F32 x, F32 y, F32 z); //set components, chained return

		INLINEFORCE F32 Max() const; // gets max component
		INLINEFORCE F32 Min() const; // gets min component

		INLINEFORCE V3 Abs() const; // Absolute value of every component of this vector

		INLINEFORCE F32 AbsMax() const; // gets absolute max component
		INLINEFORCE F32 AbsMin() const; // gets absolute min component

		INLINEFORCE V3 ComponentMin(const V3& rhs) const; //component wise max of two vectors
		INLINEFORCE V3 ComponentMax(const V3& rhs) const; //component wise max of two vectors
		INLINEFORCE V3 ComponentMin(const V2& rhs) const; //component wise min of two vectors
		INLINEFORCE V3 ComponentMax(const V2& rhs) const; //component wise min of two vectors


		INLINEFORCE F32 Len() const; // euclidean length
		INLINEFORCE F32 Len2() const; // euclidean length squared

		INLINEFORCE V3 SafeNormalize(F32 tolerance = EZERO) const; //safe normalization

		INLINEFORCE V3 Nor(F32 tolerance = EZERO); // self-normalization, chained return

		INLINEFORCE B32 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		INLINEFORCE B32 IsZero() const; //check if absolutely zero

		INLINEFORCE void ToDirectionAndMagnitude(V3* v, F32* s) const; //returns a unit direction vector as well as a magnitude
		INLINEFORCE V3 SignV3() const; //sets each component to either +1 or -1
		INLINEFORCE V3 Projection() const; //Projects 2D components of vector based on z

		INLINEFORCE V3 UnsafeNormalize() const;

		INLINEFORCE V3 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

		INLINEFORCE V3 Reciprocal() const; //Reciprocates vector

		INLINEFORCE B32 Uniform(F32 Tolerance = EPSILON) const; //checks if x == y == z

		INLINEFORCE V3 Reflect(const V3& normal) const; // reflects vector across normal vector

		//TODO: REFLECT ACROSS PLANE

		//TODO: ANGLULAR ROTATION

		INLINEFORCE B32 IsUnit(F32 len2Tolerance = EPSILON) const; //checks if it is unit

		INLINEFORCE V3 Project(const V3& v) const; // Projects this vector onto another vector

		INLINEFORCE glob B32 EqualVectors(const V3& a, const V3& b); // Checks if vectors are equal
		INLINEFORCE glob B32 VectorsAreNear(const V3& a, const V3& b, F32 dist);// checks if vectors are within distance

		//Distance from plane
		INLINEFORCE glob F32 VectorPlaneDist(const V3& point, const V3& planeBase, const V3& planeNormal);

		INLINEFORCE glob V3 ProjectPlane(const V3& point, const V3& planeBase, const V3& planeNormal);

		INLINEFORCE glob B32 Parallel(const V3& a, const V3& b); // checks if vectors are roughly parallel

		INLINEFORCE glob F32 Triple(const V3& a, const V3& b, const V3& c); // return triple: x|(y^z)

		//TODO: BEZIER CURVE		

		INLINEFORCE V2 XY() const; //Swizzles to V2(x,y)
		INLINEFORCE V2 YZ() const; //Swizzles to V2(y,z)
		INLINEFORCE V2 XZ() const; //Swizzles to V2(x,z)
		INLINEFORCE V2 YX() const; //Swizzles to V2(y,x)
		INLINEFORCE V2 ZY() const; //Swizzles to V2(z,y)
		INLINEFORCE V2 ZX() const; //Swizzles to V2(z,x)

#if CHECK_NAN
		INLINEFORCE void CheckNaN() const{
			AVRO_ASSERT(!HasNaN(), "V3 contains NaN");
		}
#else
		INLINEFORCE void CheckNaN() const{}
#endif

		INLINEFORCE B32 HasNaN() const{
			return (IsNaN(x) || IsNaN(y) || IsNaN(z) || !IsFinite(x) || !IsFinite(y) || !IsFinite(z));
		}
	};

	//Functions
	INLINEFORCE V3::V3(F32  s) :x(s), y(s), z(s){ V3::CheckNaN(); }

	INLINEFORCE V3::V3(F32 x, F32 y, F32 z) : x(x), y(y), z(z){ V3::CheckNaN(); }

	INLINEFORCE V3::V3(const V3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z){ V3::CheckNaN(); }
	INLINEFORCE V3::V3(const V2& rhs) : x(rhs.x), y(rhs.y), z(0){ V3::CheckNaN(); }
	INLINEFORCE V3::V3(const V2& rhs, F32 z) : x(rhs.x), y(rhs.y), z(z){ V3::CheckNaN(); }
	
	INLINEFORCE V3::V3(V3&& rhs) : x(rhs.x), y(rhs.y), z(rhs.z){
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		CheckNaN();
	}

	INLINEFORCE V3::V3(V2&& rhs) :x(rhs.x), y(rhs.y), z(0){
		rhs.x = 0;
		rhs.y = 0;
		CheckNaN();
	}

	INLINEFORCE V3 V3::operator=(const V3& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		CheckNaN();
	}

	INLINEFORCE V3 V3::operator=(const V2& rhs){
		x = rhs.x;
		y = rhs.y;
		z = 0;
		CheckNaN();
	}

	INLINEFORCE V3 V3::operator=(V3&& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		CheckNaN();
	}

	INLINEFORCE V3 V3::operator=(V2&& rhs){
		x = rhs.x;
		y = rhs.y;
		z = 0;
		rhs.x = 0;
		rhs.y = 0;
		CheckNaN();
	}

	INLINEFORCE V3 V3::operator+(const V3& v) const{
		return V3(x + v.x, y + v.y, z + v.z);
	}

	INLINEFORCE V3 V3::operator+(const V2& v) const{
		return V3(x + v.x, y + v.y, z);
	}

	INLINEFORCE V3 V3::operator+(F32 s) const{
		return V3(x + s, y + s, z + s);
	}

	INLINEFORCE V3 V3::operator-(const V3& v) const{
		return V3(x - v.x, y - v.y, z - v.z);
	}

	INLINEFORCE V3 V3::operator-(const V2& v) const{
		return V3(x - v.x, y - v.y, z);
	}

	INLINEFORCE V3 V3::operator-(F32 s) const{
		return V3(x - s, y - s, z - s);
	}
	INLINEFORCE V3 V3::operator*(const V3& v) const{
		return V3(x * v.x, y * v.y, z * v.z);
	}

	INLINEFORCE V3 V3::operator*(const V2& v) const{
		return V3(x * v.x, y * v.y, 0);
	}

	INLINEFORCE V3 V3::operator*(F32 s) const{
		return V3(x * s, y * s, z * s);
	}
	INLINEFORCE V3 V3::operator/(const V3& v) const{
		return V3(x / v.x, y / v.y, z / v.z);
	}

	INLINEFORCE V3 V3::operator/(const V2& v) const{
		return V3(x / v.x, y / v.y, ARCFINITY);
	}

	INLINEFORCE V3 V3::operator/(F32 s) const{
		const F32 scale = 1.0f / s;
		return V3(x * scale, y * scale, z * scale);
	}

	INLINEFORCE V3 operator*(F32 s, const V3& v){
		return v * s;
	}

	INLINEFORCE F32 V3::operator|(const V3& v) const{
		return x*v.x + y*v.y + z*v.z;
	}

	INLINEFORCE F32 V3::operator|(const V2& v) const{
		return x*v.x + y*v.y;
	}
	
	INLINEFORCE V3 V3::operator^(const V3& v) const{
		return V3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}

	INLINEFORCE V3 V3::operator^(const V2& v) const{
		return V3(-z*v.y, z*v.x, x*v.y - y*v.x);
	}

	INLINEFORCE B32 V3::operator==(const V3& v) const{
		return x == v.x && y == v.y && z == v.z;
	}

	INLINEFORCE B32 V3::operator==(F32 s) const{
		return x == s && y == s && z == s;
	}

	INLINEFORCE B32 V3::operator!=(const V3& v) const{
		return x != v.x || y != v.y || z != v.z;
	}

	INLINEFORCE B32 V3::operator!=(F32 s) const{
		return x != s || y != s || z != s;
	}

	INLINEFORCE B32 V3::operator<(const V3& v) const{
		return x < v.x && y < v.y && z < v.z;
	}

	INLINEFORCE B32 V3::operator<(F32 s) const{
		return x < s && y < s && z < s;
	}

	INLINEFORCE B32 V3::operator>(const V3& v) const{
		return x > v.x && y > v.y && z > v.z;
	}

	INLINEFORCE B32 V3::operator>(F32 s) const{
		return x > s && y > s && z > s;
	}

	INLINEFORCE B32 V3::operator<=(const V3& v) const{
		return x <= v.x && y <= v.y && z <= v.z;
	}

	INLINEFORCE B32 V3::operator<=(F32 s) const{
		return x <= s && y <= s && z <= s;
	}

	INLINEFORCE B32 V3::operator>=(const V3& v) const{
		return x >= v.x && y >= v.y && z >= v.z;
	}

	INLINEFORCE B32 V3::operator>=(F32 s) const{
		return x >= s && y >= s && z >= s;
	}

	INLINEFORCE V3 V3::operator-() const{
		return V3(-x, -y, -z);
	}

	INLINEFORCE V3 V3::operator+=(const V3& v){
		x += v.x;
		y += v.y;
		z += v.z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator+=(const V2& v){
		x += v.x;
		y += v.y;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator+=(F32 s){
		x += s;
		y += s;
		z += s;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator-=(const V3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator-=(const V2& v){
		x -= v.x;
		y -= v.y;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator-=(F32 s){
		x -= s;
		y -= s;
		z -= s;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator*=(const V3& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator*=(const V2& v){
		x *= v.x;
		y *= v.y;
		z = 0;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator*=(F32 s){
		x *= s;
		y *= s;
		z *= s;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator/=(const V3& v){
		x /= v.x;
		y /= v.y;
		z /= v.z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator/=(const V2& v){
		x /= v.x;
		y /= v.y;
		z = ARCFINITY;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator/=(F32 s){
		const F32 scale = 1.0f / s;
		x *= scale;
		y *= scale;
		z *= scale;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V3 V3::operator%(F32 tolerance) const{
#ifdef AVRO_DEBUG
		const F32 squaredSum = x*x + y*y + z*z;
		if(squaredSum == 1.0f) return *this;
		else if(squaredSum < tolerance) return V3::ZERO;
#elif AVRO_PROFILE
		const F32 squaredSum = x*x + y*y + z*z;
		if(squaredSum == 1.0f) return *this;
		else if (squaredSum < tolerance) return V3::ZERO;
#endif
		const F32 scl = SqrtInv(x*x + y*y + z*z);
		return V3(x*scl, y*scl, z*scl);
	}

	INLINEFORCE V3 V3::operator%=(const V3& v){
		*this = v % EZERO;
		return *this;
	}

	INLINEFORCE V3 V3::operator%=(const V2& v){
		*this = v % EZERO;
		return *this;
	}

	INLINEFORCE F32 V3::operator~() const{
		return x*x + y*y + z*z;
	}

	INLINEFORCE V3 V3::operator++(){
		x *= 2.f;
		y *= 2.f;
		z *= 2.f;
		return *this;
	}

	INLINEFORCE V3 V3::operator--(){
		x *= 0.5f;
		y *= 0.5f;
		z *= 0.5f;
		return *this;
	}

	INLINEFORCE F32& V3::operator[](U32 index){
		AVRO_ASSERT(index < 3, "V3 only contains 3 components, index out of bounds");
		if (index == 0) return x;
		else if (index == 1) return y;
		else return z;
	}

	INLINEFORCE F32 V3::operator[](U32 index) const{
		AVRO_ASSERT(index < 3, "V3 only contains 3 components, index out of bounds");
		if (index == 0) return x;
		else if (index == 1) return y;
		else return z;
	}

	INLINEFORCE F32 V3::Dot(const V3& a, const V3& b){
		return a | b;
	}

	INLINEFORCE F32 V3::Dot(const V3& a, const V2& b){
		return a | b;
	}

	INLINEFORCE F32 V3::Dot(const V2& a, const V3& b){
		return b | a;
	}

	INLINEFORCE F32 V3::Dist2(const V3& a, const V3& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(b.z - a.z);
	}

	INLINEFORCE F32 V3::Dist2(const V3& a, const V2& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(a.z);
	}

	INLINEFORCE F32 V3::Dist2(const V2& a, const V3& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(b.z);
	}

	INLINEFORCE F32 V3::Dist(const V3& a, const V3& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE F32 V3::Dist(const V3& a, const V2& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE F32 V3::Dist(const V2& a, const V3& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE V3 V3::Cross(const V3& a, const V3& b){
		return a ^ b;
	}

	INLINEFORCE V3 V3::Cross(const V3& a, const V2& b){
		return a ^ b;
	}

	INLINEFORCE B32 V3::Equals(const V3& v, F32 tolerance) const{
		return AU::Abs(x - v.x) < tolerance && AU::Abs(y - v.y) < tolerance && AU::Abs(z - v.z);
	}

	INLINEFORCE B32 V3::AllComponentsEqual(F32 tolerance) const{
		return AU::Abs(x - y) < tolerance && AU::Abs(y - z) < tolerance && AU::Abs(y - z) < tolerance;
	}

	INLINEFORCE V3 V3::Set(F32 x, F32 y, F32 z){
		this->x = x;
		this->y = y;
		this->z = z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE F32 Dist2BoxToPoint(const V3& min, const V3& max, const V3& point){
		F32 dist2 = 0.0f; //Accumulative distance squared

		//Unrolled loop, checks axes
		if (point.x < min.x)
			dist2 += AU::Sq(point.x - min.x);
		else if (point.x > max.x)
			dist2 += AU::Sq(point.x - max.x);

		if (point.y < min.y)
			dist2 += AU::Sq(point.y - min.y);
		else if (point.y > max.y)
			dist2 += AU::Sq(point.y - max.y);

		if (point.z < min.z)
			dist2 += AU::Sq(point.z - min.z);
		else if (point.z > max.z)
			dist2 += AU::Sq(point.z - max.z);

		return dist2;
	}

	INLINEFORCE F32 V3::Min() const{
		return AU::Min(AU::Min(x, y), z);
	}

	INLINEFORCE F32 V3::Max() const{
		return AU::Max(AU::Max(x, y), z);
	}

	INLINEFORCE F32 V3::AbsMin() const{
		return AU::Min(AU::Min(AU::Abs(x), AU::Abs(y)), AU::Abs(z));;
	}

	INLINEFORCE F32 V3::AbsMax() const{
		return AU::Max(AU::Max(AU::Abs(x), AU::Abs(y)), AU::Abs(z));
	}

	INLINEFORCE V3 V3::ComponentMin(const V3& v) const{
		return V3(AU::Min(x, v.x), AU::Min(y, v.y), AU::Min(z, v.z));
	}

	INLINEFORCE V3 V3::ComponentMax(const V3& v) const{
		return V3(AU::Max(x, v.x), AU::Max(y, v.y), AU::Max(z, v.z));
	}

	INLINEFORCE V3 V3::ComponentMin(const V2& v) const{
		return V3(AU::Min(x, v.x), AU::Min(y, v.y), AU::Min(z, 0.0f));
	}

	INLINEFORCE V3 V3::ComponentMax(const V2& v) const{
		return V3(AU::Max(x, v.x), AU::Max(y, v.y), AU::Max(z, 0.0f));
	}

	INLINEFORCE F32 V3::Len() const{
		return AU::Sqrt(x*x + y*y + z*z);
	}

	INLINEFORCE F32 V3::Len2() const{
		return x*x + y*y + z*z;
	}

	INLINEFORCE V3 V3::SafeNormalize(F32 tolerance) const{
		const F32 squaredSum = x*x + y*y + z*z;
		if (squaredSum == 1.0f) return *this;
		else if (squaredSum < tolerance) return V3::ZERO;
		const F32 scl = SqrtInv(squaredSum);
		return V3(x*scl, y*scl, z*scl);
	}

	INLINEFORCE V3 V3::Nor(F32 tolerance){
#ifdef AVRO_DEBUG
		const F32 squaredSum = x*x + y*y + z*z;
		if (squaredSum == 1.0f) return *this;
		else if (squaredSum < tolerance) return V3::ZERO;
#elif AVRO_PROFILE
		const F32 squaredSum = x*x + y*y + z*z;
		if (squaredSum == 1.0f) return *this;
		else if (squaredSum < tolerance) return V3::ZERO;
#endif
		const F32 scl = SqrtInv(x*x + y*y + z*z);
		x *= scl;
		y *= scl;
		z *= scl;
		CheckNaN();
		return *this;
	}

	INLINEFORCE B32 V3::IsEpsilonZero(F32 tolerance) const{
		return AU::Abs(x) < tolerance && AU::Abs(y) < tolerance && AU::Abs(z) < tolerance;
	}

	INLINEFORCE B32 V3::IsZero() const{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	INLINEFORCE void V3::ToDirectionAndMagnitude(V3* v, F32* s) const{
		*s = Len();
		if (*s > EPSILON){
			F32 lenReciprocal = 1.0f/ *s;
			*v = V3(x * lenReciprocal, y * lenReciprocal, z * lenReciprocal);
		}
		else{
			*v = V3::ZERO;
		}
	}

	INLINEFORCE V3 V3::SignV3() const{
		return V3(AU::SelectF32(x, 1.f, -1.f), AU::SelectF32(y, 1.f, -1.f), AU::SelectF32(z, 1.f, -1.f));
	}

	INLINEFORCE V3 V3::Projection() const{
		const F32 rz = 1.f / z;
		return V3(x*rz, y*rz, 1);
	}

	INLINEFORCE V3 V3::UnsafeNormalize() const{
		const F32 scl = SqrtInv(x*x + y*y + z*z);
		return V3(x*scl, y*scl, z*scl);
	}

	INLINEFORCE V3 V3::Clamp(F32 min, F32 max) const{
		F32 len = Len();
		const V3 dir = (len > EPSILON) ? (*this / len) : V3::ZERO;
		len = AU::Clamp(len, min, max);
		return len * dir;
	}

	INLINEFORCE V3 V3::Reciprocal() const{
		V3 vec;
		if (x != 0.f) vec.x = 1.f / x;
		else vec.x = ARCFINITY;
		if (y != 0.f) vec.y = 1.f / y;
		else vec.y = ARCFINITY;
		if (z != 0.f) vec.z = 1.f / z;
		else vec.z = ARCFINITY;
		return vec;
	}

	INLINEFORCE B32 V3::Uniform(F32 tolerance) const{
		return (AU::Abs(x - y) < tolerance) && (AU::Abs(y - z) < tolerance);
	}

	INLINEFORCE V3 V3::Reflect(const V3& normal) const{
		return *this - normal * (2.f * (*this | normal));
	}

	INLINEFORCE B32 V3::IsUnit(F32 len2Tolerance) const{
		return AU::Abs(1.0f - Len2()) < len2Tolerance;
	}

	INLINEFORCE V3 V3::Project(const V3& v) const{
		return (v * ((*this | v) / (v | v)));
	}

	INLINEFORCE B32 V3::EqualVectors(const V3& a, const V3& b){
		return (AU::Abs(a.x - b.x) < VECTOR_PROXIMITY_THRESHOLD 
			 && AU::Abs(a.y - b.y) < VECTOR_PROXIMITY_THRESHOLD 
			 && AU::Abs(a.z - b.z) < VECTOR_PROXIMITY_THRESHOLD);
	}

	INLINEFORCE B32 V3::VectorsAreNear(const V3& a, const V3& b, F32 dist){
		return (AU::Abs(a.x - b.x) < dist 
			&& AU::Abs(a.y - b.y) < dist
			&& AU::Abs(a.z - b.z) < dist);
	}

	INLINEFORCE B32 V3::Parallel(const V3& a, const V3& b){
		return (AU::Abs((a | b) - 1.0f) <= VECTOR_PARALLEL_THRESHOLD);
	}

	INLINEFORCE F32 V3::Triple(const V3& a, const V3& b, const V3& c){
		return ((a.x *(b.y * c.z - b.z * c.y))
			  + (a.y *(b.z * c.x - b.x * c.z)) 
			  + (a.z *(b.x * c.y - b.y * c.x)));
	}

	INLINEFORCE F32 V3::VectorPlaneDist(const V3& point, const V3& planeBase, const V3& planeNormal){
		return (point - planeBase) | planeNormal;
	}

	INLINEFORCE V3 V3::ProjectPlane(const V3& point, const V3& planeBase, const V3& planeNormal){
		return point - ((point - planeBase) | planeNormal) * planeNormal;
	}

	INLINEFORCE V2 V3::XY() const{
		return V2(x, y);
	}

	INLINEFORCE V2 V3::YZ() const{
		return V2(y, z);
	}

	INLINEFORCE V2 V3::XZ() const{
		return V2(x, z);
	}

	INLINEFORCE V2 V3::YX() const{
		return V2(y, x);
	}

	INLINEFORCE V2 V3::ZY() const{
		return V2(z, y);
	}

	INLINEFORCE V2 V3::ZX() const{
		return V2(z, x);
	}

	INLINEFORCE glob U64 HashV3(const V3& value){
		U64 result = 17;
		result = 31 * result + HashF32(value.x);
		result = 31 * result + HashF32(value.y);
		result = 31 * result + HashF32(value.z);
		return result;
	}

	/************************************************************************/
	/* Four-Dimensional Vector                                              */
	/************************************************************************/
	struct V4{
		F32 x;
		F32 y;
		F32 z;
		F32 w;

		glob const V4 ZERO;
		glob const V4 UNIT;
		glob const V4 X_AXIS;
		glob const V4 Y_AXIS;
		glob const V4 Z_AXIS;
		glob const V4 W_AXIS;
		glob const V4 XY_AXIS;
		glob const V4 YZ_AXIS;
		glob const V4 ZW_AXIS;
		glob const V4 XZ_AXIS;
		glob const V4 YW_AXIS;
		glob const V4 XW_AXIS;
		glob const V4 XYZ_AXIS;
		glob const V4 XYW_AXIS;
		glob const V4 XZW_AXIS;
		glob const V4 YZW_AXIS;

		INLINEFORCE V4(){}
		INLINEFORCE explicit V4(F32 s);
		INLINEFORCE V4(F32 x, F32 y, F32 z, F32 w = 1.0f);
		INLINEFORCE V4(const V3& v, F32 w = 1.0f);
		INLINEFORCE V4(const V2& v, F32 z = 0.0f, F32 w = 1.0f);
		INLINEFORCE V4(const V2& xy,const V2& zw);
		INLINEFORCE V4(const V2& v);
		INLINEFORCE V4(const V3& v);
		INLINEFORCE V4(const V4& v);
		INLINEFORCE V4(V2&& v);
		INLINEFORCE V4(V3&& v);
		INLINEFORCE V4(V4&& v);

		INLINEFORCE V4 operator=(const V2& v);
		INLINEFORCE V4 operator=(const V3& v);
		INLINEFORCE V4 operator=(const V4& v);
		INLINEFORCE V4 operator=(V2&& v);
		INLINEFORCE V4 operator=(V3&& v);
		INLINEFORCE V4 operator=(V4&& v);

		INLINEFORCE V4 operator+(const V2& v) const;
		INLINEFORCE V4 operator+(const V3& v) const;
		INLINEFORCE V4 operator+(const V4& v) const;
		INLINEFORCE V4 operator+(F32 s) const;

		INLINEFORCE V4 operator-(const V2& v) const;
		INLINEFORCE V4 operator-(const V3& v) const;
		INLINEFORCE V4 operator-(const V4& v) const;
		INLINEFORCE V4 operator-(F32 s) const;

		INLINEFORCE V4 operator*(const V2& v) const;
		INLINEFORCE V4 operator*(const V3& v) const;
		INLINEFORCE V4 operator*(const V4& v) const;
		INLINEFORCE V4 operator*(F32 s) const;

		INLINEFORCE V4 operator/(const V2& v) const;
		INLINEFORCE V4 operator/(const V3& v) const;
		INLINEFORCE V4 operator/(const V4& v) const;
		INLINEFORCE V4 operator/(F32 s) const;

		INLINEFORCE F32 operator|(const V2& v) const;
		INLINEFORCE F32 operator|(const V3& v) const;
		INLINEFORCE F32 operator|(const V4& v) const;

		INLINEFORCE V4 operator^(const V2& v) const;
		INLINEFORCE V4 operator^(const V3& v) const;
		INLINEFORCE V4 operator^(const V4& v) const;

		INLINEFORCE B32 operator==(const V4& v) const; //vector equality check
		INLINEFORCE B32 operator==(F32 s) const; //scalar comparison
		INLINEFORCE B32 operator!= (const V4& v) const; //vector inequality check
		INLINEFORCE B32 operator!= (F32 s) const; //scalar inequality check
		INLINEFORCE B32 operator<(const V4& v) const; //vector less-than comparison
		INLINEFORCE B32 operator<(F32 s) const; //scalar less-than comparison
		INLINEFORCE B32 operator>(const V4& v) const; //vector more-than comparison
		INLINEFORCE B32 operator>(F32 s) const; //scalar more-than comparison
		INLINEFORCE B32 operator<=(const V4& v) const; //vector less-than-equals comparison
		INLINEFORCE B32 operator<=(F32 s) const; //scalar less-than-equals comparison
		INLINEFORCE B32 operator>=(const V4& v) const; //vector more-than-equals comparison
		INLINEFORCE B32 operator>=(F32 s) const; //scalar more-than-equals comparison

		INLINEFORCE V4 operator-() const; // Negate this vector

		INLINEFORCE V4 operator+=(const V2& v);
		INLINEFORCE V4 operator+=(const V3& v);
		INLINEFORCE V4 operator+=(const V4& v);
		INLINEFORCE V4 operator+=(F32 v);

		INLINEFORCE V4 operator-=(const V2& v);
		INLINEFORCE V4 operator-=(const V3& v);
		INLINEFORCE V4 operator-=(const V4& v);
		INLINEFORCE V4 operator-=(F32 v);

		INLINEFORCE V4 operator*=(const V2& v);
		INLINEFORCE V4 operator*=(const V3& v);
		INLINEFORCE V4 operator*=(const V4& v);
		INLINEFORCE V4 operator*=(F32 v);

		INLINEFORCE V4 operator/=(const V2& v);
		INLINEFORCE V4 operator/=(const V3& v);
		INLINEFORCE V4 operator/=(const V4& v);
		INLINEFORCE V4 operator/=(F32 v);

		INLINEFORCE V4 operator%(F32 tolerance) const; //Normalize with tolerance
		INLINEFORCE V4 operator%=(const V2& v);
		INLINEFORCE V4 operator%=(const V3& v);
		INLINEFORCE V4 operator%=(const V4& v);

		INLINEFORCE F32 operator~() const; //euclidean length squared

		INLINEFORCE V4 operator++(); //doubles vector magnitude, chained return
		INLINEFORCE V4 operator--(); //half of vector magnitude, chained return

		INLINEFORCE F32& operator[](U32 index); // gets specific component reference
		INLINEFORCE F32 operator[](U32 index) const; // gets specific component copy

		INLINEFORCE glob F32 Dot3(const V4& a, const V4& b); //global dot product
		INLINEFORCE glob F32 Dot(const V4& a, const V4& b); //global dot product
		INLINEFORCE glob F32 Dot(const V4& a, const V3& b); //global dot product
		INLINEFORCE glob F32 Dot(const V3& a, const V4& b); //global dot product
		INLINEFORCE glob F32 Dot(const V4& a, const V2& b); //global dot product
		INLINEFORCE glob F32 Dot(const V2& a, const V4& b); //global dot product

		INLINEFORCE glob F32 Dist(const V4& a, const V4& b); //global distance
		INLINEFORCE glob F32 Dist(const V4& a, const V3& b); //global distance
		INLINEFORCE glob F32 Dist(const V3& a, const V4& b); //global distance
		INLINEFORCE glob F32 Dist(const V4& a, const V2& b); //global distance
		INLINEFORCE glob F32 Dist(const V2& a, const V4& b); //global distance

		INLINEFORCE glob F32 Dist2(const V4& a, const V4& b); //global distance squared
		INLINEFORCE glob F32 Dist2(const V4& a, const V3& b); //global distance squared
		INLINEFORCE glob F32 Dist2(const V3& a, const V4& b); //global distance squared
		INLINEFORCE glob F32 Dist2(const V4& a, const V2& b); //global distance squared
		INLINEFORCE glob F32 Dist2(const V2& a, const V4& b); //global distance squared

		INLINEFORCE glob V4 Cross(const V4& a, const V4& b); //global cross product
		INLINEFORCE glob V4 Cross(const V4& a, const V3& b); //global cross product
		INLINEFORCE glob V4 Cross(const V4& a, const V2& b); //global cross product

		INLINEFORCE B32 Equals(const V4& v, F32 tolerance = EPSILON) const; //fuzzy equality test
		INLINEFORCE B32 AllComponentsEqual(F32 tolerance = EPSILON) const;

		INLINEFORCE V4 Set(F32 x, F32 y, F32 z, F32 w = 1.0f); //set components, chained return

		INLINEFORCE F32 Max() const; // gets max component
		INLINEFORCE F32 Min() const; // gets min component

		INLINEFORCE V3 Abs() const; // Absolute value of every component of this vector

		INLINEFORCE F32 AbsMax() const; // gets absolute max component
		INLINEFORCE F32 AbsMin() const; // gets absolute min component

		INLINEFORCE V4 ComponentMin(const V4& rhs) const; //component wise max of two vectors
		INLINEFORCE V4 ComponentMax(const V4& rhs) const; //component wise max of two vectors
		INLINEFORCE V4 ComponentMax(const V3& rhs) const; //component wise max of two vectors
		INLINEFORCE V4 ComponentMin(const V3& rhs) const; //component wise min of two vectors
		INLINEFORCE V4 ComponentMin(const V2& rhs) const; //component wise min of two vectors
		INLINEFORCE V4 ComponentMax(const V2& rhs) const; //component wise min of two vectors


		INLINEFORCE F32 Len() const; // euclidean length
		INLINEFORCE F32 Len3() const; // euclidean length of three dimensional components
		INLINEFORCE F32 Len2() const; // euclidean length squared
		INLINEFORCE F32 Len32() const; // euclidean length squared of three dimensional components

		INLINEFORCE V4 SafeNormalize(F32 tolerance = EZERO) const; //safe normalization

		INLINEFORCE V4 Nor(F32 tolerance = EZERO); // self-normalization, chained return

		INLINEFORCE B32 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		INLINEFORCE B32 IsZero() const; //check if absolutely zero

		INLINEFORCE void ToDirectionAndMagnitude(V4* v, F32* s) const; //returns a unit direction vector as well as a magnitude
		INLINEFORCE V4 SignV4() const; //sets each component to either +1 or -1
		INLINEFORCE V4 Projection() const; //Projects 2D components of vector based on z

		INLINEFORCE V4 UnsafeNormalize() const;

		INLINEFORCE V4 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

		INLINEFORCE V4 Reciprocal() const; //Reciprocates vector

		INLINEFORCE B32 Uniform(F32 Tolerance = EPSILON) const; //checks if x == y == z == w
		INLINEFORCE B32 Uniform3(F32 Tolerance = EPSILON) const; //checks if x == y == z

		INLINEFORCE V4 Reflect(const V4& normal) const; // reflects vector across normal vector
		INLINEFORCE V4 Reflect3(const V4& normal) const; // reflects vector across normal vector

		//TODO: REFLECT ACROSS PLANE

		//TODO: ANGLULAR ROTATION

		INLINEFORCE B32 IsUnit(F32 len2Tolerance = EPSILON) const; //checks if it is unit

		INLINEFORCE V4 Project(const V4& v) const; // Projects this vector onto another vector

		INLINEFORCE glob B32 EqualVectors(const V4& a, const V4& b); // Checks if vectors are equal
		INLINEFORCE glob B32 VectorsAreNear(const V4& a, const V4& b, F32 dist);// checks if vectors are within distance

		//Distance from plane
		INLINEFORCE glob F32 VectorPlaneDist(const V4& point, const V3& planeBase, const V3& planeNormal);

		INLINEFORCE glob V4 ProjectPlane(const V4& point, const V3& planeBase, const V3& planeNormal);

		INLINEFORCE glob B32 Parallel(const V4& a, const V4& b); // checks if vectors are roughly parallel

		INLINEFORCE glob F32 Triple(const V4& a, const V4& b, const V4& c); // return triple: x|(y^z)

		INLINEFORCE void BestAxesV3(V3* axis1, V3* axis2); //Good arbitrary axis to represent U and V axes of a plane, given the normal

		//TODO: BEZIER CURVE		

		INLINEFORCE V2 XY() const; //Swizzles to V2(x,y)
		INLINEFORCE V2 YZ() const; //Swizzles to V2(y,z)
		INLINEFORCE V2 XZ() const; //Swizzles to V2(x,z)
		INLINEFORCE V2 YX() const; //Swizzles to V2(y,x)
		INLINEFORCE V2 ZY() const; //Swizzles to V2(z,y)
		INLINEFORCE V2 ZX() const; //Swizzles to V2(z,x)
		INLINEFORCE V2 XW() const; //Swizzles to V2(x,w)
		INLINEFORCE V2 YW() const; //Swizzles to V2(y,w)
		INLINEFORCE V2 ZW() const; //Swizzles to V2(z,w)
		INLINEFORCE V2 WX() const; //Swizzles to V2(w,x)
		INLINEFORCE V2 WY() const; //Swizzles to V2(w,y)
		INLINEFORCE V2 WZ() const; //Swizzles to V2(w,z)
		INLINEFORCE V3 XYZ() const; //Swizzles to V3(x,y,z)
		INLINEFORCE V3 XYW() const; //Swizzles to V3(x,y,w)
		INLINEFORCE V3 XZW() const; //Swizzles to V3(x,z,w)
		INLINEFORCE V3 YZW() const; //Swizzles to V3(y,z,w)

		INLINEFORCE V3 AsV3() const; //Returns V3 components

#if CHECK_NAN
		INLINEFORCE void CheckNaN() const{
			AVRO_ASSERT(!HasNaN(), "V4 contains NaN");
		}
#else
		INLINEFORCE void CheckNaN() const{}
#endif

		INLINEFORCE B32 HasNaN() const{
			return (IsNaN(x) || IsNaN(y) || IsNaN(z) || IsNaN(w) || !IsFinite(x) || !IsFinite(y) || !IsFinite(z) || !IsFinite(w));
		}
	};

	//Functions
	INLINEFORCE V4::V4(F32  s) :x(s), y(s), z(s), w(s){ V4::CheckNaN(); }

	INLINEFORCE V4::V4(F32 x, F32 y, F32 z, F32 w) : x(x), y(y), z(z), w(w){ V4::CheckNaN(); }

	INLINEFORCE V4::V4(const V4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){ V4::CheckNaN(); }
	INLINEFORCE V4::V4(const V3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(1){ V4::CheckNaN(); }
	INLINEFORCE V4::V4(const V3& rhs) : x(rhs.x), y(rhs.y), z(0), w(1){ V4::CheckNaN(); }
	INLINEFORCE V4::V4(const V3& rhs, F32 w) : x(rhs.x), y(rhs.y), z(rhs.z), w(w){ V4::CheckNaN(); }
	INLINEFORCE V4::V4(const V2& rhs, F32 z, F32 w) : x(rhs.x), y(rhs.y), z(z), w(w){ V4::CheckNaN(); }

	INLINEFORCE V4::V4(V4&& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		rhs.w = 0;
		CheckNaN();
	}

	INLINEFORCE V4::V4(V3&& rhs) :x(rhs.x), y(rhs.y), z(rhs.z), w(1){
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		CheckNaN();
	}

	INLINEFORCE V4::V4(V2&& rhs) :x(rhs.x), y(rhs.y), z(0), w(1){
		rhs.x = 0;
		rhs.y = 0;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator=(const V4& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator=(const V3& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 1;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator=(const V2& rhs){
		x = rhs.x;
		y = rhs.y;
		z = 0;
		w = 1;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator=(V4&& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		rhs.w = 0;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator=(V3&& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 1;
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator=(V2&& rhs){
		x = rhs.x;
		y = rhs.y;
		z = 0;
		w = 1;
		rhs.x = 0;
		rhs.y = 0;
		CheckNaN();
	}

	INLINEFORCE V4 V4::operator+(const V4& v) const{
		return V4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	INLINEFORCE V4 V4::operator+(const V3& v) const{
		return V4(x + v.x, y + v.y, z + v.z, w + 1);
	}

	INLINEFORCE V4 V4::operator+(const V2& v) const{
		return V4(x + v.x, y + v.y, z, w + 1);
	}

	INLINEFORCE V4 V4::operator+(F32 s) const{
		return V4(x + s, y + s, z + s, w + s);
	}

	INLINEFORCE V4 V4::operator-(const V4& v) const{
		return V4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	INLINEFORCE V4 V4::operator-(const V3& v) const{
		return V4(x - v.x, y - v.y, z - v.z, w - 1);
	}

	INLINEFORCE V4 V4::operator-(const V2& v) const{
		return V4(x - v.x, y - v.y, z, w - 1);
	}

	INLINEFORCE V4 V4::operator-(F32 s) const{
		return V4(x - s, y - s, z - s, w - s);
	}

	INLINEFORCE V4 V4::operator*(const V4& v) const{
		return V4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	INLINEFORCE V4 V4::operator*(const V3& v) const{
		return V4(x * v.x, y * v.y, z * v.z, w);
	}

	INLINEFORCE V4 V4::operator*(const V2& v) const{
		return V4(x * v.x, y * v.y, z, w);
	}

	INLINEFORCE V4 V4::operator*(F32 s) const{
		return V4(x * s, y * s, z * s, w * s);
	}

	INLINEFORCE V4 V4::operator/(const V4& v) const{
		return V4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	INLINEFORCE V4 V4::operator/(const V3& v) const{
		return V4(x / v.x, y / v.y, z / v.z, w);
	}

	INLINEFORCE V4 V4::operator/(const V2& v) const{
		return V4(x / v.x, y / v.y, z, w);
	}

	INLINEFORCE V4 V4::operator/(F32 s) const{
		const F32 scale = 1.0f / s;
		return V4(x * scale, y * scale, z * scale, w * scale);
	}

	INLINEFORCE V4 operator*(F32 s, const V4& v){
		return v * s;
	}

	INLINEFORCE F32 V4::operator|(const V4& v) const{
		return x*v.x + y*v.y + z*v.z + w+v.w;
	}

	INLINEFORCE F32 V4::operator|(const V3& v) const{
		return x*v.x + y*v.y + z*v.z;
	}

	INLINEFORCE F32 V4::operator|(const V2& v) const{
		return x*v.x + y*v.y;
	}

	INLINEFORCE V4 V4::operator^(const V4& v) const{
		return V4(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 0);
	}

	INLINEFORCE V4 V4::operator^(const V3& v) const{
		return V4(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 0);
	}

	INLINEFORCE V4 V4::operator^(const V2& v) const{
		return V4(-z*v.y, z*v.x, x*v.y - y*v.x, 0);
	}

	INLINEFORCE B32 V4::operator==(const V4& v) const{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	INLINEFORCE B32 V4::operator==(F32 s) const{
		return x == s && y == s && z == s && w == s;
	}

	INLINEFORCE B32 V4::operator!=(const V4& v) const{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	INLINEFORCE B32 V4::operator!=(F32 s) const{
		return x != s || y != s || z != s || w != s;
	}

	INLINEFORCE B32 V4::operator<(const V4& v) const{
		return x < v.x && y < v.y && z < v.z && w < v.w;
	}

	INLINEFORCE B32 V4::operator<(F32 s) const{
		return x < s && y < s && z < s && w < s;
	}

	INLINEFORCE B32 V4::operator>(const V4& v) const{
		return x > v.x && y > v.y && z > v.z && w > v.w;
	}

	INLINEFORCE B32 V4::operator>(F32 s) const{
		return x > s && y > s && z > s && w > s;
	}

	INLINEFORCE B32 V4::operator<=(const V4& v) const{
		return x <= v.x && y <= v.y && z <= v.z && w <= v.w;
	}

	INLINEFORCE B32 V4::operator<=(F32 s) const{
		return x <= s && y <= s && z <= s && w <= s;
	}

	INLINEFORCE B32 V4::operator>=(const V4& v) const{
		return x >= v.x && y >= v.y && z >= v.z && w >= v.w;
	}

	INLINEFORCE B32 V4::operator>=(F32 s) const{
		return x >= s && y >= s && z >= s && w >= s;
	}

	INLINEFORCE V4 V4::operator-() const{
		return V4(-x, -y, -z, -w);
	}

	INLINEFORCE V4 V4::operator+=(const V4& v){
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator+=(const V3& v){
		x += v.x;
		y += v.y;
		z += v.z;
		w += 1;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator+=(const V2& v){
		x += v.x;
		y += v.y;
		w += 1;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator+=(F32 s){
		x += s;
		y += s;
		z += s;
		w += s;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator-=(const V4& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator-=(const V3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= 1;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator-=(const V2& v){
		x -= v.x;
		y -= v.y;
		w -= 1;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator-=(F32 s){
		x -= s;
		y -= s;
		z -= s;
		w -= s;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator*=(const V4& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator*=(const V3& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator*=(const V2& v){
		x *= v.x;
		y *= v.y;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator*=(F32 s){
		x *= s;
		y *= s;
		z *= s;
		w = s;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator/=(const V4& v){
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator/=(const V3& v){
		x /= v.x;
		y /= v.y;
		z /= v.z;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator/=(const V2& v){
		x /= v.x;
		y /= v.y;
		z = ARCFINITY;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator/=(F32 s){
		const F32 scale = 1.0f / s;
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
		CheckNaN();
		return *this;
	}

	INLINEFORCE V4 V4::operator%(F32 tolerance) const{
#ifdef AVRO_DEBUG
		const F32 squaredSum = x*x + y*y + z*z;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			return V4(x*scl, y*scl, z*scl, 0.0f);
		}
		return V4();
#elif AVRO_PROFILE
		const F32 squaredSum = x*x + y*y + z*z;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			return V4(x*scl, y*scl, z*scl, 0.0f);
		}
		return V4();;
#endif
		const F32 scl = SqrtInv(x*x + y*y + z*z);
		return V4(x*scl, y*scl, z*scl, w*scl);
	}

	INLINEFORCE V4 V4::operator%=(const V4& v){
		*this = v % EZERO;
		return *this;
	}

	INLINEFORCE V4 V4::operator%=(const V3& v){
		*this = v % EZERO;
		return *this;
	}

	INLINEFORCE V4 V4::operator%=(const V2& v){
		*this = v % EZERO;
		return *this;
	}

	INLINEFORCE F32 V4::operator~() const{
		return x*x + y*y + z*z + w*w;
	}

	INLINEFORCE V4 V4::operator++(){
		x *= 2.f;
		y *= 2.f;
		z *= 2.f;
		w *= 2.f;
		return *this;
	}

	INLINEFORCE V4 V4::operator--(){
		x *= 0.5f;
		y *= 0.5f;
		z *= 0.5f;
		w *= 0.5f;
		return *this;
	}

	INLINEFORCE F32& V4::operator[](U32 index){
		AVRO_ASSERT(index < 4, "V4 only contains 4 components, index out of bounds");
		if (index == 0) return x;
		else if (index == 1) return y;
		else if (index == 2) return z;
		else return w;
	}

	INLINEFORCE F32 V4::operator[](U32 index) const{
		AVRO_ASSERT(index < 4, "V4 only contains 4 components, index out of bounds");
		if (index == 0) return x;
		else if (index == 1) return y;
		else if (index == 1) return z;
		else return w;
	}

	INLINEFORCE F32 V4::Dot3(const V4& a, const V4& b){
		return a | b;
	}

	INLINEFORCE F32 V4::Dot(const V4& a, const V4& b){
		return a | b;
	}

	INLINEFORCE F32 V4::Dot(const V4& a, const V3& b){
		return a | b;
	}

	INLINEFORCE F32 V4::Dot(const V3& a, const V4& b){
		return b | a;
	}

	INLINEFORCE F32 V4::Dot(const V4& a, const V2& b){
		return a | b;
	}

	INLINEFORCE F32 V4::Dot(const V2& a, const V4& b){
		return b | a;
	}

	INLINEFORCE F32 V4::Dist2(const V4& a, const V4& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(b.z - a.z) + Sq(b.w - a.w);
	}

	INLINEFORCE F32 V4::Dist2(const V4& a, const V3& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(b.z - a.z) + Sq(1 - a.w);
	}

	INLINEFORCE F32 V4::Dist2(const V3& a, const V4& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(b.z - a.y) + Sq(b.w - 1);
	}

	INLINEFORCE F32 V4::Dist2(const V4& a, const V2& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(a.z) + Sq(1 - a.w);
	}

	INLINEFORCE F32 V4::Dist2(const V2& a, const V4& b){
		return Sq(b.x - a.x) + Sq(b.y - a.y) + Sq(b.z) + Sq(b.w - 1);
	}

	INLINEFORCE F32 V4::Dist(const V4& a, const V4& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE F32 V4::Dist(const V4& a, const V3& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE F32 V4::Dist(const V3& a, const V4& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE F32 V4::Dist(const V4& a, const V2& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE F32 V4::Dist(const V2& a, const V4& b){
		return Sqrt(Dist2(a, b));
	}

	INLINEFORCE V4 V4::Cross(const V4& a, const V4& b){
		return a ^ b;
	}

	INLINEFORCE V4 V4::Cross(const V4& a, const V3& b){
		return a ^ b;
	}

	INLINEFORCE V4 V4::Cross(const V4& a, const V2& b){
		return a ^ b;
	}

	INLINEFORCE B32 V4::Equals(const V4& v, F32 tolerance) const{
		return AU::Abs(x - v.x) < tolerance && AU::Abs(y - v.y) < tolerance 
			&& AU::Abs(z - v.z) && AU::Abs(w - v.w) < tolerance;
	}

	INLINEFORCE B32 V4::AllComponentsEqual(F32 tolerance) const{
		return AU::Abs(x - y) < tolerance && AU::Abs(y - z) < tolerance 
			&& AU::Abs(y - z) < tolerance && AU::Abs(z - w) < tolerance;
	}

	INLINEFORCE V4 V4::Set(F32 x, F32 y, F32 z, F32 w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		CheckNaN();
		return *this;
	}

	INLINEFORCE F32 Dist2BoxToPoint(const V4& min, const V4& max, const V4& point){
		F32 dist2 = 0.0f; //Accumulative distance squared

		//Unrolled loop, checks axes
		if (point.x < min.x)
			dist2 += AU::Sq(point.x - min.x);
		else if (point.x > max.x)
			dist2 += AU::Sq(point.x - max.x);

		if (point.y < min.y)
			dist2 += AU::Sq(point.y - min.y);
		else if (point.y > max.y)
			dist2 += AU::Sq(point.y - max.y);

		if (point.z < min.z)
			dist2 += AU::Sq(point.z - min.z);
		else if (point.z > max.z)
			dist2 += AU::Sq(point.z - max.z);

		if (point.w < min.w)
			dist2 += AU::Sq(point.w - min.w);
		else if (point.w > max.w)
			dist2 += AU::Sq(point.w - max.w);

		return dist2;
	}

	INLINEFORCE F32 V4::Min() const{
		return AU::Min(AU::Min(AU::Min(x, y), z), w);
	}

	INLINEFORCE F32 V4::Max() const{
		return AU::Max(AU::Max(AU::Max(x, y), z), w);
	}

	INLINEFORCE F32 V4::AbsMin() const{
		return AU::Min(AU::Min(AU::Min(AU::Abs(x), AU::Abs(y)), AU::Abs(z)), AU::Abs(w));
	}

	INLINEFORCE F32 V4::AbsMax() const{
		return AU::Max(AU::Max(AU::Max(AU::Abs(x), AU::Abs(y)), AU::Abs(z)), AU::Abs(w));
	}

	INLINEFORCE V4 V4::ComponentMin(const V4& v) const{
		return V4(AU::Min(x, v.x), AU::Min(y, v.y), AU::Min(z, v.z), AU::Min(w, v.w));
	}

	INLINEFORCE V4 V4::ComponentMax(const V4& v) const{
		return V4(AU::Max(x, v.x), AU::Max(y, v.y), AU::Max(z, v.z), AU::Max(w, v.w));
	}

	INLINEFORCE V4 V4::ComponentMin(const V3& v) const{
		return V4(AU::Min(x, v.x), AU::Min(y, v.y), AU::Min(z, v.z), AU::Min(w, 1.0f));
	}

	INLINEFORCE V4 V4::ComponentMax(const V3& v) const{
		return V4(AU::Max(x, v.x), AU::Max(y, v.y), AU::Max(z, v.z), AU::Max(w, 1.0f));
	}

	INLINEFORCE V4 V4::ComponentMin(const V2& v) const{
		return V4(AU::Min(x, v.x), AU::Min(y, v.y), AU::Min(z, 0.0f), AU::Min(w, 1.0f));
	}

	INLINEFORCE V4 V4::ComponentMax(const V2& v) const{
		return V4(AU::Max(x, v.x), AU::Max(y, v.y), AU::Max(z, 0.0f), AU::Max(w, 1.0f));
	}

	INLINEFORCE F32 V4::Len() const{
		return AU::Sqrt(x*x + y*y + z*z + w*w);
	}

	INLINEFORCE F32 V4::Len3() const{
		return AU::Sqrt(x*x + y*y + z*z);
	}

	INLINEFORCE F32 V4::Len2() const{
		return x*x + y*y + z*z + w*w;
	}

	INLINEFORCE F32 V4::Len32() const{
		return x*x + y*y + z*z;
	}

	INLINEFORCE V4 V4::SafeNormalize(F32 tolerance) const{
		const F32 squaredSum = x*x + y*y + z*z + w*w;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			return V4(x*scl, y*scl, z*scl);
		}
		return V4();
	}

	INLINEFORCE V4 V4::Nor(F32 tolerance){
#ifdef AVRO_DEBUG
		const F32 squaredSum = x*x + y*y + z*z + w*w;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			x *= scl;
			y *= scl;
			z *= scl;
			w *= scl;
			CheckNaN();
			return *this;
		}
		x = y = z = 0;
		w = 1;
		return *this;
#elif AVRO_PROFILE
		const F32 squaredSum = x*x + y*y + z*z + w*w;
		if (squaredSum > tolerance){
			const F32 scl = SqrtInv(squaredSum);
			x *= scl;
			y *= scl;
			z *= scl;
			w *= scl;
			CheckNaN(0;)
			return *this;
		}
		x = y = z = 0;
		w = 1;
		return *this;;
#endif
		const F32 scl = SqrtInv(x*x + y*y + z*z + w*w);
		x *= scl;
		y *= scl;
		z *= scl;
		w *= scl;
		CheckNaN();
		return *this;
	}

	INLINEFORCE B32 V4::IsEpsilonZero(F32 tolerance) const{
		return AU::Abs(x) < tolerance && AU::Abs(y) < tolerance && AU::Abs(z) < tolerance && AU::Abs(w) < tolerance;
	}

	INLINEFORCE B32 V4::IsZero() const{
		return x == 0.f && y == 0.f && z == 0.f && w == 0.0f;
	}

	INLINEFORCE void V4::ToDirectionAndMagnitude(V4* v, F32* s) const{
		*s = Len();
		if (*s > EPSILON){
			F32 lenReciprocal = 1.0f / *s;
			*v = V4(x * lenReciprocal, y * lenReciprocal, z * lenReciprocal);
		}
		else{
			*v = V4::ZERO;
		}
	}

	INLINEFORCE V4 V4::SignV4() const{
		return V4(AU::SelectF32(x, 1.f, -1.f), AU::SelectF32(y, 1.f, -1.f), AU::SelectF32(z, 1.f, -1.f), AU::SelectF32(w, 1.f, -1.f));
	}

	INLINEFORCE V4 V4::Projection() const{
		const F32 rw = 1.f / w;
		return V4(x*rw, y*rw, z*rw, 1.0f);
	}

	INLINEFORCE V4 V4::UnsafeNormalize() const{
		const F32 scl = SqrtInv(x*x + y*y + z*z + w*w);
		return V3(x*scl, y*scl, z*scl);
	}

	INLINEFORCE V4 V4::Clamp(F32 min, F32 max) const{
		F32 len = Len();
		const V4 dir = (len > EPSILON) ? (*this / len) : V4::ZERO;
		len = AU::Clamp(len, min, max);
		return len * dir;
	}

	INLINEFORCE V4 V4::Reciprocal() const{
		V4 vec;
		if (x != 0.f) vec.x = 1.f / x;
		else vec.x = ARCFINITY;
		if (y != 0.f) vec.y = 1.f / y;
		else vec.y = ARCFINITY;
		if (z != 0.f) vec.z = 1.f / z;
		else vec.z = ARCFINITY;
		if (w != 0.f) vec.z = 1.f / w;
		else vec.w = ARCFINITY;
		return vec;
	}

	INLINEFORCE B32 V4::Uniform(F32 tolerance) const{
		return (AU::Abs(x - y) < tolerance) && (AU::Abs(y - z) < tolerance) && (AU::Abs(z - w) < tolerance);
	}

	INLINEFORCE B32 V4::Uniform3(F32 tolerance) const{
		return (AU::Abs(x - y) < tolerance) && (AU::Abs(y - z) < tolerance);
	}

	INLINEFORCE V4 V4::Reflect(const V4& normal) const{
		return *this - normal * 2.f * (*this | normal);
	}

	INLINEFORCE V4 V4::Reflect3(const V4& normal) const{
		return *this - normal * 2.f * Dot3(*this, normal);
	}

	INLINEFORCE B32 V4::IsUnit(F32 len2Tolerance) const{
		return AU::Abs(1.0f - Len2()) < len2Tolerance;
	}

	INLINEFORCE V4 V4::Project(const V4& v) const{
		return (v * ((*this | v) / (v | v)));
	}

	INLINEFORCE B32 V4::EqualVectors(const V4& a, const V4& b){
		return (AU::Abs(a.x - b.x) < VECTOR_PROXIMITY_THRESHOLD
			&& AU::Abs(a.y - b.y) < VECTOR_PROXIMITY_THRESHOLD
			&& AU::Abs(a.z - b.z) < VECTOR_PROXIMITY_THRESHOLD
			&& AU::Abs(a.w - b.w) < VECTOR_PROXIMITY_THRESHOLD);
	}

	INLINEFORCE B32 V4::VectorsAreNear(const V4& a, const V4& b, F32 dist){
		return (AU::Abs(a.x - b.x) < dist
			&& AU::Abs(a.y - b.y) < dist
			&& AU::Abs(a.z - b.z) < dist
			&& AU::Abs(a.w - b.w) < dist);
	}

	INLINEFORCE B32 V4::Parallel(const V4& a, const V4& b){
		return (AU::Abs((a | b) - 1.0f) <= VECTOR_PARALLEL_THRESHOLD);
	}

	INLINEFORCE F32 V4::Triple(const V4& a, const V4& b, const V4& c){
		return a|(b^c);
	}

	INLINEFORCE F32 V4::VectorPlaneDist(const V4& point, const V3& planeBase, const V3& planeNormal){
		return (point - planeBase) | planeNormal;
	}

	INLINEFORCE V4 V4::ProjectPlane(const V4& point, const V3& planeBase, const V3& planeNormal){
		return point - ((point - planeBase) | planeNormal) * planeNormal;
	}

	INLINEFORCE V2 V4::XY() const{
		return V2(x, y);
	}

	INLINEFORCE V2 V4::YZ() const{
		return V2(y, z);
	}

	INLINEFORCE V2 V4::XZ() const{
		return V2(x, z);
	}

	INLINEFORCE V2 V4::XW() const{
		return V2(x, w);
	}

	INLINEFORCE V2 V4::YW() const{
		return V2(y, w);
	}

	INLINEFORCE V2 V4::ZW() const{
		return V2(z, w);
	}

	INLINEFORCE V2 V4::YX() const{
		return V2(y, x);
	}

	INLINEFORCE V2 V4::ZY() const{
		return V2(z, y);
	}

	INLINEFORCE V2 V4::ZX() const{
		return V2(z, x);
	}

	INLINEFORCE V2 V4::WX() const{
		return V2(w, x);
	}

	INLINEFORCE V2 V4::WY() const{
		return V2(w, y);
	}

	INLINEFORCE V2 V4::WZ() const{
		return V2(w, z);
	}

	INLINEFORCE V3 V4::XYZ() const{
		return V3(x, y, z);
	}

	INLINEFORCE V3 V4::XYW() const{
		return V3(x, y, w);
	}

	INLINEFORCE V3 V4::YZW() const{
		return V3(y, z, w);
	}

	INLINEFORCE V3 V4::XZW() const{
		return V3(x, z, w);
	}

	INLINEFORCE V3 V4::AsV3() const{
		return V3(x, y, z);
	}

	INLINEFORCE glob U64 HashV4(const V4& value){
		U64 result = 17;
		result = 31 * result + HashF32(value.x);
		result = 31 * result + HashF32(value.y);
		result = 31 * result + HashF32(value.z);
		result = 31 * result + HashF32(value.w);
		return result;
	}
	
	/************************************************************************/
	/* Quaternion                                                           */
	/************************************************************************/
	struct Q4{
		F32 x;
		F32 y;
		F32 z;
		F32 w;

		glob const Q4 ZERO;
		glob const Q4 UNIT;
		glob const Q4 X_AXIS;
		glob const Q4 Y_AXIS;
		glob const Q4 Z_AXIS;
		glob const Q4 W_AXIS;
		glob const Q4 XY_AXIS;
		glob const Q4 YZ_AXIS;
		glob const Q4 ZW_AXIS;
		glob const Q4 XZ_AXIS;
		glob const Q4 YW_AXIS;
		glob const Q4 XW_AXIS;
		glob const Q4 XYZ_AXIS;
		glob const Q4 XYW_AXIS;
		glob const Q4 XZW_AXIS;
		glob const Q4 YZW_AXIS;

		INLINEFORCE Q4(){} //Default ctor
		INLINEFORCE explicit Q4(F32 s); //Scalar ctor
		INLINEFORCE Q4(F32 x, F32 y, F32 z, F32 w = 1); //Defined ctor
		INLINEFORCE Q4(const V3& axis, F32 rad); //Axis-Angle ctor
		INLINEFORCE explicit Q4(const M44& m); //Matrix ctor
		INLINEFORCE Q4(const Q4& rhs); //Copy ctor
		INLINEFORCE Q4(Q4&& rhs); //Move ctor

		INLINEFORCE Q4 operator=(const Q4& rhs); //Copy operator
		INLINEFORCE Q4 operator=(Q4&& rhs); //Move operator

		INLINEFORCE Q4 operator+(const Q4& q) const; //Quaternion addition
		INLINEFORCE Q4 operator-(const Q4& q) const; //Quaternion subtraction
		INLINEFORCE Q4 operator*(const V3& v) const; //Quaternion multiplication
		INLINEFORCE Q4 operator*(const M44& m) const; //Quaternion multiplication
		INLINEFORCE Q4 operator*(const Q4& q) const; //Quaternion multiplication
		INLINEFORCE Q4 operator*(F32 scl) const; //Quaternion multiplication
		INLINEFORCE Q4 operator/(F32 scl) const; //Quaternion division

		INLINEFORCE Q4 operator%(F32 tolerance) const; //Quaternion normalization
		INLINEFORCE F32 operator|(const Q4& q) const; //Quaternion dot product
		INLINEFORCE F32 operator~() const; //Euclidean length squared

		INLINEFORCE Q4 operator+=(const Q4& q); //Quaternion self-addition
		INLINEFORCE Q4 operator-=(const Q4& q); //Quaternion self-subtraction
		INLINEFORCE Q4 operator*=(const Q4& q); //Quaternion self-multiplication
		INLINEFORCE Q4 operator*=(F32 scl); //Quaternion self-multiplication
		INLINEFORCE Q4 operator/=(F32 scl); //Quaternion self-division

		INLINEFORCE Q4 operator%=(const Q4& q); //Quaternion self-normalization

		INLINEFORCE B32 operator==(const Q4& q) const; //Equality test
		INLINEFORCE B32 operator!=(const Q4& q) const; //Inequality test

		glob Q4 EulerFactory(const V3& euler); //Vector of radian angles to Quaternion
		INLINEFORCE V3 Euler() const; //Returns vector of radian angles

		INLINEFORCE Q4 Nor(F32 tolerance = EPSILON); //Normalize quaternion, chained return
		INLINEFORCE B32 IsNor() const; //Checks if already normalized

		INLINEFORCE F32 Len() const; //Euclidean length
		INLINEFORCE F32 Len2() const; //Euclidean length squared

		INLINEFORCE void ToAxisAndAngle(V3& axis, F32& angle) const; //Returns axis and angle

		INLINEFORCE V3 Rotate(V3 v) const; //Return vector rotated by this quaternion

		INLINEFORCE Q4 Log() const; //return Q4 with w = 0 and v = theta*v
		INLINEFORCE Q4 Exp() const; //Use after log, Exp(q) = (sin(theta)*v, cos(theta))

		INLINEFORCE Q4 Inverse() const; //Inverse quaternion

		void EnforceShortestArc(const Q4& other); //Enforce the delta between this Q4
												  //and an other Q4 represents the shortest
												  //possible rotation angle

		INLINEFORCE V3 XAxis() const; //Get X rotation axis
		INLINEFORCE V3 YAxis() const; //Get Y rotation axis
		INLINEFORCE V3 ZAxis() const; //Get Z rotation axis

		INLINEFORCE V3 RotationAxis() const; //Axis of the quaternion

		INLINEFORCE B32 HasNaN() const; //Check if there are NaNs

#if CHECK_NAN
		INLINEFORCE void CheckNaN() const{
			AVRO_ASSERT(!HasNaN(), "Q4 contains NaN");
		}
#else
		INLINEFORCE void CheckNaN() const{}
#endif

		glob F32 Error(const Q4& a, const Q4& b); //Error angle [0-1] between to Q4s
		glob F32 ErrorAutoNor(const Q4& a, const Q4& b); //Error with auto-normalization

		glob Q4 QuickLerp(const Q4& a, const Q4& b, const F32 alpha); //Quick Q4 linear 
																				  //interpolation

		glob Q4 QuickBilerp(const Q4& q00, const Q4& q10, const Q4& q01,
										const Q4& q11, F32 fracX, F32 fracY); //Quick Bilinear 
																			  //interpolation

		glob Q4 Slerp(const Q4& a, const Q4& b, F32 alpha); //Spherical interpolation

		glob Q4 FullSlerp(const Q4& a, const Q4& b, F32 alpha); //Slerp with no 
																//shortest distance checks

		glob Q4 Squad(const Q4& q1, const Q4& t1, const Q4& q2, const Q4& t2, F32 alpha); //Find 
				//the point at alpha between start and end Q4s and tangents

		//Calculate tangent between given points
		glob void CalcTangents(const Q4& prevP, const Q4& p, const Q4& nextP, F32 tension, Q4* outTan);

		INLINEFORCE V2 XY() const; //Swizzles to V2(x,y)
		INLINEFORCE V2 YZ() const; //Swizzles to V2(y,z)
		INLINEFORCE V2 XZ() const; //Swizzles to V2(x,z)
		INLINEFORCE V2 YX() const; //Swizzles to V2(y,x)
		INLINEFORCE V2 ZY() const; //Swizzles to V2(z,y)
		INLINEFORCE V2 ZX() const; //Swizzles to V2(z,x)
		INLINEFORCE V2 XW() const; //Swizzles to V2(x,w)
		INLINEFORCE V2 YW() const; //Swizzles to V2(y,w)
		INLINEFORCE V2 ZW() const; //Swizzles to V2(z,w)
		INLINEFORCE V2 WX() const; //Swizzles to V2(w,x)
		INLINEFORCE V2 WY() const; //Swizzles to V2(w,y)
		INLINEFORCE V2 WZ() const; //Swizzles to V2(w,z)
		INLINEFORCE V3 XYZ() const; //Swizzles to V3(x,y,z)
		INLINEFORCE V3 XYW() const; //Swizzles to V3(x,y,w)
		INLINEFORCE V3 XZW() const; //Swizzles to V3(x,z,w)
		INLINEFORCE V3 YZW() const; //Swizzles to V3(y,z,w)

	};

	//Functions

	INLINEFORCE Q4::Q4(F32 s) :x(s), y(s), z(s), w(s){}

	INLINEFORCE Q4::Q4(F32 x, F32 y, F32 z, F32 w = 1):x(x), y(y), z(z), w(w){}

	INLINEFORCE Q4::Q4(const V3& axis, F32 rad){
		const F32 halfAngle = 0.5f * rad;
		const F32 sinHalfAngle = AU::Sin(halfAngle);
		const F32 cosHalfAngle = AU::Cos(halfAngle);

		x = sinHalfAngle * axis.x;
		y = sinHalfAngle * axis.y;
		z = sinHalfAngle * axis.z;
		w = cosHalfAngle;
	}

	INLINEFORCE Q4::Q4(const M44& m){} //TODO: Complete after M44 struct

	INLINEFORCE Q4::Q4(const Q4& rhs): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}

	INLINEFORCE Q4::Q4(Q4&& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){
		rhs.x = 0;
		rhs.y = 0;
		rhs.z = 0;
		rhs.w = 0;
	}

	INLINEFORCE Q4 Q4::operator=(const Q4& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}

	INLINEFORCE Q4 Q4::operator=(Q4&& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		rhs.x = rhs.y = rhs.z = rhs.w = 0;
	}




	/************************************************************************/
	/* Three-By-Three Matrix                                                */
	/************************************************************************/
	struct M33{
		F32 m[9];

		glob const U32 m00 = 0;
		glob const U32 m01 = 3;
		glob const U32 m02 = 6;
		glob const U32 m10 = 1;
		glob const U32 m11 = 4;
		glob const U32 m12 = 7;
		glob const U32 m20 = 2;
		glob const U32 m21 = 5;
		glob const U32 m22 = 8;
	};


	




	/************************************************************************/
	/* Four-By-Three Matrix                                                 */
	/************************************************************************/
	struct M43{
		F32 m[12];
		
		glob const U32 m00 = 0;
		glob const U32 m01 = 4;
		glob const U32 m02 = 8;
		glob const U32 m10 = 1;
		glob const U32 m11 = 5;
		glob const U32 m12 = 9;
		glob const U32 m20 = 2;
		glob const U32 m21 = 6;
		glob const U32 m22 = 10;
		glob const U32 m30 = 3;
		glob const U32 m31 = 7;
		glob const U32 m32 = 11;

	};






	/************************************************************************/
	/* Four-By-Four Matrix                                                  */
	/************************************************************************/
	struct M44{
		F32 m[16];

		glob const U32 m00 = 0;
		glob const U32 m01 = 4;
		glob const U32 m02 = 8;
		glob const U32 m03 = 12;
		glob const U32 m10 = 1;
		glob const U32 m11 = 5;
		glob const U32 m12 = 9;
		glob const U32 m13 = 13;
		glob const U32 m20 = 2;
		glob const U32 m21 = 6;
		glob const U32 m22 = 10;
		glob const U32 m23 = 14;
		glob const U32 m30 = 3;
		glob const U32 m31 = 7;
		glob const U32 m32 = 11;
		glob const U32 m33 = 15;

	};








}

#endif