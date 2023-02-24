%{
    #include "parser.h"

    extern void yyerror(const char* _format, ...);
%}

%%

[ \t]+  { ; }

[_a-zA-Z]+ {
    return tIDENT;
}

[0-9]+ {
    return tINT;
}

[0-9]+\.[0-9]+ {
    return tFLOAT;
}

\"(\\.|[^"\\])*\" {
    return tSTRING;
}

. {
    yyerror("undefined token \"%s\"", yytext);
}

%%

void set_input_string(const char* data) {
    yy_scan_string(data);
}

void end_lexical_scan() {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}

int yywrap() {
    return 1;
}