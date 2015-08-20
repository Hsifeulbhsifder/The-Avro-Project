#include "AU_stdafx.h"
#include "win32_Platform.h"

glob B8* m_isRunning;

void GameWindowSetState(B8* isRunning){
	m_isRunning = isRunning;
}

LRESULT CALLBACK Win32_Callback(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
	LRESULT result = 0;

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
		U64 vkCode = wparam;
		AVI::BufferKey((U32)vkCode, (lparam & (1 << 31)) == 0, (lparam & (1 << 30)) != 0);
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