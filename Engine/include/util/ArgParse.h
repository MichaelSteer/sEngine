/*
	Argparse.h
	Michael Steer
	2017-08-02
	
	Argument parser
*/

#ifndef __ARGPARSE_H__
#define __ARGPARSE_H__

#include <vector>
#include <string>
#include <functional>
#include <map>
#include "Utility.h"

class ArgFactory;
class ArgParser;


// Function pointer wrapper
typedef std::function<bool(std::string)> callable;

// Argument class
class Arg {
	friend class ArgParser;
public:
	Arg();
	Arg(std::string arg,  
		std::string desc, 
		bool needsParam,
		bool hasDefault,
		std::string def,
		callable func);
	bool call(std::string param);
	void print();
	~Arg();

private:
	bool needsParam;
	bool hasDefault;
	std::string arg;
	std::string def;
	std::string desc;
	std::function<bool(std::string)> func;
};

// Argument Parsing class
class ArgParser : public Utility {
	friend class ArgFactory;
public:
	ArgParser();
	ArgParser(int argc, char**argv);
	~ArgParser();
	bool call(std::string arg, std::string param);
	bool parse();
	void help();
private:
	int argc;
	char**argv;
	std::map<std::string, Arg> args;
	std::vector<std::tuple<std::string, std::string>> funcs;
};

#endif // __ARGPARSE_H__