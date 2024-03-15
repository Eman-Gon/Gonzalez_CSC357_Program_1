#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *line = NULL; // Pointer to the buffer getline will allocate 
    FILE *fp = NULL; // File pointer for reading input
    size_t len = 0; // Length of the buffer, initially 0
    ssize_t read; // Number of characters read by getline//checkignif its signed
    char *prevLine = NULL; // Store the previous line for comparison

    if (argc > 1) {
        fp = fopen(argv[1], "r"); // Open the file for reading // Task1
        if (fp == NULL) {
            perror("error"); // Print an error message if the file cannot be opened
           return 1; // Exit with a failure status
        }
    } else {
        fp = stdin; // No file specified, read from stdin // Task1
    }

    while ((read = getline(&line, &len, fp)) != -1) {//using ssize_t because it has a negative value // Task1//malloc becasye its inside getline
        if (prevLine == NULL || strcmp(line, prevLine) != 0) {
            printf("%s", line); // Print the line if it's unique
            free(prevLine); // Free the memory allocated for the previous line
            prevLine = line; // Duplicate the current line to prevLine for next iteration's comparison
        }//working with pinters direclty working with the heap//no reason to have there
    }

    free(line); // Free the memory allocated for the current line
    free(prevLine); // Free the memory allocated for the previous line
    if (fp != stdin) {
        fclose(fp); // Close the file if we opened one // Task1
    }

    return 0; // Successful execution
}
