#include "AU_stdafx.h"
#include "AvroAudio.h"
#include "AvroWindow.h"
#include "AvroMath.h"

#ifdef A_W32



//TODO: Remove Globals
LPDIRECTSOUNDBUFFER globalSecondaryBuffer;
AudioOutput* globalAudioOutput;

#define DIRECT_SOUND_CREATE(name) HRESULT WINAPI name(LPCGUID guidDevice, LPDIRECTSOUND *ds, LPUNKNOWN u)
typedef DIRECT_SOUND_CREATE(DIRECT_SOUND_CREATE_FUNC_TYPE);

B8 DLLEXPORT InitAudio(Window* window, AudioOutput* audioOutput){
	globalAudioOutput = audioOutput;

	//Load DirectSound Library
	HMODULE dSoundLib = LoadLib("dsound.dll");

	if (dSoundLib){
		//Get a DirectSound object
		DIRECT_SOUND_CREATE_FUNC_TYPE* DirectSoundCreate = (DIRECT_SOUND_CREATE_FUNC_TYPE*)
										GetProcAddress(dSoundLib, "DirectSoundCreate8");

		LPDIRECTSOUND directSound;

		if (DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &directSound, 0))){
			WAVEFORMATEX waveFormat = {};
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nChannels = 2;
			waveFormat.nSamplesPerSec = globalAudioOutput->sampleHz;
			waveFormat.wBitsPerSample = globalAudioOutput->bytesPerSample * 8;
			waveFormat.nBlockAlign = (waveFormat.nChannels*globalAudioOutput->bytesPerSample);
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec*waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;

			HRESULT hr = directSound->SetCooperativeLevel(window->wnd, DSSCL_PRIORITY);
			if (SUCCEEDED(hr)){
				//Create a primary buffer
				DSBUFFERDESC bufferDesc = {};
				bufferDesc.dwSize = sizeof(DSBUFFERDESC);
				//TODO: Remove Possibly?
				//bufferDesc.dwFlags |= DSBCAPS_GLOBALFOCUS; //Keeps sound playing when window isn't active
				bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

				LPDIRECTSOUNDBUFFER primaryBuffer;
				if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, 0))){
					HRESULT error = primaryBuffer->SetFormat(&waveFormat);
					if (SUCCEEDED(error)){
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
			bufferDesc.dwSize = sizeof(bufferDesc);
			//TODO: Remove Possibly?
			bufferDesc.dwFlags |= DSBCAPS_GLOBALFOCUS; //Keeps sound playing when window isn't active
			bufferDesc.dwBufferBytes = globalAudioOutput->bufferSize;
			bufferDesc.lpwfxFormat = &waveFormat;
			
			HRESULT error = directSound->CreateSoundBuffer(&bufferDesc, &globalSecondaryBuffer, 0);
			if (SUCCEEDED(error)){
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


void DLLEXPORT UpdateAudio(){
	DWORD playCursor;
	DWORD writeCursor;
	if (SUCCEEDED(globalSecondaryBuffer->GetCurrentPosition(&playCursor, &writeCursor))){

		DWORD byteToLock = (globalAudioOutput->runningSampleIndex 
			* globalAudioOutput->bytesPerSample) % globalAudioOutput->bufferSize;

		DWORD targetCursor = playCursor + (globalAudioOutput->latencySampleCount
			* globalAudioOutput->bytesPerSample) % globalAudioOutput->bufferSize;
		DWORD bytesToWrite = 0;
		//TODO: Change this to using a lower latency offset from the play cursor when
		// sound effects are implemented
		if(byteToLock > targetCursor){
			bytesToWrite = globalAudioOutput->bufferSize - byteToLock;
			bytesToWrite += targetCursor;
		} else{
			bytesToWrite = targetCursor - byteToLock;
		}

		BufferAudio(globalAudioOutput, byteToLock, bytesToWrite);
		
	} else{
		DebugPrint("p\n");
		//TODO: Log
	}
}

void BufferAudio(AudioOutput* audioOutput, DWORD byteToLock, DWORD bytesToWrite){
	VOID* region1;
	DWORD region1Size;
	VOID* region2;
	DWORD region2Size;

	if (SUCCEEDED(globalSecondaryBuffer->
		Lock(byteToLock, bytesToWrite, &region1, &region1Size, &region2, &region2Size, 0))){

		//TODO: Assert that region1Size and region2Size are valid

		DWORD region1SampleCount = region1Size / audioOutput->bytesPerSample;
		I16* sampleOut = (I16*)region1;
		for (DWORD sampleIndex = 0; sampleIndex < region1SampleCount; sampleIndex++){

			I16 sampleValue = (I16)(AU::Sin(audioOutput->tSin) * audioOutput->volume);
			*sampleOut++ = sampleValue;
			*sampleOut++ = sampleValue;

			audioOutput->tSin += TAU * 1.0f/ (F32)audioOutput->wavePeriod;
			audioOutput->runningSampleIndex++;
		}

		DWORD region2SampleCount = region2Size / audioOutput->bytesPerSample;
		sampleOut = (I16*)region2;
		for (DWORD sampleIndex = 0; sampleIndex < region2SampleCount; sampleIndex++){

			I16 sampleValue = (I16)(AU::Sin(audioOutput->tSin) * audioOutput->volume);
			*sampleOut++ = sampleValue;
			*sampleOut++ = sampleValue;

			audioOutput->tSin += TAU / (F32)audioOutput->wavePeriod;
			audioOutput->runningSampleIndex++;
		}

		globalSecondaryBuffer->Unlock(region1, region1Size, region2, region2Size);
	} else{
		//TODO: Log
	}
}

B8 DLLEXPORT PlayAudio()
{
	HRESULT error = globalSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);
	if (SUCCEEDED(error)){
		globalAudioOutput->soundIsPlaying = true;
	} else{
		DebugPrint("No Sound\n");
		//TODO: Log
		globalAudioOutput->soundIsPlaying = false;
	}
	return globalAudioOutput->soundIsPlaying;
}

#elif A_UNX

B8 DLLEXPORT InitAudio(Window* window, U32 samplesPerSec, U32 fps){
	return false;
}

#endif

void DLLEXPORT TerminateAudio(){

}

