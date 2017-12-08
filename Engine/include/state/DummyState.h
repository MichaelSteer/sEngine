/* 
	DummyState.h
	Michael Steer
	2017-09-16
	
	Test State
*/

#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H
#include <iostream>
#include "basestate.h"
class DummyState : public State {
public:
	DummyState();
	~DummyState();

	void init()    override;
	void end()     override;
	void update()  override;
	void process() override;
	void post()    override;
};

#endif // DUMMYSTATE_H