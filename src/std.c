#include <duo.h>

#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include <dlfcn.h>

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

    duoT_base* bs = NULL;

    while (running) {
        bs = NULL;

        switch (*pc++) {
            case DUO_OPCODE_PUSH_IDENT: {
                size_t hash = *(uint32_t*) pc;

                bs = (duoT_base*)
                    duoC_table_search(_scope, hash);
                
                assert(bs != NULL);
                *++sp = bs;
            
                pc += 4;
            } break;

            case DUO_OPCODE_PUSH_INT: {
                bs = (duoT_base*)
                    duoC_int_create(*(int*) pc);
                
                assert(bs != NULL);
                *++sp = bs;
                
                pc += 4;
            } break;

            case DUO_OPCODE_PUSH_FLOAT: {
                bs = (duoT_base*)
                    duoC_float_create(*(float*) pc);
                
                assert(bs != NULL);
                *++sp = bs;
                
                pc += 4;
            } break;

            case DUO_OPCODE_PUSH_STRING: {
                size_t size = strlen((const char*) pc);

                bs = (duoT_base*)
                    duoC_string_create((const char*) pc, size);
                
                assert(bs != NULL);
                *++sp = bs;

                pc += size + 1;
            } break;

            case DUO_OPCODE_POP: {
                --sp;
            } break;

            case DUO_OPCODE_CALL: {
                size_t size = *(uint8_t*) pc;

                sp -= size;

                assert(*sp != NULL);

                bs = (duoT_base*)
                    duoC_call(*sp, sp + 1, size);
                
                assert(bs != NULL);
                *sp = bs;

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

size_t duoC_strhash(const char* _src) {
    return duoC_hash(_src, strlen(_src));
}

duoT_base* duoC_import(const char* _path) {
    void* lib = dlopen(_path, RTLD_LAZY);
    if (!lib) {
        return NULL;
    }

    void* sym = dlsym(lib, "duoC_export");
    if (!sym) {
        return NULL;
    }
    
    return ((duoT_base* (*)(const char*)) sym)(_path);
}

duoT_base* duoC_export(const char* _path) {
    duoT_table* table = duoC_table_create(32);

    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_alloc), duoC_strhash("alloc"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_realloc), duoC_strhash("realloc"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_dealloc), duoC_strhash("dealloc"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_call), duoC_strhash("call"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_execute), duoC_strhash("execute"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_compile), duoC_strhash("compile"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_hash), duoC_strhash("hash"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_import), duoC_strhash("import"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_export), duoC_strhash("export"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_print), duoC_strhash("print"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_println), duoC_strhash("println"));
    duoC_table_insert(table, (duoT_base*) duoC_function_create(duoF_abort), duoC_strhash("abort"));

    return table;
}

void duoC_print(duoT_base** _args, size_t _size) {
    char buffer[32] = {0};

    for (size_t i = 0; i < _size; ++i) {
        duoT_base* bs = _args[i];

        if (duoC_isinstance(bs, &duoG_inttype)) {
            sprintf(buffer, "%d", duoC_int_data(bs));
        } else if (duoC_isinstance(bs, &duoG_floattype)) {
            sprintf(buffer, "%g", duoC_float_data(bs));
        } else if (duoC_isinstance(bs, &duoG_booltype)) {
            if (duoC_bool_data(bs)) {
                strcpy(buffer, "true");
            } else {
                strcpy(buffer, "false");
            }
        } else if (duoC_isinstance(bs, &duoG_nonetype)) {
            strcpy(buffer, "none");
        } else if (duoC_isinstance(bs, &duoG_stringtype)) {
            fputs(duoC_string_data(bs), stdout);
            buffer[0] = 0;
        } else {
            sprintf(buffer, "\"%s\": %p", bs->bs_type->tp_name, bs);
        }

        fputs(buffer, stdout);
    }
}

void duoC_println(duoT_base** _args, size_t _size) {
    duoC_print(_args, _size);
    fputc('\n', stdout);
}

bool duoC_isinstance(duoT_base* _base, const duoT_type* _type) {
    return duoC_type_after(_base->bs_type, _type);
}

void duoC_abort() {
    abort();
}

duoT_base* duoF_alloc(duoT_base** _args, size_t _size) {
    return DUO_NONE_NONE;
}

duoT_base* duoF_realloc(duoT_base** _args, size_t _size) {
    return DUO_NONE_NONE;
}

duoT_base* duoF_dealloc(duoT_base** _args, size_t _size) {
    return DUO_NONE_NONE;
}

duoT_base* duoF_call(duoT_base** _args, size_t _size) {
    return duoC_call(_args[0], _args + 1, _size);
}

duoT_base* duoF_execute(duoT_base** _args, size_t _size) {
    return DUO_NONE_NONE;
}

duoT_base* duoF_compile(duoT_base** _args, size_t _size) {
    return DUO_NONE_NONE;
}

duoT_base* duoF_hash(duoT_base** _args, size_t _size) {
    DUO_RETURN(duoC_int_create(duoC_hash(_args[0], _args[0]->bs_type->tp_size)));
}

duoT_base* duoF_import(duoT_base** _args, size_t _size) {
    return duoC_import(duoC_string_data(_args[0]));
}

duoT_base* duoF_export(duoT_base** _args, size_t _size) {
    return DUO_NONE_NONE;
}

duoT_base* duoF_print(duoT_base** _args, size_t _size) {
    duoC_print(_args, _size);
    return DUO_NONE_NONE;
}

duoT_base* duoF_println(duoT_base** _args, size_t _size) {
    duoC_println(_args, _size);
    return DUO_NONE_NONE;
}

duoT_base* duoF_abort(duoT_base** _args, size_t _size) {
    duoC_abort();
    return DUO_NONE_NONE;
}