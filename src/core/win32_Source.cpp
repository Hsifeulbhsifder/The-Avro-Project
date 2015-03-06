#include "AA_stdafx.h"
#include <iostream>
#include <AvroMath.h>
#include <AvroVersatileEngine.h>
#include <AvroUtil.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_DEPTH 16 //16-bit depth

#define TITLE "Avro Arrow"


extern HGLRC hglrc; //OpenGL rendering context

glob B8 isRunning; //TODO: Make this local to a scope

I32 CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	AvroVersatileEngine engine;

	if (engine.Initialize(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE, AU::MiB(10), AU::MiB(250), AU::MiB(16))){
		engine.Run();

		engine.Terminate();
	}
	else{
		OutputDebugStringA("Engine Initialization has failed");
		MessageBox(NULL, "Engine Initialization has failed!", "Error!", MB_ICONERROR | MB_OK);
	}


	return 0;
}