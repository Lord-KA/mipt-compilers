#include "print.hpp"
#include "nodes.hpp"

void PrintVisitor::align()
{
    for (int i = 0; i < alignment; ++i)
        out << '\t';
}

void PrintVisitor::visit(StatementList* statement_list)
{
    for (auto &stmnt : statement_list->statements){
        stmnt->accept(this);
    }
}

void PrintVisitor::visit(Program* prog)
{
    align();
    out << "Program:" << std::endl;
    ++alignment;
    visit(prog->statements.get());
    --alignment;
}

void PrintVisitor::visit(Assignment* assignment)
{
    align();
    out << "Assignment" << std::endl;
}

void PrintVisitor::visit(Declaration* decl)
{
    align();
    out << "Declaration" << std::endl;
}

void PrintVisitor::visit(IfStatement* stmnt)
{
    align();
    out << "If:" << std::endl;
    stmnt->condition->accept(this);


    align();
    out << "Do:" << std::endl;
    ++alignment;
    visit(stmnt->if_statement.get());
    --alignment;

    if(stmnt->else_statement != nullptr){
        align();
        out << "Else:" << std::endl;

        ++alignment;
        visit(stmnt->else_statement.get());
        --alignment;
    }
}

void PrintVisitor::visit(WhileStatement* stmnt)
{
    align();
    out << "While:" << std::endl;
    stmnt->condition->accept(this);

    align();
    out << "Do:" << std::endl;
    ++alignment;
    visit(stmnt->statement.get());
    --alignment;
}

void PrintVisitor::visit(Print*)
{
    align();
    out << "Print" << std::endl;
}

void PrintVisitor::visit(AddExpression* exp)
{
    align();
    out << "Add:" << std::endl;

    ++alignment;
    exp->first->accept(this);
    --alignment;

    ++alignment;
    exp->second->accept(this);
    --alignment;
}

void PrintVisitor::visit(DivExpression* exp)
{
    align();
    out << "Div:" << std::endl;

    ++alignment;
    exp->first->accept(this);
    --alignment;

    ++alignment;
    exp->second->accept(this);
    --alignment;
}

void PrintVisitor::visit(IdentExpression* exp)
{
    align();
    out << "Ident: " << exp->ident << std::endl;
}

std::string print_operator(IfCondition* cond)
{
    switch (cond->oper)
    {
    case CompareOperators::EQUAL:
        return "==";
    case CompareOperators::NOT_EQUAL:
        return "!=";
    case CompareOperators::LOWER:
        return "<";
    case CompareOperators::GREATER:
        return ">";
    case CompareOperators::LOWER_OR_EQ:
        return "<=";
    case CompareOperators::GREATER_OR_EQ:
        return ">=";
    }

    return "";
}

void PrintVisitor::visit(IfCondition* cond)
{
    align();
    out << "If condition: " << std::endl;

    ++alignment;
	cond->first->accept(this);

    align();
    out << "operator: " << print_operator(cond) << std::endl;

    cond->second->accept(this);
    --alignment;
}

void PrintVisitor::visit(MulExpression* mul_exp)
{
    align();
    out << "Mul:" << std::endl;

    ++alignment;
    mul_exp->first->accept(this);
    --alignment;

    ++alignment;
    mul_exp->second->accept(this);
    --alignment;
}

void PrintVisitor::visit(NumberExpression* exp)
{
    align();
    out << "Number:" << exp->value << std::endl;
}

void PrintVisitor::visit(SubstractExpression* exp)
{
    align();
    out << "Sub:" << std::endl;

    ++alignment;
    exp->first->accept(this);
    --alignment;

    ++alignment;
    exp->second->accept(this);
    --alignment;
}
