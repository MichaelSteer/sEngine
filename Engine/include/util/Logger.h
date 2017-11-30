/*
	Logger.cpp
	Michael Steer
	2017-08-03

	Logging applicaiton

	LoggerLevels - enumeration for what type of info to log
	LoggerBuffer - String buffer that transfers info from
		__Logger to whever it is going to get piped
	__Logger - Logger stream
	s_longer - Typedef referring to the Logger Singleton
	Logger - Protected reference to the Logger Singleton
*/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include "Singleton.h"

enum LoggerLevels : unsigned short {
	LEVEL_INFO,
	LEVEL_WARNING, 
	LEVEL_ERROR
};

class LoggerBuffer : public std::stringbuf {
private:
	std::string m_marker;
	std::mutex lock;
public:
	LoggerBuffer(const std::string& marker);
	~LoggerBuffer();
	int sync();

	std::string getTimeString();
};

class __Logger : public std::ostream {
	friend class Singleton<__Logger>;
public:
	__Logger(LoggerLevels level=LEVEL_WARNING, 
		   bool toFile=false, 
		   bool toConsole=true);
	~__Logger();

private:
	LoggerLevels m_level;
	bool m_toFile, m_toConsole;
};

class Logger {
public:
	Logger();
	Logger(LoggerLevels level, bool toFile, bool toConsole);
protected:
	__Logger& log;
};

typedef Singleton<__Logger, LoggerLevels, bool, bool> _Logger;

#endif // __LOGGER_H__
