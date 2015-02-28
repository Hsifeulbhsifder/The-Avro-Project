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