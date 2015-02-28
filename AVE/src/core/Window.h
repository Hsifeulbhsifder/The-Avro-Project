#include <avro_typedefs.h>
#include <Avro_Preprocessor.h>

#define WINDOWED 0
#define FULLSCREEN 1

DLLEXPORT void Win32_CreateAvroWindow(HINSTANCE& hinst, HWND* hwnd,
	I32 width, I32 height, I32 depth, I32 type);