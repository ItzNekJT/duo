#pragma once

#include <duo/base.h>

#define duoC_incref(_base) (++((duoT_base*) (_base))->bs_refs)
#define duoC_decref(_base) (--((duoT_base*) (_base))->bs_refs)

extern duoT_base* duoC_call(duoT_base* _base, duoT_base** _args, size_t _nargs);

extern bool duoC_isinstance(duoT_base* _base, const duoT_type* _type);

extern void* duoC_alloc(size_t _size);
extern void* duoC_realloc(void* ptr, size_t _size);
extern void duoC_dealloc(void* ptr);

extern size_t duoC_hash(const void* _data, size_t _size);

extern void duoC_repeat(size_t _count, duoT_base* _base, duoT_base** _args, size_t _nargs);