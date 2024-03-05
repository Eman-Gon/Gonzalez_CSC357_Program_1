#include <stdio.h>
#include <ctype.h>

int main() {
    char line[255]; 
    FILE *fp = fopen("test.txt", "r"); // Open file.
    int lines = 0, chars = 0, words = 0, counter = 0; // Counters for lines, characters, words, and word

    if (fp == NULL) {
        printf("error\n"); // File open error.
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) { // Read lines.
        for (int i = 0; line[i] != '\0'; i++) { // Iterate characters.
            chars++; // Count characters.
            if (isspace(line[i]) || line[i] == '\n') { 
                if (counter) { 
                    words++; // Increment word count.
                    counter = 0; // Reset word
                }
            } else {
                counter = 1; // Inside a word.
            }
        }
        if (counter) { 
            words++; 
            counter = 0;
        }
        lines++; // Count lines.
    }

    printf("%d\t%d\t%d\n", lines, words, chars);

    fclose(fp); // Close file.
    return 0;
}

