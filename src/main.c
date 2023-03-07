#include <duo.h>

#include <stdio.h>

int main(int argc, const char** argv) {
    assert(argc == 2);

    FILE* file = fopen(argv[1], "rb");
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*) duoC_alloc(size + 1);
    data[size] = 0;

    fread(data, 1, size, file);
    fclose(file);

    uint8_t* code = duoC_compile(data);
    duoC_dealloc(data);

    if (!code) {
        return 1;
    }

    duoT_table* scope = (duoT_table*) duoC_export(NULL);

    duoC_execute(code, scope);
    duoC_dealloc(code);

    return 0;
}