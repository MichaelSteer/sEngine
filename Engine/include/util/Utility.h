/*
	Utility.h
	Michael Steer
	2017-08-03
	
	Utility Class that wraps the Classes in the Util directory
	So classes don't have thousands of subclasses 

	UtilitySettings - A struct containing all the parameters that need to 
	be passed to the utility class
*/

#ifndef __UTILITY_H__
#define __UTILITY_H__

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#include "Logger.h"

bool printVersion(std::string _);

struct UtilitySettings {
	LoggerLevels l_LoggerLevels;
	bool l_toFile;
	bool l_toConsole;
};

class Utility : virtual public Logger {
	friend class Singleton<Utility>;
public:
	Utility();
	Utility(UtilitySettings s);
};

#endif // __UTILITY_H__