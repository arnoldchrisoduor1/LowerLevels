#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to check if pattern exists in a line
bool contains_pattern(const char *line, const char *pattern) {
    int line_len = strlen(line);
    int pattern_len = strlen(pattern);
    
    // If pattern is longer than line, it can't match
    if (pattern_len > line_len) {
        return false;
    }
    
    // Check each possible starting position in the line
    for (int i = 0; i <= line_len - pattern_len; i++) {
        int j;
        // Compare pattern with substring starting at position i
        for (j = 0; j < pattern_len; j++) {
            if (line[i + j] != pattern[j]) {
                break; // Characters don't match
            }
        }
        // If we completed the inner loop, pattern was found
        if (j == pattern_len) {
            return true;
        }
    }
    
    return false;
}

// Function to search for pattern in a file
void search_file(const char *filename, const char *pattern, bool show_filename) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int line_number = 0;
    
    // Open the file
    if (filename != NULL) {
        file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
            return;
        }
    } else {
        // If no filename provided, read from stdin
        file = stdin;
    }
    
    // Read file line by line
    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        
        // Remove newline character at the end
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        
        // Check if pattern exists in this line
        if (contains_pattern(line, pattern)) {
            // Print the matching line
            if (show_filename && filename != NULL) {
                printf("%s:", filename);
            }
            printf("%s\n", line);
        }
    }
    
    // Clean up
    if (line != NULL) {
        free(line);
    }
    if (filename != NULL) {
        fclose(file);
    }
}

// Function to display usage information
void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS] PATTERN [FILE...]\n", program_name);
    printf("Search for PATTERN in each FILE or standard input.\n");
    printf("Example: %s 'hello' file.txt\n", program_name);
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
}

int main(int argc, char *argv[]) {
    char *pattern = NULL;
    bool show_filename = false;
    
    // Parse command line arguments
    if (argc < 2) {
        fprintf(stderr, "Error: Pattern argument required\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Check for help option
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    }
    
    pattern = argv[1];
    
    // Determine if we should show filenames
    // Show filenames only when searching in multiple files
    if (argc > 3) {
        show_filename = true;
    }
    
    // Handle different cases based on number of arguments
    if (argc == 2) {
        // No filename provided, read from stdin
        search_file(NULL, pattern, false);
    } else {
        // Search in each provided file
        for (int i = 2; i < argc; i++) {
            if (argc > 3) {
                // Show filename when searching multiple files
                search_file(argv[i], pattern, true);
            } else {
                // Don't show filename for single file
                search_file(argv[i], pattern, false);
            }
        }
    }
    
    return 0;
}