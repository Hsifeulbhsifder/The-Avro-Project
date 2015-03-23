#include "ARE_stdafx.h"
#include "OpenGL.h"
#include "AvroWindow.h"

B8 DLLEXPORT InitGraphics(Window* window){
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32; //Color depth, either 16 or 32
	pfd.cRedBits = 0;
	pfd.cRedShift = 0;
	pfd.cGreenBits = 0;
	pfd.cGreenShift = 0;
	pfd.cBlueBits = 0;
	pfd.cBlueShift = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumBits = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 16; //Bit depth, for depthbuffer
	pfd.cStencilBits = 0;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.bReserved = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;
	pfd.dwDamageMask = 0;

	I32 format = ChoosePixelFormat(window->deviceContext, &pfd);
	return !SetPixelFormat(window->deviceContext, format, &pfd);
	
}


void DLLEXPORT ClearScreen(F32 r, F32 g, F32 b, F32 a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void DLLEXPORT TerminateGraphics()
{

}
