#include <duo.h>

#include <string.h>

const duoT_type duoG_stringtype = {
    &duoG_typetype,         /* bs_type */
    -1,                     /* bs_refs */

    &duoG_basetype,         /* tp_base */

    "string",               /* tp_name */
    sizeof(duoT_string),    /* tp_size */

    NULL,                   /* tp_call */
};

duoT_string* duoC_string_create(const char* _data, size_t _size) {
    duoT_string* ptr = (duoT_string*)
        duoC_alloc(sizeof(duoT_string) + _size + 1);

    ptr->bs_refs = 0;
    ptr->bs_type = &duoG_stringtype;

    memcpy(ptr->m_data, _data, _size);

    ptr->m_data[_size] = 0;

    return ptr;
}