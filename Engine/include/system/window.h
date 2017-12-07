/*
	window.h
	Michael Steer
	2017-12-01
	
	Window class
*/

#ifndef __WINDOW_H__
#define __WINDOW_H__

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <string>
#define _WINDOW
// ...
#else
// ...
#endif

#include "util\Utility.h"


using std::endl;

class Window : public Utility {
private:
	unsigned int width, height;
	std::string name;

#if defined(_WIN32) || defined(_WIN64)
	HGLRC hRC;
	HDC hDC;
	HWND hWND;
	HINSTANCE hInstance;
	PIXELFORMATDESCRIPTOR pfd;

	bool setPFD();
#else
	// ...
#endif
	bool createOpenGLInstance();

public:
	Window(HINSTANCE hInstance, const unsigned int width, const unsigned int height, std::string name);
	
	bool createWindow(unsigned int width, unsigned int height, std::string name);
	bool destroyWindow();
};

#endif // __WINDOW_H__
