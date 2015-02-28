#include "AA_stdafx.h"
#include <iostream>
#include <AvroMath.h>
#include <AvroVersatileEngine.h>
#include <Window.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_DEPTH 16 //16-bit depth

#define TITLE "Avro Arrow"


extern HGLRC hglrc; //OpenGL rendering context

glob B8 isRunning; //TODO: Make this local to a scope

I32 CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	MSG msg;
	HWND hwnd;
	Window::Win32_CreateWindow(&hwnd, hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE, &isRunning);

	if (hwnd){
		isRunning = true;
		while(isRunning){

			BOOL msgResult = GetMessage(&msg, 0, 0, 0);
			if (msgResult > 0){
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			else{
				OutputDebugStringA("AvroArrow is kill\n");
				break;
			}
		}

	}
	else{
		MessageBox(NULL, "Window Not created!", "Error!", MB_ICONERROR | MB_OK);
	}

	AvroVersatileEngine engine;

	engine.Initialize();

	engine.Terminate();

	return 0;
}