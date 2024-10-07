%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <utility>

    #include "nodes.hpp"

    /* Forward declaration of classes in order to disable cyclic dependencies */
    class Scanner;
    class Driver;
}


%define parse.trace
%define parse.error verbose

%code {
    #include "location.hh"
    #include "driver.hpp"

    /* Redefine parser to use our function from scanner */
    static yy::parser::symbol_type yylex(Scanner &scanner, Driver &driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver  &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver  &driver }

%locations

%define api.token.prefix {TOK_}

%token
    EOF 0           "end of file"
    ASSIGN          "="
    MINUS           "-"
    PLUS            "+"
    STAR            "*"
    SLASH           "/"
    LPAREN          "("
    RPAREN          ")"
    POW             "**"
    EQUAL           "=="
    NOT_EQUAL        "!="
    LOWER           "<"
    GREATER         ">"
    LOWER_OR_EQ     "<="
    GREATER_OR_EQ   ">="
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER             "number"
%token       DEF                "def"
%token       MAIN               "main"
%token       LBRACKET           "{"
%token       RBRACKET           "}"
%token       INT                "int"
%token       VAR                "var"
%token       PRINT    			"Print"
%token       IF         		"if"
%token       ELSE       		"else"
%token       WHILE        		"while"

%nterm <std::shared_ptr<Expression>> 	exp
%nterm <std::shared_ptr<Assignment>> 	assignment
%nterm <std::shared_ptr<StatementList>> statements
%nterm <std::shared_ptr<Program>> 		main_def
%nterm <std::shared_ptr<Program>> 		block
%nterm <std::shared_ptr<Program>> 		unit
%nterm <std::shared_ptr<IfCondition>> 	condition
%nterm <std::shared_ptr<Print>> 		print_statement
%nterm <std::shared_ptr<IfStatement>> 	if_statement
%nterm <std::shared_ptr<Declaration>> 	declaration
%nterm <std::shared_ptr<WhileStatement>> 	while_statement

%%

%left "+" "-";
%left "*" "/";
%right "**";

%start unit;

unit: main_def { driver.program = $1; }

main_def: "def" "main" "(" ")" "{" block "}" { $$ = $6; }

block: statements { $$ = std::make_shared<Program>($1); };

statements:
    %empty { $$ =  std::make_shared<StatementList>(); }
    | statements assignment      { $1->AddStatement($2); $$ = $1; }
    | statements print_statement { $1->AddStatement($2); $$ = $1; }
    | statements if_statement    { $1->AddStatement($2); $$ = $1; }
    | statements declaration     { $1->AddStatement($2); $$ = $1; }
    | statements while_statement { $1->AddStatement($2); $$ = $1; };

print_statement: "Print" "(" exp ")" { $$ = std::make_shared<Print> ($3); };

if_statement: "if" "(" condition ")" "{" statements "}" "else" "{" statements "}" 
					{ $$ = std::make_shared<IfStatement>($3, $6, $10); }
    		| "if" "(" condition ")" "{" statements "}" 
					{ $$ = std::make_shared<IfStatement>($3, $6, nullptr); };

while_statement: "while" "(" condition ")" "{" statements "}" 
		{ $$ = std::make_shared<WhileStatement>($3, $6); };
    
assignment: "identifier" "=" exp { $$ = std::make_shared<Assignment>($1, $3); };

declaration: "var" "identifier" { $$ = std::make_shared<Declaration>($2); };

condition : exp "==" exp { $$ = std::make_shared<IfCondition>($1, $3, CompareOperators::EQUAL);}
    	  | exp "!=" exp { $$ = std::make_shared<IfCondition>($1, $3, CompareOperators::NOT_EQUAL);}
    	  | exp "<" exp  { $$ = std::make_shared<IfCondition>($1, $3, CompareOperators::LOWER);}
    	  | exp ">" exp  { $$ = std::make_shared<IfCondition>($1, $3, CompareOperators::GREATER);}
    	  | exp "<=" exp { $$ = std::make_shared<IfCondition>($1, $3, CompareOperators::LOWER_OR_EQ);}
    	  | exp ">=" exp { $$ = std::make_shared<IfCondition>($1, $3, CompareOperators::GREATER_OR_EQ);};

exp:
    "number" {$$ = std::make_shared<NumberExpression>($1); }
    | "identifier" {$$ = std::make_shared<IdentExpression>($1); }
    | exp "+" exp  { $$ = std::make_shared<AddExpression>($1, $3); }
    | exp "-" exp  { $$ = std::make_shared<SubstractExpression>($1, $3); }
    | exp "*" exp  { $$ = std::make_shared<MulExpression>($1, $3); }
    | exp "/" exp  { $$ = std::make_shared<DivExpression>($1, $3); }
    | "(" exp ")"  { $$ = $2; };

%%

void
yy::parser::error(const location_type& loc, const std::string& msg)
{
  std::cerr << loc << ": " << msg << '\n';
}
