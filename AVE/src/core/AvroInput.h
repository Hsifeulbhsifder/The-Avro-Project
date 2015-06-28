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

#define AVI_MAX_VIBRATION 65535
#define AVI_MAX_STICK_VALUE 32768
#define AVI_MAX_TRIGGER_VALUE 255

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

B8 DLLEXPORT InitInput(U32 numControllers);

//Post Initialization of Input and polling

namespace GPD{
	void DLLEXPORT Poll();

	B8 DLLEXPORT U(U32 controllerIndex);
	B8 DLLEXPORT D(U32 controllerIndex);
	B8 DLLEXPORT L(U32 controllerIndex);
	B8 DLLEXPORT R(U32 controllerIndex);
	B8 DLLEXPORT START(U32 controllerIndex);
	B8 DLLEXPORT BACK(U32 controllerIndex);
	B8 DLLEXPORT LB(U32 controllerIndex);
	B8 DLLEXPORT RB(U32 controllerIndex);
	B8 DLLEXPORT L3(U32 controllerIndex);
	B8 DLLEXPORT R3(U32 controllerIndex);
	B8 DLLEXPORT A(U32 controllerIndex);
	B8 DLLEXPORT B(U32 controllerIndex);
	B8 DLLEXPORT X(U32 controllerIndex);
	B8 DLLEXPORT Y(U32 controllerIndex);

	F32 DLLEXPORT LX(U32 controllerIndex);
	F32 DLLEXPORT LY(U32 controllerIndex);
	F32 DLLEXPORT RX(U32 controllerIndex);
	F32 DLLEXPORT RY(U32 controllerIndex);
	F32 DLLEXPORT LT(U32 controllerIndex);
	F32 DLLEXPORT RT(U32 controllerIndex);

	void DLLEXPORT Vibrate(U32 controllerIndex, F32 lmgntd, F32 rmgntd);

}



#endif