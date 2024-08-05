#include <stdio.h>
#define MAX_SIZE 100

struct Stack {
    int arr[MAX_SIZE];
    int top;
};

// Initialize the stack
void initialize(struct Stack* stack) {
    stack->top = -1;
}

// Check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top >= MAX_SIZE - 1;
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push.\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

int main() {
    struct Stack myStack;
    initialize(&myStack);

    // Push two elements onto the stack
    push(&myStack, 10);
    push(&myStack, 20);

    // Print the elements in the stack
    printf("Stack elements: ");
    for (int i = 0; i <= myStack.top; ++i) {
        printf("%d ", myStack.arr[i]);
    }
    printf("\n");

    return 0;
}
