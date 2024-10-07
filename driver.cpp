#include "driver.hpp"
#include "print.hpp"
#include "interpreter.hpp"

Driver::Driver() :
    scanner(*this), parser(scanner, *this) {
}

int Driver::print(const std::string& fileIn, std::ostream &out, bool verbose) {
    location.initialize(&fileIn);

	scanner.set_debug(verbose);

	std::ifstream stream;

    stream.open(fileIn);

    scanner.yyrestart(&stream);

    parser.set_debug_level(verbose);
    int res = parser();

    PrintVisitor visitor(out);
    visitor.visit(program.get());

    return res;
}

int Driver::interpret(const std::string& fileIn, std::ostream &out, bool verbose) {
    location.initialize(&fileIn);

	scanner.set_debug(verbose);

	std::ifstream stream;

    stream.open(fileIn);

    scanner.yyrestart(&stream);

    parser.set_debug_level(verbose);
    int res = parser();

    InterpreterVisitor visitor(out);
    visitor.visit(program.get());

    return res;
}
