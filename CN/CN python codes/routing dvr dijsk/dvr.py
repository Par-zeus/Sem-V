# # Bellman Ford

# class Edge:
#     def __init__(self, u, v, w):
#         self.u = u  # Start vertex
#         self.v = v  # End vertex
#         self.w = w  # Weight of the edge

# class Graph:
#     def __init__(self, vertices, edges):
#         self.V = vertices  # Number of vertices
#         self.E = edges  # List of edges

# def display(arr):
#     print(" ".join(map(str, arr)))

# def bellman_ford(graph, source):
#     tV = graph.V
#     tE = len(graph.E)
#     distance = [float('inf')] * tV
#     parent = [-1] * tV
#     distance[source] = 0
#     # Relax edges (V-1) times
#     for _ in range(tV - 1):
#         for edge in graph.E:
#             u = edge.u
#             v = edge.v
#             w = edge.w
#             if distance[u] != float('inf') and distance[u] + w < distance[v]:
#                 distance[v] = distance[u] + w
#                 parent[v] = u
#     # Check for negative weight cycles
#     for edge in graph.E:
#         u = edge.u
#         v = edge.v
#         w = edge.w
#         if distance[u] != float('inf') and distance[u] + w < distance[v]:
#             print("Negative Cycle detected, cannot proceed.")
#             return
#     print("Distance array: ", end="")
#     display(distance)
#     print("Predecessor array: ", end="")
#     display(parent)

# vertices = 4
# edges = [
#     Edge(0, 1, 5),
#     Edge(0, 2, 4),
#     Edge(1, 3, 3),
#     Edge(2, 1, 6),
#     Edge(3, 2, 2),]
# g = Graph(vertices, edges)
# bellman_ford(g, 0)

def print_distances(dist, V):
    print("Vertex Distance from Source")
    for i in range(V):
        print(f"{i}\t{dist[i]}")

def bellman_ford(graph, V, E, src):
    # Initialize distances to all vertices as infinite, except source
    dist = [float('inf')] * V
    dist[src] = 0
    # Relax edges V-1 times
    for _ in range(V - 1):
        for u, v, weight in graph:
            if dist[u] != float('inf') and dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
    # Check for negative-weight cycles
    for u, v, weight in graph:
        if dist[u] != float('inf') and dist[u] + weight < dist[v]:
            print("Graph contains a negative-weight cycle.")
            return
    print_distances(dist, V)

V = int(input("Enter the number of vertices: "))
E = int(input("Enter the number of edges: ")) 
graph = []
print("Enter edges (source, destination, weight):")
for _ in range(E):
    u, v, weight = map(int, input().split())
    graph.append((u, v, weight))
src = int(input("Enter the source vertex: "))
bellman_ford(graph, V, E, src)