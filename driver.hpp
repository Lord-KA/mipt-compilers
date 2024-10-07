#pragma once

#include <fstream>
#include <memory>

#include "scanner.hpp"

class Program;

class Driver {
public:
	Driver();
	int print(const std::string &file, std::ostream &out, bool verbose = false);
	int interpret(const std::string &file, std::ostream &out, bool verbose = false);

	Scanner scanner;

	std::shared_ptr<Program> program;

	yy::parser parser;
	yy::location location;
};
