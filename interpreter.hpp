#pragma once

#include <map>
#include <string>

#include "visitor.hpp"

class Program;
class StatementList;

class InterpreterVisitor : public Visitor {
public:
	InterpreterVisitor(std::ostream &out);

    void visit(Program* program);
    void visit(StatementList* list);
    virtual void visit(Assignment* assignment);
    virtual void visit(Declaration* declaration);
    virtual void visit(IfStatement* stmnt);
    virtual void visit(Print* print);
    virtual void visit(WhileStatement* stmnt);
    virtual void visit(AddExpression* exp);
    virtual void visit(DivExpression* exp);
    virtual void visit(IdentExpression* exp);
    virtual void visit(IfCondition* cond);
    virtual void visit(MulExpression* exp);
    virtual void visit(NumberExpression* exp);
    virtual void visit(SubstractExpression* exp);

    int eval(DivExpression* exp);
    int eval(AddExpression* exp);
    int eval(IdentExpression* exp);
    int eval(IfCondition* cond);
    int eval(MulExpression* exp);
    int eval(NumberExpression* exp);
    int eval(SubstractExpression* exp);

private:
    std::map<std::string, int> variables;
	std::ostream &out;
};
