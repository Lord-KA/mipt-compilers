#pragma once

#include <memory>
#include <string>
#include <vector>

#include "visitor.hpp"
#include "interpreter.hpp"

class InterpreterVisitor;
class Visitor;
class Driver;

class Node {
public:
	virtual ~Node() = default;
};

class Program : public Node {
public:
	Program(std::shared_ptr<StatementList> statements);
	std::shared_ptr<StatementList> statements;
};

class Expression : public Node {
public:
    virtual ~Expression() = default;
    virtual void accept(Visitor* visitor) = 0;
    virtual int accept_eval(InterpreterVisitor* visitor) = 0;
};

#define DEFINE_ACCEPT virtual void accept(Visitor* visitor); \
					  virtual int accept_eval(InterpreterVisitor* visitor);


class AddExpression: public Expression {
public:
    AddExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2);

    DEFINE_ACCEPT

    std::shared_ptr<Expression>  first;
    std::shared_ptr<Expression>  second;
};

class DivExpression: public Expression {
public:
    DivExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2);

    DEFINE_ACCEPT

    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
};

class IdentExpression: public Expression {
public:
    IdentExpression(const std::string& ident);
	DEFINE_ACCEPT

    std::string ident;
};

enum class CompareOperators{
    EQUAL = 1,
    NOT_EQUAL,
    LOWER,
    GREATER,
    LOWER_OR_EQ,
    GREATER_OR_EQ
};

class IfCondition: public Expression {
public:
    IfCondition(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2, CompareOperators oper);

	DEFINE_ACCEPT

	std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
    CompareOperators oper;
};

class MulExpression: public Expression {
 public:
    MulExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2);

	DEFINE_ACCEPT

    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
};

class NumberExpression: public Expression {
public:
    explicit NumberExpression(int value);

	DEFINE_ACCEPT

	int value;
};

class SubstractExpression: public Expression {
 public:
    SubstractExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs);

	DEFINE_ACCEPT

    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
};

#undef DEFINE_ACCEPT
#define DEFINE_ACCEPT virtual void accept(Visitor* visitor);

class Statement : public Node {
public:
    virtual ~Statement() = default;
    virtual void accept(Visitor* visitor) = 0;
};

class StatementList {
public:
   void AddStatement(std::shared_ptr<Statement> statement);

   std::vector<std::shared_ptr<Statement>> statements;
};

class Declaration: public Statement {
 public:
    Declaration(const std::string& variable);

	DEFINE_ACCEPT

    std::string variable;
};

class WhileStatement : public Statement {
public:
    explicit WhileStatement(std::shared_ptr<IfCondition> c, std::shared_ptr<StatementList> s);

	DEFINE_ACCEPT

    std::shared_ptr<IfCondition> condition;
    std::shared_ptr<StatementList> statement;
};

class IfStatement : public Statement {
public:
    explicit IfStatement(std::shared_ptr<IfCondition> c, std::shared_ptr<StatementList> s1, std::shared_ptr<StatementList> s2);

	DEFINE_ACCEPT

    std::shared_ptr<IfCondition> condition;
    std::shared_ptr<StatementList> if_statement;
    std::shared_ptr<StatementList> else_statement;
};

class Visitor;
class Print : public Statement{
public:
    explicit Print(std::shared_ptr<Expression> expression);

	DEFINE_ACCEPT

    std::shared_ptr<Expression> expression;
};

class Assignment: public Statement {
public:
    Assignment(const std::string& variable, std::shared_ptr<Expression> expression);

	DEFINE_ACCEPT

    std::string variable;
    std::shared_ptr<Expression> expression;
};

#undef DEFINE_ACCEPT
