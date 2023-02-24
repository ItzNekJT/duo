#include <duo.h>

const duoT_type duoG_booltype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "bool",             /* tp_name */
    sizeof(duoT_bool),  /* tp_size */

    NULL,               /* tp_attr */
    NULL,               /* tp_call */
};

const duoT_bool duoG_truebool = {
    &duoG_booltype, /* bs_type */
    -1,             /* bs_refs */

    1,              /* m_data */
};

const duoT_bool duoG_falsebool = {
    &duoG_booltype, /* bs_type */
    -1,             /* bs_refs */

    0,              /* m_data */
};