#pragma once

#include <duo/base.h>
#include <duo/opcode.h>

extern void* duoC_alloc(size_t _size);
extern void* duoC_realloc(void* _ptr, size_t _size);
extern void duoC_dealloc(void* _ptr);

extern duoT_base* duoC_call(duoT_base* _base, duoT_base** _args, size_t _nargs);

extern void duoC_execute(const uint8_t* _code, duoT_table* _scope);
extern uint8_t* duoC_compile(const char* _source);

extern size_t duoC_hash(const void* _data, size_t _size);
extern size_t duoC_strhash(const char* _src);

extern duoT_base* duoC_import(const char* _path);
extern duoT_base* duoC_export(const char* _path);

extern void duoC_print(duoT_base** _args, size_t _size);
extern void duoC_println(duoT_base** _args, size_t _size);

extern bool duoC_isinstance(duoT_base* _base, const duoT_type* _type);

extern void duoC_abort();

extern duoT_base* duoF_alloc(duoT_base** _args, size_t _size);
extern duoT_base* duoF_realloc(duoT_base** _args, size_t _size);
extern duoT_base* duoF_dealloc(duoT_base** _args, size_t _size);

extern duoT_base* duoF_call(duoT_base** _args, size_t _size);

extern duoT_base* duoF_execute(duoT_base** _args, size_t _size);
extern duoT_base* duoF_compile(duoT_base** _args, size_t _size);

extern duoT_base* duoF_hash(duoT_base** _args, size_t _size);

extern duoT_base* duoF_import(duoT_base** _args, size_t _size);
extern duoT_base* duoF_export(duoT_base** _args, size_t _size);

extern duoT_base* duoF_print(duoT_base** _args, size_t _size);
extern duoT_base* duoF_println(duoT_base** _args, size_t _size);

extern duoT_base* duoF_abort(duoT_base** _args, size_t _size);