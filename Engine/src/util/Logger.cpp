/*
	Logger.cpp
	Michael Steer
	2017-08-03
	
	Logging application
*/

#include "util/Logger.h"
#include "system/timing.h"

// Constructor
LoggerBuffer::LoggerBuffer(const std::string& marker)
	: m_marker(marker) {}

// Destructor
LoggerBuffer::~LoggerBuffer() { pubsync(); }

// Push Asyncronous Logging content
int LoggerBuffer::sync() {
	lock.lock();
	std::cout << m_marker << ": " << getTimeString() << ": " << str();
	str("");
	lock.unlock();
	return std::cout ? 0 : -1;
}

// get the current time as a string
std::string LoggerBuffer::getTimeString() {
	return timeString("[%y-%m-%d %H:%M:%S]");
}

// Constructor
__Logger::__Logger(LoggerLevels level, bool toFile, bool toConsole)
	: m_level(level), 
	  m_toFile(toFile), 
	  m_toConsole(toConsole), 
	  std::ostream(new LoggerBuffer("Log")) {}

// Destructor
__Logger::~__Logger() { delete rdbuf(); }

// Constructor
Logger::Logger() 
	: log(_Logger::getInstance(LEVEL_ERROR, true, true)) {}

// Parameterized Constructor
Logger::Logger(LoggerLevels level, bool toFile, bool toConsole) 
	: log(_Logger::getInstance(level, toFile, toConsole)) {}
