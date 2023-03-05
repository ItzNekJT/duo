#include <duo.h>

#include <string.h>
#include <stdlib.h>

extern void set_input_string(const char * _string);
extern void end_lexical_scan();
extern int yyparse();

extern int yyerrors;

extern uint8_t* yyoutput_data;
extern size_t yyoutput_size;

void* duoC_alloc(size_t _size) {
    return malloc(_size);
}

void* duoC_realloc(void* _ptr, size_t _size) {
    return realloc(_ptr, _size);
}

void duoC_dealloc(void* _ptr) {
    free(_ptr);
}

duoT_base* duoC_call(duoT_base* _base, duoT_base** _args, size_t _nargs) {
    return _base->bs_type->tp_call(_base, _args, _nargs);
}

void duoC_execute(const uint8_t* _code, duoT_table* _scope) {
    duoT_base* stack[256] = {0};

    const uint8_t* pc = _code;
    
    duoT_base** sp = stack;

    bool running = true;

    while (running) {
        switch (*pc++) {
            case DUO_OPCODE_PUSH_IDENT: {
                size_t hash = *(uint32_t*) pc;

                *++sp = (duoT_base*)
                    duoC_table_search(_scope, hash);
                
                pc += 4;
            } break;

            case DUO_OPCODE_PUSH_INT: {
                *++sp = (duoT_base*)
                    duoC_int_create(*(int*) pc);
                
                pc += 4;
            } break;

            case DUO_OPCODE_PUSH_FLOAT: {
                *++sp = (duoT_base*)
                    duoC_float_create(*(float*) pc);
                
                pc += 4;
            } break;

            case DUO_OPCODE_PUSH_STRING: {
                size_t size = strlen((const char*) pc);

                *++sp = (duoT_base*)
                    duoC_string_create((const char*) pc, size);
                
                pc += size + 1;
            } break;

            case DUO_OPCODE_POP: {
                --sp;
            } break;

            case DUO_OPCODE_CALL: {
                size_t size = *(uint8_t*) pc;

                sp -= size;
                *sp = duoC_call(*sp, sp + 1, size);

                memset(sp + 1, 0, size*sizeof(duoT_base*));

                pc += 1;
            } break;
        }
    }
}

uint8_t* duoC_compile(const char* _source) {
    yyerrors = 0;

    yyoutput_data = NULL;
    yyoutput_size = 0;

    set_input_string(_source);
    yyparse();
    end_lexical_scan();

    if (yyerrors) {
        return NULL;
    }

    return yyoutput_data;
}

size_t duoC_hash(const void* _data, size_t _size) {
    size_t hash = 0x811c9dc5;

    for (size_t i = 0; i < _size; ++i) {
        hash ^= ((const char *) _data)[i];
        hash *= 0x01000193;
    }

    return hash;
}