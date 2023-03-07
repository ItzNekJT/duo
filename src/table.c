#include <duo.h>

#include <string.h>

const duoT_type duoG_tabletype = {
    &duoG_typetype,     /* bs_type */
    -1,                 /* bs_refs */

    &duoG_basetype,     /* tp_base */

    "table",            /* tp_name */
    sizeof(duoT_table), /* tp_size */

    NULL,               /* tp_call */
};

duoT_table* duoC_table_create(size_t _size) {
    duoT_table* ptr = (duoT_table*)
        duoC_alloc(sizeof(duoT_table) + _size*sizeof(__tablenode*));
    
    ptr->bs_refs = 0;
    ptr->bs_type = &duoG_tabletype;

    ptr->m_size = _size;

    memset(ptr->m_data, 0, _size*sizeof(__tablenode*));

    return ptr;
}

void duoC_table_clear(duoT_table* _table) {
    for (size_t index = 0; index < _table->m_size; ++index) {
        __tablenode* node = _table->m_data[index];
        __tablenode* next = NULL;

        _table->m_data[index] = NULL;

        while (node) {
            next = node->m_next;
            duoC_dealloc(node);
            node = next;
        }
    }
}

void duoC_table_insert(duoT_table* _table, duoT_base* _data, size_t _hash) {
    size_t index = _hash % _table->m_size;

    __tablenode* node = _table->m_data[index];
    __tablenode* prev = NULL;

    while (node) {
        if (node->m_hash == _hash) {
            node->m_data = _data;
            return;
        }

        prev = node;
        node = node->m_next;
    }

    node = (__tablenode*)
        duoC_alloc(sizeof(__tablenode));

    node->m_next = NULL;
    node->m_data = _data;
    node->m_hash = _hash;

    if (prev) {
        prev->m_next = node;
    } else {
        _table->m_data[index] = node;
    }
}

void duoC_table_erase(duoT_table* _table, size_t _hash) {
    size_t index = _hash % _table->m_size;

    __tablenode* node = _table->m_data[index];
    __tablenode* prev = NULL;

    while (node) {
        if (node->m_hash == _hash) {
            if (prev) {
                prev->m_next = node->m_next;
            } else {
                _table->m_data[index] = node->m_next;
            }

            duoC_dealloc(node);
            return;
        }

        prev = node;
    }
}

duoT_base* duoC_table_search(duoT_table* _table, size_t _hash) {
    size_t index = _hash % _table->m_size;

    __tablenode* node = _table->m_data[index];

    while (node) {
        if (node->m_hash == _hash) {
            return node->m_data;
        }

        node = node->m_next;
    }

    return NULL;
}
