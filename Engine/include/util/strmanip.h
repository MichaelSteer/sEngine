/*
	strmanip.h
	Michael Steer
	2017-11-27
	
	string manipulation aux functions
*/

#ifndef __STRMANIP_H__
#define __STRMANIP_H__

#define DATESTRING_LENGTH 23

#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>

/// <summary>
/// Converts the Specified string into a boolean
/// </summary>
/// <param name="str">The string.</param>
/// <returns>Boolean representation of the string</returns>
bool stob(std::string str) {
	bool b;

	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::istringstream is(str);
	
	is >> std::boolalpha >> b;
	return b;
}

std::vector<std::string> tokenize(const std::string &s, char delim=' ') {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

std::string dupe(char item, unsigned int times) {
	std::string out;
	for (unsigned int i = 0; i < times; i++) {
		out += item;
	}
	return out;
}


#endif // __STRMANIP_H__