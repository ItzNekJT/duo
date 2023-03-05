#include <duo.h>

#include <stdio.h>
#include <stdlib.h>

duoT_base* duoF_print(duoT_base** _args, size_t _nargs) {
    puts(duoC_string_data(_args[0]));
    return DUO_NONE_NONE;
}

int main(int argc, const char** argv) {

    const char source[] = "print(\"Hi DUO!\")";

    const uint8_t* code = duoC_compile(source);

    duoT_table* scope = duoC_table_create(8);
    duoT_function* print = duoC_function_create(duoF_print);

    duoC_table_insert(scope, print, duoC_hash("print", 5));

    duoC_execute(code, scope);
    return EXIT_SUCCESS;
}