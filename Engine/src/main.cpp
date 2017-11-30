/* 
	main.cpp
	Michael Steer
	2017-09-16
*/

#include "application.h"
#include "util\Logger.h"
#include "math\Vector.h"
#include "math\Matrix.h"

#include <array>
#include <iostream>

#include <windows.h>
using namespace std;

int main(int argc, char** argv) {

	Application app(argc, argv);

	app.init();
	app.run();

	app.hold();
	return app.exit();
	Sleep(100000);
	return 0;
}