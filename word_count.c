#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
    FILE *fp = stdin;
    char line[MAX_LINE_LENGTH];
    int lines = 0, chars = 0, words = 0, counter = 0;

    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "No file %s\n", argv[1]);
            return 1;
        }
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
        chars++;
            if (isspace(line[i]) || line[i] == '\n') {
        if (counter) {
               words++;
                    counter = 0;
                }
            } else {
                counter = 1;
            }
        }
        if (counter) {
                   words++;
            counter = 0;
        }
    }

    if (chars > 0) {
        lines = 1;
    }

    printf("%d\t%d\t%d\n", lines, words, chars);

    if (fp != stdin) {
        fclose(fp);
    }

    return 0;
}
