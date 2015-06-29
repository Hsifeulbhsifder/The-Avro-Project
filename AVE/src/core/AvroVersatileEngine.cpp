#include "AVE_stdafx.h"
#include "AvroVersatileEngine.h"
#include <iostream>
#include <AvroMath.h>
#include <AvroWindow.h>
#include <MemoryStack.h>
#include <AvroUtil.h>
#include <iostream>
#include <AvroTimer.h>
#include <AvroInput.h>

using namespace AU;

glob U32 numControllers = 1; //Number of active controllers

B8 AvroVersatileEngine::Initialize
(Window* window, U64 permanentHeapSize, U64 transientHeapSize, U64 debugHeapSize){

	//Initialize memory
#ifdef AVRO_DEBUG
	if (!(m_debugHeap.Initialize(debugHeapSize))){
		DebugPrint("Not enough system memory to debug this game\n");
		ErrorBox("Not enough RAM to debug this game", "Error!");
		return false;
	}
#endif

	if (!(m_permanentHeap.Initialize(permanentHeapSize))){
		DebugPrint("Not enough system memory to run this game\n");
		ErrorBox("Not enough RAM to run this game", "Error!");
		return false;
	}
	if (!(m_transientHeap.Initialize(transientHeapSize))){
		DebugPrint("Run this game on a lower setting\n");
		ErrorBox("Run this game on a lower setting", "Error!");
		return false;
	}

	//initialize Input
	if (!(InitInput(numControllers))){
		numControllers = 0;
	}

	//Initialize window
	m_isRunning = false;
	m_window = window;
	GameWindowSetState(&m_isRunning);

	CreateGLContext(m_window);
	MakeCurrent(m_window);
	

	if (!(m_renderingEngine.Initialize(m_window))){
		DebugPrint("Rendering engine initialization has failed\n");
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

				F32 testSecondsElapsedForFrame = SecondsElapsed(lastCounter, 
												PerformanceCounter(), m_perfFrequency);
				AVRO_ASSERT(testSecondsElapsedForFrame > 0, "Slept too long!")
				while (secondsElapsedForFrame < m_targetSecondsPerFrame){

					secondsElapsedForFrame = 
						SecondsElapsed(lastCounter, PerformanceCounter(), m_perfFrequency);
				}
			}else{
				//TODO: MISSED FRAME RATE
				//TODO: Log
			}

			//TODO: Handle Input Updating and rendering

			//Input
			AVI::SquareInputs(true); //TODO: Possibly remove from here
			//TODO: Poll more frequently
			if (AVI::GetKeyTapped('W')){
				DebugPrint("W \n");
			} 
			AVI::Poll();
			for (U32 i = 0; i < numControllers; i++){
				if (AVI::GamePadIsActive(i)){
					B8 dUp = AVI::U(i);
					B8 dDown = AVI::D(i);
					B8 dLeft = AVI::L(i);
					B8 dRight = AVI::R(i);
					B8 start = AVI::START(i);
					B8 back = AVI::BACK(i);
					B8 lb = AVI::LB(i);
					B8 rb = AVI::RB(i);
					B8 l3 = AVI::L3(i);
					B8 r3 = AVI::R3(i);
					B8 a = AVI::A(i);
					B8 b = AVI::B(i);
					B8 x = AVI::X(i);
					B8 y = AVI::Y(i);
					F32 lx = AVI::LX(i);
					F32 ly = AVI::LY(i);
					F32 rx = AVI::RX(i);
					F32 ry = AVI::RY(i);
					F32 lt = AVI::LT(i);
					F32 rt = AVI::RT(i);

					AVI::Vibrate(i, AU::Sqrt(lx*lx + ly*ly), AU::Sqrt(rx*rx + ry*ry));

					char buffer[256];
					sprintf_s(buffer, sizeof(buffer), 
							"LX: %.03f LY: %.03f RX: %.03f RY: %.03f LT: %.03f RT: %.03f\n", 
							lx, ly, rx, ry, lt, rt);
					DebugPrint(buffer);
				}
			}

			m_renderingEngine.Render();

			U64 endCounter = PerformanceCounter();
			F32 frameTime = (1000.0f * SecondsElapsed(lastCounter, endCounter, m_perfFrequency));
			lastCounter = endCounter;
			F32 frameRate = 1000.0f / (F32) frameTime;
			U64 endCycleCount = __rdtsc();
			U64 cyclesElapsed = endCycleCount - lastCycleCount;
			lastCycleCount = endCycleCount;
			F64 kcyclesPerFrame = (F64) cyclesElapsed / (1000.0);

			char buffer[256];
			sprintf_s(buffer, sizeof(buffer), "%.04fms | (%.02f Hz) | %.02fkcpf\n", 
					frameTime, frameRate, kcyclesPerFrame);
			//DebugPrint(buffer);

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
