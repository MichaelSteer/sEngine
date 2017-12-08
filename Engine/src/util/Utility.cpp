/*
	Utility.h
	Michael Steer
	2017-08-03

	Utility Class that wraps the Classes in the Util directory
	So classes don't have thousands of subclasses
*/

#include "util/Utility.h"

// Constructor
Utility::Utility() {}

// Parameterized Constructor
Utility::Utility(UtilitySettings s)
	: Logger(s.l_LoggerLevels, s.l_toFile, s.l_toConsole) {}