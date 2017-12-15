/*
Application.h
Michael Steer
2017-09-16

Program Application
*/

#include <iostream>
#include "application.h"
#include "util\ArgFactory.h"
#include "state\DummyState.h"

using std::cout;
using std::cin;
using std::endl;

// Constructor
Application::Application(int argc, char **argv) {
	log << "Creating Application" << endl;
	//parseArgs(argc, argv);
}

// Destructor
Application::~Application() {
	log << "Unloading Application" << endl;
}

// parse input arguments
bool Application::parseArgs(char argc, char** argv) {

	ArgParser &parser = Singleton<ArgParser, int, char**>::getInstance(argc, argv);
	Singleton<ArgFactory, ArgParser>::getInstance(parser);
	parser.parse();
	log << "Parsing application arguments" << endl;
	return true;
}

// Initialize the application
bool Application::init(HINSTANCE hInstance) {
	log << "Initializing Applicaiton" << endl;
	log << "Pushing initial state" << endl;
	AppRunning = true;

	hardwareManager = new HardwareManager();
	windowManager = new Window(hInstance, 1000, 1000, "test");
	
	std::unique_ptr<DummyState> s;

	states.push(std::make_unique<DummyState>());

	incrementTimer.start();
	frameCounter = 0;
	FramesPerSecond = 60.0f;
	return true;
}

bool Application::systemEvents() {
#if defined(_WIN32) || defined(_WIN64)
	// Windows events
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return true;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return false;
#elif
	// Unix Events
#endif
}

void Application::statistics() {
	hardwareManager->poll();
	hardwareManager->print();
	incrementTimer.reset();
	log << "FPS: "
		<< frameCounter
		<< endl;
}

// start the application
bool Application::start() {
	while (loop()) {
	}
	return true;
}

bool Application::loop() {

	// Timing and resource analysis once per second
	if (incrementTimer.getElapsedTime() > 1000) {
		statistics();
		frameCounter = 0;
	}

	// Events
	if (systemEvents()) {
		return false;
	}

	// State events
	states.top()->events();

	// State Logic
	states.top()->logic();
	
	// State render
	states.top()->render();

	// Post logic
	frameCounter++;
	return true;

}

// run the applicaiton
bool Application::run() {
	log << "Starting Application" << endl;
	start();
	return true;
}

// pause the application
bool Application::hold() {
	log << "Exit prompt requested." << endl;
	return true;
}

// exit the application

int Application::exit() {
	states.top()->end();
	windowManager->destroyWindow();
	system("PAUSE");
	return 0;
}

