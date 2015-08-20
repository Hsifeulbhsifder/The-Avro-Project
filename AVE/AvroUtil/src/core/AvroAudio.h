#ifndef AVRO_UTIL_AUDIO_H
#define AVRO_UTIL_AUDIO_H

//TODO: Move all includes to source file, do same for input
#ifdef A_W32
#include <dsound.h>

#elif A_UNX

#endif

struct Window;

struct AudioOutput{
	F32 tSin;
	U32 sampleHz;
	U32 toneHz;
	U32 runningSampleIndex;
	U32 wavePeriod;
	U32 bytesPerSample;
	U32 bufferSize;
	U32 latencySampleCount;
	I16 volume;
	B8 soundIsPlaying;
};

B8 DLLEXPORT InitAudio(Window* window, AudioOutput* audioOutput);

void DLLEXPORT UpdateAudio();

void DLLEXPORT BufferAudio(AudioOutput* audioOutput, DWORD byteToWrite, DWORD bytesToLock);

B8 DLLEXPORT PlayAudio();

void DLLEXPORT TerminateAudio();

#endif