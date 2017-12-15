/*
	basestate.cpp
	Michael Steer
	2017-09-16

	Base State class for state machine
*/

#include <iostream>
#include "state\basestate.h"

using std::cout;
using std::endl;

/*
	State creation
*/
State::State() {
	log << "Creating Base State" << endl;
}

/*
	State Deletion
*/
State::~State() {
	log << "Destroying Base State" << endl;
}


// init
void State::init() {}

// delete
void State::end() {}

// update
void State::events() {}

// process state
void State::logic() {}

// Render state
void State::render() {}