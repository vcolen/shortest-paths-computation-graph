#include <iostream>
#include <climits>

using namespace std;

// A structure to represent a weighted edge in the graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a connected, directed, and weighted graph
struct Graph {
    int V, E;
    Edge* edge;
};

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// A utility function used to print the solution
void printArr(int dist[], int n) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm.
// The function also detects negative weight cycles
void BellmanFord(Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int* dist = new int[V];

    // Step 1: Initialize distances from src to all other
    // vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at most |V| - 1 edges
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: check for negative-weight cycles.
    // The above step guarantees shortest distances
    // if the graph doesn't contain a negative weight cycle.
    // If we get a shorter path, then there is a cycle.
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle");
            delete[] dist;
            return; // If a negative cycle is detected, simply return
        }
    }

    printArr(dist, V);

    delete[] dist;
    return;
}

// Driver's code
int main() {
    // Let us create the graph given in the above example
    int V = 5; // Number of vertices in the graph
    int E = 8; // Number of edges in the graph
    Graph* graph = createGraph(V, E);

    // Add edges to the graph
    graph->edge[0] = {0, 1, -1};
    graph->edge[1] = {0, 2, 4};
    graph->edge[2] = {1, 2, 3};
    graph->edge[3] = {1, 3, 2};
    graph->edge[4] = {1, 4, 2};
    graph->edge[5] = {3, 2, 5};
    graph->edge[6] = {3, 1, 1};
    graph->edge[7] = {4, 3, -3};

    // Function call
    BellmanFord(graph, 0);

    delete[] graph->edge;
    delete graph;

    return 0;
}
