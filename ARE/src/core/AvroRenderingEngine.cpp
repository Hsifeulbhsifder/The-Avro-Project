#include "ARE_stdafx.h"
#include "AvroRenderingEngine.h"

B8 AvroRenderingEngine::Initialize(){
	DebugPrint("Renderer Initialization Sequence Is Complete\n");
	return true;
}

void AvroRenderingEngine::Render(F32 delta){
}

void AvroRenderingEngine::Terminate(){
	DebugPrint("Renderer Termination Sequence Is Complete\n");
}