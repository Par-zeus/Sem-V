#include <stdio.h>
#define INT_MAX 999
#define vertices 9

int visited[vertices], parent[vertices], distance[vertices];

int cost[vertices][vertices] = { 
    { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
    { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
    { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
    { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
    { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
    { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
    { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
    { 0, 0, 2, 0, 0, 0, 6, 7, 0 } 
};

int isToExplore() {
    for (int i = 0; i < vertices; i++) {
        if (visited[i] == 0) {
            return 1;
        }
    }
    return 0;
}

void initializeGraph() {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j && cost[i][j] == 0) {
                cost[i][j] = INT_MAX;
            }
        }
    }
}

void initializeSingleSource(int source) {
    initializeGraph();
    for (int i = 0; i < vertices; i++) {
        parent[i] = -1;
        visited[i] = 0;
        distance[i] = INT_MAX;
    }
    distance[source] = 0;
}

int getMinNode() {
    int min = -1; // Initialize to -1
    for (int i = 0; i < vertices; i++) {
        if (visited[i] != 1 && (min == -1 || distance[i] < distance[min])) {
            min = i;
        }
    }
    return min;
}

void Relax(int u, int v) {
    if ((distance[u] + cost[u][v]) < distance[v]) {
        distance[v] = distance[u] + cost[u][v];
        parent[v] = u;
    }
    printf("Relaxing: From Node %d to Node %d | Tentative Distance: %d | Parent: %d\n", u, v, distance[v], parent[v]);
}

void Dijkstra(int source) {
    initializeSingleSource(source);
    printf("\n");
    while (isToExplore()) {
        int u = getMinNode();
        visited[u] = 1; // Mark node as permanent
        printf("Node %d is now permanent.\n", u);
        
        for (int v = 0; v < vertices; v++) {
            if (cost[u][v] != INT_MAX && u != v) {
                Relax(u, v);
            }
        }
    }
}

void printPath(int node) {
    if (node == -1) {
        return;
    }
    printPath(parent[node]);
    printf("%d ", node);
}

void printSol() {
    printf("\nNode\tTentative Distance\tParent Node\tPath\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d\t\t%d\t\t\t%d\t\t", i, (distance[i] == INT_MAX) ? -1 : distance[i], parent[i]);
        printf("Path: ");
        printPath(i);
        printf("\n");
    }
}

int main() {
    int source;
    printf("Enter the source vertex (0 to 8): ");
    scanf("%d", &source);
    
    if (source < 0 || source >= vertices) {
        printf("Invalid source vertex. Please enter a number between 0 and 8.\n");
        return 1;
    }
    
    Dijkstra(source);
    printSol();

    return 0;
}
