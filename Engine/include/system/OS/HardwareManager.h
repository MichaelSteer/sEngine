/*
	HardwareManager.h
	Michael Steer
	2017-11-29

	Hardware Managment class
	for displaying the users
	hardware
*/

#ifndef __HARDWARE_MANAGER_H__
#define __HARDWARE_MANAGER_H__

#include <string>
#include "system\OS\CPU.h"
#include "system\OS\Memory.h"
#include "util\Utility.h"

using std::endl;

class HardwareManager : public Memory, public CPU, public Utility {
public:

	void poll();

	HardwareManager();

	// Output calls
	std::string getHardwareInfo();
	std::string getPerformanceInfo();
	std::string basicProcessInfo();

	void print();

	// RAM Calls
	unsigned long long getTotalRAM();	
	unsigned long long getUsedRAM();
	unsigned long long getProcessRAM();
	double getUsedRAMPercentage();
	double getProcessRAMPercentage();

	// Page File Calls
	unsigned long long getTotalPageFile();
	unsigned long long getUsedPageFile();
	unsigned long long getProcessPageFile();
	double getUsedPageFilePercentage();
	double getProcessPageFilePercentage();

	// CPU Calls
	double getCPUUsage();
	double getProcessCPUUsage();	 
	unsigned short getNCores();

	// Output Operator
	template<typename T, typename Traits>
	friend std::basic_ostream<T, Traits> &operator<<
		(std::basic_ostream<T, Traits> &out, const HardwareManager &hwm) {
		return basicProcessInfo(); }

};

#endif // __HARDWARE_MANAGER_H__
