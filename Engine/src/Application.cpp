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
bool Application::init() {
	log << "Initializing Applicaiton" << endl;
	log << "Pushing initial state" << endl;

	AppRunning = true;

	std::unique_ptr<DummyState> s;

	states.push(std::make_unique<DummyState>());

	incrementTimer.start();
	frameCounter = 0;
	FramesPerSecond = 60.0f;
	frameTimer.start();
	return true;
}


// start the application
bool Application::start() {
	while (AppRunning) {
		frameTimer.reset();
		
		if (incrementTimer.getElapsedTime() > 1000) {
			incrementTimer.reset();
			hardSleep(1);
			log << "FPS: " 
				<< frameTimer.getFrequency()
				<< endl;
			frameTimer.reset();
		}
	}
	return true;
}

// run the applicaiton
bool Application::run() {
	log << "Starting Application" << endl;
	this->start();
	return true;
}

// pause the application
bool Application::hold() {
	log << "holding..." << endl;
	bool dummy;
	cin >> dummy;
	return true;
}

// exit the application

int Application::exit() {
	return 0;
}

