#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Open file or set to read from stdin
int openFile(int argc, char *argv[], FILE **fp) {
    if (argc > 1) {
        *fp = fopen(argv[1], "r");
        if (*fp == NULL) {
            perror("Can't open file");
            return 1;
        }
    } else {
       *fp = stdin;
    }
    return 0;
}

// Print unique lines from file or stdin
int printLine(FILE *fp) {
    char *line = NULL;
    char *prevLine = NULL;
    size_t length = 0;
    ssize_t read;

    while ((read = getline(&line, &length, fp)) != -1) {
        if (prevLine == NULL || strcmp(line, prevLine) != 0) {
            printf("%s", line);
            free(prevLine);
            prevLine = strdup(line);
            if (prevLine == NULL) {
                perror("error");
                free(line);
                return 1;
            }
        }
    }

    free(line);
    free(prevLine);
    return 0;
}

// Main function: handles file operations
int main(int argc, char *argv[]) {
    FILE *fp;
    if (openFile(argc, argv, &fp) != 0) {
        return 1;
    }
   printLine(fp);

    if (fp != stdin) {
        fclose(fp);
    }

    return 0;
}
