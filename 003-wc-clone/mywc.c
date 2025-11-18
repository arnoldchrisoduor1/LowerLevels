#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int c; // int because fgetc returns int.

    if (argc < 2) {
        printf("Usage: %s <filename\n>", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: cannot open file %s\n", argv[1]);
        return 1;
    }

    // Read file character by character.
    while((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    fclose(fp);
    return 0;

}