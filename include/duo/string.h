#pragma once

#include <duo/base.h>

#define duoC_string_data(_string) (((duoT_string*) (_string))->m_data)
#define duoC_string_size(_string) (strlen(((duoT_string*) (_string))->m_data))

typedef struct duoT_string duoT_string;

struct duoT_string {
    DUO_BASE_HEAD;

    char m_data[0];
};

extern const duoT_type duoG_stringtype;

extern duoT_string* duoC_string_create(const char* _data, size_t _size);