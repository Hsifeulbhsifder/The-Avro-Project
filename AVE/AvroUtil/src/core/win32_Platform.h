#ifndef AVRO_UTIL_WIN32_PLATFORM_H
#define AVRO_UTIL_WIN32_PLATFORM_H
#include <float.h>
#include <windows.h>

#pragma warning(disable : 4005)

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define VARARGS __cdecl
#define CDECL __cdecl
#define STDCALL __stdcall
#define INLINEFORCE __forceinline
#define NOINLINE __declspec(noinline)

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define AvroDebugBreak() DebugBreak()

static INLINEFORCE char IsNaN(float f) { return _isnan(f); }
static INLINEFORCE char IsFinite(float f) { return _finite(f); }

#define LoadLib(str) LoadLibraryA(str)

#ifdef AVRO_DEBUG

#define DebugPrint(str){ \
	OutputDebugStringA(str);\
}

#elif AVRO_PROFILE

#define DebugPrint(str){ \
	OutputDebugStringA(str);\
}

#elif AVRO_RELEASE

#define DebugPrint(str){}

#elif AVRO_PRODUCTION

#define DebugPrint(str){}

#endif


#define ErrorBox(str, title){\
	MessageBox(NULL, str, title, MB_ICONERROR | MB_OK);\
}

#endif