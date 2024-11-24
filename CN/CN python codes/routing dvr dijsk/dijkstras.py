import sys
V = 6  # Number of vertices

def min_distance(dist, spt_set):
    min_val = sys.maxsize
    min_index = -1
    for v in range(V):
        if not spt_set[v] and dist[v] < min_val:
            min_val = dist[v]
            min_index = v
    return min_index

def print_solution(dist):
    print("Vertex \t Distance from Source")
    for i in range(V):
        print(f"{i} \t\t {dist[i]}")

def dijkstra(graph, src):
    dist = [sys.maxsize] * V
    spt_set = [False] * V
    dist[src] = 0
    for _ in range(V - 1):
        u = min_distance(dist, spt_set)
        spt_set[u] = True
        for v in range(V):
            if not spt_set[v] and graph[u][v] and dist[u] != sys.maxsize and dist[u] + graph[u][v] < dist[v]:
                dist[v] = dist[u] + graph[u][v]
    print_solution(dist)

graph = []
print("Enter the adjacency matrix representation of the graph:")
for _ in range(V):
    graph.append(list(map(int, input().split())))
source = int(input("Enter the source vertex: "))
dijkstra(graph, source)   