/*
	timing.h
	Michael Steer
	2017-11-20
	
	Timing functionality
*/

#ifndef __TIMING_H__
#define __TIMING_H__

#include <iomanip>
#include <sstream>

// Physically wait for a specified number of milliseconds
void hardSleep(unsigned long milliseconds);

std::string timeString(std::string formatting);

#endif // __TIMING_H__