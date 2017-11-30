/*
	OS.h
	Michael Steer

	2017-11-27

	Various Operating System
	specific macros and functions
*/

#ifndef __OS_H__
#define __OS_H__

#include <string>


std::string getMemUsage();

std::string getCpuUsgae();

std::string getWindowsOSVersion();

inline std::string getOsDistro() {
	#ifdef _WIN32
		return "Windows 32-bit";
	#elif _WIN64
		return "Windows 64-bit";
	#elif __unix || __unix__
		return "Unix";
	#elif __APPLE__ || __MACH__
		return "Mac OSX";
	#elif __linux__
		return "Linux";
	#elif __FreeBSD__
		return "FreeBSD";
	#else
		return "Other";
	#endif
}


#endif // _OS_H__

