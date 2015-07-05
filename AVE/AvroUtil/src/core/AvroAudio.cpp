#include "AU_stdafx.h"
#include "AvroAudio.h"
#include "AvroWindow.h"

#ifdef A_W32

#define DIRECT_SOUND_CREATE(name) HRESULT WINAPI name(LPCGUID guidDevice, LPDIRECTSOUND *ds, LPUNKNOWN u)
typedef DIRECT_SOUND_CREATE(DIRECT_SOUND_CREATE_FUNC_TYPE);

B8 DLLEXPORT InitAudio(Window* window, U32 samplesPerSec, U32 fps){
	//Load DirectSound Library
	HMODULE dSoundLib = LoadLib("dsound.dll");

	if (dSoundLib){
		//Get a DirectSound object
		DIRECT_SOUND_CREATE_FUNC_TYPE* DirectSoundCreate = (DIRECT_SOUND_CREATE_FUNC_TYPE*)
										GetProcAddress(dSoundLib, "DirectSoundCreate");

		LPDIRECTSOUND directSound;

		if (DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &directSound, 0))){
			WAVEFORMATEX waveFormat = {};
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nChannels = 2;
			waveFormat.nSamplesPerSec = samplesPerSec;
			waveFormat.wBitsPerSample = 16;
			waveFormat.nBlockAlign = (waveFormat.nChannels*waveFormat.wBitsPerSample) / 8;
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec*waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;
			if (SUCCEEDED(directSound->SetCooperativeLevel(window->wnd, DSSCL_PRIORITY))){
				//Create a primary buffer
				DSBUFFERDESC bufferDesc = {};
				bufferDesc.dwSize = sizeof(DSBUFFERDESC);
				//TODO: Remove Possibly?
				bufferDesc.dwFlags |= DSBCAPS_GLOBALFOCUS; //Keeps sound playing when window isn't active
				bufferDesc.dwFlags |= DSBCAPS_PRIMARYBUFFER;

				LPDIRECTSOUNDBUFFER primaryBuffer;
				if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, 0))){
					if (SUCCEEDED(primaryBuffer->SetFormat(&waveFormat))){
						//TODO: Log
						DebugPrint("Primary Buffer Initialized\n");
					} else{
						//TODO: Log
					}
				} else{
					//TODO: Log
				}
			} else{
				//TODO: Log
			}


			//Create a secondary buffer
			DSBUFFERDESC bufferDesc = {};
			bufferDesc.dwSize = sizeof(DSBUFFERDESC);
			//TODO: Remove Possibly?
			bufferDesc.dwFlags |= DSBCAPS_GLOBALFOCUS; //Keeps sound playing when window isn't active
			bufferDesc.dwBufferBytes = (2 * fps * waveFormat.nSamplesPerSec *
							waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
			bufferDesc.lpwfxFormat = &waveFormat;
			LPDIRECTSOUNDBUFFER secondaryBuffer;
			if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDesc, &secondaryBuffer, 0))){
				//TODO: Log
				DebugPrint("Secondary Buffer Initialized\n");
			} else{
				//TODO: Log
			}


		} else{
			//TODO: Log
		}

	} else{
		//TODO: Log
	}

	return true;
}

#elif A_UNX

B8 DLLEXPORT InitAudio(Window* window, U32 samplesPerSec, U32 fps){
	return false;
}

#endif

void DLLEXPORT TerminateAudio(){

}
