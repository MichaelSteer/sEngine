/* 
	Application.h
	Michael Steer
	2017-09-16

	Program Application
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <stack>
#include <memory>
#include "util/Utility.h"
#include "state/basestate.h"
#include "system/timer.h"
#include "system/timing.h"

class Application : public Utility {
public:
	Application(int argc, char **argv);
	~Application();
	bool parseArgs(char argc, char**argv);
	bool init();
	bool start();
	bool run();
	bool hold();
	int exit();

private:
	std::stack<std::unique_ptr<State>> states;
	Timer frameTimer, incrementTimer;
	bool AppRunning;
	unsigned short frameCounter;
	float FramesPerSecond;
};

#endif // BASESTATE_H