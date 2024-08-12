#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *stack;
    int top;
    int capacity;
    int push_count;
    int pop_count;
    int multipop_count;
    int totalcost;
} Aggregate;

void init(Aggregate *a) {
    a->capacity = 10; // initial capacity
    a->stack = (int *)malloc(a->capacity * sizeof(int));
    a->top = -1;
    a->push_count = 0;
    a->pop_count = 0;
    a->multipop_count = 0;
    a->totalcost = 0;
}

void push(Aggregate *a, int x) {
    if (a->top == a->capacity - 1) {
        a->capacity *= 2;
        a->stack = (int *)realloc(a->stack, a->capacity * sizeof(int));
    }
    a->stack[++(a->top)] = x;
    a->push_count++;
    a->totalcost++;
}

void pop(Aggregate *a) {
    if (a->top != -1) {
        a->top--;
        a->pop_count++;
    }
    a->totalcost++;
}

void multipop(Aggregate *a, int k) {
    int n = a->top + 1;
    if (k <= n) {
        for (int i = 0; i < k; i++) {
            a->top--;
        }
        a->totalcost += k;
    } else {
        a->top = -1; // empty the stack
        a->totalcost += n;
    }
    a->multipop_count++;
}

void freeAggregate(Aggregate *a) {
    free(a->stack);
}

int main() {
    Aggregate a;
    init(&a);
    
    for (int i = 0; i < 9; i++) {
        push(&a, i);
    }

    for (int i = 0; i < 3; i++) {
        pop(&a);
    }

    for (int i = 0; i < 3; i++) {
        multipop(&a, 2);
    }

    int total_operations = a.push_count + a.pop_count + a.multipop_count;
    printf("Total Operations : %d\n", total_operations);
    printf("Total cost : %d\n", a.totalcost);
    printf("Amortized Cost Per Operation : %.2f\n", (float)a.totalcost / total_operations);

    freeAggregate(&a);
    return 0;
}

