#ifndef AVRO_UTIL_WIN32_PLATFORM_H
#define AVRO_UTIL_WIN32_PLATFORM_H
#include <float.h>

#pragma warning(disable : 4005)

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define INLINEFORCE __forceinline
#define NOINLINE __declspec(noinline)

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define AvroDebugBreak() DebugBreak()

static INLINEFORCE bool IsNaN(float f) { return _isnan(f) != 0; }
static INLINEFORCE bool IsFinite(float f) { return _finite(f) != 0; }


#endif