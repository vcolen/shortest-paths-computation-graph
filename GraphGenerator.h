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
    vector<vector<int>> generateGraph(int vertices, int edges)
    {
        vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
        srand(time(0));

        // Gerando um grafo conexo sequencialmente
        for (int i = 1; i < vertices; ++i)
        {
            int weight = rand() % 100 + 1; // Valor aleatório entre 1 e 100
            graph[i - 1][i] = weight;
            graph[i][i - 1] = weight;
        }

        // Adicionando arestas restantes
        int count = vertices - 1;
        while (count < edges)
        {
            int i = rand() % vertices;
            int j = rand() % vertices;

            // Aleatorizando as arestas restantes
            if (i != j && graph[i][j] == 0)
            {
                int weight = rand() % 100 + 1; // Valor aleatório entre 1 e 100
                graph[i][j] = weight;
                graph[j][i] = weight;
                count++;
            }
        }
        return graph;
    }
};
#endif