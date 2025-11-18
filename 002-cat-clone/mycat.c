/* mycat.c
 * Minimal cat clone
 *
 * - Supports multiple files: ./mycat file1 file2 ...
 * - If no files provided, reads from stdin.
 * - If a filename is "-" it reads from stdin at that position.
 * - Binary-safe, uses a buffer.
 * - Prints error messages to stderr and returns non-zero if any file failed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 8192

/* copy_stream: copy from infile to stdout using a buffer.
 * infile must be an open FILE* (can be stdin).
 * Returns 0 on success, non-zero on error.
 */
static int copy_stream(FILE *infile, const char *name_for_err) {
    char buf[BUF_SIZE];
    size_t nread, nwritten;
    while ((nread = fread(buf, 1, sizeof(buf), infile)) > 0) {
        nwritten = fwrite(buf, 1, nread, stdout);
        if (nwritten < nread) {
            /* write error */
            fprintf(stderr, "mycat: write error while writing output: %s\n", strerror(errno));
            return 1;
        }
    }

    if (ferror(infile)) {
        fprintf(stderr, "mycat: error reading %s: %s\n", name_for_err, strerror(errno));
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int exit_status = 0;

    /* If no filenames provided, read from stdin */
    if (argc <= 1) {
        if (copy_stream(stdin, "stdin") != 0) exit_status = 1;
        return exit_status;
    }

    /* Iterate over each filename */
    int i;
    for (i = 1; i < argc; ++i) {
        const char *filename = argv[i];

        /* Convention: "-" means read from stdin */
        if (strcmp(filename, "-") == 0) {
            if (copy_stream(stdin, "stdin") != 0) exit_status = 1;
            continue;
        }

        FILE *fp = fopen(filename, "rb"); /* binary-safe */
        if (fp == NULL) {
            /* Print a message similar to real cat */
            fprintf(stderr, "mycat: %s: %s\n", filename, strerror(errno));
            exit_status = 1;
            continue; /* keep going with other files */
        }

        if (copy_stream(fp, filename) != 0) exit_status = 1;

        if (fclose(fp) != 0) {
            fprintf(stderr, "mycat: error closing %s: %s\n", filename, strerror(errno));
            exit_status = 1;
        }
    }

    return exit_status;
}
