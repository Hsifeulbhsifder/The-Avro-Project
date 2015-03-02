#ifndef AVRO_UTIL_AVRO_UTIL_H
#define AVRO_UTIL_AVRO_UTIL_H
#include "avro_typedefs.h"

namespace AU{

	INLINEFORCE U16 EndianSwapU16(U16 value){
		return ((value & 0x00FF) << 8)
			 | ((value & 0xFF00) >> 8);
	}

	INLINEFORCE U32 EndianSwapU32(U32 value){
		return ((value & 0x000000FF) << 24)
			 | ((value & 0x0000FF00) << 8)
			 | ((value & 0x00FF0000) >> 8)
			 | ((value & 0xFF000000) >> 24);
	}

	INLINEFORCE U64 EndianSwapU64(U64 value){
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

	INLINEFORCE U32 F32ToU32Bits(F32 value){
		U32F32 u;
		u.f32 = value;
		return u.u32;
	}

	INLINEFORCE F32 U32ToF32Bits(U32 value){
		U32F32 u;
		u.u32 = value;
		return u.f32;
	}

	INLINEFORCE F32 EndianSwapF32(F32 value){
		U32F32 u;
		u.f32 = value;

		u.u32 = EndianSwapU32(u.u32); //Swap as int32
		return u.f32;
	}

	union U64F64{
		U64 u64;
		F64 f64;
	};

	INLINEFORCE U64 F64ToU64Bits(F64 value){
		U64F64 u;
		u.f64 = value;
		return u.u64;
	}

	INLINEFORCE F64 U64ToF64Bits(U64 value){
		U64F64 u;
		u.u64 = value;
		return u.f64;
	}

	INLINEFORCE F64 EndianSwapF32(F64 value){
		U64F64 u;
		u.f64 = value;

		u.u64 = EndianSwapU64(u.u64); //Swap as int64
		return u.f64;
	}

	INLINEFORCE U64 KiB(U64 bytes){
		return bytes * 1024;
	}

	INLINEFORCE U64 MiB(U64 bytes){
		return bytes * 1048576;
	}

	INLINEFORCE U64 GiB(U64 bytes){
		return bytes * 1073741824;
	}

	template<typename T>
	INLINEFORCE U32 SizeofArr(T* arr){ return (sizeof(arr) / sizeof(arr[0])); }

	template<typename T>
	INLINEFORCE void swap(T* a, T* b){
		T* tmp = a;
		a = b;
		b = tmp;
	}

}

#endif