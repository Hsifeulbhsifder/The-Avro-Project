#ifndef AVRO_VERSATILE_ENGINE_H
#define AVRO_VERSATILE_ENGINE_H

#include <MemoryHeap.h>
#include <AvroRenderingEngine.h>

struct Window;

class DLLEXPORT AvroVersatileEngine{
private:
	AvroVersatileEngine(const AvroVersatileEngine& rhs){}
	void operator=(const AvroVersatileEngine& rhs){}
public:
	Window* m_window;
	B8 m_isRunning;
	MemoryHeap m_permanentHeap;
	MemoryHeap m_transientHeap;
#ifdef AVRO_DEBUG
	MemoryHeap m_debugHeap;
#endif

	AvroRenderingEngine m_renderingEngine;

	AvroVersatileEngine(){}

	B8 Initialize(Window* window, U64 permanentHeapSize, U64 transientHeapSize, U64 debugHeapSize);

	void Run();

	void Terminate();

	~AvroVersatileEngine(){}

};

#endif
