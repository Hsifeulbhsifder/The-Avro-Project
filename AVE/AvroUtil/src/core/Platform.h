#ifndef AVRO_UTIL_PLATFORM_H
#define AVRO_UTIL_PLATFORM_H

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

static INLINEFORCE bool IsNaN(float f);
static INLINEFORCE bool IsFinite(float f);


#endif