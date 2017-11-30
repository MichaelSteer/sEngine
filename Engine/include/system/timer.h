/*
	timer.h
	Michael Steer
	2017-11-20
	
	Timer Class
*/
#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
#include <ostream>
#include "../util/Utility.h"

class Timer;

class Timer : public Utility {
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::high_resolution_clock::time_point time;
	typedef std::chrono::milliseconds ms;

private:
	time _start, _paused, _stop;
	bool started, paused;

public:
	Timer();

	void start();
	void stop();
	unsigned long long getElapsedTime();

	double getPeriod();
	double getFrequency();

	void reset();

	void pause();
	void unpause();

	std::string out() {
		return std::to_string(getElapsedTime());
	}

	template<typename T, typename Traits>
	friend std::basic_ostream<T, Traits> &operator<<
		(std::basic_ostream<T, Traits> &out, const Timer &timer) {
		return out << timer.out() << "ms"; }
};

#endif // __TIMER_H__