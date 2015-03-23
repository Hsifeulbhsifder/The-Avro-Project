#ifndef ARE_OPENGL_RENDERING_H
#define ARE_OPENGL_RENDERING_H

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <avro_typedefs.h>

struct Window;
B8 DLLEXPORT InitGraphics(Window* window);

void DLLEXPORT ClearScreen(F32 r = 0.0f, F32 g = 0.0f, F32 b = 0.0f, F32 a = 0.0f);

void DLLEXPORT TerminateGraphics();

#endif