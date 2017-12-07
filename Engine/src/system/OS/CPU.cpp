/*
	CPU.h
	Michael Steer
	2017-11-27

	CPU Specific calls
*/


#include "system\OS\CPU.h"

#ifdef _WIN32
#include <Pdh.h>
CPU::CPU() {
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddEnglishCounter(cpuQuery, (LPCSTR)"\\Processor(_Total\\% Processor Time", NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);

	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	nProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&last, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSys, &fsys, sizeof(FILETIME));
	memcpy(&lastUser, &fuser, sizeof(FILETIME));
}

void CPU::poll() {

	// Total
	PDH_FMT_COUNTERVALUE counter;

	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counter);

	totalUsage =  counter.doubleValue;

	// Process
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));

	percent = (double)(sys.QuadPart - lastSys.QuadPart) + (user.QuadPart - lastUser.QuadPart);
	percent /= now.QuadPart - last.QuadPart;
	percent /= nProcessors;

	last = now;
	lastUser = user;
	lastSys = sys;

	processUsage = percent * 100;
}

#else

#include <sys/times.h>
#include <sys/vtimes.h>

CPU::CPU() {
	
	struct tms timeSample;
	char line[128];
	nProcessors = 0;
	lastCPU = times(&timeSample);
	lastSysCPU = timeSample.tms_stime;
	lastUserCPUI = timeSample.tmns_utime;

	FILE *f = fopen("/proc/stat", "r");
	fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow, &lastTotalSys, &lastTotalIdle);
	fclose(f);

	FILE *g = fopen("/proc/cpuinfo", "r");
	while (fgets(line, 128, f) != NULL) {
		if (strncmp(line, "processor", 9) == 0) nProcessors++;
	}
	fclose(g);
}

void CPU::poll() {
	double percent;
	FILE *f;
	unsigned totalUser, totalUserLow, totalSys, totalIdle, total;
	f = fopen("/proc/stat", "r");
	fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow, &totalSys, &totalIdle);
	fclose(f);

	if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow) || totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
	percent = -1.0f;
	}
	else {
		total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) + (totalSys - lastTotalSys);
		percent = total;
		total += (totalIdle - lastTotalIdle);
		percent /= total;
		percent *= 100;
	}

	lastTotalUser = totalUser;
	lastTotalUserLow = totalUserLow;
	lastTotalSys = totalSys;
	lastTotalIdle = totalIdle;

	totalUsage = percent;

	// Process
	percent = 0.0f;
	struct tms timeSample;
	clock_t now;

	now = times(&timeSample);
	if (now <= lastCPU || timeSample.tms_stime < lastSysCPU) || timeSample.tms_utime < lastUserCPU) {
	percent = -1.0f;
	}
	else {
		percent = (timeSample.tms_stime - lastSysCPU) + (timeSample.tms_utime - lastUserCPU);
		percent /= (now - lastCPU);
		percent /= nProcessors;
		percent *= 100;
	}

	processUsage = percent;
}

#endif

double CPU::getTotalUsage() {
	return totalUsage;
}

double CPU::getProcessUsage() {
	return processUsage;
}

unsigned short CPU::getNumberOfCores() {
	return nProcessors;
}