#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int height;
} Skyline;

typedef struct {
    int left;
    int height;
    int right;
} Building;

// Function to merge two skylines
Skyline* mergeSkylines(Skyline* left_skyline, int left_size, Skyline* right_skyline, int right_size, int* mergedSize) {
    Skyline* merge_skyline = (Skyline*)malloc((left_size + right_size) * sizeof(Skyline));
    int left_idx = 0, right_idx = 0, currentHeight = 0, left_height = 0, right_height = 0;
    int merge_idx = 0;

    while (left_idx < left_size && right_idx < right_size) {
        int x;
        if (left_skyline[left_idx].x < right_skyline[right_idx].x) {
            x = left_skyline[left_idx].x;
            left_height = left_skyline[left_idx].height;
            left_idx++;
        } else {
            x = right_skyline[right_idx].x;
            right_height = right_skyline[right_idx].height;
            right_idx++;
        }

        int max_height = left_height > right_height ? left_height : right_height;
        if (merge_idx == 0 || merge_skyline[merge_idx - 1].height != max_height) {
            merge_skyline[merge_idx].x = x;
            merge_skyline[merge_idx].height = max_height;
            merge_idx++;
        }
    }

    while (left_idx < left_size) {
        merge_skyline[merge_idx++] = left_skyline[left_idx++];
    }

    while (right_idx < right_size) {
        merge_skyline[merge_idx++] = right_skyline[right_idx++];
    }

    *mergedSize = merge_idx;
    return merge_skyline;
}

Skyline* findSkyline(Building* buildings, int start, int end, int* size) {
    if (start == end) {
        Skyline* skyline = (Skyline*)malloc(2 * sizeof(Skyline));
        skyline[0].x = buildings[start].left;
        skyline[0].height = buildings[start].height;
        skyline[1].x = buildings[start].right;
        skyline[1].height = 0;
        *size = 2;
        return skyline;
    }

    int mid = (start + end) / 2;
    int left_size, right_size;
    Skyline* left_skyline = findSkyline(buildings, start, mid, &left_size);
    Skyline* right_skyline = findSkyline(buildings, mid + 1, end, &right_size);

    return mergeSkylines(left_skyline, left_size, right_skyline, right_size, size);
}

void printSkyline(Skyline* skyline, int size) {
    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", skyline[i].x, skyline[i].height);
    }
    printf("\n");
}

int main() {
  
    Building buildings[] = {
        {3, 13, 9},
        {1, 11, 5},
        {12, 7, 16},
        {14, 3, 25},
        {19, 18, 22},
        {2, 6, 7},
        {23, 13, 29},
        {23, 4, 28}
    };

    int numBuildings = sizeof(buildings) / sizeof(buildings[0]);
    int skylineSize;

    Skyline* skyline = findSkyline(buildings, 0, numBuildings - 1, &skylineSize);

    printSkyline(skyline, skylineSize);

    free(skyline);

    return 0;
}
