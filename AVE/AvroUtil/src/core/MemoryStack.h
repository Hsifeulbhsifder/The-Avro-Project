#ifndef AVRO_UTIL_MEMORY_STACK_H
#define AVRO_UTIL_MEMORY_STACK_H
#include "avro_typedefs.h"
#include "AvroAllocator.h"

class MemoryStack : public AvroAllocator{
public:
	// Stack marker: Represents the current top of the
	// stack. You can only roll back to a marker, not to
	// arbitrary locations within the stack.
	typedef U64 Marker;

	U8* m_root;
	U64 m_stackSize_bytes;
	Marker m_currMarker;

	// Constructor
	MemoryStack();

	// Initialize stack with new memory 
	B32 Initialize(U64 stackSize_bytes);

	// Allocates a new block of the given size from stack
	// top.
	void* Allocate(U64 size_bytes);

	void* AllocateAligned(U64 size_bytes, U8 alignment);
	
	// Returns a marker to the current stack top.
	INLINEFORCE Marker GetMarker() const { return m_currMarker; }

	// Rolls the stack back to a previous marker.
	INLINEFORCE void FreeToMarker(Marker marker);

	INLINEFORCE void Dissipate(void* mem){} //Do not call

	// resets all member variables
	INLINEFORCE void Reset();

	// Clears the entire stack (rolls the stack back to
	// zero).
	INLINEFORCE void Clear(){
		m_currMarker = reinterpret_cast<Marker>(m_root);
	}

	// Frees all memory of stack
	void Terminate();

	//Destructor
	~MemoryStack();

private:
	MemoryStack(const MemoryStack& rhs){}
	void operator=(const MemoryStack& rhs){}
};

/************************************************************************/
/* Double Buffered Stack for frame allocations across two frames        */
/************************************************************************/
class DiBufferedStack : public AvroAllocator{
	U32 m_currStack;
	MemoryStack m_stack[2];
public:
	INLINEFORCE B32 Initialize(U64 stackSize_bytes){
		return (m_stack[0].Initialize(stackSize_bytes)) && (m_stack[1].Initialize(stackSize_bytes));
	}

	INLINEFORCE void SwapBuffers(){
		m_currStack = (U32)!m_stack;
	}

	INLINEFORCE void ClearCurrentBuffer(){
		m_stack[m_currStack].Clear();
	}

	INLINEFORCE void* Allocate(U64 size_bytes){
		return m_stack[m_currStack].Allocate(size_bytes);
	}

	INLINEFORCE void* AllocateAligned(U64 size_bytes, U8 alignment){
		return m_stack[m_currStack].AllocateAligned(size_bytes, alignment);
	}

	INLINEFORCE void Dissipate(void* mem){} //Do not call

private:
	DiBufferedStack(const DiBufferedStack& rhs){}
	void operator=(const DiBufferedStack& rhs){}
};

/************************************************************************/
/* Triple Buffered Stack for frame allocations across three frames      */
/************************************************************************/
class TriBufferedStack : public AvroAllocator{

	U32 m_currStack;
	MemoryStack m_stack[3];
public:
	INLINEFORCE B32 Initialize(U64 stackSize_bytes){
		return (m_stack[0].Initialize(stackSize_bytes))
			&& (m_stack[1].Initialize(stackSize_bytes))
			&& (m_stack[2].Initialize(stackSize_bytes));
	}

	INLINEFORCE void SwapBuffers(){
		m_currStack = (m_currStack + 1) % 3;
	}

	INLINEFORCE void ClearCurrentBuffer(){
		m_stack[m_currStack].Clear();
	}

	INLINEFORCE void* Allocate(U64 size_bytes){
		return m_stack[m_currStack].Allocate(size_bytes);
	}

	INLINEFORCE void* AllocateAligned(U64 size_bytes, U8 alignment){
		return m_stack[m_currStack].AllocateAligned(size_bytes, alignment);
	}

	INLINEFORCE void Dissipate(void* mem){} //Do not call

private:
	TriBufferedStack(const TriBufferedStack& rhs){}
	void operator=(const TriBufferedStack& rhs){}
};

/************************************************************************/
/* Quadruple Buffered Stack for frame allocations across four frames    */
/************************************************************************/
class QuadBufferedStack : public AvroAllocator{

	U32 m_currStack;
	MemoryStack m_stack[4];
public:
	INLINEFORCE B32 Initialize(U64 stackSize_bytes){
		return (m_stack[0].Initialize(stackSize_bytes))
			&& (m_stack[1].Initialize(stackSize_bytes))
			&& (m_stack[2].Initialize(stackSize_bytes))
			&& (m_stack[3].Initialize(stackSize_bytes));
	}

	INLINEFORCE void SwapBuffers(){
		m_currStack = (m_currStack + 1) % 4;
	}

	INLINEFORCE void ClearCurrentBuffer(){
		m_stack[m_currStack].Clear();
	}

	INLINEFORCE void* Allocate(U64 size_bytes){
		return m_stack[m_currStack].Allocate(size_bytes);
	}

	INLINEFORCE void* AllocateAligned(U64 size_bytes, U8 alignment){
		return m_stack[m_currStack].AllocateAligned(size_bytes, alignment);
	}

	INLINEFORCE void Dissipate(void* mem){} //Do not call

private:
	QuadBufferedStack(const QuadBufferedStack& rhs){}
	void operator=(const QuadBufferedStack& rhs){}
};

#endif