%{
    #include <duo.h>

    #include "parser.h"

    extern void yyerror(const char * _format, ...);
%}

%%

[ \t\n] {

}

"," {
    return tCOMMA;
}

"(" {
    return tLPAREN;
}

")" {
    return tRPAREN;
}

[_a-zA-Z]+ {
    yylval.mIDENT = duoC_hash(yytext, strlen(yytext));
    return tIDENT;
}

[0-9]+ {
    yylval.mINT = atoi(yytext);
    return tINT;
}

[0-9]+\.[0-9]+ {
    yylval.mFLOAT = atof(yytext);
    return tFLOAT;
}

\"(\\.|[^"\\])*\" {
    size_t len = strlen(yytext) - 2;

    yylval.mSTRING = malloc(len + 1);
    yylval.mSTRING[len] = 0;

    memcpy(yylval.mSTRING, yytext + 1, len);
    return tSTRING;
}

. {
    yyerror("undefined token \"%s\"", yytext);
}

%%

void set_input_string(const char * _string) {
    yy_scan_string(_string);
}

void end_lexical_scan() {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}

int yywrap() {
    return 1;
}