/*
	CPU.h
	Michael Steer
	2017-11-27
	
	CPU Specific calls

	References:
	https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
*/

#ifndef __CPU_H__
#define __CPU_H__

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <tchar.h>
#include <Pdh.h>
#include <PdhMsg.h>
#else
//...

//TODO: REWRITE WITH C++11
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#include <string>
class CPU {
private:

	double totalUsage, processUsage;

#if defined(_WIN32) || defined(_WIN64)
	PDH_HQUERY cpuQuery;
	PDH_HCOUNTER cpuTotal;
	ULARGE_INTEGER last, lastSys, lastUser;
	int nProcessors;
	HANDLE self;
#else
	static unsigned long long lastTotalUser, lastTotalUserLow;
	static unsigned long long lastTotalSys;
	static unsigned long long lastTotalIdle;
	static clock_t lastCPU, lastSysCPU, lastUserCPU;
	static int nProcessors;
#endif
public:
	CPU();

	void poll();

	double getTotalUsage();
	double getProcessUsage();
	//std::string getCPUName();
	unsigned short getNumberOfCores();
};

#endif // __CPU_H__