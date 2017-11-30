/*
	basestate.h
	Michael Steer
	2017-09-16
	
	Base state for state machine
*/
#ifndef	BASESTATE_H
#define BASESTATE_H

#include <iostream>
#include "util/Utility.h"
class State : virtual public Utility {
public:
	State();
	~State();

	virtual void init();
	virtual void end();

	virtual void update();
	virtual void process();
	virtual void post();
};

#endif // BASESTATE_H
