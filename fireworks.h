// Fireworks.h
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>

#include "resource.h"


extern GLuint txSparkle;


bool LoadBitmapTexture(int RES, GLuint &texid);


void InitFireworks();

void RenderFireworks();

