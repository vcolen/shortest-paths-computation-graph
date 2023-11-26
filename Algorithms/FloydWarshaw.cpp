// https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/?ref=header_search

#include <iostream>
#include <limits.h>

// Number of vertices in the graph
#define V 5

// Define Infinite as a large enough value.
#define INF INT_MAX

void printSolution(int dist[V][V]) {
    std::cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                std::cout << "INF "
                          << " ";
            else
                std::cout << dist[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void floydWarshall(int dist[V][V]) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printSolution(dist);
}

int main() {
    int graph[V][V] = {{0, 1, INF, 7, INF},
                       {1, 0, INF, INF, INF},
                       {INF, INF, 0, 5, INF},
                       {7, INF, 5, 0, INF},
                       {INF, INF, INF, INF, 0}};

    floydWarshall(graph);
    return 0;
}
