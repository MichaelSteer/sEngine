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
	cout << "      ______             _             " << endl;
	cout << "     |  ____|           (_)            " << endl;
	cout << "  ___| |__   _ __   __ _ _ _ __   ___ 	" << endl;
	cout << " / __|  __| | '_ \\/  _` | | '_  \\/ _ \\	" << endl;
	cout << " \\__ \\ |____| | | | (_| | | | | |  __/	" << endl;
	cout << " |___/______|_| |_|\\__, |_|_| |_|\\___|	" << endl;
	cout << "                    __/ |             	" << endl;
	cout << "                   |___/               " << endl;

	cout << "         App : " << getApplicationName() << endl;
	cout << "      Author : " << getApplicationAuthor() << endl;
	cout << "     Version : " << __version__major__() << "." << __version__minor__() << endl;
	cout << "        Date : " << getApplicaitonCompilationDate() << endl;
	cout << " Github Hash : " << endl;
}
