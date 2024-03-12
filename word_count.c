#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>

int main() {
    char line[255]; 
    FILE *fp = fopen("test.txt", "r"); 
    int lines = 0, chars = 0, words = 0, counter = 0; 
    if (fp == NULL) {
        printf("error\n"); 
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) { 
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
        lines++; 
    }
    printf("%d\t%d\t%d\n", lines, words, chars);

    fclose(fp); 
    return 0;
}

