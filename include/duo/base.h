#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define DUO_BASE_HEAD \
    const duoT_type* bs_type; \
    size_t bs_refs

typedef struct duoT_base duoT_base;
typedef struct duoT_type duoT_type;

struct duoT_base {
    DUO_BASE_HEAD;
};

extern const duoT_type duoG_basetype;

extern duoT_base* duoC_base_attr(duoT_base* _self, const char* _attr);
extern duoT_base* duoC_base_call(duoT_base* _self, duoT_base** _args, size_t _nargs);

extern bool duoC_isinstance(duoT_base* _base, duoT_type* _type);

extern void duoC_incref(duoT_base* _base);
extern void duoC_decref(duoT_base* _base);

extern void* duoC_alloc(size_t _size);
extern void* duoC_realloc(void* ptr, size_t size);
extern void duoC_dealloc(void* _ptr);