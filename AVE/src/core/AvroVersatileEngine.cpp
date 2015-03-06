#include "AVE_stdafx.h"
#include "AvroVersatileEngine.h"
#include <iostream>
#include <AvroMath.h>
#include <Window.h>
#include <MemoryStack.h>
#include <AvroUtil.h>

using namespace AU;

B8 AvroVersatileEngine::Initialize(HINSTANCE appInstance, U32 width, U32 height, char* title, U64 permanentHeapSize, U64 transientHeapSize, U64 debugHeapSize){

#ifdef AVRO_DEBUG
	if (!(m_debugHeap.Initialize(debugHeapSize))){
		OutputDebugStringA("Not enough system memory to debug this game");
		MessageBox(NULL, "Not enough RAM to debug this game", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}
#endif

	if (!(m_permanentHeap.Initialize(permanentHeapSize))){
		OutputDebugStringA("Not enough system memory to run this game");
		MessageBox(NULL, "Not enough RAM to run this game", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}
	if (!(m_transientHeap.Initialize(transientHeapSize))){
		OutputDebugStringA("Run this game on a lower setting");
		MessageBox(NULL, "Run this game on a lower setting", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}

	m_isRunning = false;
	Window::Win32_CreateWindow(&m_window, appInstance, width, height, title, &m_isRunning);
	if (!m_window) {
		OutputDebugStringA("Window creation has failed");
		MessageBox(NULL, "Window Not created!", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}

	if (!(m_renderingEngine.Initialize())){
		OutputDebugStringA("Rendering engine initialization has failed");
		MessageBox(NULL, "Rendering Engine initialization Not created!", "Error!", MB_ICONERROR | MB_OK);
		return false;
	}

	OutputDebugStringA("Engine Initialization Sequence Is Complete\n");
	return true;
}

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
				OutputDebugStringA("AvroArrow is kill\n");
				m_isRunning = false;
				break;
			}

			m_renderingEngine.Render(0);

			U64 endCycleCount = __rdtsc();

			LARGE_INTEGER endCounter;
			QueryPerformanceCounter(&endCounter);

			U64 cyclesElapsed = endCycleCount - lastCycleCount;
			U64 counterElapsed = endCounter.QuadPart - lastCounter.QuadPart;
			U64 frameTime = (U64)((1000.0 * counterElapsed) / perfCountFrequency);
			U64 frameRate = perfCountFrequency / counterElapsed;
			U64 kcyclesPerFrame = cyclesElapsed / (1000);

			char buffer[256];
			wsprintfA(buffer, "%dms | (%d Hz) | %dkcpf\n", frameTime, frameRate, kcyclesPerFrame);
			OutputDebugStringA(buffer);
			//TODO: Display this value
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

	OutputDebugStringA("Engine Termination Sequence Is Complete\n");
}
