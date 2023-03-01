#pragma once

#include <duo/base.h>
#include <duo/opcode.h>

void* duoC_alloc(size_t _size);
void* duoC_realloc(void* _ptr, size_t _size);
void duoC_dealloc(void* _ptr);

duoT_base* duoC_call(duoT_base* _base, duoT_base** _args, size_t _nargs);

void duoC_execute(const uint8_t* _code, duoT_table* _scope);
const uint8_t* duoC_compile(const char* _source);