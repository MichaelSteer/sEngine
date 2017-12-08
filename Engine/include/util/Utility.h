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

#include "Logger.h"

// UtilitySetting structure
struct UtilitySettings {
	LoggerLevels l_LoggerLevels;
	bool l_toFile;
	bool l_toConsole;
};

// Utility Structure
class Utility : virtual public Logger {
	friend class Singleton<Utility>;
public:
	Utility();
	Utility(UtilitySettings s);
};

#endif // __UTILITY_H__