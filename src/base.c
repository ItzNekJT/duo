#include <duo.h>

#include <string.h>
#include <stdlib.h>

const duoT_type duoG_basetype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "base",             /* tp_name */
    sizeof(duoT_base),  /* tp_size */

    duoC_base_attr,     /* tp_attr */
    duoC_base_call,     /* tp_call */
};

duoT_base* duoC_base_attr(duoT_base* _self, const char* _attr) {
    return NULL;
}

duoT_base* duoC_base_call(duoT_base* _self, duoT_base** _args, size_t _nargs) {
    return NULL;
}

bool duoC_isinstance(duoT_base* _base, duoT_type* _type) {
    if (_type == &duoG_basetype) {
        return true;
    }

    const duoT_type* type = _base->bs_type;

    while (type) {
        if (type == _type) {
            return true;
        }

        type = type->tp_base;
    }

    return false;
}

duoT_base* duoC_attr(duoT_base* _base, const char* _attr) {
    return _base->bs_type->tp_attr(_base, _attr);
}

void duoC_destruct(duoT_base* _base) {
    duoT_base* attr = duoC_attr(_base, "__destruct");
    if (attr) {
        duoC_function_call(attr, NULL, 0);
    }
}

void duoC_incref(duoT_base* _base) {
    ++_base->bs_refs;
}

void duoC_decref(duoT_base* _base) {
    if (_base->bs_refs) {
        --_base->bs_refs;
    } else {
        duoC_destruct(_base);
        duoC_dealloc(_base);
    }
}

void* duoC_alloc(size_t _size) {
    return malloc(_size);
}

void* duoC_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

void duoC_dealloc(void* _ptr) {
    free(_ptr);
}
