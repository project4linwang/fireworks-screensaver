// fireworks.cpp
#include "fireworks.h"


CParticleSystem FireworkBang;

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
     
     FireworkBang.minparticlespeed = -0.05f;
     FireworkBang.maxparticlespeed = 0.05f;
     FireworkBang.settsx = 0.0f;
     FireworkBang.settsy = -0.002f;
     FireworkBang.settsz = 0.0f;
     
     FireworkBang.setsize = 0.2f;
     
     FireworkBang.RED   = 1.0f;
     FireworkBang.GREEN = 0.0f;
     FireworkBang.BLUE  = 0.0f;
     
     FireworkBang.RANDOMCOLOUR = true;
     
}



void RenderFireworks(){
     
     if(!FireworkBang.ACTIVE){FireworkBang.Activate(0.0f, 0.0f, -5.0f, 100, 20, 40);}
     
     FireworkBang.Render();
          
}



