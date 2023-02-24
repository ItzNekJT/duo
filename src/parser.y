%{
    #include <duo.h>

    #include <stddef.h>
    #include <stdarg.h>

    #include <stdio.h>
    #include <stdlib.h>

    extern void yyerror(const char* _format, ...);
    extern int yylex();

    extern int yylineno;
%}

%locations

%token tIDENT
%token tINT
%token tFLOAT
%token tSTRING

%type program
%type expressions
%type expression

%%

program
    : expressions   { ; }
    ;

expressions
    : expressions expression    { ; }
    |                           { ; }
    ;

expression
    : tIDENT    { ; }
    | tINT      { ; }
    | tFLOAT    { ; }
    | tSTRING   { ; }

    ;

%%

void yyerror(const char* _format, ...) {
    va_list va;

    fprintf(stderr, "duo: error: line %d: ", yylineno);

    va_start(va, _format);
    vfprintf(stderr, _format, va);
    va_end(va);

    fprintf(stderr, "\n");
}