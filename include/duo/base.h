#pragma once

#include <assert.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#define DUO_BASE_HEAD \
    const duoT_type* bs_type; \
    size_t bs_refs

#define duoC_base_type(_base) (((duoT_base*) (_base))->bs_type)

typedef struct duoT_base duoT_base;
typedef struct duoT_type duoT_type;

struct duoT_base {
    DUO_BASE_HEAD;
};

extern const duoT_type duoG_basetype;