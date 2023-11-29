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
        if (edges < vertices - 1)
        {
            cout << "Error: The graph cannot be connected with fewer edges than vertices-1." << endl;
            return vector<vector<int>>();
        }

        vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

        // Generate a connected graph
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

            // Avoid loops and duplicate edges
            if (i != j && graph[i][j] == 0)
            {
                int weight = rand() % 10 + 1; // Assign a random weight between 1 and 10
                graph[i][j] = weight;
                graph[j][i] = weight;
                count++;

                // Ensure the graph remains connected after adding the edge
                vector<bool> visited(vertices, false);
                queue<int> bfsQueue;
                bfsQueue.push(0); // Start from vertex 0
                visited[0] = true;

                while (!bfsQueue.empty())
                {
                    int currentVertex = bfsQueue.front();
                    bfsQueue.pop();

                    for (int neighbor = 0; neighbor < vertices; ++neighbor)
                    {
                        if (graph[currentVertex][neighbor] != 0 && !visited[neighbor])
                        {
                            bfsQueue.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }
                }

                // Check if the graph is still connected
                if (find(visited.begin(), visited.end(), false) != visited.end())
                {
                    // If there is an unvisited vertex, undo the last edge addition
                    graph[i][j] = 0;
                    graph[j][i] = 0;
                    count--;
                }
            }
        }
        return graph;
    }

    // Função para imprimir a matriz de adjacência do grafo
    void printGraph(const vector<vector<int>> &graph)
    {
        for (const auto &row : graph)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};
#endif