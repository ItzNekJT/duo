%{
    #include <duo.h>

    #include <string.h>
    #include <stdio.h>

    extern void yyerror(const char * _format, ...);
    extern int yylex();

    extern int yylineno;
    extern int yyerrors;

    extern uint8_t* yyoutput_data;
    extern size_t yyoutput_size;

    extern uint8_t yylstack[256];
    extern uint8_t* yyltop;
%}

%locations

%union {
    uint32_t mIDENT;
    int32_t mINT;
    float mFLOAT;
    char* mSTRING;

    struct YYCODE {
        size_t size;
        uint8_t* data;
    } mCODE;
}

%token <mIDENT>  tIDENT
%token <mINT>    tINT
%token <mFLOAT>  tFLOAT
%token <mSTRING> tSTRING
%token <mCODE>   tCODE

%token tCOMMA

%token tLPAREN
%token tRPAREN

%type <mCODE> program

%type <mCODE> statement
%type <mCODE> statements

%type <mCODE> expression
%type <mCODE> expressions

%%

program
    : statements {
        $$ = $1;

        yyoutput_data = $$.data;
        yyoutput_size = $$.size;
    }
    ;

statements
    : statements statement {
        $$.data = (uint8_t*)
            duoC_realloc($$.data, $$.size + $2.size);

        memcpy($$.data + $$.size, $2.data, $2.size);
        duoC_dealloc($2.data);

        $$.size += $2.size;
    }
    | {
        $$.size = 0;
        $$.data = NULL;
    }
    ;

statement
    : expression {
        $$ = $1;
    }
    ;

expressions
    : expressions tCOMMA expression {
        $$.data = (uint8_t*)
            duoC_realloc($$.data, $$.size + $3.size);
        
        memcpy($$.data + $$.size, $3.data, $3.size);
        duoC_dealloc($3.data);

        $$.size += $3.size;
    
        ++*yyltop;
    }
    | expression {
        $$ = $1;
    
        *++yyltop = 1;
    }
    | {
        $$.data = NULL;
        $$.size = 0;

        *++yyltop = 0;
    }
    ;

expression
    : tLPAREN expression tRPAREN {
        $$ = $2;
    }
    | expression tLPAREN expressions tRPAREN {
        $$.data = duoC_alloc($1.size + $3.size + 2);

        memcpy($$.data, $1.data, $1.size);
        duoC_dealloc($1.data);

        memcpy($$.data + $1.size, $3.data, $3.size);
        duoC_dealloc($3.data);

        $$.data[$1.size + $3.size] = DUO_OPCODE_CALL;
        $$.data[$1.size + $3.size + 1] = *yyltop--;

        $$.size = $1.size + $3.size + 2;
    }
    | tIDENT {
        $$.size = 5;
        $$.data = (uint8_t*)
            duoC_alloc(5);
        
        $$.data[0] = DUO_OPCODE_PUSH_IDENT;

        memcpy($$.data + 1, &$1, 4);
    }
    | tINT {
        $$.size = 5;
        $$.data = (uint8_t*)
            duoC_alloc(5);
        
        $$.data[0] = DUO_OPCODE_PUSH_INT;

        memcpy($$.data + 1, &$1, 4);
    }
    | tFLOAT {
        $$.size = 5;
        $$.data = (uint8_t*)
            duoC_alloc(5);
        
        $$.data[0] = DUO_OPCODE_PUSH_FLOAT;

        memcpy($$.data + 1, &$1, 4);
    }
    | tSTRING {
        $$.size = strlen($1) + 2;
        $$.data = (uint8_t*)
            duoC_alloc($$.size);
        
        $$.data[0] = DUO_OPCODE_PUSH_STRING;

        strcpy((char*) $$.data + 1, $1);
        duoC_dealloc($1);
    }
    | tCODE {
        $$ = $1;
    }
    ;

%%

int yyerrors = 0;

uint8_t* yyoutput_data = NULL;
size_t yyoutput_size = 0;

uint8_t yylstack[256] = {0};
uint8_t* yyltop = yylstack;

void yyerror(const char * _format, ...) {
    char buffer[256] = {0};

    yyerrors += 1;
    
    va_list va;

    va_start(va, _format);
    vsprintf(buffer, _format, va);
    va_end(va);

    fprintf(stderr, "duo: error: line %d: %s\n", yylineno, buffer);
}