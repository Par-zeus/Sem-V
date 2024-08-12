#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct {
    int stack[STACK_SIZE];
    int top;
    int push_charge;
    int pop_charge;
    int multipop_charge;
    int balance;
} Accounting;

void init(Accounting *a) {
    a->top = -1;
    a->push_charge = 2;
    a->pop_charge = 0;
    a->multipop_charge = 0;
    a->balance = 0;
}

void push(Accounting *a, int x) {
    int push_cost = 1;
    if (a->top < STACK_SIZE - 1) {
        a->stack[++(a->top)] = x;
        a->balance -= push_cost - a->push_charge;
    }
}

void pop(Accounting *a) {
    int pop_cost = 1;
    if (a->top != -1) {
        a->top--;
        a->balance -= pop_cost - a->pop_charge;
    }
}

void multipop(Accounting *a, int k) {
    int n = a->top + 1;
    int multipop_cost;
    if (k <= n) {
        multipop_cost = k;
        for (int i = 0; i < k; i++) {
            a->top--;
        }
    } else {
        multipop_cost = n;
        for (int i = 0; i < n; i++) {
            a->top--;
        }
    }
    a->balance -= multipop_cost - a->multipop_charge;
}

int main() {
    Accounting a;
    init(&a);

    printf("Operation\tCharge\tCost\tBalance\n");
    for (int i = 0; i < 9; i++) {
        push(&a, i);
        printf("Push\t\t2\t1\t%d\n", a.balance);
    }

    for (int i = 0; i < 3; i++) {
        pop(&a);
        printf("Pop\t\t0\t1\t%d\n", a.balance);
    }

    for (int i = 0; i < 3; i++) {
        int k = 2;
        multipop(&a, k);
        printf("Multipop\t0\t%d\t%d\n", k, a.balance);
    }

    printf("Final balance : %d\n", a.balance);
    return 0;
}

