#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void count_file(FILE *fp, long *lines, long *words, long *chars) {
    int c;
    int in_word = 0;
    
    *lines = *words = *chars = 0;
    
    while ((c = fgetc(fp)) != EOF) {
        (*chars)++;
        
        if (c == '\n') {
            (*lines)++;
        }
        
        if (isspace(c)) {
            in_word = 0;
        } else {
            if (!in_word) {
                (*words)++;
                in_word = 1;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    long total_lines = 0, total_words = 0, total_chars = 0;
    int i;
    int use_stdin = 0;
    
    // If no arguments, we'll use stdin
    if (argc == 1) {
        use_stdin = 1;
    }
    
    // Check if we have only "-" as argument
    if (argc == 2 && strcmp(argv[1], "-") == 0) {
        use_stdin = 1;
        argc = 1; // Trick to make it behave like no arguments
    }
    
    if (use_stdin) {
        long lines, words, chars;
        count_file(stdin, &lines, &words, &chars);
        printf("%ld %ld %ld\n", lines, words, chars);
        return 0;
    }
    
    // Process each file
    for (i = 1; i < argc; i++) {
        long lines, words, chars;
        
        if (strcmp(argv[i], "-") == 0) {
            count_file(stdin, &lines, &words, &chars);
        } else {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "mywc: %s: No such file\n", argv[i]);
                continue;
            }
            count_file(fp, &lines, &words, &chars);
            fclose(fp);
        }
        
        printf("%ld %ld %ld %s\n", lines, words, chars, argv[i]);
        
        total_lines += lines;
        total_words += words;
        total_chars += chars;
    }
    
    if (argc > 2) {
        printf("%ld %ld %ld total\n", total_lines, total_words, total_chars);
    }
    
    return 0;
}