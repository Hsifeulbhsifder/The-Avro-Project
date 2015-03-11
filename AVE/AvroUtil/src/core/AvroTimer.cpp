#include "AU_stdafx.h"
#include "AvroTimer.h"

#ifdef A_W32

INLINEFORCE intern U64 Win32PerformanceFrequency(LARGE_INTEGER* lInt){
	QueryPerformanceFrequency(lInt);
	return lInt->QuadPart;
}

INLINEFORCE intern U64 Win32PerformanceCounter(LARGE_INTEGER* lInt){
	QueryPerformanceCounter(lInt);
	return lInt->QuadPart;
}

#elif A_UNX

INLINEFORCE intern U64 UnixPerformanceFrequency(){
	return 0;
}

INLINEFORCE intern U64 UnixPerformanceCounter(){
	return 0;
}

#endif

INLINEFORCE DLLEXPORT U64 PerformanceFrequency()
{
#ifdef A_W32
	LARGE_INTEGER perfomanceFrequency;
	return Win32PerformanceFrequency(&perfomanceFrequency);	
#elif A_UNX
	return UnixPerformanceFrequency();
#endif
}

INLINEFORCE DLLEXPORT U64 PerformanceCounter()
{
#ifdef A_W32
	LARGE_INTEGER perfomanceCounter;
	return Win32PerformanceCounter(&perfomanceCounter);
#elif A_UNX
	return UnixPerformanceCounter();
#endif
}
