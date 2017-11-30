/*
	SettingManager.cpp
	Michael Steer
	2017-11-25

	Setting Manager class
*/

#include <fstream>
#include "util\SettingManager.h"
#include "util\strmanip.h"

SettingManager::SettingManager(const std::string path)
	: path(path) {}

bool SettingManager::Load(const std::string _path) {
	std::string buffer, path;
	std::ifstream settingFile(path);

	if (_path == "") path = this->path;
	else path = _path;

	if (!settingFile) {
		log << "Error: Unable to open Settings file: " << path << endl;
		return false;
	}

	while (std::getline(settingFile, buffer)) {
		std::vector<std::string> tokens = tokenize(buffer, ':');

		char type = tokens[0][0];
		std::string setting = tokens[0];
		std::string value = tokens[1];

		switch (type) {
		case   'b' : setSetting(setting, stob(value));		break;
		case   'i' : setSetting(setting, std::stoll(value));		break;
		case   'f' : setSetting(setting, std::stod(value));		break;
		case   's' : setSetting(setting, value);		break;
		default: log << "Invalid Setting " << setting << " detected. Ignoring" << endl;	break;
		}
	}

	settingFile.close();
	return true;
}

bool SettingManager::Save(const std::string _path) {
	std::string path;
	std::ofstream settingFile(path);
	if (_path == "") path = this->path;
	else path = _path;

	if (!settingFile) {
		log << "Error: Unable to save settings to file: " << path << endl;
		return false;
	}

	for (auto setting : settings) {
		settingFile << setting.first << ":" << setting.second << endl;
	}

	settingFile.close();
	return true;
}

std::string SettingManager::getSecond(const std::string setting) {
	setting_iter si = settings.find(setting);
	if (si != settings.end()) return si->second; 
	else log << "Warning: Unable to read or find Setting: " << setting << " as type integer" << endl;
	return "";
}

long long SettingManager::igetSetting(const std::string setting) {
	try { return std::stoull(setting); }
	catch (InvalidSettingTypeException &e) {
			log << e.what() << endl;
	}
}

std::string SettingManager::sgetSetting(const std::string setting) {
	return getSecond(setting);
}

bool SettingManager::bgetSetting(const std::string setting) {
	try { return stob(setting); }
	catch (InvalidSettingTypeException &e) {
		log << e.what() << endl;
	}
}

double SettingManager::fgetSetting(const std::string setting) {
	try { return std::stod(setting); }
	catch (InvalidSettingTypeException &e) {
		log << e.what() << endl;
	}
}

bool SettingManager::setSetting(const setting setting) {
	settings[std::get<0>(setting)] = std::get<1>(setting);
	return true;
}

bool SettingManager::setSetting(const std::string setting, const std::string value) {
	if (setting[0] == 's') {
		settings[setting] = value;
		return true;
	}
	else {
		log << "Warning: attempted to write Setting " << setting << "as type string" 
			<< endl;
		return false;
	}
}

bool SettingManager::setSetting(const std::string setting, const long long value) {
	if (setting[0] == 'i') {
		settings[setting] = std::to_string(value);
		return true;
	}
	else {
		log << "Warning: attempted to write Setting " << setting << "as integer type" 
			<< endl;
		return false;
	}
}

bool SettingManager::setSetting(const std::string setting, const bool value) {
	if (setting[0] == 'b') {
		settings[setting] = std::to_string(value);
		return true;
	}
	else {
		log << "Warning: attempted to write Setting " << setting << "as boolean type" 
			<< endl;
		return false;
	}
}

bool SettingManager::setSetting(const std::string setting, const double value) {
	if (setting[0] == 'f') {
		settings[setting] = std::to_string(value);
		return true;
	}
	else {
		log << "Warning: attempted to write Setting " << setting << "as floating point type" 
			<< endl;
		return false;
	}
}