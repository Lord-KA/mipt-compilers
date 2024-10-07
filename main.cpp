#include <iostream>
#include <string>
#include <fstream>

#include "driver.hpp"
#include "print.hpp"

void showHelp() {
    std::string helpMessage =
        "Usage: frontend [options]\n"
        "Options:\n"
        "  -h, --help           Show this help message\n"
        "  -v, --verbose        Enable verbose mode\n"
        "  -p, --print FILE     Print the AST of the program\n"
        "  -i, --interpret FILE Interpret the program\n"
        "  -o, --output FILE    Write output to the specified FILE\n";
    std::cout << helpMessage;
}

int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string outputFile;
    bool verbose = false;
    bool interpret = false;
    bool print = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            showHelp();
            return 0;
        } else if (arg == "-v" || arg == "--verbose") {
            verbose = true;
            std::cerr << "Verbose mode enabled." << std::endl;
        } else if (arg == "-p" || arg == "--print") {
            if (i + 1 >= argc) {
                std::cerr << "Error: No filename specified for print option." << std::endl;
                return 1;
            }
            inputFile = argv[++i];
            print = true;
        } else if (arg == "-i" || arg == "--interpret") {
            if (i + 1 >= argc) {
                std::cerr << "Error: No filename specified for interpret option." << std::endl;
                return 1;
            }
            inputFile = argv[++i];
            interpret = true;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Error: No filename specified for output option." << std::endl;
                return 1;
            }
            outputFile = argv[++i];
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
            return 1;
        }
    }

    if (print && interpret) {
        std::cerr << "Error: You cannot use both --print and --interpret." << std::endl;
        return 1;
    }

    if (inputFile.empty()) {
        std::cerr << "Error: No input file specified." << std::endl;
        return 1;
    }

	Driver driver;
	if (not outputFile.empty()) {
		std::ofstream out(outputFile);

	    if (print)
			driver.print(inputFile, out, verbose);
	    if (interpret)
			driver.interpret(inputFile, out, verbose);
	} else {
	    if (print)
			driver.print(inputFile, std::cout, verbose);
	    if (interpret)
			driver.interpret(inputFile, std::cout, verbose);

	}

    return 0;
}
