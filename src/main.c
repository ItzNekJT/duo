#include <duo.h>

#include <stdio.h>
#include <stdlib.h>

void set_input_string(const char* data);
void end_lexical_scan();
int yyparse();

int main(int argc, const char ** argv) {
    // if (argc == 1) {
    //     fprintf(stderr, "duo: error: usage %s <file>\n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    // const char* path = argv[1];

    const char* path = "main.duo";

    FILE * file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "duo: error: cannot open file \'%s\'\n", path);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*) malloc(size + 1);
    fread(data, 1, size, file);

    data[size] = 0;

    fclose(file);

    set_input_string(data);
    int e = yyparse();
    end_lexical_scan();

    if (e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}