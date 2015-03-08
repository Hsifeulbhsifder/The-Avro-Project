#ifndef ARE_AVRO_WINDOW_H
#define ARE_AVRO_WINDOW_H

#ifdef A_W32
struct DLLEXPORT Window{
	HWND wnd;
	HGLRC glContext;
};
#elif A_UNX
struct DLLEXPORT Window{

};
#endif


DLLEXPORT void CreateGameWindow(Window* window, U32 width, U32 height, char* title);
DLLEXPORT void GameWindowSetState(B8* isRunning);


#endif