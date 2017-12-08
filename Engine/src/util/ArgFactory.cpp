/*
	ArgFactory.h
	Michael Steer
	2017-08-04

	Argument Parser factory for adding in
	arguments that have a name, default parameter,
	description, and function pointer
*/

#include "util/ArgFactory.h"

// Parse arguments
ArgFactory::ArgFactory(ArgParser &parser)
	: parser(parser) {
}


// Add an argument to the argFactory
bool ArgFactory::addArg(std::string arg, std::string desc, bool needsParam, bool hasDefault, std::string def, callable func) {
	parser.args[arg] = Arg(arg, desc, needsParam, hasDefault, def, func);
	return true;
}