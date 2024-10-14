#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Include conio.h for getch()

// A point structure to represent a point in 2D space
struct Point {
    int x, y;
};

// Function to find the orientation of the ordered triplet (p, q, r)
// Returns 0 if p, q and r are collinear
// Returns 1 if clockwise
// Returns 2 if counterclockwise
int orientation(struct Point p, struct Point q, struct Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

// Function to perform insertion sort based on y-coordinate
void insertionSort(struct Point points[], int n) {
    int i=1;
    for (i = 1; i < n; i++) {
        struct Point key = points[i];
        int j = i - 1;
        // Move elements of points[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && (points[j].y > key.y || (points[j].y == key.y && points[j].x > key.x))) {
            points[j + 1] = points[j];
            j = j - 1;
        }
        points[j + 1] = key;
    }
}

// Function to perform the Graham Scan algorithm
int grahamScan(struct Point points[], int n, struct Point hull[]) {
    // Sort points using insertion sort

    int hullIndex = 0;
    int lowerSize = hullIndex;
    int i=0;
    // Build lower hull
    insertionSort(points, n);
    for (i = 0; i < n; i++) {
        while (hullIndex >= 2 && orientation(hull[hullIndex - 2], hull[hullIndex - 1], points[i]) != 2) {
            hullIndex--;
        }
        hull[hullIndex++] = points[i];
    }

    i=n-1;
    // Build upper hull
    for ( i = n - 1; i >= 0; i--) {
        while (hullIndex > lowerSize && orientation(hull[hullIndex - 2], hull[hullIndex - 1], points[i]) != 2) {
            hullIndex--;
        }
        hull[hullIndex++] = points[i];
    }

    // Remove the last point because it's the same as the first one
    return hullIndex - 1; // Number of points in the hull
}

// Function to visualize the convex hull
void drawHull(struct Point hull[], int n) {
    int i=0;
    for (i = 0; i < n; i++) {
        line(hull[i].x, hull[i].y, hull[(i + 1) % n].x, hull[(i + 1) % n].y);
    }
}

// Driver function
int main() {
    // Initialize graphics

     struct Point hull[100];
	struct Point points[] = {
	{100, 200}, {200, 300}, {300, 250}, {150, 100}, {400, 150},
	{350, 350}, {250, 400}, {50, 50}, {450, 50}, {200, 200}
    };
    int gd = DETECT, gm;
    int n = sizeof(points) / sizeof(points[0]);
    int i=0;
    // Ensure sufficient size for hull
    int hullSize = grahamScan(points, n, hull);


    // Sample points

    initgraph(&gd, &gm, "c:\\turboc3\\bgi");

    // Draw points
    for (i = 0; i < n; i++) {
	putpixel(points[i].x, points[i].y, WHITE);
    }

    
    drawHull(hull, hullSize);

    // Wait for a key press
    getch();
    closegraph();
    return 0;
}
