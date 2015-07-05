#ifndef AVRO_UTIL_AUDIO_H
#define AVRO_UTIL_AUDIO_H

//TODO: Move all includes to source file, do same for input
#ifdef A_W32
#include <dsound.h>

#elif A_UNX

#endif

struct Window;

B8 DLLEXPORT InitAudio(Window* window, U32 samplesPerSec, U32 fps);

void DLLEXPORT TerminateAudio();

#endif