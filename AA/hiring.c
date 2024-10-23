#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 100

// Function to simulate the hiring problem
int hiring_problem(int candidates[], int n) {
    int num_to_interview = n / 3; // Interview the first n/e candidates (approximated as n/3)
    int best_candidate = candidates[0];

    // Find the best candidate in the first num_to_interview candidates
    for (int i = 0; i < num_to_interview; i++) {
        if (candidates[i] > best_candidate) {
            best_candidate = candidates[i];
        }
    }

    // Hire the first candidate better than the best in the initial subset
    for (int i = num_to_interview; i < n; i++) {
        if (candidates[i] > best_candidate) {
            return candidates[i]; // Return the hired candidate
        }
    }

    // If no candidate is hired, return the last candidate
    return candidates[n - 1];
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int n = 10; // Total number of candidates
    int candidates[MAX_CANDIDATES];

    // Generate a pool of candidates (random ratings between 1 and 100)
    for (int i = 0; i < n; i++) {
        candidates[i] = rand() % 100 + 1; // Ratings between 1 and 100
    }

    // Display the candidates
    printf("Candidates: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", candidates[i]);
    }
    printf("\n");

    int best_hire = hiring_problem(candidates, n);
    printf("Best hire selected: %d\n", best_hire);

    return 0;
}
