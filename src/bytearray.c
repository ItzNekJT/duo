#include <duo.h>

#include <string.h>

const duoT_type duoG_bytearraytype = {
    &duoG_typetype,         /* bs_type */
    -1,                     /* bs_refs */

    &duoG_basetype,         /* tp_base */

    "bytearray",            /* tp_name */
    sizeof(duoT_bytearray), /* tp_size */

    NULL,                   /* tp_attr */
    NULL,                   /* tp_call */
};

duoT_bytearray* duoC_bytearray_create(uint8_t* _data, size_t _size) {
    duoT_bytearray* ptr = (duoT_bytearray*)
        duoC_alloc(sizeof(duoT_bytearray) + _size);
    
    ptr->bs_type = &duoG_bytearraytype;

    ptr->m_size = _size;

    memcpy(ptr->m_data, _data, _size);

    return ptr;
}

duoT_bytearray* duoC_bytearray_append(duoT_bytearray* _ba, uint8_t* _data, size_t _size) {
    size_t old_size = _ba->m_size;

    duoT_bytearray* ptr = (duoT_bytearray*)
        duoC_realloc(_ba, sizeof(duoT_bytearray) + old_size + _size);

    ptr->m_size = old_size + _size;

    memcpy(ptr->m_data + old_size, _data, _size);

    return ptr;
}

duoT_bytearray* duoC_bytearray_push(duoT_bytearray* _ba, uint8_t _data) {
    return duoC_bytearray_append(_ba, &_data, 1);
}
