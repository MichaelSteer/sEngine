/*
Argparse.h
Michael Steer
2017-08-02

Argument parser
*/

#include "util/ArgParse.h"

// Constructor
Arg::Arg()
	: func(nullptr), arg(""), desc(""), def(""), needsParam(false), hasDefault(false) {
}

// Constryctir
Arg::Arg(std::string arg, std::string desc, bool needsParam, bool hasDefault, std::string def, callable func)
	: func(func), arg(arg), desc(desc), def(def), needsParam(needsParam), hasDefault(hasDefault) {}

Arg::~Arg() {}

// Call an argument function
bool Arg::call(std::string param) {
	std::cout << "DONT RUN" << std::endl;
	std::cout << "CALLING FUNCTION: " << arg << std::endl;
	if (param=="" && hasDefault && needsParam) return func(def);
	else if (!needsParam) return func("");
	else {
		
		return func(param);
	}
}

// Print a specific argument to the console
void Arg::print() {
	std::cout << "[" << arg << "]" << std::endl;
	std::cout << desc << std::endl << std::endl;
	if (needsParam && hasDefault) std::cout << "Default Value: " << def << std::endl;
}

// Constructor
ArgParser::ArgParser() 
	: argc(0), argv(nullptr) {
}

// Constructor with program arguments
ArgParser::ArgParser(int argc, char**argv) 
	: argc(argc), argv(argv) {

}

// Destructor
ArgParser::~ArgParser() { }

// Call specific argument function
bool ArgParser::call(std::string arg, std::string param) {
	return args[arg].call(param);
}

// Parse arguments
// something dies in here. FIND it
bool ArgParser::parse() {
	log << "PARSING" << std::endl;
	log << "argc " << argc << std::endl;
	int i = 1;
	while (i < argc) {
		if (argv[i][0] == '-') { // function
			log << "FOUND FUNCTION " << argv[i] << std::endl;
			if (i + 1 < argc) { // still one more item
				if (argv[i + 1][0] != '-') {
					funcs.push_back(std::tuple<std::string, std::string>(std::string(argv[i]), argv[i + 1]));
					i += 2;
					log << "SHOULD BE DONE" << std::endl;
				}
				else {
					funcs.push_back(std::tuple<std::string, std::string>(std::string(argv[i]), ""));
					funcs.push_back(std::tuple<std::string, std::string>(std::string(argv[i+1]), ""));
					i += 1;
					log << "SHOULD BE DONE" << std::endl;
				}
			}
			else {
				funcs.push_back(std::tuple<std::string, std::string>(std::string(argv[i]), ""));
				i++;
			}
		}
		else {
			i++;
		}
	}

	for (auto func : funcs) {
		call(std::get<0>(func), std::get<1>(func));
	}
	return true;
}


// Print help information
void ArgParser::help() {
	for (auto &arg : args) {
		std::cout << arg.second.arg;
		if (arg.second.needsParam) {
			std::cout << " " << (arg.second.hasDefault ? arg.second.def : "[ ]") << " ";
		}
	}
	std::cout << std::endl;

	std::cout << "Descriptions: " << std::endl << "==============" << std::endl;
	for (auto &arg : args) arg.second.print();
}
