// fireworks.cpp
#include "fireworks.h"


CParticleSystem FireworkBang;
CParticleSystem FireworkFuse;

int FireworkCount = 0;



bool LoadBitmapTexture(int RES, GLuint &texid)					// Creates Texture From A Bitmap File
{
	HBITMAP hBMP;														// Handle Of The Bitmap
	BITMAP	BMP;														// Bitmap Structure

	glGenTextures(1, &texid);   // Create The Texture

	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(RES), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );

	if (!hBMP)	return FALSE;														// Does The Bitmap Exist?

	GetObject(hBMP, sizeof(BMP), &BMP);									// Get The Object
																		// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);								// Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);													// Delete The Object
	return TRUE;														// Loading Was Successful
}




void InitFireworks(){
     
     LoadBitmapTexture(IDB_SPARKLE, FireworkBang.texture);     
     FireworkFuse.texture = FireworkBang.texture;
 
     FireworkFuse.x = 0.0f;
     FireworkFuse.y = 0.0f;
     FireworkFuse.z = 0.0f;
     
     FireworkFuse.sx = 0.0f;
     FireworkFuse.sy = 0.0f;
     FireworkFuse.sz = 0.0f;
     
     FireworkFuse.tsx = 0.0f;
     FireworkFuse.tsy = 0.0f;
     FireworkFuse.tsz = 0.0f;
     
     FireworkFuse.minparticlespeedx = -0.02f;
     FireworkFuse.maxparticlespeedx =  0.02f;
     FireworkFuse.minparticlespeedy =  0.00f;
     FireworkFuse.maxparticlespeedy =  0.05f;
     FireworkFuse.minparticlespeedz = -0.02f;
     FireworkFuse.maxparticlespeedz =  0.02f;

     FireworkFuse.NORMALIZE = false;
     FireworkFuse.NormalizedSpeedFactor = 0.1f;
     
     FireworkFuse.settsx = 0.0f;
     FireworkFuse.settsy = -0.02f;
     FireworkFuse.settsz = 0.0f;
     
     FireworkFuse.setsize = 0.05f;
     
     FireworkFuse.RED   = 1.0f;
     FireworkFuse.GREEN = 1.0f;
     FireworkFuse.BLUE  = 0.8f;
     
     FireworkFuse.RANDOMCOLOUR = false;
     FireworkFuse.CONTINUOUS = true;
     
     FireworkFuse.ParticleCount = 1000;
     FireworkFuse.ActivateCountPerFrame = 10;
     
     FireworkFuse.minTTL = 10;
     FireworkFuse.maxTTL = 30;
     
     FireworkFuse.Activate();
 
     
}



void RenderFireworks(){
     
     glTranslatef(0.0f, -3.5f, -10.0f);
     
     CheckFireworks();

     FireworkFuse.Render();
     
     FireworkBang.Render();

          
}


void CheckFireworks(){
     
     if(!FireworkBang.ACTIVE){SetFireworkLit();}
     
     if(FireworkBang.y > 6.0f && FireworkBang.CONTINUOUS){SetFireworkBang();}  
}

void SetFireworkLit(){
     
     FireworkBang.x = 0.0f;
     FireworkBang.y = 0.0f;
     FireworkBang.z = 0.0f;
     
     FireworkBang.sx = 0.0f;
     FireworkBang.sy = 0.0f;
     FireworkBang.sz = 0.0f;
     
     FireworkBang.tsx = FireworkBang.CParticleSystem::RandomFloat(-0.4f, 0.4f, 100);
     FireworkBang.tsy = 0.6f;
     FireworkBang.tsz = 0.0f;
     
     FireworkBang.minparticlespeedx =  -0.01f - (FireworkBang.tsx / 10.0f);
     FireworkBang.maxparticlespeedx =  0.01f - (FireworkBang.tsx / 10.0f);
     FireworkBang.minparticlespeedy = -0.02f;
     FireworkBang.maxparticlespeedy = -0.05f;
     FireworkBang.minparticlespeedz =  0.02f;
     FireworkBang.maxparticlespeedz = -0.02f;

     FireworkBang.NORMALIZE = false;
     FireworkBang.NormalizedSpeedFactor = 0.1f;
     
     FireworkBang.settsx = 0.0f;
     FireworkBang.settsy = -0.02f;
     FireworkBang.settsz = 0.0f;
     
     FireworkBang.setsize = 0.05f;
     
     FireworkBang.RED   = 1.0f;
     FireworkBang.GREEN = 1.0f;
     FireworkBang.BLUE  = 0.8f;
     
     FireworkBang.RANDOMCOLOUR = false;
     FireworkBang.CONTINUOUS = true;
     
     FireworkBang.ParticleCount = 1000;
     FireworkBang.ActivateCountPerFrame = 10;
     
     FireworkBang.minTTL = 10;
     FireworkBang.maxTTL = 30;
     
     FireworkBang.Activate();
}

void SetFireworkBang(){
     
//     FireworkBang.x = 0.0f;
//     FireworkBang.y = 0.0f;
//     FireworkBang.z = 0.0f;
     
     FireworkBang.sx = 0.0f;
     FireworkBang.sy = 0.0f;
     FireworkBang.sz = 0.0f;
     
     FireworkBang.tsx = 0.0f;
     FireworkBang.tsy = -0.02f;
     FireworkBang.tsz = 0.0f;
     
     FireworkBang.minparticlespeedx = -0.09f;
     FireworkBang.maxparticlespeedx =  0.09f;
     FireworkBang.minparticlespeedy = -0.09f;
     FireworkBang.maxparticlespeedy =  0.09f;
     FireworkBang.minparticlespeedz = -0.09f;
     FireworkBang.maxparticlespeedz =  0.09f;
     
     FireworkBang.NORMALIZE = true;
     FireworkBang.NormalizedSpeedFactor = 0.1f;
     
     FireworkBang.settsx = 0.0f;
     FireworkBang.settsy = -0.02f;
     FireworkBang.settsz = 0.0f;
     
     FireworkBang.setsize = 0.15f;
     
     FireworkBang.RED   = FireworkBang.CParticleSystem::RandomFloat(0.7f, 1.0f, 30);
     FireworkBang.GREEN = FireworkBang.CParticleSystem::RandomFloat(0.7f, 1.0f, 30);
     FireworkBang.BLUE  = FireworkBang.CParticleSystem::RandomFloat(0.7f, 1.0f, 30);
     
     FireworkBang.RANDOMCOLOUR = false;
     FireworkBang.CONTINUOUS = false;
     
     FireworkBang.ParticleCount = 1000;
     FireworkBang.ActivateCountPerFrame = 1;
     
     FireworkBang.minTTL = 30;
     FireworkBang.maxTTL = 60;
    
     FireworkBang.CParticleSystem::Activate();
}
