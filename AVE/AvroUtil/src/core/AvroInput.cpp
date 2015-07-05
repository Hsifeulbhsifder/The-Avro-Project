#include "AU_stdafx.h"
#include <AvroInput.h>
#include <AvroAllocator.h>
#include <AvroUtil.h>
#include <AvroMath.h>

glob U32 numControllers; 

glob GamePad* gamepads;
glob U8* prevKeys;

glob U32 inputType = AVI_LINEAR_INPUT; //Flag for squaring inputs 
glob F32 STICK_DEADZONE = 8269; //Average of two recommended values on MSDN
glob U32 STICK_DEADZONE2 = 68376361; //Square of the average of two recommended values on MSDN
glob F32 TRIGGER_DEADZONE = 30; //Recommendation from MSDN

#ifdef A_W32

//Supports XInputGetState and XInputSetState without requiring XInput
#define XINPUT_GET_STATE(name) U32 WINAPI name(U32 userIndex, XINPUT_STATE* state)
#define XINPUT_SET_STATE(name) U32 WINAPI name(U32 userIndex, XINPUT_VIBRATION* vibration)
typedef XINPUT_GET_STATE(XINPUT_GET_STATE_FUNC_TYPE);
typedef XINPUT_SET_STATE(XINPUT_SET_STATE_FUNC_TYPE);

XINPUT_GET_STATE(XInputGetStateStub){
	return ERROR_DEVICE_NOT_CONNECTED;
}

XINPUT_SET_STATE(XInputSetStateStub){
	return ERROR_DEVICE_NOT_CONNECTED;
}
glob XINPUT_GET_STATE_FUNC_TYPE* XInputGetState_ = XInputGetStateStub;
glob XINPUT_SET_STATE_FUNC_TYPE* XInputSetState_ = XInputSetStateStub;
#define XInputGetState XInputGetState_
#define XInputSetState XInputSetState_

INLINEFORCE B8 Win32LoadXInput(){
	HMODULE xInputLib = LoadLib("xinput1_4.dll");
	if (!xInputLib)	{
		// TODO(casey): Diagnostic
		xInputLib = LoadLibraryA("xinput9_1_0.dll");
	}

	if (!xInputLib)	{
		// TODO(casey): Diagnostic
		xInputLib = LoadLibraryA("xinput1_3.dll");
	}

	if (xInputLib){
		XInputGetState = (XINPUT_GET_STATE_FUNC_TYPE*)
						GetProcAddress(xInputLib, "XInputGetState");
		XInputSetState = (XINPUT_SET_STATE_FUNC_TYPE*)
						GetProcAddress(xInputLib, "XInputSetState");
		return true;
	}
	else{
		return false;
	}
}
#elif A_UNX

#endif

//TODO: Support lack of gamepads
B8 InitInput(U32 _numControllers){

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
	prevKeys = (U8*)AVRO_DEFAULT_ALLOCATOR.Allocate(AVI_NUM_KEYS);
	return true;
}

void TerminateInput(){
	AVRO_DEFAULT_ALLOCATOR.Dissipate(gamepads);
	AVRO_DEFAULT_ALLOCATOR.Dissipate(prevKeys);
}


namespace AVI{



	B8 U(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_U;
	}

	B8 D(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_D;
	}

	B8 L(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_L;
	}

	B8 R(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_DPAD_R;
	}

	B8 START(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_START;
	}

	B8 BACK(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_BACK;
	}

	B8 LB(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_LB;
	}

	B8 RB(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_RB;
	}

	B8 L3(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_L3;
	}

	B8 R3(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_R3;
	}

	B8 A(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_A;
	}

	B8 B(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_B;
	}

	B8 X(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_X;
	}

	B8 Y(U32 controllerIndex){
		return gamepads[controllerIndex].buttons & AVI_Y;
	}

	F32 LX(U32 controllerIndex){
		return gamepads[controllerIndex].lx;
	}

	F32 LY(U32 controllerIndex){
		return gamepads[controllerIndex].ly;
	}

	F32 RX(U32 controllerIndex){
		return gamepads[controllerIndex].rx;
	}

	F32 RY(U32 controllerIndex){
		return gamepads[controllerIndex].ry;
	}

	F32 LT(U32 controllerIndex){
		return gamepads[controllerIndex].lt;
	}

	F32 RT(U32 controllerIndex){
		return gamepads[controllerIndex].rt;
	}

	void Vibrate(U32 controllerIndex, F32 lmgntd, F32 rmgntd){
		gamepads[controllerIndex].lv = lmgntd;
		gamepads[controllerIndex].rv = rmgntd;
	}

	void SetInputType(U32 _inputType){
		inputType = _inputType;
	}

	void SetStickDeadzone(F32 stickDeadzone){
		STICK_DEADZONE = (stickDeadzone * AVI_MAX_STICK_VALUE);
		STICK_DEADZONE2 = (U32) AU::Sq(STICK_DEADZONE);
	}

	void SetTriggerDeadzone(F32 triggerDeadzone){
		TRIGGER_DEADZONE = (triggerDeadzone * AVI_MAX_TRIGGER_VALUE);
	}

	F32 GetStickDeadzone(){
		return STICK_DEADZONE / AVI_MAX_STICK_VALUE;
	}

	F32 GetTriggerDeadzone(){
		return TRIGGER_DEADZONE / AVI_MAX_TRIGGER_VALUE;
	}
	
	B8 GamePadIsActive(U32 controllerIndex){
		lscope XINPUT_STATE controllerState;
		return (XInputGetState(controllerIndex, &controllerState) == ERROR_SUCCESS);
	}

	B8 GetKeyTapped(U32 vkCode){
		return GetKey(vkCode) && !prevKeys[vkCode];
	}

	B8 GetKeyReleased(U32 vkCode){
		return !GetKey(vkCode) && prevKeys[vkCode];
	}

	void Poll(){
		//Poll keyboard
		for (U32 i = 0; i < AVI_NUM_KEYS; i++){
			prevKeys[i] = GetKey(i);
		}


		//TODO: Check only plugged in controllers and optimize
		//Poll gamepads and controllers
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
				} else{
					F32 lmgntd = AU::Sqrt((F32)lmgntd2);
					F32 nlxFactor = lx / lmgntd;
					F32 nlyFactor = ly / lmgntd;
					if (lmgntd > AVI_MAX_STICK_VALUE) lmgntd = AVI_MAX_STICK_VALUE;
					lmgntd -= STICK_DEADZONE;
					lx = nlxFactor * lmgntd;
					ly = nlyFactor * lmgntd;
					if (inputType == AVI_LINEAR_INPUT){
						gamepads[i].lx = lx / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nlxFactor * AU::Sgn(lx));
						gamepads[i].ly = ly / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nlyFactor * AU::Sgn(ly));
					} else if(inputType == AVI_SQUARED_INPUT){
						gamepads[i].lx = AU::Sq(lx / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nlxFactor * AU::Sgn(lx)));
						gamepads[i].ly = AU::Sq(ly / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nlyFactor * AU::Sgn(ly)));
					} else if (inputType == AVI_QUARTIC_INPUT){
						gamepads[i].lx = AU::Quart(lx / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nlxFactor * AU::Sgn(lx)));
						gamepads[i].ly = AU::Quart(ly / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nlyFactor * AU::Sgn(ly)));
					}
				}

				//Circular deadzone processing of right joystick
				F32 rx = (&controllerState.Gamepad)->sThumbRX;
				F32 ry = (&controllerState.Gamepad)->sThumbRY;
				U32 rmgntd2 = (U32)(rx*rx + ry*ry);
				if (rmgntd2 < STICK_DEADZONE2){
					gamepads[i].rx = 0.f;
					gamepads[i].ry = 0.f;
				} else{
					F32 rmgntd = AU::Sqrt((F32)rmgntd2);
					F32 nrxFactor = rx / rmgntd;
					F32 nryFactor = ry / rmgntd;
					if (rmgntd > AVI_MAX_STICK_VALUE) rmgntd = AVI_MAX_STICK_VALUE;
					rmgntd -= STICK_DEADZONE;
					rx = nrxFactor * rmgntd;
					ry = nryFactor * rmgntd;
					if (inputType == AVI_LINEAR_INPUT){
						gamepads[i].rx = rx / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nrxFactor * AU::Sgn(rx));
						gamepads[i].ry = ry / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nryFactor * AU::Sgn(ry));
					} else if (inputType == AVI_SQUARED_INPUT){
						gamepads[i].rx = AU::Sq(rx / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nrxFactor * AU::Sgn(rx)));
						gamepads[i].ry = AU::Sq(ry / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nryFactor * AU::Sgn(ry)));
					} else if (inputType == AVI_QUARTIC_INPUT){
						gamepads[i].rx = AU::Quart(rx / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nrxFactor * AU::Sgn(rx)));
						gamepads[i].ry = AU::Quart(ry / (AVI_MAX_STICK_VALUE -
							STICK_DEADZONE * nryFactor * AU::Sgn(ry)));
					}
				}

				//Linear deadzone processing of left trigger
				F32 lt = (&controllerState.Gamepad)->bLeftTrigger;
				if (lt < TRIGGER_DEADZONE){
					gamepads[i].lt = 0.f;
				} else{
					if (inputType == AVI_LINEAR_INPUT){
						gamepads[i].lt = lt / AVI_MAX_TRIGGER_VALUE;
					} else if (inputType == AVI_SQUARED_INPUT){
						gamepads[i].lt = AU::Sq(lt / AVI_MAX_TRIGGER_VALUE);
					} else if (inputType == AVI_QUARTIC_INPUT){
						gamepads[i].lt = AU::Quart(lt / AVI_MAX_TRIGGER_VALUE);
					}
				}

				//Linear deadzone processing of right trigger
				F32 rt = (&controllerState.Gamepad)->bRightTrigger;
				if (rt < TRIGGER_DEADZONE){
					gamepads[i].rt = 0.f;
				} else{
					if (inputType == AVI_LINEAR_INPUT){
						gamepads[i].rt = rt / AVI_MAX_TRIGGER_VALUE;
					} else if (inputType == AVI_SQUARED_INPUT){
						gamepads[i].rt = AU::Sq(rt / AVI_MAX_TRIGGER_VALUE);
					} else if (inputType == AVI_QUARTIC_INPUT){
						gamepads[i].rt = AU::Quart(rt / AVI_MAX_TRIGGER_VALUE);
					}
				}

				XINPUT_VIBRATION vibration;
				vibration.wLeftMotorSpeed = (U32)(gamepads[i].lv * AVI_MAX_VIBRATION);
				vibration.wRightMotorSpeed = (U32)(gamepads[i].rv * AVI_MAX_VIBRATION);
				XInputSetState(i, &vibration);
			} else{
				//Controller not available

			}
		}
	}
}