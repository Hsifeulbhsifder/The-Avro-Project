#include "AVE_stdafx.h"
#include "AvroVersatileEngine.h"
#include <iostream>
#include <AvroMath.h>
#include <AvroWindow.h>
#include <MemoryStack.h>
#include <AvroUtil.h>
#include <iostream>
#include <AvroTimer.h>

using namespace AU;

B8 AvroVersatileEngine::Initialize(Window* window, U64 permanentHeapSize, U64 transientHeapSize, U64 debugHeapSize){

#ifdef AVRO_DEBUG
	if (!(m_debugHeap.Initialize(debugHeapSize))){
		DebugPrint("Not enough system memory to debug this game");
		ErrorBox("Not enough RAM to debug this game", "Error!");
		return false;
	}
#endif

	if (!(m_permanentHeap.Initialize(permanentHeapSize))){
		DebugPrint("Not enough system memory to run this game");
		ErrorBox("Not enough RAM to run this game", "Error!");
		return false;
	}
	if (!(m_transientHeap.Initialize(transientHeapSize))){
		DebugPrint("Run this game on a lower setting");
		ErrorBox("Run this game on a lower setting", "Error!");
		return false;
	}

	m_window = window;
	m_isRunning = false;
	GameWindowSetState(&m_isRunning);

	CreateGLContext(m_window);
	MakeCurrent(m_window);
	

	if (!(m_renderingEngine.Initialize(m_window))){
		DebugPrint("Rendering engine initialization has failed");
		ErrorBox("Rendering Engine initialization Not created!", "Error!");
		return false;
	}

	m_perfFrequency = PerformanceFrequency();

	U32 gameUpdateHz = GetVRefreshRate();
	m_targetSecondsPerFrame = 1.0f / (F32)gameUpdateHz;

	m_granularSleeping = SetOSSchedulerGranularity(1);

	DebugPrint("Engine Initialization Sequence Is Complete\n");
	return true;
}

//TODO: Heavily modify
void AvroVersatileEngine::Run(){
	if (!m_isRunning){
		MSG msg;
		m_isRunning = true;

		MemoryStack singleFrameAllocator;
		singleFrameAllocator.Initialize(AU::KiB(1024));

		U64 lastCounter = PerformanceCounter();

		U64 lastCycleCount = __rdtsc();

		while (m_isRunning){
			U64 beginCount = PerformanceCounter();

			singleFrameAllocator.Clear();

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



			U64 workCounter = PerformanceCounter();

			F32 workSecondsElapsed = SecondsElapsed(lastCounter, workCounter, m_perfFrequency);
			
			F32 secondsElapsedForFrame = workSecondsElapsed;
			if (secondsElapsedForFrame < m_targetSecondsPerFrame){
				if (m_granularSleeping){
					U32 sleepMS = (U32)(1000.0f * (m_targetSecondsPerFrame - secondsElapsedForFrame));
					if (sleepMS > 0) OSSleep(sleepMS);
				}

				F32 testSecondsElapsedForFrame = SecondsElapsed(lastCounter, PerformanceCounter(), m_perfFrequency);
				AVRO_ASSERT(testSecondsElapsedForFrame > 0, "Slept too long!")
				while (secondsElapsedForFrame < m_targetSecondsPerFrame){

					secondsElapsedForFrame = 
						SecondsElapsed(lastCounter, PerformanceCounter(), m_perfFrequency);
				}
			}else{
				//TODO: MISSED FRAME RATE
				//TODO: Log
			}

			m_renderingEngine.Render(0);

			U64 endCounter = PerformanceCounter();
			F32 frameTime = (1000.0f * SecondsElapsed(lastCounter, endCounter, m_perfFrequency));
			lastCounter = endCounter;
			F32 frameRate = 1000.0f / (F32) frameTime;
			U64 endCycleCount = __rdtsc();
			U64 cyclesElapsed = endCycleCount - lastCycleCount;
			lastCycleCount = endCycleCount;
			F64 kcyclesPerFrame = (F64) cyclesElapsed / (1000.0);

			char buffer[256];
			sprintf_s(buffer, sizeof(buffer), "%.04fms | (%.02f Hz) | %.02fkcpf\n", frameTime, frameRate, kcyclesPerFrame);
			DebugPrint(buffer);

		}
	}
}

void AvroVersatileEngine::Execute(){
	if (!m_isRunning){

		MemoryStack singleFrameAllocator;

		while (m_isRunning){

		}

	}
}

void AvroVersatileEngine::Terminate(){
	m_renderingEngine.Terminate();

	MakeCurrent(m_window, true);
	TerminateGLContext(m_window);

#ifdef AVRO_DEBUG
	m_debugHeap.Terminate();
#endif
	m_transientHeap.Terminate();
	m_permanentHeap.Terminate();

	DebugPrint("Engine Termination Sequence Is Complete\n");
}
