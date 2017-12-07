/*
	timing.cpp.h
	Michael Steer
	2017-11-20

	Timing functionality
*/

#include <chrono>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "system\timing.h"

// stop the process for a number of milliseconds
void hardSleep(unsigned long milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds);
#else 
	usleep(milliseconds * 1000);
#endif
}

// turn the current time into a GMT formatted string
std::string timeString(std::string formatting) {
	time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm _tm;
	std::stringstream o;
	localtime_s(&_tm, &t);
	if (_tm.tm_year) {
		o << std::put_time(&_tm, formatting.c_str());
		return o.str();
	}
}