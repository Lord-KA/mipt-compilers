#include <iostream>

#include "visitor.hpp"

class Program;
class StatementList;

class PrintVisitor : public Visitor {
public:
    PrintVisitor(std::ostream &out) : out(out) { }

    void visit(Program* program);
    void visit(StatementList* statement_list);

    virtual void visit(Assignment* assignment);
    virtual void visit(Declaration* declaration);
    virtual void visit(IfStatement* stmnt);
    virtual void visit(WhileStatement* stmnt);
    virtual void visit(Print* print);
    virtual void visit(AddExpression* exp);
    virtual void visit(DivExpression* exp);
    virtual void visit(IdentExpression* exp);
    virtual void visit(IfCondition* cond);
    virtual void visit(MulExpression* exp);
    virtual void visit(NumberExpression* exp);
    virtual void visit(SubstractExpression* exp);

private:
    void align();

    int alignment = 0;
    std::ostream& out;
};
