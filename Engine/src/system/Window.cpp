/*
	window.cpp
	Michael Steer
	2017-12-01

	Window class
*/

#define GLEW_STATIC
#define _CRT_SECURE_NO_DEPRECATE

#include "system\window.h" 
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GL/GL.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_SIZE: {
			//resize
			break;
		}
		case WM_DESTROY: {
			// exit
			PostQuitMessage(0);
			break;
		}
		default : {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}

Window::Window(HINSTANCE hInstance, const unsigned int width, const unsigned int height, std::string name)
	: hInstance(hInstance), width(width), height(height), name(name) {
	if (!createWindow(width, height, name)) {
		log << "Error opening window." << endl;
		exit(0);
	}
}

bool Window::createWindow(unsigned int width, unsigned int height, std::string name) {
#if defined(_WIN32) || (_WIN64)
	WNDCLASS windowClass;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	hInstance = GetModuleHandle(NULL);

	windowClass.style		  = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc   = WndProc;
	windowClass.cbClsExtra    = 0;
	windowClass.cbWndExtra    = 0;
	windowClass.hInstance     = hInstance;
	windowClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName  = NULL;
	windowClass.lpszClassName = (LPCSTR)name.c_str();

	if (!RegisterClass(&windowClass)) {
		log << "Error: Could not initialize window handle" << endl;
		return false;
	}

	hWND = CreateWindowEx(dwExStyle, 
						  (LPCSTR)name.c_str(),
						  (LPCSTR)name.c_str(),
						  WS_OVERLAPPEDWINDOW, 
						  CW_USEDEFAULT, 
						  0, 
						  width, 
						  height, 
						  NULL, 
						  NULL, 
						  hInstance, 
						  NULL);

	log << hWND << endl;
	hDC = GetDC(hWND);
	if (!setPFD()) {
		log << "Error setting PFD and initializing window" << endl;
		return false;
	}
	if (!createOpenGLInstance()) {
		log << "Error setting up openGL window" << endl;
		return false;
	}

	ShowWindow(hWND, SW_SHOW);
	UpdateWindow(hWND);
	return true;
#else 
	// ...
#endif
}

bool Window::destroyWindow() {
#if defined(_WIN32) || (_WIN64)
	wglMakeCurrent(hDC, 0);
	wglDeleteContext(hRC);
	ReleaseDC(hWND, hDC);
	return true;
#else 
	// ...
#endif
}

#if defined(_WIN32) || (_WIN64)
bool Window::setPFD() {
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER
				| PFD_SUPPORT_OPENGL
				| PFD_DRAW_TO_WINDOW;

	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	BOOL PixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (PixelFormat == FALSE) {
		log << "Error: Invalid Pixel format: " << PixelFormat << endl;
		return false;
	}

	BOOL out = SetPixelFormat(hDC, PixelFormat, &pfd);
	if (out == FALSE) {
		log << "Error: Could not set pixel format: " << PixelFormat << endl;
		return false;
	}
	return true;
}
#endif

bool Window::createOpenGLInstance() {
#if defined(_WIN32) || (_WIN64)
	HGLRC t_hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, t_hRC);	GLenum err = glewInit();	if (GLEW_OK != err) {
		log << "Error: Could not enable GLEW: " << err << endl;
		return false;
	}

	int GLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0 };

	if (wglewIsSupported("WGL_ARB_create_context")) {
		hRC = wglCreateContextAttribsARB(hDC, NULL, GLAttributes);

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(t_hRC);
		wglMakeCurrent(hDC, hRC);
	}
	else {
		hRC = t_hRC;
	}
	return true;
#else 
	// ...
#endif
}