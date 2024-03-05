#define _GNU_SOURCE
//fdd this line ixes comments
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int openFile(int argc, char *argv[], FILE **fp) {
    if (argc > 1) {
        *fp = fopen(argv[1], "r"); // Open file 
        if (*fp == NULL) {
            perror("Can't open file"); // Print error if file can't open
            return 1; // Return error
        }
    } else {
       *fp = stdin; // Use stin if no file
    }
    return 0; // returned well
}

int printLine(FILE *fp) {
    char *line = NULL; // line pointer to NULL
    char *prevLine = NULL; // previous line pointer to NULL
    size_t length = 0; // length for getline
    ssize_t read; // store read status

    while ((read = getline(&line, &length, fp)) != -1) { // Read lines until end of file
        if (prevLine == NULL || strcmp(line, prevLine) != 0) { // Check if line is different from before
            printf("%s", line); // Print line
            free(prevLine); // Free 
            prevLine = strdup(line); // Duplicate current line to prevLine
            if (prevLine == NULL) {
                perror("error"); // Print error if strdup fails
                free(line); // Free line before returning
                return 1; // Return 1 to indicate error
            }
        }
    }

    free(line); // Free line 
    free(prevLine); // Free prev line
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fp; // Declare FILE pointer
    if (openFile(argc, argv, &fp) != 0) { // Open file
        return 1; // Return 1 if file cannot be opened
    }
   printLine(fp);

    if (fp != stdin) {
        fclose(fp); // Close file if not stdin
    }

    return 0; // works
}
