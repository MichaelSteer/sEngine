/*
	winapi.h
	Michael Steer
	2017-12-06

	Windows specific API calls
*/

#ifndef __WINAPI_H__
#define __WINAPI_H__

#include <windows.h>
#include <cstdio>

/* Produce a console for the windows version
   of this application							*/
inline void InitConsole() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}

#endif // __WINAPI_H__