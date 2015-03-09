#include "AA_stdafx.h"
#ifdef A_UNX
#include <Window.h>
#include <AvroVersatileEngine.h>
#include <AvroUtil.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_DEPTH 16 //16-bit depth

#define TITLE "Avro Arrow"

I32 main(I32 argc, char** argv){

	Window window;
	CreateGameWindow(window, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);



	if (engine.Initialize(&window, AU::MiB(10), AU::MiB(250), AU::MiB(16))){
		engine.Run();

		engine.Terminate();
	}
	else{
		DebugPrint("Engine Initialization has failed");
		//MessageBox(NULL, "Engine Initialization has failed!", "Error!", MB_ICONERROR | MB_OK);
	}


}



#endif