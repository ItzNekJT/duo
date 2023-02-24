#include <duo.h>

const duoT_type duoG_typetype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "type",             /* tp_name */
    sizeof(duoT_type),  /* tp_size */

    NULL,               /* tp_attr */
    NULL,               /* tp_call */
};