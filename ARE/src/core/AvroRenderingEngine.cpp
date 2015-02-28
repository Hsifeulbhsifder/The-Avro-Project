#include "ARE_stdafx.h"
#include "AvroRenderingEngine.h"

B8 AvroRenderingEngine::Initialize(){
	OutputDebugStringA("Renderer Initialization Sequence Is Complete\n");
	return true;
}

void AvroRenderingEngine::Render(F32 delta){
	OutputDebugStringA("Rendering\n");
}

void AvroRenderingEngine::Terminate(){
	OutputDebugStringA("Renderer Termination Sequence Is Complete\n");
}