#include <duo.h>

const duoT_type duoG_functiontype = {
    &duoG_typetype,             /* bs_type */
    -1,                         /* bs_refs */

    &duoG_basetype,             /* tp_base */

    "function",                 /* tp_name */
    sizeof(duoT_function),      /* tp_size */

    NULL,                       /* tp_attr */
    (void*) duoC_function_call, /* tp_call */
};

duoT_function* duoC_function_create(duoT_base* (*_data)
    (duoT_base** _args, size_t _nargs)) {
    duoT_function* ptr = (duoT_function*)
        duoC_alloc(sizeof(duoT_function));
    
    ptr->bs_type = &duoG_functiontype;

    ptr->m_data = _data;

    return ptr;
}

duoT_base* duoC_function_call(duoT_function* _function,
    duoT_base** _args, size_t _nargs) {
    return _function->m_data(_args, _nargs);
}