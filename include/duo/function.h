#pragma once

#include <duo/base.h>

#define DUO_RETURN(_base) return (duoT_base*) (_base)

typedef struct duoT_function duoT_function;

struct duoT_function {
    DUO_BASE_HEAD;

    duoT_base* (*m_data)(duoT_base** _args, size_t _nargs);
};

extern const duoT_type duoG_functiontype;

extern duoT_function* duoC_function_create(duoT_base* (*_data)
    (duoT_base** _args, size_t _nargs));

extern duoT_base* duoC_function_call(duoT_function* _function,
    duoT_base** _args, size_t _nargs);