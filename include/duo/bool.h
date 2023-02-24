#pragma once

#include <duo/base.h>

#include <stdbool.h>

#define DUO_TRUE  ((duoT_base*) &duoG_truebool)
#define DUO_FALSE ((duoT_base*) &duoG_falsebool)

#define duoC_bool_create(_data) ((_data) ? (DUO_TRUE) : (DUO_FALSE))

typedef struct duoT_bool duoT_bool;

struct duoT_bool {
    DUO_BASE_HEAD;

    bool m_data;
};

extern const duoT_type duoG_booltype;

extern const duoT_bool duoG_truebool;
extern const duoT_bool duoG_falsebool;
