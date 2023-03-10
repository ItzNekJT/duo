#pragma once

#include <duo/base.h>

#include <stddef.h>

typedef struct duoT_type duoT_type;

struct duoT_type {
    DUO_BASE_HEAD;

    const duoT_type* tp_base;

    const char* tp_name;
    size_t tp_size;

    duoT_base* (*tp_call)(duoT_base* _self, duoT_base** _args, size_t _nargs);
};

extern const duoT_type duoG_typetype;

extern bool duoC_type_after(const duoT_type* _type, const duoT_type* _parent);