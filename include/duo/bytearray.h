#pragma once

#include <duo/base.h>

typedef struct duoT_bytearray duoT_bytearray;

struct duoT_bytearray {
    DUO_BASE_HEAD;

    size_t m_size;

    uint8_t m_data[0];
};

extern const duoT_type duoG_bytearraytype;

extern duoT_bytearray* duoC_bytearray_create(uint8_t* _data, size_t _size);
extern duoT_bytearray* duoC_bytearray_append(duoT_bytearray* _ba, uint8_t* _data, size_t _size);
extern duoT_bytearray* duoC_bytearray_push(duoT_bytearray* _ba, uint8_t _data);