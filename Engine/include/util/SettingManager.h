/*
	SettingManager.h
	Michael Steer
	2017-11-25

	Setting Manager class
*/

#ifndef __SETTING_MANAGER_H__
#define __SETTING_MANAGER_H__

#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <ostream>
#include <sstream> 
#include <exception>
#include "util\Utility.h"

typedef std::tuple<std::string, std::string> setting;
typedef std::map<std::string, std::string>::iterator setting_iter;

using std::endl;

class InvalidSettingTypeException : public std::invalid_argument {
	InvalidSettingTypeException() : invalid_argument("Setting is invalid") {}
};

class SettingManager : public Utility {
private:
	std::map<std::string, std::string> settings;
	std::string path;

	std::string getSecond(const std::string setting);
public:
	SettingManager(const std::string path);

	bool Load(const std::string path="");
	bool Save(const std::string path="");

	long long igetSetting(const std::string setting);
	std::string sgetSetting(const std::string setting);
	bool bgetSetting(const std::string setting);
	double fgetSetting(const std::string setting);

	bool setSetting(const setting setting);
	bool setSetting(const std::string setting, const std::string value);
	bool setSetting(const std::string setting, const long long value);
	bool setSetting(const std::string setting, const bool value);
	bool setSetting(const std::string setting, const double value);

	template<typename T, typename Traits>
	friend std::basic_ostream<T, Traits> &operator<<
		(std::basic_ostream<T, Traits> &out, const SettingManager &setting) {
		std::stringstream s;
		for (auto &setting : settings) {
			s << setting << std::endl;
		}	 
		return out << s.str();
	}
};

#endif // __SETTING_MANAGER_H__
