#include <windows.h>
#include <scrnsave.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <time.h>


bool SetupOpenGL();
void KillGL();

void DrawGLScene();



HDC					hDC=NULL;
HGLRC				hRC=NULL;
HWND				hWnd=NULL;
HINSTANCE			hInstance;


int uTimer;



LONG WINAPI ScreenSaverProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
    // Handles screen saver messages
    switch(message)
    {
    case WM_CREATE:
        // Creation of the screen saver window
		hWnd = hwnd;
		SetupOpenGL();
		// Set Timer (Target 60 fps ish (1000/60 = 16)
		uTimer = SetTimer(hwnd, 1, 16, NULL); 
        return 0;
        
    case WM_ERASEBKGND:
        // Erases the screen saver background
		// Not needed with OpenGL
        return 0;
        
        
    case WM_TIMER:
        // Handles the timer
		DrawGLScene();
        return 0;
        
        
    case WM_DESTROY:
        // Cleans up the screen saver window
		KillTimer(hwnd, uTimer);
		KillGL();
        PostQuitMessage(0);
        return 0;
    }
    return DefScreenSaverProc(hwnd,message,wparam,lparam);
}



BOOL WINAPI ScreenSaverConfigureDialog(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
    return true;
}


BOOL WINAPI RegisterDialogClasses(HANDLE hmodule)
{
    return true;
}



bool SetupOpenGL()
{


	GLuint PixelFormat;			// Holds The Results After Searching For A Match

	int width;
	int height;

	width = GetDeviceCaps(GetDC(NULL), HORZRES);	// GetDC(NULL) returns a
	height = GetDeviceCaps(GetDC(NULL), VERTRES);	// HDC for the whole screen

	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,											// Select Our Color Depth (bits)
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGL();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGL();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGL();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGL();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGL();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}




	// Set Up Our Perspective GL Screen
	if (height==0){height=1;}
	glViewport(0,0,width,height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);


	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix



	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	return TRUE;									// Success
}





void KillGL(GLvoid){
	ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
	if (hRC){										// Do We Have A Rendering Context?
		wglMakeCurrent(NULL,NULL);					// Release The DC And RC Contexts
		wglDeleteContext(hRC);						// Delete The RC
		hRC=NULL;									// Set RC To NULL
	}
	ReleaseDC(hWnd,hDC);							// Release The DC
}







void DrawGLScene(){


	// First we clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Then we reset the modelview matrix
	glLoadIdentity();






	SwapBuffers(hDC);

}

