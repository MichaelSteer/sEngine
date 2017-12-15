/* 
	main.cpp
	Michael Steer
	2017-09-16
*/
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include "application.h"
#include "util\Logger.h"
#include "system\window.h"
#include "misc\splash.h"
#include <array>
#include <iostream>

#include <windows.h>


using namespace std;

#if defined(_WIN32) || (_WIN64)
#include "system\OS\winapi.h"

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow) {
	

	int argc = __argc;
	char** argv = __argv;
	InitConsole();
	splash();

	Application app(argc, argv);

	app.init(hInstance);
	app.run();
	app.hold();
	return app.exit();
	
}
#else
int main(int argc, char** argv) {

	Application app(argc, argv);

	app.init();
	app.run();

	app.hold();
	return app.exit();
	Sleep(100000);
	return 0;
}
#endif