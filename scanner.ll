%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hpp"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  yy::parser::symbol_type make_number(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}


id     [a-zA-Z][a-zA-Z_0-9]*
int    [0-9]+
blank  [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

"+"        return yy::parser::make_PLUS       	 (loc);
"-"        return yy::parser::make_MINUS       	 (loc);
"*"        return yy::parser::make_STAR      	 (loc);
"/"        return yy::parser::make_SLASH     	 (loc);
"("        return yy::parser::make_LPAREN   	 (loc);
")"        return yy::parser::make_RPAREN        (loc);
"{"        return yy::parser::make_LBRACKET      (loc);
"}"        return yy::parser::make_RBRACKET 	 (loc);
"="        return yy::parser::make_ASSIGN        (loc);
"=="       return yy::parser::make_EQUAL         (loc);
"!="       return yy::parser::make_NOT_EQUAL     (loc);
"<"        return yy::parser::make_LOWER         (loc);
">"        return yy::parser::make_GREATER       (loc);
"<="       return yy::parser::make_LOWER_OR_EQ   (loc);
">="       return yy::parser::make_GREATER_OR_EQ (loc);

"def"      return yy::parser::make_DEF   (loc);
"main"     return yy::parser::make_MAIN  (loc);
"Print"    return yy::parser::make_PRINT (loc);
"if"       return yy::parser::make_IF    (loc);
"else"     return yy::parser::make_ELSE  (loc);
"while"    return yy::parser::make_WHILE (loc);
"var"      return yy::parser::make_VAR   (loc);
"int"      return yy::parser::make_INT   (loc);

\n+        loc.lines(yyleng); loc.step();
{int}      return make_number(yytext, loc);
{blank}+   loc.step();
{id}       return yy::parser::make_IDENTIFIER(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_EOF(loc);
%%

yy::parser::symbol_type make_number(const std::string &s, const yy::parser::location_type& loc) 
{
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}
