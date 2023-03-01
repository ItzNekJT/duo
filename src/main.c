#include <duo.h>

#include <stdio.h>
#include <stdlib.h>

duoT_base* duoF_print(duoT_base** _args, size_t _nargs) {
    puts(duoC_string_data(_args[0]));
    return DUO_NONE_NONE;
}

int main(int argc, const char** argv) {

    const uint8_t code[] = {
        DUO_OPCODE_PUSH_IDENT, 0, 0, 0, 0,
        DUO_OPCODE_PUSH_STRING, 'H', 'i', ' ', 'D', 'u', 'o', '!', 0,
        DUO_OPCODE_CALL, 1
    };

    duoT_table* scope = duoC_table_create(8);
    duoT_function* print = duoC_function_create(duoF_print);

    duoC_table_insert(scope, print, 0);

    duoC_execute(code, scope);
    return EXIT_SUCCESS;
}