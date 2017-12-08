/*
	ArgFactory.h
	Michael Steer
	2017-08-04
	
	Argument Parser factory for adding in
	arguments that have a name, default parameter,
	description, and function pointer
*/
#ifndef __ARG_FACTORY__H__
#define __ARG_FACTORY__H__

#include "ArgParse.h"

/* Argument Factory. This class statically loads arguments, if static loading is needed
	TODO: Get rid of this and make settings dynamic
*/
class ArgFactory {
public:
	ArgFactory(ArgParser &parser);
	bool addArg(std::string arg, std::string desc, bool needsParam, bool hasDefault, std::string def, callable func);
private:
	ArgParser &parser;
};

#endif // __ARG_FACTORY_H__