#ifndef AVRO_UTIL_WIN32_PLATFORM_H
#define AVRO_UTIL_WIN32_PLATFORM_H
#include <float.h>

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


#endif