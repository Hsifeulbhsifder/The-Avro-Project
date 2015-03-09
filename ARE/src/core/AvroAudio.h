#ifndef ARE_AVRO_WINDOW_H
#define ARE_AVRO_WINDOW_H

struct DLLEXPORT SoundBuffer{
	U32 Hz;
	U32 sampleCount;
	U16* samples;
};

#endif