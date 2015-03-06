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
template <AvroAllocator Allocator = AVRO_DEFAULT_ALLOCATOR>
class VoidArr{
	void* m_data;
	U32 m_size;
	U32 m_capacity;
	//Allocator& m_allocator;
public:
	explicit INLINEFORCE VoidArr(U32 capacity = 16):m_capacity(capacity):SIZE(0){
		data = Allocator.Allocate(capacity);
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
		if (m_size == m_capacity) {}//TODO: resize array
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
		if ((m_size + 1) == m_capacity){} //TODO: resize array

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

	//TODO: change the functions below to assertions if necessary
	INLINEFORCE void* Pop(){
		if (m_size){
			m_size--;
			return m_data[m_size];
		}
		return nullptr;
	}

	INLINEFORCE void* Peek(){
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
		if (m_size != m_capacity){} //TODO: resize
		return m_data;
	}

	INLINEFORCE void* ReserveCapacity(U32 additionalCapacity){
		I32 sizeRequired = m_size + additionalCapacity;
		if (sizeRequired > m_capacity) {} //TODO: resize
		return m_data;
	}

private:
	INLINEFORCE void* Resize(U32 newSize){
		void* newData = Allocator.Allocate(newSize);
		if (!newData) return nullptr;

		for (U32 i = 0; i < m_size; i++) newData[i] = m_data[i];


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

#endif