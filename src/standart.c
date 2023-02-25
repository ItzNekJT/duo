#include <duo.h>

#include <string.h>

#include <stdlib.h>
#include <stdio.h>

duoT_base* duoC_call(duoT_base* _base, duoT_base** _args, size_t _nargs) {
    return _base->bs_type->tp_call(_base, _args, _nargs);
}

bool duoC_isinstance(duoT_base* _base, const duoT_type* _type) {
    return duoC_type_before(_base->bs_type, _type);
}

void* duoC_alloc(size_t _size) {
    return malloc(_size);
}

void* duoC_realloc(void* ptr, size_t _size) {
    return realloc(ptr, _size);
}

void duoC_dealloc(void* ptr) {
    free(ptr);
}

size_t duoC_hash(const void* _data, size_t _size) {
    const char* src = (const char*) _data;

    uint32_t hash = 0x811c9dc5;

    for (size_t i = 0; i < _size; ++i) {
        hash *= 0x01000193;
        hash ^= src[i];
    }

    return hash;
}

void duoC_repeat(size_t _count, duoT_base* _base, duoT_base** _args, size_t _nargs) {
    for (size_t i = 0; i < _count; ++i) {
        duoC_call(_base, _args, _nargs);
    }
}