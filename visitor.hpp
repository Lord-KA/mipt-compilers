#pragma once

class IfStatement;
class WhileStatement;
class Assignment;
class Print;
class Declaration;

class AddExpression;
class DivExpression;
class IdentExpression;
class IfCondition;
class MulExpression;
class NumberExpression;
class SubstractExpression;

class Visitor {
public:
    virtual void visit(Assignment* assignment)   = 0;
    virtual void visit(Declaration* declaration) = 0;
    virtual void visit(IfStatement* stmnt)       = 0;
    virtual void visit(WhileStatement* stmnt)    = 0;
    virtual void visit(Print* println)           = 0;

    virtual void visit(AddExpression* exp)       = 0;
    virtual void visit(DivExpression* exp)       = 0;
    virtual void visit(IdentExpression* exp)     = 0;
    virtual void visit(IfCondition* cond)        = 0;
    virtual void visit(MulExpression* exp)       = 0;
    virtual void visit(NumberExpression* exp)    = 0;
    virtual void visit(SubstractExpression* exp) = 0;
};
