#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>

using namespace std;

class Dijkstra
{
public:
    void dijkstra(vector<vector<int>> &graph)
    {
        int verticesCount = graph.size();

        vector<int> distances(verticesCount, numeric_limits<int>::max());
        distances[0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (currentDist > distances[u])
                continue;

            for (int v = 0; v < verticesCount; ++v)
            {
                if (graph[u][v] != 0)
                {
                    int newDist = distances[u] + graph[u][v];
                    if (newDist < distances[v])
                    {
                        distances[v] = newDist;
                        pq.push({distances[v], v});
                    }
                }
            }
        }
    }

    void operator()(vector<vector<int>>& graph) {
        dijkstra(graph);
    }
};

#endif