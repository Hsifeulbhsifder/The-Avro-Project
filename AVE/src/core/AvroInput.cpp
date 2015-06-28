#include "AVE_stdafx.h"
#include <AvroInput.h>
#include <AvroAllocator.h>
#include <AvroUtil.h>
#include <AvroMath.h>

intern U32 numControllers; 
intern GamePad *gamepads;
intern F32 STICK_DEADZONE = 8269; //Average of two recommended values on MSDN
intern U32 STICK_DEADZONE2 = 68376361; //Square of the average of two recommended values on MSDN
intern F32 TRIGGER_DEADZONE = 30; //Recommendation from MSDN

#ifdef A_W32

//Supports XInputGetState and XInputSetState without requiring XInput
#define XINPUT_GET_STATE(name) U32 WINAPI name(U32 userIndex, XINPUT_STATE* state)
#define XINPUT_SET_STATE(name) U32 WINAPI name(U32 userIndex, XINPUT_VIBRATION* vibration)
typedef XINPUT_GET_STATE(XINPUT_GET_STATE_FUNC_TYPE);
typedef XINPUT_SET_STATE(XINPUT_SET_STATE_FUNC_TYPE);

XINPUT_GET_STATE(XInputGetStateStub){
	return 0;
}

XINPUT_SET_STATE(XInputSetStateStub){
	return 0;
}
glob XINPUT_GET_STATE_FUNC_TYPE* XInputGetState_ = XInputGetStateStub;
glob XINPUT_SET_STATE_FUNC_TYPE* XInputSetState_ = XInputSetStateStub;
#define XInputGetState XInputGetState_
#define XInputSetState XInputSetState_

INLINEFORCE B8 Win32LoadXInput(){
	HMODULE XInputLibrary = LoadLibrary("xinput1_3.dll");
	if (XInputLibrary){
		XInputGetState = (XINPUT_GET_STATE_FUNC_TYPE*)GetProcAddress(XInputLibrary, "XInputGetState");
		XInputSetState = (XINPUT_SET_STATE_FUNC_TYPE*)GetProcAddress(XInputLibrary, "XInputSetState");
		return true;
	}
	else{
		return false;
	}
}
#elif A_UNX

#endif

//TODO: Support lack of gamepads
B8 DLLEXPORT InitInput(U32 _numControllers){

#ifdef A_W32
	if (Win32LoadXInput()){
		DebugPrint("Loaded XInput\n");
	}
	else{
		DebugPrint("Failed to load XInput\n");
		numControllers = 0;
		return false;
	}
#elif A_UNX

#endif
	
	if (_numControllers > 0 && _numControllers < 5){
		numControllers = _numControllers;
	}
	else{
		numControllers = 0;
		return false;
	}

	gamepads = (GamePad*) AVRO_DEFAULT_ALLOCATOR.Allocate(numControllers * sizeof(Controller));
	return true;
}

namespace GPD{

	void DLLEXPORT Poll(){
		for (U32 i = 0; i < numControllers; i++){
			XINPUT_STATE controllerState;
			if (XInputGetState(i, &controllerState) == ERROR_SUCCESS){
				//Controller is available

				//Get buttons
				gamepads[i].buttons = (&controllerState.Gamepad)->wButtons;

				//Circular deadzone processing of left joystick
				F32 lx = (&controllerState.Gamepad)->sThumbLX;
				F32 ly = (&controllerState.Gamepad)->sThumbLY;
				U32 lmgntd2 = (U32)(lx*lx + ly*ly);
				if (lmgntd2 < STICK_DEADZONE2){
					gamepads[i].lx = 0.f;
					gamepads[i].ly = 0.f;
				}
				else{
					F32 lmgntd = AU::Sqrt((F32)lmgntd2);
					F32 nlxFactor = lx / lmgntd;
					F32 nlyFactor = ly / lmgntd;
					if (lmgntd > AVI_MAX_STICK_VALUE) lmgntd = AVI_MAX_STICK_VALUE;
					lmgntd -= STICK_DEADZONE;
					lx = nlxFactor * lmgntd;
					ly = nlyFactor * lmgntd;

					gamepads[i].lx = lx / (AVI_MAX_STICK_VALUE - STICK_DEADZONE * nlxFactor * AU::Sgn(lx));
					gamepads[i].ly = ly / (AVI_MAX_STICK_VALUE - STICK_DEADZONE * nlyFactor * AU::Sgn(ly));
				}

				//Circular deadzone processing of right joystick
				F32 rx = (&controllerState.Gamepad)->sThumbRX;
				F32 ry = (&controllerState.Gamepad)->sThumbRY;
				U32 rmgntd2 = (U32)(rx*rx + ry*ry);
				if (rmgntd2 < STICK_DEADZONE2){
					gamepads[i].rx = 0.f;
					gamepads[i].ry = 0.f;
				}
				else{
					F32 rmgntd = AU::Sqrt((F32)rmgntd2);
					F32 nrxFactor = rx / rmgntd;
					F32 nryFactor = ry / rmgntd;
					if (rmgntd > AVI_MAX_STICK_VALUE) rmgntd = AVI_MAX_STICK_VALUE;
					rmgntd -= STICK_DEADZONE;
					rx = nrxFactor * rmgntd;
					ry = nryFactor * rmgntd;

					gamepads[i].rx = rx / (AVI_MAX_STICK_VALUE - STICK_DEADZONE * nrxFactor * AU::Sgn(rx));
					gamepads[i].ry = ry / (AVI_MAX_STICK_VALUE - STICK_DEADZONE * nryFactor * AU::Sgn(ry));
				}

				//Linear deadzone processing of left trigger
				F32 lt = (&controllerState.Gamepad)->bLeftTrigger;
				if (lt < TRIGGER_DEADZONE){
					gamepads[i].lt = 0.f;
				}
				else{
					gamepads[i].lt = lt / AVI_MAX_TRIGGER_VALUE;
				}

				//Linear deadzone processing of right trigger
				F32 rt = (&controllerState.Gamepad)->bRightTrigger;
				if (rt < TRIGGER_DEADZONE){
					gamepads[i].rt = 0.f;
				}
				else{
					gamepads[i].rt = rt / AVI_MAX_TRIGGER_VALUE;
				};

				XINPUT_VIBRATION vibration;
				vibration.wLeftMotorSpeed = (U32) (gamepads[i].lv * AVI_MAX_VIBRATION);
				vibration.wRightMotorSpeed = (U32) (gamepads[i].rv * AVI_MAX_VIBRATION);
				XInputSetState(i, &vibration);
			}
			else{
				//Controller not available

			}
		}
	}


	B8 DLLEXPORT U(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_U;
	}

	B8 DLLEXPORT D(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_D;
	}

	B8 DLLEXPORT L(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_L;
	}

	B8 DLLEXPORT R(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_R;
	}

	B8 DLLEXPORT START(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_START;
	}

	B8 DLLEXPORT BACK(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_BACK;
	}

	B8 DLLEXPORT LB(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_LB;
	}

	B8 DLLEXPORT RB(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_RB;
	}

	B8 DLLEXPORT L3(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_L3;
	}

	B8 DLLEXPORT R3(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_R3;
	}

	B8 DLLEXPORT A(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_A;
	}

	B8 DLLEXPORT B(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_B;
	}

	B8 DLLEXPORT X(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_X;
	}

	B8 DLLEXPORT Y(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_Y;
	}

	F32 DLLEXPORT LX(U32 controllerIndex){
		return gamepads[controllerIndex].lx;
	}

	F32 DLLEXPORT LY(U32 controllerIndex){
		return gamepads[controllerIndex].ly;
	}

	F32 DLLEXPORT RX(U32 controllerIndex){
		return gamepads[controllerIndex].rx;
	}

	F32 DLLEXPORT RY(U32 controllerIndex){
		return gamepads[controllerIndex].ry;
	}

	F32 DLLEXPORT LT(U32 controllerIndex){
		return gamepads[controllerIndex].lt;
	}

	F32 DLLEXPORT RT(U32 controllerIndex){
		return gamepads[controllerIndex].rt;
	}

	void DLLEXPORT Vibrate(U32 controllerIndex, F32 lmgntd, F32 rmgntd){
		gamepads[controllerIndex].lv = lmgntd;
		gamepads[controllerIndex].rv = rmgntd;
	}

}