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

template <typename T>
void intern Merge(T* arr, U32 begin, U32 mid, U32 end){
	U32 n = end - begin + 1;
	U32 na = mid - begin + 1; 
	U32 nb = end - mid;
	U32 i = 0;
	U32 j = 1;

	T* tmp = malloc(n); //TODO: Replace with default allocator
	CopyArr(arr, begin, tmp, begin, n);

	for (U32 k = 0; k < n; k++){
		if (tmp[begin + i] < tmp[mid + j] && (i < na)){
			arr[k] = tmp[begin + i];
			i++;
		}
		else if (tmp[mid + j] < tmp[begin + i] && (j < nb)){
			arr[k] = tmp[mid + j];
			j++;
		}
	}

	free(tmp); //TODO: Replace with default allocator
}

template <typename T>
glob void MergeSort(T* arr, U32 begin, U32 end){
	if (end - begin > 1){
		U32 mid = (end - begin) / 2;
		MergeSort(arr, begin, mid);
		MergeSort(arr, mid + 1, end);
		Merge(arr, begin, mid, end)
	}
}

//TODO: Make more efficient
template <typename T>
glob void CopyArr(T* src, U32 srcStart, T* dest, U32 destStart, U32 numElements){
	I32 diff = destStart - srcStart;
	for (U32 i = srcStart; i < srcStart + numElements; i++){
		dest[i + diff] = src[i];
	}
}