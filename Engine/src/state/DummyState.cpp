/*
	DummyState.cpp
	Michael Steer
	2017-09-16

	Test State
*/

#include "state\DummyState.h"
using std::cout;
using std::endl;

// constructor
DummyState::DummyState() {
	log << "Creating Dummy State" << endl;
}

// deletion
DummyState::~DummyState() {
	log << "Deleting (~) Dummy State" << endl;
}

// initialization
void DummyState::init() {
	log << "Creating DummyState" << endl;
}

// deletion
void DummyState::end() {
	log << "Deleting (end) DummyState" << endl;
}

// update
void DummyState::update() {
	log << "Updating DummyState" << endl;
}

void DummyState::process() {
	log << "Processing content in DummyState" << endl;
}

void DummyState::post() {
	log << "DummyState Post Processing" << endl;
}
