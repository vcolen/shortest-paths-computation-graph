#ifndef JOHNSON_H
#define JOHNSON_H

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

class Johnson
{
public:
    const int INF = numeric_limits<int>::max();

    vector<vector<int>> johnson(const vector<vector<int>> &graph)
    {
        // Step 1: Add a new vertex and edges with weight 0 to all other vertices
        vector<vector<int>> graph_prime = AddNewVertex(graph);

        // Step 2: Run the Bellman-Ford algorithm on the graph with the new vertex
        vector<int> reweighting_values = BellmanFord(graph_prime);

        // Step 3: Remove the added vertex and adjust edge weights
        vector<vector<int>> graph_reweighted = RemoveNewVertex(graph_prime, reweighting_values);

        // Step 4: Initialize the matrix of minimum distances
        vector<vector<int>> distances = InitializeMatrix(graph_reweighted);

        // Step 5: Run the Dijkstra algorithm for each vertex
        for (int v = 0; v < graph_reweighted.size(); ++v)
        {
            Dijkstra(graph_reweighted, v, distances[v]);
        }

        // Step 6: Undo the adjustment of minimum distances
        distances = UndoAdjustment(distances, reweighting_values);

        printDistances(distances);
        return distances;
    }

    void printDistances(const vector<vector<int>> &distances)
    {
        cout << "Minimum Distances Matrix:" << endl;
        for (const auto &row : distances)
        {
            for (int distance : row)
            {
                if (distance == INF)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << distance << " ";
                }
            }
            cout << endl;
        }
    }

private:
    // Add a new vertex and edges with weight 0
    vector<vector<int>> AddNewVertex(const vector<vector<int>> &graph)
    {
        int n = graph.size() + 1;
        vector<vector<int>> graph_prime(n, vector<int>(n, 0));

        for (int v = 1; v < n; ++v)
        {
            graph_prime[0][v] = 0;
        }

        for (int u = 1; u < n; ++u)
        {
            for (int v = 1; v < n; ++v)
            {
                graph_prime[u][v] = graph[u - 1][v - 1];
            }
        }

        return graph_prime;
    }

    // Bellman-Ford algorithm to find reweighting values
    vector<int> BellmanFord(const vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> distances(n, INF);

        for (int i = 0; i < n - 1; ++i)
        {
            for (int u = 0; u < n; ++u)
            {
                for (int v = 0; v < n; ++v)
                {
                    if (graph[u][v] != 0 && distances[u] != INF && distances[u] + graph[u][v] < distances[v])
                    {
                        distances[v] = distances[u] + graph[u][v];
                    }
                }
            }
        }

        return distances;
    }

// Remove the added vertex and adjust edge weights
vector<vector<int>> RemoveNewVertex(const vector<vector<int>>& graph, const vector<int>& reweighting_values) {
    int n = graph.size();
    vector<vector<int>> graph_reweighted = graph;

    for (int u = 1; u < n; ++u) {
        for (int v = 1; v < n; ++v) {
            if (graph[u - 1][v - 1] != 0) {
                graph_reweighted[u][v] = graph[u - 1][v - 1] - reweighting_values[u] + reweighting_values[v];
            }
        }
    }

    return graph_reweighted;
}



    // Initialize matrix of minimum distances
    vector<vector<int>> InitializeMatrix(const vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<vector<int>> distances(n, vector<int>(n, INF));

        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                distances[u][v] = graph[u][v];
            }
        }

        return distances;
    }

    // Dijkstra algorithm to find minimum distances from a source vertex
    void Dijkstra(const vector<vector<int>> &graph, int source, vector<int> &distances)
    {
        int verticesCount = graph.size();

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

    // Undo the adjustment of minimum distances
    vector<vector<int>> UndoAdjustment(const vector<vector<int>> &distances, const vector<int> &reweighting_values)
    {
        int n = distances.size();
        vector<vector<int>> undone_distances = distances;

        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                undone_distances[u][v] = undone_distances[u][v] - reweighting_values[u] + reweighting_values[v];
            }
        }

        return undone_distances;
    }
};

#endif
