/*
	timer.cpp
	Michael Steer
	2017-11-20

	Timing functionality
*/

#include "system/timer.h"
#include <algorithm>

// create timer
Timer::Timer()
	: started(false) {}

// Start the timer
void Timer::start() {
	started = true;
	_start = clock::now();
}

// Stop the timer
void Timer::stop() {
	if (started) {
		started = false;
		_stop = clock::now();
	}
}


// Get the elapsed time in milliseconds
unsigned long long Timer::getElapsedTime() {
	if (started) {
		if (paused) return std::chrono::duration_cast<ms>(_paused - _start).count();
		else	    return std::chrono::duration_cast<ms>(clock::now() - _start).count();
	}
	else {
		return std::chrono::duration_cast<ms>(_start - _stop).count();
	}
}

// get the period the timer has elapsed in double floating point
double Timer::getPeriod() {
	return std::min((double)getElapsedTime(), (double)1000.0f);
}

// get the frequency of the timers stop/start periods
double Timer::getFrequency() {
	return (1.0f / getPeriod()) * 1000.0f;
}

// pause the timer
void Timer::pause() {
	if (started) {
		if (paused) {
			paused = true;
			_paused = clock::now();
		}
	}
}

// restart the timer
void Timer::unpause() {
	if (paused) {
		paused = false;
		_start = time(std::chrono::duration_cast<ms>(clock::now() - _paused));
	}
}

// reset the timer
void Timer::reset() {
	start();
	paused = false;
}