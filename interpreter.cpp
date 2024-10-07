#include "interpreter.hpp"
#include <iostream>
#include <ostream>

#include "print.hpp"
#include "nodes.hpp"

InterpreterVisitor::InterpreterVisitor(std::ostream &out) : out(out) { }

int InterpreterVisitor::eval(AddExpression* exp)
{
	return exp->first->accept_eval(this) + exp->second->accept_eval(this);
}

int InterpreterVisitor::eval(SubstractExpression* exp)
{
	return exp->first->accept_eval(this) - exp->second->accept_eval(this);
}

int InterpreterVisitor::eval(MulExpression* exp)
{
	return exp->first->accept_eval(this) * exp->second->accept_eval(this);
}

int InterpreterVisitor::eval(DivExpression* exp)
{
	return exp->first->accept_eval(this) / exp->second->accept_eval(this);
}

int InterpreterVisitor::eval(IdentExpression* exp)
{
	return variables[exp->ident];
}

int InterpreterVisitor::eval(IfCondition* cond)
{
	int lhs = cond->first->accept_eval(this);
	int rhs = cond->second->accept_eval(this);

	switch (cond->oper) {
	case CompareOperators::EQUAL:
		return lhs == rhs;
	case CompareOperators::LOWER:
		return lhs < rhs;
	case CompareOperators::LOWER_OR_EQ:
		return lhs <= rhs;
	case CompareOperators::GREATER:
		return lhs > rhs;
	case CompareOperators::GREATER_OR_EQ:
		return lhs >= rhs;
	case CompareOperators::NOT_EQUAL:
		return lhs != rhs;
	}
}

int InterpreterVisitor::eval(NumberExpression* exp)
{
	return exp->value;
}

void InterpreterVisitor::visit(StatementList* list)
{
	for (auto &stmnt : list->statements)
		stmnt->accept(this);
}

void InterpreterVisitor::visit(Program* prog)
{
	visit(prog->statements.get());
}

void InterpreterVisitor::visit(Assignment* asmt)
{
	variables[asmt->variable] = asmt->expression->accept_eval(this);
}

void InterpreterVisitor::visit(Declaration* decl)
{
	variables.insert({decl->variable, 0});
}

void InterpreterVisitor::visit(IfStatement* stmnt)
{
	if (stmnt->condition->accept_eval(this))
		visit(stmnt->if_statement.get());
	else
		visit(stmnt->else_statement.get());
}

void InterpreterVisitor::visit(WhileStatement* stmnt)
{
	while (stmnt->condition->accept_eval(this))
		visit(stmnt->statement.get());
}

void InterpreterVisitor::visit(Print* exp)
{
	out << exp->expression->accept_eval(this) << std::endl;
}

void InterpreterVisitor::visit(AddExpression*) { }
void InterpreterVisitor::visit(SubstractExpression*) { }
void InterpreterVisitor::visit(MulExpression*) { }
void InterpreterVisitor::visit(DivExpression*) { }

void InterpreterVisitor::visit(NumberExpression*) { }
void InterpreterVisitor::visit(IdentExpression* ident_exp) { }
void InterpreterVisitor::visit(IfCondition* if_cond) { }
