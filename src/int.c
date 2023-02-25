#include <duo.h>

const duoT_type duoG_inttype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "int",             /* tp_name */
    sizeof(duoT_int),  /* tp_size */

    NULL,               /* tp_call */
};

duoT_int* duoC_int_create(int _data) {
    duoT_int* ptr = (duoT_int*)
        duoC_alloc(sizeof(duoT_int));
    
    ptr->bs_type = &duoG_inttype;
    ptr->bs_refs = 0;

    ptr->m_data = _data;

    return ptr;
}