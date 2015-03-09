#include "AU_stdafx.h"
#include "AvroUtil.h"


template <typename T>
U32 intern Partition(T* arr, U32 begin, U32 end){
	U32 i = arr[begin];
	U32 j = begin;
	for (U32 k = begin + 1; k < end; k++){
		if (arr[k] <= i){
			i++;
			Swap(arr[j], arr[k]);
		}
	}
	Swap(arr[j], arr[begin]);
	return j;
}

template <typename T>
glob void Sort(T* arr, U32 begin, U32 end){
	if (begin < end){
		U32 middle = Partition(arr, begin, end);
		Sort(arr, begin, middle);
		Sort(arr, middle + 1, end);
	}
}