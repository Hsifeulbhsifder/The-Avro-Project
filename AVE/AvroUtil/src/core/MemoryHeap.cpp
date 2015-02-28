#include "AU_stdafx.h"
#include "MemoryHeap.h"

const glob U64 HEADER_SIZE = sizeof(U8);
const glob U64 FOOTER_SIZE = sizeof(U8);
const glob U8 BLOCK_ALLOCATION_BIT = 0x80;

MemoryHeap::MemoryHeap(){
	Reset();
}

MemoryHeap::~MemoryHeap(){
	Terminate();
}

void MemoryHeap::Reset(){
	m_heapBlocks = nullptr;
	m_root = nullptr;
	m_heapSize_bytes = 0;
	m_memoryAvailable = 0;
	m_numBlocks = 0;
	m_resizable = false;
}

void MemoryHeap::Terminate(){
	//Free all memory
	U8* currPointer = m_root;
	for (U64 i = 0; i < m_numBlocks; i++){
		U64 currPointerSize = *currPointer;
		U8* nextPointer = currPointer + currPointerSize;
		free(currPointer);
		currPointer = nextPointer;
	}
	free(m_heapBlocks);

	Reset();
}

B8 MemoryHeap::Initialize(U64 heapSize_bytes)
{
	if (m_heapBlocks) Terminate(); // Pre-allocation check
	AVRO_ASSERT(heapSize_bytes > 0, "Size too low");
	m_heapSize_bytes = heapSize_bytes; // Store heapSize in bytes

	if (GrowHeapSize()) return true;
	return false;
}

void* MemoryHeap::Allocate(U64 size_bytes)
{	
	AVRO_ASSERT(size_bytes > 0, "Size of allocation requested is too small");
	AVRO_ASSERT(size_bytes < 128, "Size of allocation requested is too large")
	size_bytes += HEADER_SIZE + FOOTER_SIZE; //makes room for headers and footers
	//TODO: don't forget the header and footer size
	U8* srchPointer = m_root;
	B8 found = false;
	//Iterate through list until valid location is found
	for (U64 i = 0; i < m_numBlocks; i++){
		U8 srchpointerSize = *srchPointer;
		if (!(*(srchPointer)& BLOCK_ALLOCATION_BIT) && size_bytes <= srchpointerSize){
			found = true;
			break;
		}
		srchPointer += srchpointerSize;
	}
	AllocateNewBlock(srchPointer, size_bytes);
	if (found) return static_cast<void*>(srchPointer + HEADER_SIZE); // return pointer data only, skips head
	return nullptr;
}

void* MemoryHeap::AllocateAligned(U64 size_bytes, U8 alignment)
{
	AVRO_ASSERT(alignment > 0, "Alignment is too small");
	AVRO_ASSERT(alignment <= 128, "Alignment is too large");
	AVRO_ASSERT((alignment & (alignment - 1)) == 0, "Alignment is not Power of Two");

	// Determine total amount of memory to allocate
	U64 expandedSize_bytes = size_bytes + alignment;

	// Allocate unaligned block & convert address to U64
	U64 rawAddress = reinterpret_cast<U64>(Allocate(expandedSize_bytes));

	// Calculate the adjustment by masking off the lower bits of the address, to determine how 
	// misaligned it is
	U8 mask = (alignment - 1);
	U64 misalignment = (rawAddress & mask);
	U64 adjustment = alignment - misalignment;

	// Calculate the adjusted address
	U64 alignedAddress = rawAddress + adjustment;

	// Store the adjustment in the byte immediately
	// preceding the adjusted address
	AVRO_ASSERT(adjustment < 256, "Adjustment larger than one byte worth");
	U8* alignedMem = reinterpret_cast<U8*>(alignedAddress);
	alignedMem[-1] = static_cast<U8>(adjustment);
	return static_cast<void*>(alignedMem);
}

void MemoryHeap::Dissipate(void* mem)
{
	if (mem == nullptr) return;
	U8* readjustedPointer = static_cast<U8*>(mem);
	readjustedPointer -= FOOTER_SIZE; // Adjust back to full pointer size
	*readjustedPointer &= ~BLOCK_ALLOCATION_BIT;
	Coalesce(readjustedPointer);
}

void MemoryHeap::DissipateAligned(void* mem)
{
	const U8* alignedMem = reinterpret_cast<const U8*>(mem);
	U64 alignedAddress = reinterpret_cast<U64>(mem);
	U64 adjustment = static_cast<U64>(alignedMem[-1]);

	U64 rawAddress = alignedAddress - adjustment;
	void* rawMem = reinterpret_cast<void*>(rawAddress);

	Dissipate(rawMem);
}

B8 MemoryHeap::GrowHeapSize()
{
	//allocate a new array
	U64 mallocSize = sizeof(U8*) * (m_numBlocks + 1);
	U8** newHeapBlocks = static_cast<U8**>(malloc(mallocSize));

	//check allocation success
	if (!newHeapBlocks) return false;

	//copy existing pointers over (if any)
	for (U64 i = 0; i < m_numBlocks; i++) newHeapBlocks[i] = m_heapBlocks[i];

	//allocate new memory block
	newHeapBlocks[m_numBlocks] = static_cast<U8*>(malloc(m_heapSize_bytes));

	// check allocation
	if (!newHeapBlocks[m_numBlocks]) return false;

	//Attach block
	m_root = newHeapBlocks[0];

	//Check if already a heap pointer
	if (m_heapBlocks) free(m_heapBlocks);

	m_heapBlocks = newHeapBlocks;
	m_numBlocks++;


	return true;
}

//TODO: change block checks to ~
void MemoryHeap::AllocateNewBlock(U8* pointer, U64 size_bytes)
{
	AVRO_ASSERT(size_bytes <= *pointer, "Too much allocated for block, check Allocate function");
	AVRO_ASSERT(!(*pointer & BLOCK_ALLOCATION_BIT), "Block already allocated, check Allocate function");
	U8 oldSize = *pointer;
	//Set new size + alloc bit
	*pointer = static_cast<U8>(size_bytes) | BLOCK_ALLOCATION_BIT;
	*(pointer + size_bytes - FOOTER_SIZE) = static_cast<U8>(size_bytes) | BLOCK_ALLOCATION_BIT;
	//Set size of remaining part of free block in header and footer
	if (size_bytes < oldSize){
		*(pointer + size_bytes) = oldSize - static_cast<U8>(size_bytes);
		if (pointer != m_root)*(pointer + oldSize - FOOTER_SIZE) = oldSize - static_cast<U8>(size_bytes);
	}
}

void MemoryHeap::Coalesce(U8* pointer)
{
	//Forward Coalescing (only if not last pointer)
	if (pointer + *pointer != m_root + m_heapSize_bytes){
		if (!(*(pointer + *pointer) & BLOCK_ALLOCATION_BIT)){
			*pointer += *(pointer + *pointer);
			*(pointer + *pointer) = *pointer;
		}
	}

	//Backward coalescing (only if is not root pointer)
	if (pointer != m_root){
		if (!(*(pointer - FOOTER_SIZE) & BLOCK_ALLOCATION_BIT)){
			U8 prevPointerSize = *(pointer - FOOTER_SIZE);
			U8 pointerSize = *(pointer);
			*(pointer - prevPointerSize) += pointerSize;
			*(pointer + pointerSize) = *(pointer - prevPointerSize);
		}
	}
}
