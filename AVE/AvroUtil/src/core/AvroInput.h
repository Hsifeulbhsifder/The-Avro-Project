#ifndef AVRO_INPUT_H
#define AVRO_INPUT_H

#include <Avro_typedefs.h>
#include <Avro_Preprocessor.h>

//Initialization of Input
#ifdef A_W32
#include <Xinput.h>

#elif A_UNX

#endif

#define AVI_DPAD_U XINPUT_GAMEPAD_DPAD_UP
#define AVI_DPAD_D XINPUT_GAMEPAD_DPAD_DOWN
#define AVI_DPAD_L XINPUT_GAMEPAD_DPAD_LEFT
#define AVI_DPAD_R XINPUT_GAMEPAD_DPAD_RIGHT
#define AVI_START XINPUT_GAMEPAD_START
#define AVI_BACK XINPUT_GAMEPAD_BACK
#define AVI_LB XINPUT_GAMEPAD_LEFT_SHOULDER
#define AVI_RB XINPUT_GAMEPAD_RIGHT_SHOULDER
#define AVI_L3 XINPUT_GAMEPAD_LEFT_THUMB
#define AVI_R3 XINPUT_GAMEPAD_RIGHT_THUMB
#define AVI_A XINPUT_GAMEPAD_A
#define AVI_B XINPUT_GAMEPAD_B
#define AVI_X XINPUT_GAMEPAD_X
#define AVI_Y XINPUT_GAMEPAD_Y

#define AVI_LINEAR_INPUT 0
#define AVI_SQUARED_INPUT 1
#define AVI_QUARTIC_INPUT 2

#define AVI_MAX_VIBRATION 65535
#define AVI_MAX_STICK_VALUE 32768
#define AVI_MAX_TRIGGER_VALUE 255

#define AVI_NUM_KEYS 256
#define AVI_PREV_KEY_BIT (1 << 1)
#define AVI_KEY_BIT (1 << 15)

struct Controller{
	F32 lx;
	F32 ly;
	F32 rx;
	F32 ry;
	F32 lt;
	F32 rt;
	F32 lv;
	F32 rv;
	U16 buttons;
};
typedef Controller GamePad;

B32 InitInput(U32 numControllers);

//Termination of Input
void TerminateInput();

//Post Initialization of Input and polling

namespace AVI{
	//Update Input
	void Poll();

	//Gamepad
	U16 Buttons(U32 controllerIndex);
	B32 U(U32 controllerIndex);
	B32 D(U32 controllerIndex);
	B32 L(U32 controllerIndex);
	B32 R(U32 controllerIndex);
	B32 START(U32 controllerIndex);
	B32 BACK(U32 controllerIndex);
	B32 LB(U32 controllerIndex);
	B32 RB(U32 controllerIndex);
	B32 L3(U32 controllerIndex);
	B32 R3(U32 controllerIndex);
	B32 A(U32 controllerIndex);
	B32 B(U32 controllerIndex);
	B32 X(U32 controllerIndex);
	B32 Y(U32 controllerIndex);

	F32 LX(U32 controllerIndex);
	F32 LY(U32 controllerIndex);
	F32 RX(U32 controllerIndex);
	F32 RY(U32 controllerIndex);
	F32 LT(U32 controllerIndex);
	F32 RT(U32 controllerIndex);

	void Vibrate(U32 controllerIndex, F32 lmgntd, F32 rmgntd);
	void SetInputType(U32 _inputType);

	void SetStickDeadzone(F32 stickDeadzone);
	void SetTriggerDeadzone(F32 triggerDeadzone);
	F32 GetStickDeadzone();
	F32 GetTriggerDeadzone();

	B32 GamePadIsActive(U32 controllerIndex);

	//Keyboard

#ifdef A_W32
	INLINEFORCE U8 GetKey(U32 vkCode){
		return (GetAsyncKeyState(vkCode) & AVI_KEY_BIT) != 0;
	}

#elif A_UNX

	INLINEFORCE B32 GetKey(U32 vkCode){ return false; }

#endif

	B32 GetKeyTapped(U32 vkCode);
	B32 GetKeyReleased(U32 vkCode);

}

#endif