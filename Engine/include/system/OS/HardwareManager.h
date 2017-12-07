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
using std::endl;

#include "system\OS\CPU.h"
#include "system\OS\Memory.h"
#include "util\Utility.h"
class HardwareManager : public Memory, public CPU, public Utility {
public:

	void poll();

	HardwareManager();

	std::string getHardwareInfo();
	std::string getPerformanceInfo();

	unsigned long long getTotalRAM();	
	unsigned long long getUsedRAM();
	unsigned long long getProcessRAM();
	double getUsedRAMPercentage();
	double getProcessRAMPercentage();

	unsigned long long getTotalPageFile();
	unsigned long long getUsedPageFile();
	unsigned long long getProcessPageFile();
	double getUsedPageFilePercentage();
	double getProcessPageFilePercentage();

	double getCPUUsage();
	double getProcessCPUUsage();	 

	unsigned short getNCores();

	std::string basicProcessInfo();
	// std::string fullProcessInfo();
	void print();

	template<typename T, typename Traits>
	friend std::basic_ostream<T, Traits> &operator<<
		(std::basic_ostream<T, Traits> &out, const HardwareManager &hwm) {
		return basicProcessInfo(); }

};

#endif // __HARDWARE_MANAGER_H__
