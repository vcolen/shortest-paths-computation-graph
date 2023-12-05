#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

class BellmanFord
{
public:
    void bellmanFord(vector<vector<int>> &graph)
    {
        int verticesCount = graph.size();

        vector<int> distances(verticesCount, INT_MAX);
        distances[0] = 0;

        for (int i = 0; i < verticesCount - 1; ++i)
        {
            for (int u = 0; u < verticesCount; ++u)
            {
                for (int v = 0; v < verticesCount; ++v)
                {
                    if (graph[u][v] != 0)
                    {
                        int newDist = distances[u] + graph[u][v];
                        if (newDist < distances[v])
                        {
                            distances[v] = newDist;
                        }
                    }
                }
            }
        }

        // Não checaremos por ciclos negativos pois
        // estamos lidando com arestas de peso positivo
    }

    void operator()(vector<vector<int>> &graph)
    {
        bellmanFord(graph);
    }
};
#endif
