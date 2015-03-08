#include "AVE_stdafx.h"
#include "AvroVersatileEngine.h"
#include <iostream>
#include <AvroMath.h>
#include <Window.h>
#include <MemoryStack.h>
#include <AvroUtil.h>
#include <iostream>

using namespace AU;

B8 AvroVersatileEngine::Initialize(Window* window, U64 permanentHeapSize, U64 transientHeapSize, U64 debugHeapSize){

#ifdef AVRO_DEBUG
	if (!(m_debugHeap.Initialize(debugHeapSize))){
		DebugPrint("Not enough system memory to debug this game");
		MessageBox(NULL, "Not enough RAM to debug this game", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}
#endif

	if (!(m_permanentHeap.Initialize(permanentHeapSize))){
		DebugPrint("Not enough system memory to run this game");
		MessageBox(NULL, "Not enough RAM to run this game", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}
	if (!(m_transientHeap.Initialize(transientHeapSize))){
		DebugPrint("Run this game on a lower setting");
		MessageBox(NULL, "Run this game on a lower setting", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}

	m_window = window;
	m_isRunning = false;
	GameWindowSetState(&m_isRunning);
	

	if (!(m_renderingEngine.Initialize())){
		DebugPrint("Rendering engine initialization has failed");
		MessageBox(NULL, "Rendering Engine initialization Not created!", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}

	DebugPrint("Engine Initialization Sequence Is Complete\n");
	return true;
}

//TODO: Heavily modify
void AvroVersatileEngine::Run(){
	if (!m_isRunning){
		LARGE_INTEGER perfomanceFrequency;
		QueryPerformanceFrequency(&perfomanceFrequency);
		U64 perfCountFrequency = perfomanceFrequency.QuadPart;

		MSG msg;
		m_isRunning = true;

		MemoryStack singleFrameAllocator;
		singleFrameAllocator.Initialize(AU::KiB(1024));

		LARGE_INTEGER lastCounter;
		QueryPerformanceCounter(&lastCounter);

		U64 lastCycleCount = __rdtsc();

		while (m_isRunning){
			singleFrameAllocator.Clear();
			LARGE_INTEGER beginCount;
			QueryPerformanceCounter(&beginCount);

			PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
			if (msg.message != WM_QUIT){
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			else{
				DebugPrint("AvroArrow is kill\n");
				m_isRunning = false;
				break;
			}

			m_renderingEngine.Render(0);

			U64 endCycleCount = __rdtsc();

			LARGE_INTEGER endCounter;
			QueryPerformanceCounter(&endCounter);

			U64 cyclesElapsed = endCycleCount - lastCycleCount;
			U64 counterElapsed = endCounter.QuadPart - lastCounter.QuadPart;
			F64 frameTime = (1000.0 * counterElapsed) / (F64) perfCountFrequency;
			F64 frameRate = (F64) perfCountFrequency / (F64) counterElapsed;
			F64 kcyclesPerFrame = (F64) cyclesElapsed / (1000.0);

			char buffer[256];
			sprintf_s(buffer, sizeof(buffer), "%.04fms | (%.02f Hz) | %.02fkcpf\n", frameTime, frameRate, kcyclesPerFrame);
			DebugPrint(buffer);
			lastCounter = endCounter;
			lastCycleCount = endCycleCount;
		}
	}
}

void AvroVersatileEngine::Terminate(){
	m_renderingEngine.Terminate();
#ifdef AVRO_DEBUG
	m_debugHeap.Terminate();
#endif
	m_transientHeap.Terminate();
	m_permanentHeap.Terminate();

	DebugPrint("Engine Termination Sequence Is Complete\n");
}
