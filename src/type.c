#include <duo.h>

const duoT_type duoG_typetype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "type",             /* tp_name */
    sizeof(duoT_type),  /* tp_size */

    NULL,               /* tp_call */
};

bool duoC_type_before(const duoT_type* _type, const duoT_type* _parent) {
    if (_parent == &duoG_basetype) {
        return true;
    }

    while (_type != &duoG_basetype) {
        if (_type == _parent) {
            return true;
        }

        _type = _type->tp_base;
    }

    return false;
}