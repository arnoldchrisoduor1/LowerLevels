#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int c; // int because fgetc returns int.
    long lines = 0, words = 0, chars = 0;
    int in_word = 0;

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
        chars ++; // counting every character.

        if (c == '\n') {
            lines++;
        }

        // now for the word counting logic.
        if (isspace(c)) {
            in_word = 0; // to show we are in a white space not in a word
        } else {
            // if we were not in a word and now in a non-whitespace (first letter after whitespace)
            if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }

    printf("%ld %ld %ld %s\n", lines, words, chars, argv[1]);
    fclose(fp);
    return 0;

}