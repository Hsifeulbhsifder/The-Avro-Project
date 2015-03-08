#ifndef AVRO_UTIL_UNIX_PLATFORM_H
#define AVRO_UTIL_UNIX_PLATFORM_H
#ifdef A_UNX

#define VARARGS 
#define CDECL 
#define STDCALL 
#define INLINEFORCE __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))

#define DLLEXPORT __attribute__((visibility("default")))
#define DLLIMPORT __attribute__((visibility("default")))

static INLINEFORCE char IsNaN(float f) { return isnan(f); }
static INLINEFORCE char IsFinite(float f) { return isfinite(f); }

#endif
#endif