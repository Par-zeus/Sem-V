#include <stdio.h>
#include <math.h>

// Function to calculate parity
int hamming_calculate(int pos, int len, int code[])
{
    int count = 0;
    for (int i = pos - 1; i < len; i += 2 * pos)
        for (int j = i; j < i + pos && j < len; j++)
            count += code[j];
    return count % 2;
}

// Detect errors in the Hamming code
void detect_error(int code[], int len, int p, int is_odd_parity)
{
    int error_position = 0;

    for (int i = 0; i < p; i++)
    {
        int position = pow(2, i);
        int calculated_parity = hamming_calculate(position, len, code);

        if (is_odd_parity)
            calculated_parity ^= 1; // Toggle for odd parity

        if (calculated_parity != 0)
            error_position += position;
    }

    if (error_position == 0)
        printf("No errors detected in the Hamming code.\n");
    else
    {
        printf("Error detected at position: %d (from right to left)\n", error_position);
        code[error_position - 1] ^= 1; // Correct the error
        printf("Corrected Hamming code:\n");
        for (int i = len - 1; i >= 0; i--)
            printf("%d ", code[i]);
        printf("\n");
    }
}

int main()
{
    int len, is_odd_parity;
    printf("Enter the total length of the Hamming code: ");
    scanf("%d", &len);

    int code[len];
    printf("Enter the Hamming code bits:\n");
    for (int i = 0; i < len; i++)
    {
        printf("Enter bit %d: ", i + 1);
        scanf("%d", &code[i]);
    }

    printf("Enter 0 for Even Parity or 1 for Odd Parity: ");
    scanf("%d", &is_odd_parity);

    int p = 0;
    while (pow(2, p) < len)
        p++;

    detect_error(code, len, p, is_odd_parity);

    return 0;
}
