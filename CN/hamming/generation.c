#include <stdio.h>
#include <math.h>

// Function to calculate parity for even parity
int hamming_calculate_even(int pos, int len, int code[])
{
    int count = 0;
    for (int i = pos - 1; i < len; i += 2 * pos)
        for (int j = i; j < i + pos && j < len; j++)
            count += code[j];
    return count % 2; // Returns 0 for even, 1 for odd
}

// Function to calculate parity for odd parity
int hamming_calculate_odd(int pos, int len, int code[])
{
    int count = 0;
    for (int i = pos - 1; i < len; i += 2 * pos)
        for (int j = i; j < i + pos && j < len; j++)
            count += code[j];
    return (count % 2) ^ 1; // Toggle result for odd parity
}

// Function to print Hamming code
void print(int n, int p, int code[])
{
    for (int i = n + p - 1; i >= 0; i--)
        printf("%d ", code[i]);
    printf("\n");
}

int main()
{
    int n, p = 0;
    printf("Enter the size of the data bits: ");
    scanf("%d", &n);

    // Calculate the number of parity bits
    while (pow(2, p) < n + p + 1)
        p++;

    int code[n + p], input[n];
    printf("Enter the data bits:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter bit %d: ", i + 1);
        scanf("%d", &input[i]);
    }

    // Insert data bits and reserve space for parity bits
    for (int i = 0, j = 0, k = n - 1; i < n + p; i++)
        code[i] = (i == pow(2, j) - 1) ? (j++, 0) : input[k--];

    printf("Initial Hamming code (with parity bits as 0):\n");
    print(n, p, code);

    // Calculate parity bits for even parity
    for (int i = 0; i < p; i++)
    {
        int position = pow(2, i);
        int value = hamming_calculate_even(position, n + p, code);
        code[position - 1] = value;
    }

    printf("Final Hamming code (Even Parity):\n");
    print(n, p, code);

    return 0;
}
