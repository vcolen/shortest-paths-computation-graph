#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

class BellmanFord
{

public:

    const int verticesCount;

    BellmanFord(int count) : verticesCount(count) {}

    void printSolution(int distances[])
    {
        cout << "Vértice \t Distância da fonte" << endl;
        for (int i = 0; i < verticesCount; i++)
            cout << i << " \t\t\t\t" << distances[i] << endl;
    }

    void bellmanFord(vector<vector<int>>& graph, int source)
    {
        int verticesCount = graph.size();

        int distances[verticesCount];

        // Inicializa as distâncias como infinito e a fonte como 0
        for (int i = 0; i < verticesCount; i++)
            distances[i] = INT_MAX;
            distances[source] = 0;

        // Relaxa todas as arestas |V| - 1 vezes
        for (int count = 0; count < verticesCount - 1; count++)
        {
            // Itera por todas as arestas e atualiza distâncias
            for (int u = 0; u < verticesCount; u++)
            {
                for (int v = 0; v < verticesCount; v++)
                {
                    if (graph[u][v] != 0 && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v])
                    {
                        distances[v] = distances[u] + graph[u][v];
                    }
                }
            }
        }

        // Checa ciclos negativos
        for (int u = 0; u < verticesCount; u++)
        {
            for (int v = 0; v < verticesCount; v++)
            {
                if (graph[u][v] != 0 && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v])
                {
                    cout << "Graph contains negative weight cycle" << endl;
                    return;
                }
            }
        }

       // printSolution(distances);
    }
};
#endif
