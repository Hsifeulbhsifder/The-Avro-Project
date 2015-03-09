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


INLINEFORCE DLLEXPORT void CreateGameWindow(Window* window, U32 width, U32 height, char* title);
INLINEFORCE DLLEXPORT void GameWindowSetState(B8* isRunning);

INLINEFORCE DLLEXPORT void ClearBuffer(F32 r, F32 g, F32 b, F32 a){
	//TODO: Implement
}

INLINEFORCE DLLEXPORT void SwapBuffers(Window* window); //TODO: Implement

INLINEFORCE DLLEXPORT void CreateGLContext(Window* window);

INLINEFORCE DLLEXPORT B8 TerminateGLContext(Window* window);

INLINEFORCE DLLEXPORT B8 MakeCurrent(Window* window, B8 terminate = false);


#endif