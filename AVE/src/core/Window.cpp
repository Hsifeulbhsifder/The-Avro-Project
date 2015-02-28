#include "Window.h"

void Win32_CreateAvroWindow(HINSTANCE& hinst, HWND* hwnd, U32 width, U32 height, U32 depth, I32 type)
{
	//Center position
	I32 xPos = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
	I32 yPos = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

	//Set up the window for a windowed application by default
	I64 wndStyle = WS_OVERLAPPEDWINDOW;

	I32 screenMode = WINDOWED;

	//if full screen
	if (type = FULLSCREEN){
		wndStyle = WS_POPUP;
		screenMode = FULLSCREEN;
		xPos = 0;
		yPos = 0;

		//change resolution before the widow is created
		
	}
	

}

