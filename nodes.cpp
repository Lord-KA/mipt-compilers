#include "nodes.hpp"

Program::Program(std::shared_ptr<StatementList> statements) : statements(statements) { }


AddExpression::AddExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2) : first(e1), second(e2) { }
void AddExpression::accept(Visitor* visitor) { visitor->visit(this); };
int AddExpression::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }


DivExpression::DivExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2) : first(e1), second(e2) {};
void DivExpression::accept(Visitor* visitor) { visitor->visit(this); };
int DivExpression::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }


IdentExpression::IdentExpression(const std::string& ident) : ident(ident) { }
void IdentExpression::accept(Visitor* visitor) { visitor->visit(this); };
int IdentExpression::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }


IfCondition::IfCondition(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2, CompareOperators oper)
		: first(e1), second(e2), oper(oper) { }
void IfCondition::accept(Visitor* visitor) { visitor->visit(this); };
int IfCondition::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }


MulExpression::MulExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2)
		: first(e1), second(e2) {}
void MulExpression::accept(Visitor* visitor) { visitor->visit(this); };
int MulExpression::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }


NumberExpression::NumberExpression(int value) : value(value) { }
void NumberExpression::accept(Visitor* visitor) { visitor->visit(this); };
int NumberExpression::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }


SubstractExpression::SubstractExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
			: first(lhs), second(rhs) { }
void SubstractExpression::accept(Visitor* visitor) { visitor->visit(this); };
int SubstractExpression::accept_eval(InterpreterVisitor* visitor) { return visitor->eval(this); }




void StatementList::AddStatement(std::shared_ptr<Statement> statement)
{
    statements.push_back(statement);
}

Declaration::Declaration(const std::string& variable) :
		variable(variable) { }
void Declaration::accept(Visitor* visitor) { visitor->visit(this); };


WhileStatement::WhileStatement(std::shared_ptr<IfCondition> c, std::shared_ptr<StatementList> s)
		: condition(c), statement(s) { }
void WhileStatement::accept(Visitor* visitor) { visitor->visit(this); };


IfStatement::IfStatement(std::shared_ptr<IfCondition> c, std::shared_ptr<StatementList> s1, std::shared_ptr<StatementList> s2)
		: condition(c), if_statement(s1), else_statement(s2) { }
void IfStatement::accept(Visitor* visitor) { visitor->visit(this); };


Print::Print(std::shared_ptr<Expression> expression)
		: expression(expression) { }
void Print::accept(Visitor* visitor) { visitor->visit(this); };


Assignment::Assignment(const std::string& variable, std::shared_ptr<Expression> expression)
		: variable(variable), expression(expression) { }
void Assignment::accept(Visitor* visitor) { visitor->visit(this); };
