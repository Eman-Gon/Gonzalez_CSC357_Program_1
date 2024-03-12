#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
    FILE *fp = stdin;
    char line[MAX_LINE_LENGTH];
    char prevLine[MAX_LINE_LENGTH] = "";

    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
        fprintf(stderr, "Can't open file: %s\n", argv[1]);
        return 1;
        }
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strcmp(line, prevLine) != 0) {
            printf("%s", line);
            strcpy(prevLine, line);
        }
    }

    if (fp != stdin) {
        fclose(fp);
    }
            return 0;
}