#include <duo.h>

const duoT_type duoG_floattype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "float",             /* tp_name */
    sizeof(duoT_float),  /* tp_size */

    NULL,               /* tp_call */
};

duoT_float* duoC_float_create(float _data) {
    duoT_float* ptr = (duoT_float*)
        duoC_alloc(sizeof(duoT_float));
    
    ptr->bs_type = &duoG_floattype;
    ptr->bs_refs = 0;
 
    ptr->m_data = _data;

    return ptr;
}