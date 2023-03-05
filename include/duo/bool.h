#pragma once

#include <duo/base.h>

#include <stdbool.h>

#define DUO_BOOL_TRUE (&duoG_true)
#define DUO_BOOL_FALSE (&duoG_false)

#define duoC_bool_create(_data) ((_data) ? (DUO_BOOL_TRUE) : (DUO_BOOL_FALSE))

#define duoC_bool_data(_bool) (((duoT_bool*) (_bool))->m_data)

typedef struct duoT_bool duoT_bool;

struct duoT_bool {
    DUO_BASE_HEAD;

    bool m_data;
};

extern const duoT_type duoG_booltype;

extern const duoT_bool duoG_true;
extern const duoT_bool duoG_false;