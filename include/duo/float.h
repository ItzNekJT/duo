#pragma once

#include <duo/base.h>

typedef struct duoT_float duoT_float;

struct duoT_float {
    DUO_BASE_HEAD;

    float m_data;
};

extern const duoT_type duoG_floattype;

extern duoT_float* duoC_float_create(float _data);