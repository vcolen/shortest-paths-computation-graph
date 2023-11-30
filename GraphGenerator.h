#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <iostream>
#include <vector>
#include <ctime>
#include <queue>

using namespace std;

class GraphGenerator
{

public:
    // Função para gerar um grafo com a quantidade específica de vértices e arestas
    vector<vector<int>> generateGraph(int vertices, int edges)
    {
        vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

        // Generate a connected graph sequentially
        for (int i = 1; i < vertices; ++i)
        {
            int weight = rand() % 10 + 1; // Assign a random weight between 1 and 10
            graph[i - 1][i] = weight;
            graph[i][i - 1] = weight;
        }

        // Add additional edges to reach the desired edge count
        srand(time(0));
        int count = vertices - 1;
        while (count < edges)
        {
            int i = rand() % vertices;
            int j = rand() % vertices;

            // Ensure that the graph remains connected
            if (i != j && graph[i][j] == 0)
            {
                int weight = rand() % 10 + 1; // Assign a random weight between 1 and 10
                graph[i][j] = weight;
                graph[j][i] = weight;
                count++;
            }
        }

        return graph;
    }
};
#endif