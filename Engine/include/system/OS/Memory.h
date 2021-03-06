/*
	Memory.h
	Michael Steer
	2017-11-27
	
	Memory class for RAM Usage
*/

#ifndef __MEMORY_H__
#define __MEMORY_H__

// Memory class structure
class Memory {
private:
	unsigned long long TotalPhysical;
	unsigned long long TotalVirtual;

	unsigned long long UsedPhysical;
	unsigned long long UsedVirtual;

	unsigned long long ProcessPhysical;
	unsigned long long ProcessVirtual;
public:
	Memory();
	void poll();

	unsigned long long getPhysical();
	unsigned long long getUsedPhysical();
	unsigned long long getProcessPhysical();
	float			   getUsagePercentage();														   
	float			   getProcessPercentage();


	unsigned long long getVirtual();
	unsigned long long getUsedVirtual();
	unsigned long long getProcessVirtual();
	float			   getVirtualUsagePercentage();
	float			   getVirtualProcessPercentage();
};				

#endif // __MEMORY_H__