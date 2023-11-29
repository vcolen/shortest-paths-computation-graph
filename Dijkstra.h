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
    const int INF = numeric_limits<int>::max();

    void printSolution(const vector<int> &distances)
    {
        cout << "Vertex \t Distance from source" << endl;
        for (int i = 0; i < distances.size(); ++i)
            cout << i << " \t\t\t\t" << distances[i] << endl;
    }

    void dijkstra(vector<vector<int>> &graph, int source)
    {
        int verticesCount = graph.size();

        vector<int> distances(verticesCount, INF);
        distances[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});

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
};

#endif