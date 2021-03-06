#ifndef AVRO_VERSATILE_ENGINE_H
#define AVRO_VERSATILE_ENGINE_H

#include <MemoryHeap.h>
#include <AvroRenderingEngine.h>

struct Window;
struct AudioOutput;

class DLLEXPORT AvroVersatileEngine{
private:
	AvroVersatileEngine(const AvroVersatileEngine& rhs){}
	void operator=(const AvroVersatileEngine& rhs){}
	F32 m_targetSecondsPerFrame;
	U64 m_perfFrequency;
	B8 m_granularSleeping;
public:
	MemoryHeap m_permanentHeap;
	MemoryHeap m_transientHeap;
#ifdef AVRO_DEBUG
	MemoryHeap m_debugHeap;
#endif
	Window* m_window;
	AudioOutput* audioOutput;
	B8 m_isRunning;

	AvroRenderingEngine m_renderingEngine;

	AvroVersatileEngine(){}

	B8 Initialize(Window* window, U64 permanentHeapSize, U64 transientHeapSize, U64 debugHeapSize);

	void Run();
	
	void Execute();

	void Terminate();

	~AvroVersatileEngine(){}

};

#endif
