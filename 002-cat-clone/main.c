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
#include <string.h>
#include <errno.h>

#define BUF_SIZE 8192

/*
* copy_stream: copy from infile to stdout using buffer.
* infile must be an open FILE*
* returns 0 on success, non-zero on error.
*
*/

static int copy_stream(FILE *infile, const char *name_for_err) {
    char buf[BUF_SIZE];
    size_t nread, nwritten;
    while((nread = fread(buf, 1, sizeof(buf), infile)) > 0) {
        nwritten = fwrite(buf, 1, nread, stdout);
        if(nwritten < nread) {
            // a write error.
            fprintf(stderr, "mycat: write error while writing output: %s\n", strerror(errno));
            return 1;
        }
    }

    if(ferror(infile)) {
        fprintf(stderr, "mycat: error reading %s: %s\n", name_for_err, strerror(errno));
        return 1;
    }
    return 0;
}