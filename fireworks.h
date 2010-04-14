// Fireworks.h
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>

#include "resource.h"
#include "cparticlesystem.h"






extern int FireworkCount;

extern CParticleSystem FireworkBang;

bool LoadBitmapTexture(int RES, GLuint &texid);


void InitFireworks();
void RenderFireworks();
void CheckFireworks();
void SetFireworkLit();
void SetFireworkBang();


