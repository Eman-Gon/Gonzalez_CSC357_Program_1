#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int openFile(int argc, char *argv[], FILE **fp) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    *fp = fopen(argv[1], "r");
    if (*fp == NULL) {
        perror("Can't open file");
        return 1;
    }
    return 0;
}

int printLastTwoLines(FILE *fp) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *lastTwoLines[2] = {NULL, NULL};
    while ((nread = getline(&line, &len, fp)) != -1) {
        free(lastTwoLines[0]);
        lastTwoLines[0] = lastTwoLines[1];
        lastTwoLines[1] = strdup(line);
        if (lastTwoLines[1] == NULL) {
            perror("Failed to duplicate the line");
            free(line);
            return 1;
        }
    }
    if (lastTwoLines[0]) printf("%s", lastTwoLines[0]);
    if (lastTwoLines[1]) printf("%s", lastTwoLines[1]);
    free(line);
    free(lastTwoLines[0]);
    free(lastTwoLines[1]);
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    if (openFile(argc, argv, &fp) != 0) return 1;
    if (printLastTwoLines(fp) != 0) {
        fclose(fp);
        return 1;
    }
    if (fp != stdin) fclose(fp);
    return 0;
}

