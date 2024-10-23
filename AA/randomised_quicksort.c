#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Randomized pivot selection
int randomized_partition(int arr[], int low, int high) {
    int random_index = low + rand() % (high - low + 1);
    swap(&arr[random_index], &arr[high]);  // Swap random pivot with the last element
    return high;  // Pivot is now the last element
}

// Lomuto partition scheme
int lomuto_partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Hoare partition scheme
int hoare_partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1, j = high + 1;
    
    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j)
            return j;
        
        swap(&arr[i], &arr[j]);
    }
}

// Randomized Quick Sort with Lomuto partition scheme
void randomized_quick_sort_lomuto(int arr[], int low, int high) {
    if (low < high) {
        int pivot_index = randomized_partition(arr, low, high);
        int partition_index = lomuto_partition(arr, low, pivot_index);
        randomized_quick_sort_lomuto(arr, low, partition_index - 1);
        randomized_quick_sort_lomuto(arr, partition_index + 1, high);
    }
}

// Randomized Quick Sort with Hoare partition scheme
void randomized_quick_sort_hoare(int arr[], int low, int high) {
    if (low < high) {
        int pivot_index = randomized_partition(arr, low, high);
        int partition_index = hoare_partition(arr, low, pivot_index);
        randomized_quick_sort_hoare(arr, low, partition_index);
        randomized_quick_sort_hoare(arr, partition_index + 1, high);
    }
}

// Helper function to print the array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int arr1[MAX], arr2[MAX];  
    int n = 20; // Total number of elements

    // Generate random elements for the array
    for (int i = 0; i < n; i++) {
        int random_val = rand() % 100;
        arr1[i] = random_val;
        arr2[i] = random_val; // Duplicate for the second sorting
    }

    printf("Original array: \n");
    print_array(arr1, n);

    // Timing Lomuto partition
    clock_t start_lomuto = clock();
    randomized_quick_sort_lomuto(arr1, 0, n - 1);
    clock_t end_lomuto = clock();
    double time_lomuto = (double)(end_lomuto - start_lomuto) / CLOCKS_PER_SEC;

    // Timing Hoare partition
    clock_t start_hoare = clock();
    randomized_quick_sort_hoare(arr2, 0, n - 1);
    clock_t end_hoare = clock();
    double time_hoare = (double)(end_hoare - start_hoare) / CLOCKS_PER_SEC;

    printf("\nSorted array with Lomuto partition: \n");
    print_array(arr1, n);
    printf("Time taken by Lomuto partition: %f seconds\n", time_lomuto);

    printf("\nSorted array with Hoare partition: \n");
    print_array(arr2, n);
    printf("Time taken by Hoare partition: %f seconds\n", time_hoare);

    return 0;
}
