#include "AU_stdafx.h"
#include "MemoryQuantum.h"

const glob U64 TOP_QUARK_SIZE = sizeof(U8*);

MemoryQuantum::MemoryQuantum(){
	Reset();
}

MemoryQuantum::~MemoryQuantum(){
	Terminate();
}

B8 MemoryQuantum::Initialize(U64 quantumSize, U64 quanta){
	if (m_universe) Terminate(); //Check if already allocated
	AVRO_ASSERT(quantumSize > 0, "Size too low")
	//set size for memory units
	m_quantumSize = quantumSize;
	m_quanta = quanta;

	//Attempt memory expansion
	if (ExpandUniverse())  return true;
	return false;

}

void MemoryQuantum::Terminate(){
	//Free all memory
	for (U64 i = 0; i < m_particles; i++) AVRO_DEFAULT_ALLOCATOR.Dissipate(m_universe[i]);
	AVRO_DEFAULT_ALLOCATOR.Dissipate(m_universe);

	Reset(); // update member Variables
}

void* MemoryQuantum::Allocate(){

	//check if out of memory chunks
	if (!m_singularity){
		//Allocate new block
		//NOTE: VERY EXPENSIVE!!

		if (!m_resizable) return nullptr; //check if allowed to resize
		if (!ExpandUniverse()) return nullptr; //check if can allocate
	}

	U8* returnPointer = m_singularity;
	m_singularity = GetNext(m_singularity);
	return scast<void*>((returnPointer + TOP_QUARK_SIZE)); // return pointer data only, skips head
}

void MemoryQuantum::Dissipate(void* quantum){
	//check if passed pointer is null
	if (quantum != nullptr){
		//goes to front of chunk, gets full chunk
		U8* quantumVolume = ((U8*)quantum) - TOP_QUARK_SIZE;

		//push the chunk to the front of list
		SetNext(quantumVolume, m_singularity);
		m_singularity = quantumVolume;
	}
}

void MemoryQuantum::Reset(){
	m_universe = nullptr;
	m_singularity = nullptr;
	m_quantumSize = 0;
	m_quanta = 0;
	m_particles = 0;
	m_resizable = false;
}

B8 MemoryQuantum::ExpandUniverse(){

	//allocates a new array
	U64 universeSize = sizeof(U8*) * (m_particles + 1);
	U8** newUniverse = scast<U8**>(AVRO_DEFAULT_ALLOCATOR.Allocate(universeSize));

	// check allocation success
	if (!newUniverse) return false;

	//copy existing pointers over (if any)
	for (U64 i = 0; i < m_particles; i++) newUniverse[i] = m_universe[i];


	// Allocate new memory block
	newUniverse[m_particles] = AllocateNewQuantumVolume((m_quantumSize + TOP_QUARK_SIZE) * m_quanta, m_quantumSize);

	// attach the block to end of current block set
	if (m_singularity){
		U8* current = m_singularity;
		U8* next = GetNext(m_singularity);

		//iterate to the end of block set
		while (next){
			current = next;
			next = GetNext(next);
		}
		SetNext(current, newUniverse[m_particles]);
	}
	else{
		m_singularity = newUniverse[m_particles];
	}

	// destroy old universe of pointers
	if (m_universe) AVRO_DEFAULT_ALLOCATOR.Dissipate(m_universe);

	// assign the new universe of pointers and increment amount of pointers
	m_universe = newUniverse;
	m_particles++;

	return true;
}

U8* MemoryQuantum::AllocateNewQuantumVolume(U64 total_size, U64 segment_size){

	//calculate the size of each volume
	U64 volumeSize = segment_size;

	//calculate total size to be created
	U64 totalVolumeSize = total_size;

	//allocate new Volume
	U8* newVolume = (U8*)AVRO_DEFAULT_ALLOCATOR.Allocate(totalVolumeSize);
	if (!newVolume) return nullptr;

	// turn the memory into linked list of chunks
	U8* end = newVolume + totalVolumeSize;
	U8* current = newVolume;
	
	//iterate through new volume 
	while (current < end){
		// calculate the next pointer position
		U8* next = current + volumeSize;

		// set the next & previous pointers
		U8** topQuark = (U8**)current;
		topQuark[0] = (next < end ? next: nullptr);

		//move to next block
		current += volumeSize;
	}

	return newVolume;

}

INLINEFORCE U8* MemoryQuantum::GetNext(U8* volume){
	U8** topQuark = (U8**)volume;
	return topQuark[0];
}

INLINEFORCE void MemoryQuantum::SetNext(U8* volumeToModify, U8* newNext){
	U8** topQuark = (U8**)volumeToModify;
	topQuark[0] = newNext;
}