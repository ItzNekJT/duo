#pragma once

#include <assert.h>

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