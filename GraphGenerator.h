#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class GraphGenerator
{

public:
    // Função para gerar um grafo com a quantidade específica de vértices e arestas
    vector<vector<int>> generateGraph(int vertices, int edges)
    {
        vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

        // Gera arestas aleatórias
        srand(time(0));
        int count = 0;
        while (count < edges)
        {
            int i = rand() % vertices;
            int j = rand() % vertices;

            // Evita laços e arestas duplicadas
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

    // Função para medir o tempo de execução de um algoritmo
    double measureTime(void (*func)(const vector<vector<int>> &), const vector<vector<int>> &graph)
    {
        clock_t start = clock();
        func(graph);
        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC;
        return duration;
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

private:

void execute() {
    // for (int x = 1; x <= 5; ++x) {
    //     int vertices = pow(5, x);

    //     // Gera valores equidistantes para as arestas
    //     vector<int> edgesValues;
    //     int minEdgeCount = vertices-1;
    //     int maxEdgeCount = (vertices * (vertices - 1)) / 2;
    //     edgesValues.push_back(minEdgeCount);
    //     edgesValues.push_back(maxEdgeCount);
        
    //     for (int i = 1; i < 4; ++i) {
    //         edgesValues.push_back(minEdgeCount + (maxEdgeCount - minEdgeCount)/4 * i);
    //     }
    //     sort(edgesValues.begin(), edgesValues.end());

    //     int baseGraph = ((x-1) * 5) + 1;
    //     cout << "Grafos " << baseGraph << "-" << x*5 << " com " << vertices << " vértices:" << endl;
    //     for (int i = 0; i < edgesValues.size(); i ++) {
    //         cout << "Grafo " << baseGraph + i << ": " << edgesValues[i] << " arestas." << endl;
    //     }
    //     cout << endl;

    //     for (int edges : edgesValues) {
    //         vector<vector<int>> graph = generateGraph(vertices, edges);
    //         double executionTime = measureTime(seuAlgoritmo, graph);

    //        cout << "Vertices: " << vertices << ", Arestas: " << edges << ", Tempo: " << executionTime << " segundos";
    //     }
    // }
}
};
#endif