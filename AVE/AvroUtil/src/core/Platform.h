#ifndef AVRO_UTIL_PLATFORM_H
#define AVRO_UTIL_PLATFORM_H

//TODO: make this use our atomic types

#ifdef _WIN32 //TODO: declare this in cmake
#define A_W32
#ifdef _WIN64
#define A_W64
#endif
#elif __unix
#define A_UNX
#endif

#ifndef INLINEFORCE
#define INLINEFORCE
#endif

#ifndef DLLEXPORT
#define DLLEXPORT
#endif

#ifndef DLLIMPORT
#define DLLIMPORT
#endif

static INLINEFORCE char IsNaN(float f);
static INLINEFORCE char IsFinite(float f);


#endif