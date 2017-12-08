/*
	HardwareManager.h
	Michael Steer
	2017-11-29

	Hardware Managment class
	for displaying the users
	hardware
*/

#include <cmath>
#include <sstream>
#include <iomanip>
#include "system\OS\HardwareManager.h"
HardwareManager::HardwareManager() : Memory(), CPU() {}

void HardwareManager::poll() {
	Memory::poll();
	CPU::poll();
}

std::string HardwareManager::getHardwareInfo() {
	return "";
}

std::string HardwareManager::getPerformanceInfo() {
	return "";
}

unsigned long long HardwareManager::getTotalRAM() {
	return (unsigned long long)std::ceil(Memory::getPhysical()) / 1024 / 1024;
}

unsigned long long HardwareManager::getUsedRAM() {
	return Memory::getUsedPhysical();
}

unsigned long long HardwareManager::getProcessRAM() {
	return Memory::getProcessPhysical();
}

double HardwareManager::getUsedRAMPercentage() {
	return Memory::getUsagePercentage();
}

double HardwareManager::getProcessRAMPercentage() {
	return Memory::getProcessPercentage();
}

unsigned long long HardwareManager::getTotalPageFile() {
	return Memory::getVirtual();
}

unsigned long long HardwareManager::getUsedPageFile() {
	return Memory::getUsedVirtual();
}

unsigned long long HardwareManager::getProcessPageFile() {
	return Memory::getProcessVirtual();
}

double HardwareManager::getUsedPageFilePercentage() {
	return Memory::getVirtualUsagePercentage();
}

double HardwareManager::getProcessPageFilePercentage() {
	return Memory::getVirtualProcessPercentage();
}

double HardwareManager::getCPUUsage() {
	return CPU::getTotalUsage();
}

double HardwareManager::getProcessCPUUsage() {
	return CPU::getProcessUsage();
}

unsigned short HardwareManager::getNCores() {
	return CPU::getNumberOfCores();
}

void HardwareManager::print() {
	log << basicProcessInfo();
}

std::string HardwareManager::basicProcessInfo() {
	std::stringstream out;

	out.precision(3);
	out << "Cores (" << getNCores() << ") Core Usage: "<< getProcessCPUUsage() << "\% " << "(Total: "
		<< getCPUUsage() << "%)" << endl;

	// POS FUCKING SPACER FUNC THAT WONT COMPILE
	for (unsigned int i = 0; i < 26; i++) {
		out << " ";
	}
	out << "RAM (MB): " << (getProcessRAM() / 1024 / 1024) << " MB (" << getProcessRAMPercentage() << "%)" << endl;
	return out.str();
}

/*
std::string fullProcessInfo() {
//out << "   CPU Usage Information: " << endl;
//out << "         Number of cores: " << getNCores() << endl;
//out << "         Total CPU Usage: " << getCPUUsage() << endl;
//out << "       Process CPU Usage: " << getProcessCPUUsage() << endl;

//out << "Memory Usage Information: " << endl;
//out << "               Total RAM: " << getTotalRAM() << "GB" << endl;
//out << "           Available RAM: " << getTotalRAM() - getUsedRAM() << "GB" << endl;
//out << "                Used RAM: " << getProcessRAM() << "GB" << endl;

//return out.str();
}*/
