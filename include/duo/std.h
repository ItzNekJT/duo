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