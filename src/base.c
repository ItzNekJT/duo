#include <duo.h>

#include <string.h>
#include <stdlib.h>

const duoT_type duoG_basetype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "base",             /* tp_name */
    sizeof(duoT_base),  /* tp_size */

    NULL,               /* tp_call */
};