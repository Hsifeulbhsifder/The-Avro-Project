#include "AVE_stdafx.h"
#include "AvroVersatileEngine.h"
#include <iostream>
#include <AvroMath.h>
#include <VectorMath.h>

using namespace ave;

B8 AvroVersatileEngine::Initialize(){
	OutputDebugStringA("Engine Initialization Sequence Is Complete\n");
	return true;
}

void AvroVersatileEngine::Run(){
	if (!isRunning){
		isRunning = true;


		while (isRunning){
			OutputDebugStringA("Engine Is Running\n");
		}
	}
}

void AvroVersatileEngine::Terminate(){
	OutputDebugStringA("Engine Termination Sequence Is Complete\n");
}
