#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *stack;
    int size;
    int total_amortized_cost;
    int capacity;
} Potential;

void init(Potential *p) {
    p->capacity = 10;
    p->stack = (int *)malloc(p->capacity * sizeof(int));
    p->size = 0;
    p->total_amortized_cost = 0;
}

void push(Potential *p, int x) {
    if (p->size == p->capacity) {
        p->capacity *= 2;
        p->stack = (int *)realloc(p->stack, p->capacity * sizeof(int));
    }
    int cost = 1;
    p->stack[p->size] = x;
    int amortized_cost = cost + ((p->size + 1) - (p->size));
    p->size += 1;
    p->total_amortized_cost += amortized_cost;
    printf("Push\t\t%d\t\t%d\t\t%d\n", cost, amortized_cost, p->total_amortized_cost);
}

void pop(Potential *p) {
    if (p->size != 0) {
        int cost = 1;
        p->size -= 1;
        int amortized_cost = cost + ((p->size) - (p->size + 1));
        p->total_amortized_cost += amortized_cost;
        printf("Pop\t\t%d\t\t%d\t\t%d\n", cost, amortized_cost, p->total_amortized_cost);
    }
}

void multipop(Potential *p, int k) {
    int n = p->size;
    int cost;
    if (k <= n) {
        cost = k;
        p->size -= k;
    } else {
        cost = n;
        p->size = 0;
    }
    int amortized_cost = cost + ((p->size) - (n));
    p->total_amortized_cost += amortized_cost;
    printf("MultiPop\t%d\t\t%d\t\t%d\n", cost, amortized_cost, p->total_amortized_cost);
}

int main() {
    Potential a;
    init(&a);

    printf("Operations\tActual-Cost\tAmortized-Cost\tTotal-Cost\n");
    for (int i = 0; i < 9; i++) {
        push(&a, i);
    }

    for (int i = 0; i < 3; i++) {
        pop(&a);
    }

    for (int i = 0; i < 3; i++) {
        multipop(&a, 2);
    }

    printf("Total Amortized Cost : %d\n", a.total_amortized_cost);

    free(a.stack);
    return 0;
}

