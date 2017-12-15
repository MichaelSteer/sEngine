/* 
	Application.h
	Michael Steer
	2017-09-16

	Program Application
*/

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Windows.h>

#include <stack>
#include <memory>
#include "util/Utility.h"
#include "state/basestate.h"
#include "system/timer.h"
#include "system/timing.h"
#include "system/OS/HardwareManager.h"
#include "system\window.h"

class Application : public Utility {
public:
	Application(int argc, char **argv);
	~Application();
	bool parseArgs(char argc, char**argv);
	bool init(HINSTANCE hInstance);
	bool systemEvents();
	void statistics();
	bool start();
	bool loop();
	bool run();
	bool hold();
	int exit();

private:
	MSG msg;
	HardwareManager *hardwareManager;
	std::stack<std::unique_ptr<State>> states;
	Timer incrementTimer;


	bool AppRunning;
	unsigned int frameCounter;
	float FramesPerSecond;

	Window *windowManager;
};

#endif // BASESTATE_H