/*
	Memory.h
	Michael Steer
	2017-11-27

	Memory class for RAM Usage

	https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
*/
 
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#include <Psapi.h>
#include "system\OS\Memory.h"
void Memory::poll() {

	MEMORYSTATUSEX memory;
	PROCESS_MEMORY_COUNTERS_EX pmc;

	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	memory.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memory);

	// VRAM
	TotalVirtual = memory.ullTotalPageFile;
	UsedVirtual = memory.ullTotalPageFile - memory.ullAvailPageFile;
	ProcessVirtual procVMemoryUsed = pmc.PrivateUsage;

	// Physical Memory
	TotalPhysical = memory.ullTotalPhys;
	UsedPhysical = memory.ullTotalPhys - memory.ullAvailPhys;
	ProcessPhysical  = pmc.WorkingSetSize;
}

#else
#include <sys/types.h>
#include <sys/sysinfo.h>
void Memory::poll() {
	struct sysinfo meminfo;
	sysinfo(&meminfo);

	// VRAM
	TotalVirtual = meminfo.totalram;
	TotalVirtual += meminfo.totalswap;
	TotalVirtual *= meminfo.mem_unit;

	UsedVirtual = meminfo.totalram - meminfo.freeram;
	UsedVirtual += meminfo.totalswap;
	UsedVirtual *= meminfo.mem_unit;

	// WRITE PROC CODE HERE

	// RAM
	TotalPhysical = meminfo.totalram;
	TotalPhysical *= memino.mem_unit;

	UsedPhysical = meminfo.totalram - meminfo.freeram;
	UsedPhysical *= memoinfo.mem_unit;
}
#endif

unsigned long long Memory::getPhysical() { return TotalPhysical; }
unsigned long long Memory::getUsedPhysical() { return UsedPhysical; }
unsigned long long Memory::getProcessPhysical() { return ProcessPhysical; }
float Memory::getUsagePercentage() { return (float)UsedPhysical / (float)TotalPhysical; }
float Memory::getProcessPercentage() { return (float)ProcessPhysical / (float)TotalPhysical; }

unsigned long long Memory::getVirtual() { return TotalVirtual; }
unsigned long long Memory::getUsedVirtual() { return UsedVirtual; }
unsigned long long Memory::getProcessVirtual() { return ProcessVirtual; }
float Memory::getVirtualUsagePercentage() { return (float)UsedVirtual / (float)TotalVirtual; }
float Memory::getVirtualProcessPercentage() { return (float)ProcessVirtual / (float)TotalVirtual; }