#include "AU_stdafx.h"
#include "MemoryStack.h"

MemoryStack::MemoryStack(){
	Reset();
}

MemoryStack::~MemoryStack(){
	Terminate();
}

void MemoryStack::Reset(){
	m_root = nullptr;
	m_stackSize_bytes = 0;
	m_currMarker = 0;
}

INLINEFORCE void MemoryStack::Terminate(){
	AVRO_DEFAULT_ALLOCATOR.Dissipate(m_root);
	Reset();
}

B8 MemoryStack::Initialize(U64 stackSize_bytes){
	if (m_root) Terminate();
	AVRO_ASSERT(stackSize_bytes > 0, "Stack Size too low");
	m_stackSize_bytes = stackSize_bytes;
	m_root = scast<U8*>(AVRO_DEFAULT_ALLOCATOR.Allocate(stackSize_bytes));
	if (!m_root) return false;

	m_currMarker = rcast<Marker>(m_root);
	return true;
}

void* MemoryStack::Allocate(U64 size_bytes)
{
	AVRO_ASSERT(m_root, "Memory Stack has not been initialized");
	AVRO_ASSERT(size_bytes > 0, "Allocation size too small");
	Marker rootAddress = rcast<Marker>(m_root);
	if ((rootAddress + m_stackSize_bytes - m_currMarker) >= size_bytes){
		Marker memAddress = m_currMarker;
		m_currMarker += size_bytes;
		return rcast<void*>(m_currMarker);
	}

	return nullptr;
}

void* MemoryStack::AllocateAligned(U64 size_bytes, U8 alignment)
{
	AVRO_ASSERT(alignment > 0, "Bit alignment too small");
	AVRO_ASSERT(alignment <= 128, "Bit alignment too large");
	AVRO_ASSERT((alignment & (alignment - 1)) == 0, "Bit alignment not Power of Two");

	// Determine total amount of memory to allocate.
	U64 expandedSize_bytes = size_bytes + alignment;

	// Allocate unaligned block & convert address to Marker.
	Marker rawAddress = rcast<Marker>(Allocate(expandedSize_bytes));

	// Calculate the adjustment by masking off the lower bits
	// of the address, to determine how "misaligned" it is.
	U64 mask = (alignment - 1);
	Marker misalignment = (rawAddress & mask);
	ptrdiff_t adjustment = alignment - misalignment;

	// Calculate the adjusted address
	Marker alignedAddress = rawAddress + adjustment;

	return rcast<void*>(alignedAddress);
}

INLINEFORCE void MemoryStack::FreeToMarker(Marker marker)
{
	U64 rootAddress = rcast<U64>(m_root);
	AVRO_ASSERT(marker >= rootAddress, "Marker precedes root stack pointer");
	AVRO_ASSERT(marker <= (rootAddress + m_stackSize_bytes), "Marker succeeds end of stack");

	m_currMarker = marker;
}
