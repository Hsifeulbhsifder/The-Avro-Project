#include "AA_stdafx.h"
#ifdef A_W32
#include <AvroWindow.h>
#include <AvroVersatileEngine.h>
#include <AvroUtil.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_DEPTH 16 //16-bit depth

#define TITLE "Avro Arrow"

I32 STDCALL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	Window window;

	CreateGameWindow(&window, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	if (!window.wnd) {
		DebugPrint("Window creation has failed");
		ErrorBox("Window Not created!", "Error!");
		return false;
	}

	AvroVersatileEngine engine;

	if (engine.Initialize(&window, AU::MiB(16), AU::MiB(256), AU::MiB(16))){
		engine.Run();

		engine.Terminate();
	}
	else{
		DebugPrint("Engine Initialization has failed");
		ErrorBox("Engine Initialization has failed!", "Error!");
	}

	return 0;
}

#endif