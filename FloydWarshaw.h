#ifndef FLOYDWARSHAW_H
#define FLOYDWARSHAW_H

// https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/?ref=header_search

#include <iostream>
#include <limits.h>
#include <vector>

// Define Infinite as a large enough value.
#define INF INT_MAX

class FloydWarshaw {

    public:
        void floydWarshall(vector<vector<int>> graph) {
            int verticesCount = graph.size();
            for (int k = 0; k < verticesCount; k++) {
                for (int i = 0; i < verticesCount; i++) {
                    for (int j = 0; j < verticesCount; j++) {
                        if (graph[i][j] > (graph[i][k] + graph[k][j]) && (graph[k][j] != INF && graph[i][k] != INF)) {
                            graph[i][j] = graph[i][k] + graph[k][j];
                        }
                    }
                }
            }
            printSolution(graph);
        }

        void printSolution(vector<vector<int>> graph) {
            int verticesCount = graph.size();
            std::cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
            for (int i = 0; i < verticesCount; i++) {
                for (int j = 0; j < verticesCount; j++) {
                    if (graph[i][j] == INF)
                        std::cout << "INF "
                                << " ";
                    else
                        std::cout << graph[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
};

#endif