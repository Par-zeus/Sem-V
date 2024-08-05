#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];
    FILE* filePtr;
    
    
    filePtr = fopen("..\\stacks.c", "r");
    if (filePtr == NULL) {
        printf("Error opening the file.\n");
        return 1; 
    }
    
    // Counters for operations
    int push_count = 0;
    int pop_count = 0;
    int top_count = 0;

    
    while (fgets(buffer, BUFFER_SIZE, filePtr) != NULL) {
       
        if (strstr(buffer, "push") != NULL) {
            push_count++;
        }
        if (strstr(buffer, "pop") != NULL) {
            pop_count++;
        }
        if (strstr(buffer, "top") != NULL) {
            top_count++;
        }
    }

    fclose(filePtr); 

    printf("Total number of push operations: %d\n", push_count);
    printf("Total number of pop operations: %d\n", pop_count);
    printf("Total number of top operations: %d\n", top_count);

    return 0;
}
