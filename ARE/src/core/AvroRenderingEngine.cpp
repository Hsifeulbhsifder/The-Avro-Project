#include "ARE_stdafx.h"
#include "AvroRenderingEngine.h"
#include "OpenGL.h"
#include "AvroWindow.h"

B8 AvroRenderingEngine::Initialize(Window* window){
	m_window = window;
	if (!InitGraphics(m_window)){
		DebugPrint("Could Not Initialize Graphics");
		ErrorBox("Cant Initialize Graphics", "Error!");
		return false;
	}
	DebugPrint("Renderer Initialization Sequence Is Complete\n");
	return true;
}

void AvroRenderingEngine::Render(F32 delta){
	ClearScreen();


	SwapBuffers(m_window);
}

void AvroRenderingEngine::Terminate(){

	DebugPrint("Renderer Termination Sequence Is Complete\n");
}