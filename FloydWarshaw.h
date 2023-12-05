#ifndef FLOYDWARSHAW_H
#define FLOYDWARSHAW_H

#include <iostream>
#include <limits.h>
#include <vector>

class FloydWarshaw
{

public:
    const int INF = INT_MAX;
    void floydWarshaw(vector<vector<int>> &graph)
    {
        int verticesCount = graph.size();
        for (int k = 0; k < verticesCount; k++)
        {
            for (int i = 0; i < verticesCount; i++)
            {
                for (int j = 0; j < verticesCount; j++)
                {
                    if (graph[i][j] > (graph[i][k] + graph[k][j]) && (graph[k][j] != INF && graph[i][k] != INF))
                    {
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
    }

    void operator()(vector<vector<int>> &graph)
    {
        floydWarshaw(graph);
    }
};

#endif