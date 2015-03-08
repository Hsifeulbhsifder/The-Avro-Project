#ifndef AVRO_UTIL_AVRO_UTIL_H
#define AVRO_UTIL_AVRO_UTIL_H
#include "avro_typedefs.h"

#define FNV_PRIME_32 16777619L
#define FNV_OFFSET_32 2166136261L
#define FNV_PRIME_64 1099511628211LL
#define FNV_OFFSET_64 14695981039346656037LL

namespace AU{

	template<typename T>
	INLINEFORCE glob U32 SizeofArr(T* arr){ return (sizeof(arr) / sizeof(arr[0])); }

	INLINEFORCE glob U16 EndianSwapU16(U16 value){
		return ((value & 0x00FF) << 8)
			 | ((value & 0xFF00) >> 8);
	}

	INLINEFORCE glob U32 EndianSwapU32(U32 value){
		return ((value & 0x000000FF) << 24)
			 | ((value & 0x0000FF00) << 8)
			 | ((value & 0x00FF0000) >> 8)
			 | ((value & 0xFF000000) >> 24);
	}

	INLINEFORCE glob U64 EndianSwapU64(U64 value){
		return ((value & 0x00000000000000FF) << 56)
			 | ((value & 0x000000000000FF00) << 40)
			 | ((value & 0x0000000000FF0000) << 24)
			 | ((value & 0x00000000FF000000) << 8)
			 | ((value & 0x000000FF00000000) >> 8)
			 | ((value & 0x0000FF0000000000) >> 24)
			 | ((value & 0x00FF000000000000) >> 40)
			 | ((value & 0xFF00000000000000) >> 56);
	}

	union U32F32{
		U32 u32;
		F32 f32;
	};

	INLINEFORCE glob U32 F32ToU32Bits(F32 value){
		U32F32 u;
		u.f32 = value;
		return u.u32;
	}

	INLINEFORCE glob F32 U32ToF32Bits(U32 value){
		U32F32 u;
		u.u32 = value;
		return u.f32;
	}

	INLINEFORCE glob F32 EndianSwapF32(F32 value){
		U32F32 u;
		u.f32 = value;

		u.u32 = EndianSwapU32(u.u32); //Swap as int32
		return u.f32;
	}

	union U64F64{
		U64 u64;
		F64 f64;
	};

	INLINEFORCE glob U64 F64ToU64Bits(F64 value){
		U64F64 u;
		u.f64 = value;
		return u.u64;
	}

	INLINEFORCE glob F64 U64ToF64Bits(U64 value){
		U64F64 u;
		u.u64 = value;
		return u.f64;
	}

	INLINEFORCE glob F64 EndianSwapF32(F64 value){
		U64F64 u;
		u.f64 = value;

		u.u64 = EndianSwapU64(u.u64); //Swap as int64
		return u.f64;
	}

	INLINEFORCE glob U64 HashB8(B8 value){
		if (value) value /= value;
		return (U64)value;
	}

	INLINEFORCE glob U64 HashU8(U8 value){
		return (U64)value;
	}

	INLINEFORCE glob U64 HashU16(U16 value){
		return (U64)value;
	}
	
	INLINEFORCE glob U64 HashU32(U32 value){
		return (U64)value;
	}
	
	INLINEFORCE glob U64 HashU64(U64 value){
		return value;
	}

	union U8I8{
		U8 u8;
		I8 i8;
	};
	
	INLINEFORCE glob U64 HashI8(I8 value){
		U8I8 u;
		u.i8 = value;
		return (U64)u.u8;
	}

	union U16I16{
		U16 u16;
		I16 i16;
	};

	INLINEFORCE glob U64 HashI16(I16 value){
		U16I16 u;
		u.i16 = value;
		return (U64)u.u16;
	}

	union U32I32{
		U32 u32;
		I32 i32;
	};

	INLINEFORCE glob U64 HashI32(I32 value){
		U32I32 u;
		u.i32 = value;
		return (U64)u.u32;
	}

	union U64I64{
		U64 u64;
		I64 i64;
	};

	INLINEFORCE glob U64 HashI64(I64 value){
		U64I64 u;
		u.i64 = value;
		return u.u64;
	}
	
	INLINEFORCE glob U64 HashF32(F32 value){
		U32F32 u;
		u.f32 = value;
		return (U64)u.u32;
	}

	INLINEFORCE glob U64 HashF64(F64 value){
		U64F64 u;
		u.f64 = value;
		return u.u64;
	}

	INLINEFORCE glob U64 HashSTR(char* str){
		U64 hash = FNV_OFFSET_64;
		for (U32 i = 0; i < SizeofArr(str); i++){
			hash ^= str[i];
			hash *= FNV_PRIME_64;
		}
		return hash;
	}

	INLINEFORCE glob U64 KiB(U64 bytes){
		return bytes * 1024LL;
	}

	INLINEFORCE glob U64 MiB(U64 bytes){
		return bytes * 1048576LL;
	}

	INLINEFORCE glob U64 GiB(U64 bytes){
		return bytes * 1073741824LL;
	}


	//Default swap function, define other swap functions 
	//and use template specialization to do custom swaps
	template<typename T>
	INLINEFORCE glob void Swap(T* a, T* b){
		T* tmp = a;
		a = b;
		b = tmp;
	}

}

#endif