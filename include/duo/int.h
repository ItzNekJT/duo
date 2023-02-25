#pragma once

#include <duo/base.h>

#define duoC_int_data(_int) (((duoT_int*) (_int))->m_data)

typedef struct duoT_int duoT_int;

struct duoT_int {
    DUO_BASE_HEAD;

    int m_data;
};

extern const duoT_type duoG_inttype;

extern duoT_int* duoC_int_create(int _data);