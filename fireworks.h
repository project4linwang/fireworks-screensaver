// Fireworks.h
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>

#include "resource.h"

#define MAX_FIREWORKS 3
#define MAX_BANGPARTICLES 100

extern GLuint txSparkle;

struct PARTICLE {
       
    float x,y,z;
    float sx,sy,sz;
    float tsx,tsy,tsz;
    float R,G,B;
    int TTL;       
       
};

extern PARTICLE BangParticles[MAX_BANGPARTICLES][MAX_FIREWORKS];

extern int FireworkCount;

bool LoadBitmapTexture(int RES, GLuint &texid);
void InitFireworks();
void RenderFireworks();
void CreateNewBang();
