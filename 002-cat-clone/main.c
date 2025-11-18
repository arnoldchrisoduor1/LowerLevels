/*
* IMPLEMENTATIONS
* Read one or many files
* Print their contents to stdout (terminal)
* If no file is passed, read from stdin (keyboard input).
* Handle errors (file not found)
* work with text and binary.
* concatenate files by printing them sequentially.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // read the filename from command
    const char filename = argv[1];

    // opening the file.
    FILE *fp = fopen(filename, "r");

    // reading the file into a buffer.
    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        if (fwrite(buffer, 1, bytes, stdout) != bytes) {
            // handle write error.
            perror("Write error");
            break;
        }
    }
    if (ferror(fp)) {
        perror("Read error");
    }

    // Closing the file.
    fclose(fp);

    // printing errors to stderr
    fprintf(stderr, "cat: cannot open %s\n", filename);

}