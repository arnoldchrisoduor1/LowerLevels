#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_file(FILE *fp, long *lines, long *words, long *chars) {
    int c;
    int in_word = 0;
    
    *lines = *words = *chars = 0;  // Initialize counters
    
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
    
    // If no arguments, read from stdin
    if (argc == 1) {
        long lines, words, chars;
        count_file(stdin, &lines, &words, &chars);
        printf("%ld %ld %ld\n", lines, words, chars);
        return 0;
    }
    
    // Process each file
    for (i = 1; i < argc; i++) {
        long lines, words, chars;
        
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("mywc: %s: No such file\n", argv[i]);
            continue;  // Skip to next file
        }
        
        count_file(fp, &lines, &words, &chars);
        fclose(fp);
        
        printf("%ld %ld %ld %s\n", lines, words, chars, argv[i]);
        
        // Add to totals
        total_lines += lines;
        total_words += words;
        total_chars += chars;
    }
    
    // Print totals if multiple files
    if (argc > 2) {
        printf("%ld %ld %ld total\n", total_lines, total_words, total_chars);
    }
    
    return 0;
}