#include <duo.h>

const duoT_type duoG_nonetype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "none",             /* tp_name */
    sizeof(duoT_none),  /* tp_size */

    NULL,               /* tp_call */
};

duoT_none duoG_none = {
    &duoG_nonetype,     /* bs_type */
    -1,                 /* bs_refs */
};