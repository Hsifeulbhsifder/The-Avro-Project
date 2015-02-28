#ifndef AVRO_UTIL_MEMORY_QUANTUM_H
#define AVRO_UTIL_MEMORY_QUANTUM_H
#include "avro_typedefs.h"

class MemoryQuantum{


	U8** m_universe;
	U8* m_singularity;
	U64 m_quantumSize;
	U64 m_quanta;
	U64 m_particles;
	B8 m_resizable;
	
public:
	MemoryQuantum();

	B8 Initialize(U64 quantumSize, U64 quanta);

	// Allocates from pool
	void* Allocate();
	// Frees memory, returns it to pool
	void Dissipate(void* quantum);
	INLINEFORCE U64 GetQuantumSize() const { return m_quantumSize; }

	// Frees all memory from pool
	void Terminate();

	~MemoryQuantum();

private:

	void Reset();

	B8 ExpandUniverse();
	U8* AllocateNewQuantumVolume(U64 total_size, U64 segment_size);

	INLINEFORCE U8* GetNext(U8* volume);
	INLINEFORCE void SetNext(U8* volumeToModify, U8* newNext);

	MemoryQuantum(const MemoryQuantum& rhs){}
	void operator=(const MemoryQuantum& rhs){}
};

#endif