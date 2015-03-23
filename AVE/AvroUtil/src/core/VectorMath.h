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

		INLINEFORCE B8 Equals(const V2& v, F32 tolerance = EPSILON) const; //fuzzy equality test

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

		INLINEFORCE B8 Equals(const V3& v, F32 tolerance = EPSILON) const; //fuzzy equality test
		INLINEFORCE B8 AllComponentsEqual(F32 tolerance = EPSILON) const;

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

		INLINEFORCE B8 IsEpsilonZero(F32 tolerance = EPSILON) const; // fuzzy check for zero
		INLINEFORCE B8 IsZero() const; //check if absolutely zero

		INLINEFORCE void ToDirectionAndMagnitude(V3* v, F32* s) const; //returns a unit direction vector as well as a magnitude
		INLINEFORCE V3 SignV3() const; //sets each component to either +1 or -1
		INLINEFORCE V3 Projection() const; //Projects 2D components of vector based on z

		INLINEFORCE V3 UnsafeNormalize() const;

		INLINEFORCE V3 Clamp(F32 min, F32 max) const; //copies this vector, but clamps axes

		INLINEFORCE V3 Reciprocal() const; //Reciprocates vector

		INLINEFORCE B8 Uniform(F32 Tolerance = EPSILON) const; //checks if x == y == z

		INLINEFORCE V3 Reflect(const V3& normal) const; // reflects vector across normal vector

		//TODO: REFLECT ACROSS PLANE

		//TODO: ANGLULAR ROTATION

		INLINEFORCE B8 IsUnit(F32 len2Tolerance = EPSILON) const; //checks if it is unit

		INLINEFORCE V3 Project(const V3& v) const; // Projects this vector onto another vector

		INLINEFORCE glob B8 EqualVectors(const V3& a, const V3& b); // Checks if vectors are equal
		INLINEFORCE glob B8 VectorsAreNear(const V3& a, const V3& b, F32 dist);// checks if vectors are within distance

		//Distance from plane
		INLINEFORCE glob F32 VectorPlaneDist(const V3& point, const V3& planeBase, const V3& planeNormal);

		INLINEFORCE glob V3 ProjectPlane(const V3& point, const V3& planeBase, const V3& planeNormal);

		INLINEFORCE glob B8 Parallel(const V3& a, const V3& b); // checks if vectors are roughly parallel

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

		INLINEFORCE B8 HasNaN() const{
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

	INLINEFORCE B8 V3::operator==(const V3& v) const{
		return x == v.x && y == v.y && z == v.z;
	}

	INLINEFORCE B8 V3::operator==(F32 s) const{
		return x == s && y == s && z == s;
	}

	INLINEFORCE B8 V3::operator!=(const V3& v) const{
		return x != v.x || y != v.y || z != v.z;
	}

	INLINEFORCE B8 V3::operator!=(F32 s) const{
		return x != s || y != s || z != s;
	}

	INLINEFORCE B8 V3::operator<(const V3& v) const{
		return x < v.x && y < v.y && z < v.z;
	}

	INLINEFORCE B8 V3::operator<(F32 s) const{
		return x < s && y < s && z < s;
	}

	INLINEFORCE B8 V3::operator>(const V3& v) const{
		return x > v.x && y > v.y && z > v.z;
	}

	INLINEFORCE B8 V3::operator>(F32 s) const{
		return x > s && y > s && z > s;
	}

	INLINEFORCE B8 V3::operator<=(const V3& v) const{
		return x <= v.x && y <= v.y && z <= v.z;
	}

	INLINEFORCE B8 V3::operator<=(F32 s) const{
		return x <= s && y <= s && z <= s;
	}

	INLINEFORCE B8 V3::operator>=(const V3& v) const{
		return x >= v.x && y >= v.y && z >= v.z;
	}

	INLINEFORCE B8 V3::operator>=(F32 s) const{
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
		return Square(b.x - a.x) + Square(b.y - a.y) + Square(b.z - a.z);
	}

	INLINEFORCE F32 V3::Dist2(const V3& a, const V2& b){
		return Square(b.x - a.x) + Square(b.y - a.y) + Square(a.z);
	}

	INLINEFORCE F32 V3::Dist2(const V2& a, const V3& b){
		return Square(b.x - a.x) + Square(b.y - a.y) + Square(b.z);
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

	INLINEFORCE B8 V3::Equals(const V3& v, F32 tolerance) const{
		return AU::Abs(x - v.x) < tolerance && AU::Abs(y - v.y) < tolerance && AU::Abs(z - v.z);
	}

	INLINEFORCE B8 V3::AllComponentsEqual(F32 tolerance) const{
		return AU::Abs(x - y) < tolerance && AU::Abs(y - z) < tolerance && AU::Abs(y - z);
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
			dist2 += AU::Square(point.x - min.x);
		else if (point.x > max.x)
			dist2 += AU::Square(point.x - max.x);

		if (point.y < min.y)
			dist2 += AU::Square(point.y - min.y);
		else if (point.y > max.y)
			dist2 += AU::Square(point.y - max.y);

		if (point.z < min.z)
			dist2 += AU::Square(point.z - min.z);
		else if (point.z > max.z)
			dist2 += AU::Square(point.z - max.z);

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

	INLINEFORCE B8 V3::IsEpsilonZero(F32 tolerance) const{
		return AU::Abs(x) < tolerance && AU::Abs(y) < tolerance && AU::Abs(z) < tolerance;
	}

	INLINEFORCE B8 V3::IsZero() const{
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

	INLINEFORCE B8 V3::Uniform(F32 tolerance) const{
		return (AU::Abs(x - y) < tolerance) && (AU::Abs(y - z) < tolerance);
	}

	INLINEFORCE V3 V3::Reflect(const V3& normal) const{
		return *this - normal * (2.f * (*this | normal));
	}

	INLINEFORCE B8 V3::IsUnit(F32 len2Tolerance) const{
		return AU::Abs(1.0f - Len2()) < len2Tolerance;
	}

	INLINEFORCE V3 V3::Project(const V3& v) const{
		return (v * ((*this | v) / (v | v)));
	}

	INLINEFORCE B8 V3::EqualVectors(const V3& a, const V3& b){
		return (AU::Abs(a.x - b.x) < VECTOR_PROXIMITY_THRESHOLD 
			 && AU::Abs(a.y - b.y) < VECTOR_PROXIMITY_THRESHOLD 
			 && AU::Abs(a.z - b.z) < VECTOR_PROXIMITY_THRESHOLD);
	}

	INLINEFORCE B8 V3::VectorsAreNear(const V3& a, const V3& b, F32 dist){
		return (AU::Abs(a.x - b.x) < dist 
			&& AU::Abs(a.y - b.y) < dist
			&& AU::Abs(a.z - b.z) < dist);
	}

	INLINEFORCE B8 V3::Parallel(const V3& a, const V3& b){
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
	};

	






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
	};






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