#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

int isLoopKeyword(const char *buffer) {
    const char *keywords[] = {"for", "while", "do"};
    for (int i = 0; i < 3; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char buffer[BUFFER_SIZE];
    FILE* filePtr;

    filePtr = fopen("..\\news.c", "r"); // Adjust file path as necessary
    if (filePtr == NULL) {
        printf("Error opening the file.\n");
        return 1; 
    }

    int loop_count = 0;
    int nested_level = 0;
    int max_nested_level = 0;

    // Read file line by line
    while (fgets(buffer, BUFFER_SIZE, filePtr) != NULL) {
        char *ptr = buffer;
        
        while (*ptr) {
            // Count opening braces to determine nesting level
            if (*ptr == '{') {
                nested_level++;
                if (nested_level > max_nested_level) {
                    max_nested_level = nested_level;
                }
            } else if (*ptr == '}') {
                nested_level--;
            }

            // Check for loop keywords
            if (isalpha(*ptr)) {
                char keyword[10];
                int i = 0;
                while (isalpha(*ptr) || *ptr == '_') {
                    keyword[i++] = *ptr++;
                }
                keyword[i] = '\0';
                
                if (isLoopKeyword(keyword)) {
                    loop_count++;
                }
            } else {
                ptr++;
            }
        }
    }

    fclose(filePtr);

    printf("Total number of loops: %d\n", loop_count);
    printf("Maximum nesting level: %d\n", max_nested_level);

    return 0;
}
