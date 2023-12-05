#ifndef JOHNSON_H
#define JOHNSON_H

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>

using namespace std;

class Johnson
{
public:
    void johnson(vector<vector<int>>& graph)
    {
        int verticesCount = graph.size();

        // Passo 1: Adicionar um novo vértice e conectar a todos os outros com arestas de peso zero
        vector<vector<int>> modifiedGraph(verticesCount + 1, vector<int>(verticesCount + 1, 0));
        for (int i = 0; i < verticesCount; ++i)
            for (int j = 0; j < verticesCount; ++j)
                modifiedGraph[i][j] = graph[i][j];

        // Adiciona arestas de peso zero do novo vértice para todos os outros
        for (int i = 0; i < verticesCount; ++i)
            modifiedGraph[verticesCount][i] = 0;

        // Passo 2: Executa Bellman-Ford no grafo modificado
        vector<int> h(verticesCount + 1, 0);
        if (!bellmanFord(modifiedGraph, h))
        {
            cout << "O grafo contém ciclos de peso negativo." << endl;
            return;
        }

        // Passo 3: Repondera as arestas do grafo original
        for (int i = 0; i < verticesCount; ++i)
            for (int j = 0; j < verticesCount; ++j)
                if (modifiedGraph[i][j] != 0)
                    modifiedGraph[i][j] += h[i] - h[j];

        // Passo 4: Remove o vértice adicional e executa Dijkstra para cada vértice
        for (int source = 0; source < verticesCount; ++source)
            dijkstra(graph, source, h);
    }

    void operator()(vector<vector<int>>& graph) {
        johnson(graph);
    }

private:
    bool bellmanFord(vector<vector<int>>& graph, vector<int>& distances)
    {
        int verticesCount = graph.size();

        fill(distances.begin(), distances.end(), numeric_limits<int>::max());
        distances[verticesCount - 1] = 0;

        for (int i = 0; i < verticesCount - 1; ++i)
            for (int u = 0; u < verticesCount; ++u)
                for (int v = 0; v < verticesCount; ++v)
                    if (graph[u][v] != 0 && distances[u] != numeric_limits<int>::max() && distances[u] + graph[u][v] < distances[v])
                        distances[v] = distances[u] + graph[u][v];

        // Não checaremos por ciclos negativos pois
        // estamos lidando com arestas de peso positivo

        return true;
    }

    void dijkstra(vector<vector<int>>& graph, int source, const vector<int>& h)
    {
        int verticesCount = graph.size();

        vector<int> distances(verticesCount, numeric_limits<int>::max());
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
                    int newDist = distances[u] + graph[u][v] + h[v] - h[u];
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
