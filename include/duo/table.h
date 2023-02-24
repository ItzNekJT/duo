#pragma once

#include <duo/base.h>

#include <stddef.h>

typedef struct __tablenode __tablenode;

struct __tablenode {
    __tablenode* m_next;

    duoT_base* m_data;
    size_t m_hash;
};

typedef struct duoT_table duoT_table;

struct duoT_table {
    DUO_BASE_HEAD;

    size_t m_size;
    __tablenode* m_data[0];
};

extern const duoT_type duoG_tabletype;

extern duoT_table* duoC_table_create(size_t _size);

extern void duoC_table_clear(duoT_table* _table);

extern void duoC_table_insert(duoT_table* _table, duoT_base* _data, size_t _hash);
extern void duoC_table_erase(duoT_table* _table, size_t _hash);
extern duoT_base* duoC_table_search(duoT_table* _table, size_t _hash);