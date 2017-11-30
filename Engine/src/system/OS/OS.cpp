/*
	OS.h
	Michael Steer

	2017-11-27

	Various Operating System
	specific macros and functions
*/


/*
	WINDOWS SPECIFIC STUFF GOES HERE
*/
#include "system/OS/OS.h"

#ifdef _WIN32 || _WIN64
#include <Windows.h>
#include <Psapi.h>
std::string getWindowsOSVersion() {
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx(&info);

	if (info.wProductType == VER_NT_WORKSTATION) {
		switch (std::string(info.dwMajorVersion ? ) + "." + std::string(info.dwMinorVersion) {
		case "10.0": return "Windows 10";		break;
		case "6.3":  return "Windows 8.1";		break;
		case "6.2":  return "Windows 8";		break;
		case "6.1":  return "Windows 7";		break;
		case "6.0":  return "Windows Vista";		break;
		case "5.2":  return "Windows XP Professional Edition";		break;
		case "5.1":  return "Windows XP";		break;
		case "5.0":  return "Windows 2000";		break;
		}
	}
	else {
		switch (std::string(info.dwMajorVersion ? ) + "." + std::string(info.dwMinorVersion) {
		case "10.0": return "Windows Server 2016    ";		break;
		case "6.3":  return "Windows Server 2012 R2 ";		break;
		case "6.2":  return "Windows Server 2012    ";		break;
		case "6.1":  return "Windows Server 2008    ";		break;
		case "6.0":  return "Windows 10";		break;
		case "5.2": {
			if (GetSystemMetrics(SM_SERVERR2) != 0) return "Windows Server 2003 R2";	break;
			else return "Windows Home Server";	break;
			}
		}
	}
	return "Bad windows version";
}


#else
std::string getWindowsOSVersion() {
	return "Not a windows OS";
}
/*
	NON WINDOWS SPECIFIC STUFF GOES HERE
	ANY OTHER NON WINDOWS DIFFERENCES
	GET NESTED
*/
#endif
