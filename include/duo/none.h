#pragma once

#include <duo/base.h>

#define DUO_NONE ((duoT_base*) &duoG_none)

#define duoC_none_create() (DUO_NONE)

typedef struct duoT_none duoT_none;

struct duoT_none {
    DUO_BASE_HEAD;
};

extern const duoT_type duoG_nonetype;

extern duoT_none duoG_none;