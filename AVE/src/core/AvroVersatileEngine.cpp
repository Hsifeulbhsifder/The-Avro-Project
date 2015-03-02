#include "AVE_stdafx.h"
#include "AvroVersatileEngine.h"
#include <iostream>
#include <AvroMath.h>
#include <Window.h>
#include <MemoryStack.h>
#include <AvroUtil.h>

using namespace AU;

B8 AvroVersatileEngine::Initialize(HINSTANCE appInstance, U32 width, U32 height, char* title, U64 permanentHeapSize, U64 transientHeapSize){

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
	MSG msg;
	if (!m_isRunning){
		m_isRunning = true;

		MemoryStack singleFrameAllocator;
		singleFrameAllocator.Initialize(AU::KiB(1024));

		while (m_isRunning){
			singleFrameAllocator.Clear();

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

		}
	}
}

void AvroVersatileEngine::Terminate(){
	m_renderingEngine.Terminate();
	m_transientHeap.Terminate();
	m_permanentHeap.Terminate();

	OutputDebugStringA("Engine Termination Sequence Is Complete\n");
}
