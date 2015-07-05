#include "AU_stdafx.h"
#include "AvroWindow.h"
#include <AvroInput.h>

#ifdef A_W32

glob PAINTSTRUCT paint;
glob B8* m_isRunning;

void GameWindowSetState(B8* isRunning){
	m_isRunning = isRunning;
}

#ifdef A_W32
I64 intern CALLBACK Win32_Callback(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
	I64 result = 0;
	
	switch (message){
	case WM_CREATE:{

	}break;
	case WM_SIZE:{
	}break;
	case WM_DESTROY:{
		*m_isRunning = false; //TODO: Handle this as error
	}break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:{
		//Drown These messages, we are using GetKeyState(VK_Menu)
	}break;
	case WM_CLOSE:{
		*m_isRunning = false; //TODO: Handle this as message to user
	}break;
	case WM_ACTIVATEAPP:{
	}break;
	default:{
		result = DefWindowProcA(hwnd, message, wparam, lparam);
	}break;
	}

	return result;
}
#endif

#ifdef A_W32
void intern Win32CreateWindow(HWND hwnd, U32 width, U32 height, char* title){
	WNDCLASSEX wcx = {};
	char* WNDCLASSNAME = "AvroRenderingEngineWindowClass";

	wcx.cbSize = sizeof(WNDCLASSEX); // size of wndclass
	wcx.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = (WNDPROC)Win32_Callback;
	wcx.cbClsExtra = 0; // if we want to store extra memory
	wcx.cbWndExtra = 0; // if we want to store extra memory
	wcx.hInstance = GetModuleHandle(0);
	wcx.hIcon = LoadIconA(NULL, IDI_APPLICATION); //TODO: set Icon
	wcx.hCursor = 0; // no cursor
	wcx.hbrBackground = NULL; // no background clearing
	wcx.lpszMenuName = NULL; // no menu needed
	wcx.lpszClassName = WNDCLASSNAME;
	wcx.hIconSm = NULL; //TODO: set icon

	if (!RegisterClassEx(&wcx)){
		DebugPrint("Couldn't register window class\n");
		ErrorBox("Couldn't register window class", "Error!");
		exit(-1);
	}

	hwnd = CreateWindowEx(NULL,              // Extended Style For The Window
		WNDCLASSNAME,               // Class Name
		title,                  // Window Title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,          // Required Window Style
		CW_USEDEFAULT,					 // X pos
		CW_USEDEFAULT,                   // Y pos
		width,      // Width
		height,     // Height
		NULL,                   // No Parent Window
		NULL,                   // No Menu
		GetModuleHandle(0),              // Instance
		NULL);                  // Don't Pass Anything To WM_CREATE
}

INLINEFORCE intern void Win32TerminateWindow(HWND hwnd, HDC hdc){
	ReleaseDC(hwnd, hdc);
}

INLINEFORCE intern void Win32CreateOpenGLContext(HDC deviceContext, HGLRC glContext){
	glContext = wglCreateContext(deviceContext);
}

INLINEFORCE intern B8 Win32TerminateOpenGLContext(HGLRC glContext){
	return wglDeleteContext(glContext);
}

INLINEFORCE intern B8 Win32MakeCurrentRenderingContext(HDC deviceContext, HGLRC glContext){
	return wglMakeCurrent(deviceContext, glContext);
}

#elif A_UNX
void intern UnixCreateWindow(U32 width, U32 height, char* title){


}

INLINEFORCE intern void UnixTerminateWindow(){
	
}

INLINEFORCE intern void UnixCreateOpenGLContext(){

}

INLINEFORCE intern B8 UnixTerminateOpenGLContext(){
	return false;
}

INLINEFORCE intern B8 UnixMakeCurrentRenderingContext(){
	return false;
}

#endif

INLINEFORCE DLLEXPORT void CreateGameWindow(Window* window, U32 width, U32 height, char* title)
{
	
#ifdef A_W32
	Win32CreateWindow(window->wnd, width, height, title);
	window->deviceContext = GetDC(window->wnd);
#elif A_UNX
	UnixCreateWindow(width, height, title);
#endif

}

INLINEFORCE DLLEXPORT void TerminateGameWindow(Window* window)
{
#ifdef A_W32
	Win32TerminateWindow(window->wnd, window->deviceContext);
#elif A_UNX
	UnixTerminateWindow();
#endif
}

INLINEFORCE DLLEXPORT void CreateGLContext(Window* window)
{
#ifdef A_W32
	Win32CreateOpenGLContext(window->deviceContext, window->glContext);
#elif A_UNX
	UnixCreateOpenGLContext();
#endif
}

INLINEFORCE DLLEXPORT B8 TerminateGLContext(Window* window)
{
#ifdef A_W32
	return Win32TerminateOpenGLContext(window->glContext);
#elif A_UNX
	return UnixTerminateOpenGLContext();
#endif
}

INLINEFORCE DLLEXPORT B8 MakeCurrent(Window* window, B8 terminate)
{
#ifdef A_W32
	if (!terminate)	return Win32MakeCurrentRenderingContext(GetDC(window->wnd), window->glContext);
	return Win32MakeCurrentRenderingContext(window->deviceContext, NULL);
#elif A_UNX
	return UnixMakeCurrentRenderingContext();
#endif
}

INLINEFORCE DLLEXPORT void SwapBuffers(Window* window)
{
#ifdef A_W32
	SwapBuffers(window->deviceContext);
#elif A_UNX
	return SwapBuffers();
#endif
}

INLINEFORCE DLLEXPORT U32 GetVRefreshRate(){
#ifdef A_W32
	return 60;
#elif A_UNX
	return 60;
#endif
}

#endif