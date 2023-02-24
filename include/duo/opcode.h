#pragma once

typedef unsigned char DUO_OPCODE;

enum {
    DUO_OPCODE_PUSH_IDENT,
    DUO_OPCODE_PUSH_INT,
    DUO_OPCODE_PUSH_FLOAT,
    DUO_OPCODE_PUSH_STRING,

    DUO_OPCODE_CALL,
};