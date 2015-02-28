#ifndef AVRO_UTIL_MEMORY_HEAP_H
#define AVRO_UTIL_MEMORY_HEAP_H

#include "avro_typedefs.h"

class DLLEXPORT MemoryHeap{
	U8** m_heapBlocks;
	U8* m_root;
	U64 m_heapSize_bytes;
	U64 m_memoryAvailable;
	B8 m_resizable;
	U64 m_numBlocks;
public:
	MemoryHeap();
	
	// Initialize heap with memory size
	B8 Initialize(U64 heapSize_bytes);
	
	// Allocates from heap
	void* Allocate(U64 size_bytes);
	// Allocates Aligned memory from heap
	void* AllocateAligned(U64 size_bytes, U8 alignment = 16);
	// Frees memory, returns it to heap
	void Dissipate(void* mem);
	// Frees aligned memory, returns it to heap
	void DissipateAligned(void* mem);
	// Returns memory remaining
	INLINEFORCE U64 GetAvailableMemory() const; //TODO: implement

	// Frees all memory from heap
	void Terminate();

	~MemoryHeap();

private:
	// Resets all member variables
	void Reset();
	// Expands heap, if flagged for resizing
	B8 GrowHeapSize();
	// Allocates a new Block
	void AllocateNewBlock(U8* pointer, U64 size_bytes);

	void Coalesce(U8* pointer);

	MemoryHeap(const MemoryHeap& rhs){}
	void operator=(const MemoryHeap& rhs){}
};

#endif