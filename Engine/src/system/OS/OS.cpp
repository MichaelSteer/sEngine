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

#if defined(_WIN32) || defined(_WIN64)

#pragma warning(disable : 4996) /* This PRAGMA disables the GetVersionExA deprecation
								   Warning. you aren't supposed to use this to check
								   Windows version info anymore. I am using it to
								   get a string representation and that is it, so it
								   should be okay
								*/
#include <Windows.h>
#include <Psapi.h>
#include <cstdint>
std::string getWindowsOSVersion() {
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx((OSVERSIONINFO*)&info);

	if (info.wProductType == VER_NT_WORKSTATION) {
		std::string check = std::to_string((uint32_t)info.dwMajorVersion) + "." + std::to_string((uint32_t)info.dwMinorVersion);
		if		(check == "10.0") return "Windows 10";
		else if (check == "6.3")  return "Windows 8.1";
		else if (check == "6.2")  return "Windows 8";
		else if (check == "6.1")  return "Windows 7";	
		else if (check == "6.0")  return "Windows Vista";	
		else if (check == "5.2")  return "Windows XP Professional Edition";
		else if (check == "5.1")  return "Windows XP";	
		else if (check == "5.0")  return "Windows 2000";
	}
	else {
		std::string check = std::to_string((uint32_t)info.dwMajorVersion) + "." + std::to_string((uint32_t)info.dwMinorVersion);
		if		(check == "10.0") return "Windows Server 2016    ";	
		else if (check == "6.3")  return "Windows Server 2012 R2 ";
		else if (check == "6.2")  return "Windows Server 2012    ";
		else if (check == "6.1")  return "Windows Server 2008    ";	
		else if (check == "6.0")  return "Windows 10";	
		else if (check == "5.2") {
			if (GetSystemMetrics(SM_SERVERR2) != 0) return "Windows Server 2003 R2";
			else return "Windows Home Server";
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
