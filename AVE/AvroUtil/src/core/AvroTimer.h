#ifndef AVRO_UTIL_TIMER_H
#define AVRO_UTIL_TIMER_H
#include "Avro_Preprocessor.h"

INLINEFORCE DLLEXPORT U64 PerformanceFrequency();

INLINEFORCE DLLEXPORT U64 PerformanceCounter();

INLINEFORCE DLLEXPORT F32 SecondsElapsed(U64 begin, U64 end, U64 perfFrequency);

INLINEFORCE DLLEXPORT void OSSleep(U32 ms);

INLINEFORCE DLLEXPORT B8 SetOSSchedulerGranularity(U32 msGranularity);

#endif