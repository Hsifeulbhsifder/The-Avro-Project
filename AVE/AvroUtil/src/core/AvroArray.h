#ifndef AVRO_UTIL_ARRAY_H
#define AVRO_UTIL_ARRAY_H
#include "avro_typedefs.h"

/**
* Generic iterator which can operate on types that expose the following:
* - A type called ElementType representing the contained type.
* - A method IndexType Num() const that returns the number of items in the container.
* - A method bool IsValidIndex(IndexType index) which returns whether a given index is valid in the container.
* - A method T& operator\[\](IndexType index) which returns a reference to a contained object by index.
*/
template<typename C, typename E, typename I>
class IndexedIterator{
public:
	IndexedIterator(C& container, I startIndex = 0) :m_container(container), m_index(index){}

	// Next element
	INLINEFORCE IndexedIterator& operator++(){
		m_index++;
		return *this;
	}

	INLINEFORCE IndexedIterator operator++(I32){
		IndexedIterator tmp(*this);
		m_index++;
		return tmp;
	}
	// Previous element
	INLINEFORCE IndexedIterator& operator--(){
		m_index--;
		return *this;
	}

	INLINEFORCE IndexedIterator operator--(I32){
		IndexedIterator tmp(*this);
		m_index--;
		return tmp;
	}

	// Arithmetic operations
	INLINEFORCE IndexedIterator& operator+=(I32 offset){
		m_index += offset;
		return *this;
	}

	INLINEFORCE IndexedIterator operator+(I32 offset) const{
		IndexedIterator tmp(*this);
		return tmp += offset;
	}

	INLINEFORCE IndexedIterator& operator-=(I32 offset){
		return *this -= -offset;
	}

	INLINEFORCE IndexedIterator operator-(I32 offset) const{
		IndexedIterator tmp(*this);
		return tmp -= offset;
	}

	/** @name element access*/
	//@{
	INLINEFORCE E& operator*() const{
		return m_container[m_index];
	}

	INLINEFORCE E* operator->() const{
		return &m_container[m_index];
	}
	//@}

	INLINEFORCE B8 operator bool() const{
		return m_container.IsValidIndex(m_index)
	}

	INLINEFORCE B8 operator!() const{
		return !(bool)*this;
	}

	INLINEFORCE I GetIndex() const{
		return m_index;
	}

	void Reset(){
		m_index = 0;
	}

	INLINEFORCE friend B8 operator==(const IndexedIterator& lhs, const IndexedIterator& rhs){
		return &lhs.m_container == &rhs.m_container && lhs.m_index == rhs.m_index;
	}

	INLINEFORCE friend B8 operator!=(const IndexedIterator& lhs, const IndexedIterator& rhs){
		return &lhs.m_container != &rhs.m_container || lhs.m_index != rhs.m_index;
	}

private:
	C& m_container;
	I m_index;
};

template <typename C, typename E, typename I>
INLINEFORCE IndexedIterator<C, E, I> 
operator+(I32 offset, IndexedIterator<C, E, I> rhs){
	return rhs + offset;
}

/************************************************************************/
/* Base Dynamic Array, untyped data, unordered                          */
/************************************************************************/
template <class Allocator = AVRO_DEFAULT_ALLOCATOR>
class VoidArr{
	void* m_data;
	U32 m_size;
	U32 m_capacity;
	//Allocator& m_allocator;

private:
	INLINEFORCE void* Resize(U32 newSize){
		void* newData = Allocator.Allocate(newSize);
		if (!newData) return nullptr;

		for (U32 i = 0; i < m_size; i++) newData[i] = m_data[i];
		if (m_data) Allocator.Dissipate(m_data);
		m_data = newData;
		m_capacity = newSize;
		return m_data;
	}

public:
	explicit INLINEFORCE VoidArr(U32 capacity = 16):m_capacity(capacity), m_size(0){
		m_data = Allocator.Allocate(capacity);
	}
	explicit INLINEFORCE VoidArr(void* data) : m_data(data){
		m_capacity = AU::SizeofArr(data);
		m_size = m_capacity;
	}

	INLINEFORCE void* GetData(){ return m_data; }
	INLINEFORCE const void* GetData() const { return m_data; }

	INLINEFORCE B8 IsValidIndex(U32 i) const{
		return i >= 0 && i < m_size;
	}

	INLINEFORCE U32 Size() const{ return m_size; }

	INLINEFORCE void*& operator[](U32 index){
		AVRO_ASSERT(index < m_size, "Array access request out of bounds");
		return m_data[index];
	}

	INLINEFORCE void* operator[](U32 index) const{
		AVRO_ASSERT(index < m_size, "Array access request out of bounds");
		return m_data[index];
	}

	INLINEFORCE void Push(void* value){
		if (m_size == m_capacity) Resize(AU::Max(8, m_size * 2));
		m_data[m_size++] = value;
	}

	INLINEFORCE void PushArr(void* arr,U32 start, U32 count){
		//TODO: Optimize
		for (U32 i = 0, i < count, i++) Push(arr[i + start]);
	}

	INLINEFORCE void PushArr(const VoidArr& arr){
		//TODO: Optimize
		for (U32 i = 0, i < arr.m_size; i++) Push(arr[i]);
	}

	INLINEFORCE void PushArr(const VoidArr& arr, U32 start, U32 count){
		//TODO: Optimize
		for (U32 i = 0; i < count; i++) Push(arr[i + start]);
	}

	INLINEFORCE void Insert(void* value, U32 index){
		AVRO_ASSERT(index < m_size, "Array access request out of bounds");
		if ((m_size + 1) == m_capacity) Resize(AU::Max(8, m_size * 2));

		m_data[m_size++] = m_data[index];
		m_data[index] = value;
	}

	INLINEFORCE void InsertArr(void* arr, U32 start, U32 count){
		//TODO: Optimize
		for (U32 i = 0; i < count; i++) Insert(arr[i + start]);
	}

	INLINEFORCE void Swap(U32 indexA, U32 indexB){
		AVRO_ASSERT(indexA < m_size, "Array access request out of bounds");
		AVRO_ASSERT(indexB < m_size, "Array access request out of bounds");
		AU::Swap(m_data[indexA], m_data[indexB]);
	}

	INLINEFORCE B8 Contains(void* value, B8 reverseDir = false) const{
		if (reverseDir){
			for (U32 i = m_size - 1; i >= 0; i--)
				if (m_data[i] == value) return true;
		}
		else{
			for (U32 i = 0; i < m_size; i++)
				if (m_data[i] == value) return true;
		}

		return false;
	}

	INLINEFORCE I32 IndexOf(void* value, B8 reverseDir = false) const{
		if (reverseDir){
			for (U32 i = m_size - 1; i >= 0; i--)
				if (m_data[i] == value) return i;
		}
		else{
			for (U32 i = 0; i < m_size; i++)
				if (m_data[i] == value) return i;
		}

		return -1;
	}

	INLINEFORCE B8 Remove(void* value, B8 reverseDir = false){
		if (reverseDir){
			for (U32 i = m_size - 1; i >= 0; i--){
				if (m_data[i] == value){
					m_data[i] = m_data[m_size - 1];
					m_size--;
					return true;
				}
			}
		}
		else{
			for (U32 i = 0; i < m_size; i++){
				if (m_data[i] == value){
					m_data[i] = m_data[m_size - 1];
					m_size--;
					return true;
				}
			}
		}

		return false;
	}

	INLINEFORCE void* Remove(U32 index){
		AVRO_ASSERT(indexA < m_size, "Array access request out of bounds");
		void* value = m_data[index];
		m_data[index] = m_data[m_size - 1];
		m_size--;
		return value;
	}

	INLINEFORCE void Remove(U32 start, U32 end){
		if (start > end){
			AU::Swap(&start, &end);
		}
		AVRO_ASSERT(end < m_size, "Array access request out of bounds");
		U32 count = end - start + 1;
		for (U32 i = 0; i < count; i++)
			m_data[start + i] = m_data[m_size - 1 - i];

		m_size -= count;
	}

	// returns true i array was modified
	B8 RemoveArr(const void* arr, U32 start, U32 count, B8 reverseDir = false){
		//TODO: Optimize
		U32 sizeAtStart = m_size;
		if (reverseDir){
			for (U32 i = count - 1; i >= 0; i--){
				for (U32 j = m_size - 1; j >= 0; j--){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}
		else{
			for (U32 i = 0; i < count; i++){
				for (U32 j = 0; j < m_size; j++){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}

		return sizeAtStart - m_size;
	}

	B8 RemoveArr(const VoidArray& arr, B8 reverseDir = false){
		//TODO: Optimize
		U32 sizeAtStart = m_size;
		if (reverseDir){
			for (U32 i = arr.m_size - 1; i >= 0; i--){
				for (U32 j = m_size - 1; j >= 0; j--){
					if (arr[i] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}
		else{
			for (U32 i = 0; i < arr.m_size; i++){
				for (U32 j = 0; j < m_size; j++){
					if (arr[i] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}

		return sizeAtStart - m_size;
	}

	B8 RemoveArr(const VoidArray& arr, U32 start, U32 count, B8 reverseDir = false){
		//TODO: Optimize
		U32 sizeAtStart = m_size;
		if (reverseDir){
			for (U32 i = count - 1; i >= 0; i--){
				for (U32 j = m_size - 1; j >= 0; j--){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}
		else{
			for (U32 i = 0; i < count; i++){
				for (U32 j = 0; j < m_size; j++){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}

		return sizeAtStart - m_size;
	}

	//TODO: change the functions below to assertions if necessary
	INLINEFORCE void* Pop(){
		if (m_size){
			m_size--;
			return m_data[m_size];
		}
		return nullptr;
	}

	INLINEFORCE void* Peek() const{
		if (m_size){
			return m_data[Size - 1];
		}
		return nullptr;
	}

	INLINEFORCE void* First(){
		if (m_size) return m_data[0];
		return nullptr;
	}

	INLINEFORCE void Clear(){
		for (U32 i = 0; i < m_size; i++) m_data[i] = nullptr;
		m_size = 0;
	}

	INLINEFORCE void* Compress(){
		if (m_size != m_capacity) Resize(m_size);
		return m_data;
	}

	INLINEFORCE void* ReserveCapacity(U32 additionalCapacity){
		I32 sizeRequired = m_size + additionalCapacity;
		if (sizeRequired > m_capacity) Resize(sizeRequired);
		return m_data;
	}

	INLINEFORCE void Reverse(){
		for (U32 i = 0, lastIndex = m_size - 1, n = m_size / 2; i < n; i++){
			U32 j = lastIndex - i;
			AU::Swap(&m_data[i], &m_data[j]);
		}
	}

	INLINEFORCE void Shuffle(){
		//TODO: Implement shuffling
	}

	INLINEFORCE void Truncate(U32 newSize){
		AVRO_ASSERT(m_size <= newSize, "New size cannot be equal to or greater than past size during truncation");
		for (U32 i = newSize; i < m_size; i++)
			m_data[i] = nullptr;
		m_size = newSize;
	}

	INLINEFORCE void*& RandomIndex(){
		if (m_size){}
		//TODO: Implement random index
		return nullptr;
	}

	INLINEFORCE void* RandomIndex() const{
		if (m_size){}
		//TODO: Implement random index
		return nullptr;
	}

	INLINEFORCE void* ToArr() const{
		return m_data;
	}

	template<typename T>
	INLINEFORCE T* ToArr() const{
		return (T*)m_data;
	}

};


/**
* ReversePredicateWrapper class used by implicit heaps.
* it reverses the comparison at the same time
*/
template <typename E, typename P>
class ReversePredicateWrapper{
	const P& m_predicate;
public:
	ReversePredicateWrapper(const P& predicate) : m_predicate(predicate){}

	INLINEFORCE B8 operator()(E& a, E& b) const{ return m_predicate(b, a); }
	INLINEFORCE B8 operator()(const E& a, const E& b) const{ return m_predicate(b, a); }
};

/**
* Partially specialized version of the above.
*/

template <typename E, typename P>
class ReversePredicateWrapper < E*, P > {
	const P& m_predicate;
public:
	ReversePredicateWrapper(const P& predicate) : m_predicate(predicate){}

	INLINEFORCE B8 operator()(E* a, E* b) const{
		AVRO_ASSERT(a, "Element 'a' is null");
		AVRO_ASSERT(b, "Element 'b' is null");
		return m_predicate(*b, *a);
	}

	INLINEFORCE B8 operator()(const E* a, const E* b) const{
		AVRO_ASSERT(a, "Element 'a' is null");
		AVRO_ASSERT(b, "Element 'b' is null");
		return m_predicate(*b, *a);
	}



};

/************************************************************************/
/* Templated Dynamic Array, unordered                                   */
/************************************************************************/

template<typename E, typename Allocator = AVRO_DEFAULT_ALLOCATOR>
class Array{
	E* m_data;
	U32 m_size;
	U32 m_capacity;

private:
	template <typename E, typename Allocator>
	INLINEFORCE E* Resize(U32 newSize){
		E* newData = Allocator.Allocate(newSize * sizeof(E));
		if (!newData) return nullptr;

		for (U32 i = 0; i < m_size; i++) newData[i] = m_data[i];
		if (m_data) Allocator.Dissipate(m_data);
		m_data = newData;
		m_capacity = newSize;
		return m_data;
	}

public:

	template<typename E, typename Allocator>
	INLINEFORCE explicit Array(U32 capacity = 16):m_capacity(capacity), m_size(0){
		m_data = (E*)Allocator.Allocate(capacity * sizeof(E));
	}

	template<typename E>
	INLINEFORCE Array(E* arr) : m_data(arr){
		m_capacity = AU::SizeofArr(arr);
		m_size = capacity;
	}
	

	template<typename OtherAllocator>
	INLINEFORCE Array(const Array<E, OtherAllocator>& rhs)
		:m_capacity(rhs.m_capacity), m_size(rhs.m_size){
		//TODO: Optimize

		m_data = (E*)OtherAllocator.Allocate(capacity * sizeof(E));
		for (U32 i = 0; i < rhs.m_size; i++) m_data[i] = rhs.m_data[i];
	}

	INLINEFORCE Array(const Array& rhs)
		:m_capacity(rhs.m_capacity), m_size(rhs.m_size){
		//TODO: Optimize
		m_data = (E*)Allocator.Allocate(capacity * sizeof(E));
		for (U32 i = 0; i < rhs.m_size; i++) m_data[i] = rhs.m_data[i];
	}

	INLINEFORCE Array(Array&& rhs)
		:m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(rhs.m_data){
		rhs.m_capacity = 0;
		rhs.m_size = 0;
		rhs.m_data = nullptr;
	}

	template<typename OtherAllocator>
	Array& operator=(const Array<E, OtherAllocator> rhs){
		//TODO: Optimize
		m_capacity = rhs.m_capacity;
		m_size = rhs.m_size;
		m_data = (E*)OtherAllocator.Allocate(capacity * sizeof(E));
		for (U32 i = 0; i < rhs.m_size; i++) m_data[i] = rhs.m_data[i];
		return *this;
	}

	Array& operator=(const Array<E, Allocator>& rhs){
		if (this != &rhs){
			//TODO: Optimize
			m_capacity = rhs.m_capacity;
			m_size = rhs.m_size;
			m_data = (E*)Allocator.Allocate(capacity * sizeof(E));
			for (U32 i = 0; i < rhs.m_size; i++) m_data[i] = rhs.m_data[i];
		}
		return *this;
	}

	template<typename OtherAllocator>
	Array& operator=(Array<E, OtherAllocator>&& rhs){
		m_capacity = rhs.m_capacity;
		m_size = rhs.m_size;
		m_data = rhs.m_data;
		rhs.m_capacity = 0;
		rhs.m_size = 0;
		rhs.m_data = nullptr;
		return *this;
	}

	Array& operator=(Array<E, Allocator>&& rhs){
		if (this != &rhs){
			m_capacity = rhs.m_capacity;
			m_size = rhs.m_size;
			m_data = rhs.m_data;
			rhs.m_capacity = 0;
			rhs.m_size = 0;
			rhs.m_data = nullptr;
		}
		return *this;
	}

	INLINEFORCE E* GetData(){ return m_data; }
	INLINEFORCE const E* GetData() const { return m_data; }

	INLINEFORCE B8 IsValidIndex(U32 i) const{
		return i >= 0 && i < m_size;
	}

	INLINEFORCE U32 Size() const{ return m_size; }

	INLINEFORCE E& operator[](U32 index){
		AVRO_ASSERT(index < m_size, "Array access request out of bounds");
		return m_data[index];
	}

	INLINEFORCE E operator[](U32 index) const{
		AVRO_ASSERT(index < m_size, "Array access request out of bounds");
		return m_data[index];
	}

	INLINEFORCE void Push(const E& value){
		if (m_size == m_capacity) Resize(AU::Max(8, m_size * 2));
		m_data[m_size++] = value;
	}

	INLINEFORCE void PushArr(const E& arr, U32 start, U32 count){
		//TODO: Optimize
		for (U32 i = 0, i < count, i++) Push(arr[i + start]);
	}

	INLINEFORCE void PushArr(const Array& arr){
		//TODO: Optimize
		for (U32 i = 0, i < arr.m_size; i++) Push(arr[i]);
	}

	INLINEFORCE void PushArr(const Array& arr, U32 start, U32 count){
		//TODO: Optimize
		for (U32 i = 0; i < count; i++) Push(arr[i + start]);
	}

	INLINEFORCE void Insert(const E& value, U32 index){
		AVRO_ASSERT(index < m_size, "Array access request out of bounds");
		if ((m_size + 1) == m_capacity) Resize(AU::Max(8, m_size * 2));

		m_data[m_size++] = m_data[index];
		m_data[index] = value;
	}

	INLINEFORCE void InsertArr(const E& arr, U32 start, U32 count){
		//TODO: Optimize
		for (U32 i = 0; i < count; i++) Insert(arr[i + start]);
	}

	INLINEFORCE void Swap(U32 indexA, U32 indexB){
		AVRO_ASSERT(indexA < m_size, "Array access request out of bounds");
		AVRO_ASSERT(indexB < m_size, "Array access request out of bounds");
		AU::Swap(m_data[indexA], m_data[indexB]);
	}

	INLINEFORCE B8 Contains(const E& value, B8 reverseDir = false) const{
		if (reverseDir){
			for (U32 i = m_size - 1; i >= 0; i--)
				if (m_data[i] == value) return true;
		}
		else{
			for (U32 i = 0; i < m_size; i++)
				if (m_data[i] == value) return true;
		}

		return false;
	}

	INLINEFORCE I32 IndexOf(const E& value, B8 reverseDir = false) const{
		if (reverseDir){
			for (U32 i = m_size - 1; i >= 0; i--)
				if (m_data[i] == value) return i;
		}
		else{
			for (U32 i = 0; i < m_size; i++)
				if (m_data[i] == value) return i;
		}

		return -1;
	}

	INLINEFORCE B8 Remove(const E& value, B8 reverseDir = false){
		if (reverseDir){
			for (U32 i = m_size - 1; i >= 0; i--){
				if (m_data[i] == value){
					m_data[i] = m_data[m_size - 1];
					m_size--;
					return true;
				}
			}
		}
		else{
			for (U32 i = 0; i < m_size; i++){
				if (m_data[i] == value){
					m_data[i] = m_data[m_size - 1];
					m_size--;
					return true;
				}
			}
		}

		return false;
	}

	INLINEFORCE E Remove(U32 index){
		AVRO_ASSERT(indexA < m_size, "Array access request out of bounds");
		void* value = m_data[index];
		m_data[index] = m_data[m_size - 1];
		m_size--;
		return value;
	}

	INLINEFORCE void Remove(U32 start, U32 end){
		if (start > end){
			AU::Swap(&start, &end);
		}
		AVRO_ASSERT(end < m_size, "Array access request out of bounds");
		U32 count = end - start + 1;
		for (U32 i = 0; i < count; i++)
			m_data[start + i] = m_data[m_size - 1 - i];

		m_size -= count;
	}

	// returns true i array was modified
	B8 RemoveArr(const E* arr, U32 start, U32 count, B8 reverseDir = false){
		//TODO: Optimize
		U32 sizeAtStart = m_size;
		if (reverseDir){
			for (U32 i = count - 1; i >= 0; i--){
				for (U32 j = m_size - 1; j >= 0; j--){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}
		else{
			for (U32 i = 0; i < count; i++){
				for (U32 j = 0; j < m_size; j++){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}

		return sizeAtStart - m_size;
	}

	B8 RemoveArr(const Array& arr, B8 reverseDir = false){
		//TODO: Optimize
		U32 sizeAtStart = m_size;
		if (reverseDir){
			for (U32 i = arr.m_size - 1; i >= 0; i--){
				for (U32 j = m_size - 1; j >= 0; j--){
					if (arr[i] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}
		else{
			for (U32 i = 0; i < arr.m_size; i++){
				for (U32 j = 0; j < m_size; j++){
					if (arr[i] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}

		return sizeAtStart - m_size;
	}

	B8 RemoveArr(const Array& arr, U32 start, U32 count, B8 reverseDir = false){
		//TODO: Optimize
		U32 sizeAtStart = m_size;
		if (reverseDir){
			for (U32 i = count - 1; i >= 0; i--){
				for (U32 j = m_size - 1; j >= 0; j--){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}
		else{
			for (U32 i = 0; i < count; i++){
				for (U32 j = 0; j < m_size; j++){
					if (arr[i + start] == m_data[j]){
						Remove(j);
						break;
					}
				}
			}
		}

		return sizeAtStart - m_size;
	}

	//TODO: change the functions below to assertions if necessary
	INLINEFORCE E Pop(){
		if (m_size){
			m_size--;
			return m_data[m_size];
		}
		return nullptr;
	}

	INLINEFORCE E Peek() const{
		if (m_size){
			return m_data[Size - 1];
		}
		return nullptr;
	}

	INLINEFORCE E First(){
		if (m_size) return m_data[0];
		return nullptr;
	}

	INLINEFORCE void Clear(){
		for (U32 i = 0; i < m_size; i++) m_data[i] = nullptr;
		m_size = 0;
	}

	INLINEFORCE E* Compress(){
		if (m_size != m_capacity) Resize(m_size);
		return m_data;
	}

	INLINEFORCE E* ReserveCapacity(U32 additionalCapacity){
		I32 sizeRequired = m_size + additionalCapacity;
		if (sizeRequired > m_capacity) Resize(sizeRequired);
		return m_data;
	}

	INLINEFORCE void Reverse(){
		for (U32 i = 0, lastIndex = m_size - 1, n = m_size / 2; i < n; i++){
			U32 j = lastIndex - i;
			AU::Swap(&m_data[i], &m_data[j]);
		}
	}

	//Quick Sort
	INLINEFORCE void Sort(){
		AU::Sort<E>(m_data, 0, m_size);
	}

	INLINEFORCE void Shuffle(){
		//TODO: Implement shuffling
	}

	INLINEFORCE void Truncate(U32 newSize){
		AVRO_ASSERT(m_size <= newSize, "New size cannot be equal to or greater than past size during truncation");
		for (U32 i = newSize; i < m_size; i++)
			m_data[i] = nullptr;
		m_size = newSize;
	}

	INLINEFORCE E& RandomIndex(){
		if (m_size){}
		//TODO: Implement random index
		return nullptr;
	}

	INLINEFORCE E RandomIndex() const{
		if (m_size){}
		//TODO: Implement random index
		return nullptr;
	}

	INLINEFORCE E* ToArr() const{
		return m_data;
	}

	template<typename T>
	INLINEFORCE T* ToArr() const{
		return (T*)m_data;
	}
};

#endif