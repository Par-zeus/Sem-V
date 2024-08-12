#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Global variables for stack operations
int top = -1;          // Index of the top element
int items[MAX];        // Array to hold stack elements
int credits = 0;       // For Accounting Method
int potential = 0;     // For Potential Method

// Function to check if the stack is full
int isFull() {
    return top == (MAX - 1);
}

// Function to check if the stack is empty
int isEmpty() {
    return top == -1;
}

// Function to push an item onto the stack
void push(int item) {
    if (isFull()) {
        printf("Stack overflow. Cannot push %d\n", item);
        return;
    }
    items[++top] = item;
    potential++;         // For Potential Method
    credits += 2;        // For Accounting Method
}

// Function to pop an item from the stack
int pop() {
    if (isEmpty()) {
        printf("Stack underflow. Cannot pop.\n");
        return -1;
    }
    potential--;         // For Potential Method
    credits--;           // For Accounting Method
    return items[top--];
}

// Function to multi-pop items from the stack
int multipop(int k) {
    int count = 0;
    while (k-- > 0 && !isEmpty()) {
        pop();
        count++;
    }
    return count;
}

int main() {
    int push_count = 1000;
    int pop_count = 1000;

    // Perform push operations
    for (int i = 0; i < push_count; i++) {
        push(i);
    }

    // Perform pop operations
    for (int i = 0; i < pop_count; i++) {
        pop();
    }

    // Aggregate Method Calculation
    int total_operations = push_count + pop_count;
    printf("Aggregate Method:\n");
    printf("Total number of operations: %d\n", total_operations);
    printf("Amortized cost per operation: %.2f\n", (float)total_operations / total_operations);

    // Accounting Method Calculation
    printf("\nAccounting Method:\n");
    printf("Total number of push operations: %d\n", push_count);
    printf("Total number of pop operations: %d\n", pop_count);
    printf("Total credits used: %d\n", credits);
    printf("Amortized cost per operation: %.2f\n", (float)credits / (push_count + pop_count));

    // Potential Method Calculation
    int total_cost = push_count + pop_count;
    printf("\nPotential Method:\n");
    printf("Total number of push operations: %d\n", push_count);
    printf("Total number of pop operations: %d\n", pop_count);
    printf("Final potential value: %d\n", potential);
    printf("Amortized cost per operation: %.2f\n", (float)total_cost / (push_count + pop_count));

    return 0;
}
