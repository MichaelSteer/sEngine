/*
	splash.cpp
	Michael Steer
	2017-11-21
	
	Splash file
	
*/

#include <iostream>
#include "misc\splash.h"

using std::cout;
using std::endl;

/*
	Splash screen
*/
void splash() {
	cout << "          sEngine   " << endl;
	cout << "              App : " << getApplicationName() << endl;
	cout << "           Author : " << getApplicationAuthor() << endl;
	cout << "          Version : " << getVersion() << endl;
	cout << "             Date : " << getApplicaitonCompilationDate() << endl;
}
