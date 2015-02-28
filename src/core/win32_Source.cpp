#include "AA_stdafx.h"
#include <iostream>
#include <AvroMath.h>
#include <AvroVersatileEngine.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_DEPTH 16 //16-bit depth

#define WNDCLASSNAME "AvroArrowWindowClass"
#define TITLE "Avro Arrow"


extern HGLRC hglrc; //OpenGL rendering context
//extern HWND hwnd; // handle to window

glob B8 isRunning; //TODO: Make this local to a scope

I64 CALLBACK MainWindowCallback(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
	I64 result = 0;

	switch (message){
		case WM_SIZE:{
			OutputDebugStringA("WM_SIZE\n");
		}break;
		case WM_DESTROY:{
			isRunning = false; //TODO: Handle this as error
		}break;
		case WM_CLOSE:{
			isRunning = false; //TODO: Handle this as message to user
		}break;
		case WM_ACTIVATEAPP:{
			OutputDebugStringA("WM_ACTIVATE\n");
		}break;
		case WM_PAINT:{
			PAINTSTRUCT paint;
			HDC hdc = BeginPaint(hwnd, &paint);
			I32 x = paint.rcPaint.left;
			I32 y = paint.rcPaint.top;
			I32 height = paint.rcPaint.bottom - paint.rcPaint.top;
			I32 width = paint.rcPaint.right - paint.rcPaint.left;
			lscope I32 operation = WHITENESS;
			PatBlt(hdc,x,y,width, height, operation);
			if (operation == WHITENESS) operation = BLACKNESS;
			else operation = WHITENESS;
			EndPaint(hwnd, &paint);
		}break;
		default:{
			result = DefWindowProcA(hwnd, message, wparam, lparam);
		}break;
	}

	return result;
}

I32 CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	MSG msg;
	WNDCLASSEX wndclassex = {};

	wndclassex.cbSize = sizeof(WNDCLASSEX); // size of wndclass
	wndclassex.style = CS_OWNDC|CS_VREDRAW|CS_HREDRAW;
	wndclassex.lpfnWndProc = (WNDPROC) MainWindowCallback;
	wndclassex.cbClsExtra = 0; // if we want to store extra memory
	wndclassex.cbWndExtra = 0; // if we want to store extra memory
	wndclassex.hInstance = hInstance;
	wndclassex.hIcon = LoadIconA(NULL, IDI_APPLICATION); //TODO: set Icon
	wndclassex.hCursor = 0; // no cursor
	wndclassex.hbrBackground = NULL; // no background clearing
	wndclassex.lpszMenuName = NULL; // no menu needed
	wndclassex.lpszClassName = WNDCLASSNAME; 
	wndclassex.hIconSm = NULL; //TODO: set icon

	if (!RegisterClassEx(&wndclassex)){
		OutputDebugStringA("Couldn't register window class");
		exit(-1);
	}

	HWND hwnd = CreateWindowEx(NULL,              // Extended Style For The Window
		WNDCLASSNAME,               // Class Name
		TITLE,                  // Window Title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,          // Required Window Style
		CW_USEDEFAULT,					 // X pos
		CW_USEDEFAULT,                   // Y pos
		SCREEN_WIDTH,      // Width
		SCREEN_HEIGHT,     // Height
		NULL,                   // No Parent Window
		NULL,                   // No Menu
		hInstance,              // Instance
		NULL);                  // Don't Pass Anything To WM_CREATE


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

	AvroVersatileEngine engine;

	engine.Initialize();

	engine.Terminate();

	return 0;
}