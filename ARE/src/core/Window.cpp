#include "ARE_stdafx.h"
#include "Window.h"
#include <cstring>

#ifdef A_W32

glob PAINTSTRUCT paint;
glob HDC hDC;
glob B8* m_isRunning;

I64 CALLBACK Window::Win32_Callback(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
	I64 result = 0;

	switch (message){
	case WM_CREATE:{

	}break;
	case WM_SIZE:{
		OutputDebugStringA("WM_SIZE\n");
	}break;
	case WM_DESTROY:{
		*m_isRunning = false; //TODO: Handle this as error
	}break;
	case WM_CLOSE:{
		*m_isRunning = false; //TODO: Handle this as message to user
	}break;
	case WM_ACTIVATEAPP:{
		OutputDebugStringA("WM_ACTIVATE\n");
	}break;
	case WM_PAINT:{
		hDC = BeginPaint(hwnd, &paint);
		SetTextColor(hDC, COLORREF(0x00FF00FF));
		TextOut(hDC, 150, 150, "Hello, World!", sizeof("Hello, World!"));
		EndPaint(hwnd, &paint);
	}break;
	default:{
		result = DefWindowProcA(hwnd, message, wparam, lparam);
	}break;
	}

	return result;
}

void Window::Win32_CreateWindow(HWND* window, HINSTANCE hInstance, U32 width, U32 height, char* title, B8* isRunning)
{
	m_isRunning = isRunning;
	WNDCLASSEX wcx = {};
	char* WNDCLASSNAME = "AvroRenderingEngineWindowClass";

	wcx.cbSize = sizeof(WNDCLASSEX); // size of wndclass
	wcx.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = (WNDPROC) Win32_Callback;
	wcx.cbClsExtra = 0; // if we want to store extra memory
	wcx.cbWndExtra = 0; // if we want to store extra memory
	wcx.hInstance = hInstance;
	wcx.hIcon = LoadIconA(NULL, IDI_APPLICATION); //TODO: set Icon
	wcx.hCursor = 0; // no cursor
	wcx.hbrBackground = NULL; // no background clearing
	wcx.lpszMenuName = NULL; // no menu needed
	wcx.lpszClassName = WNDCLASSNAME;
	wcx.hIconSm = NULL; //TODO: set icon

	if (!RegisterClassEx(&wcx)){
		MessageBox(NULL, "Couldn't register window class", "Error!", MB_ICONERROR | MB_OK); 
		exit(-1);
	}

	*window = CreateWindowEx(NULL,              // Extended Style For The Window
		WNDCLASSNAME,               // Class Name
		title,                  // Window Title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,          // Required Window Style
		CW_USEDEFAULT,					 // X pos
		CW_USEDEFAULT,                   // Y pos
		width,      // Width
		height,     // Height
		NULL,                   // No Parent Window
		NULL,                   // No Menu
		hInstance,              // Instance
		NULL);                  // Don't Pass Anything To WM_CREATE

}
#endif