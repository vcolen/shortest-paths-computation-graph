#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

class Dijkstra
{

public:

    const int verticesCount;

    Dijkstra(int count) : verticesCount(count) {}

    int getMinimumDistanceVertexIndex(int distances[], bool isShortestPathTreeSet[])
    {
        int minimumDistance = INT_MAX;
        int minimumDistanceIndex;

        for (int vertex = 0; vertex < verticesCount; vertex++)
            // Se não estiver na árvore (para evitar ciclos) e a distância for menor,
            // esse se torna o novo vértice escolhido
            if (!isShortestPathTreeSet[vertex] && distances[vertex] <= minimumDistance)
                minimumDistance = distances[vertex], minimumDistanceIndex = vertex;

        return minimumDistanceIndex;
    }

    void printSolution(int distances[])
    {
        cout << "Vértice \t Distância a partir da Fonte" << endl;
        for (int i = 0; i < verticesCount; i++)
            cout << i << " \t\t\t\t" << distances[i] << endl;
    }

    void dijkstra(vector<vector<int>>& graph, int source)
    {
        int verticesCount = graph.size();

        int distances[verticesCount]; // Contém as distâncias da fonte para os outros vértices
        bool shortestPathTreeSet[verticesCount];

        // Inicializando os vetores
        for (int i = 0; i < verticesCount; i++)
            distances[i] = INT_MAX, shortestPathTreeSet[i] = false;

        distances[source] = 0;

        // Encontrar o caminho mais curto para todos os outros vértices
        for (int count = 0; count < verticesCount - 1; count++)
        {
            int minimumDistanceVertexIndex = getMinimumDistanceVertexIndex(distances, shortestPathTreeSet);

            // Marca o vértice escolhido como incluso na árvore
            shortestPathTreeSet[minimumDistanceVertexIndex] = true;

            // Atualiza o valor de distância dos vértices adjacentes
            for (int v = 0; v < verticesCount; v++)

                // Atualiza distances[v] somente se:
                // - Vértice v não está no conjunto da árvore de caminho mais curto,
                // - Existe uma aresta de minimumDistanceVertexIndex para v,
                // - A distância total do caminho de source para v, passando por minimumDistanceVertexIndex,
                // é menor do que o valor atual de distances[v]
                if (!shortestPathTreeSet[v] &&
                    graph[minimumDistanceVertexIndex][v] &&
                    distances[minimumDistanceVertexIndex] != INT_MAX &&
                    distances[minimumDistanceVertexIndex] + graph[minimumDistanceVertexIndex][v] < distances[v])
                {
                    distances[v] = distances[minimumDistanceVertexIndex] + graph[minimumDistanceVertexIndex][v];
                }
        }

        //printSolution(distances);
    }

    // int main()
    // {
    //     int graph[verticesCount][verticesCount] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
    //                                                  {4, 0, 8, 0, 0, 0, 0, 11, 0},
    //                                                  {0, 8, 0, 7, 0, 4, 0, 0, 2},
    //                                                  {0, 0, 7, 0, 9, 14, 0, 0, 0},
    //                                                  {0, 0, 0, 9, 0, 10, 0, 0, 0},
    //                                                  {0, 0, 4, 14, 10, 0, 2, 0, 0},
    //                                                  {0, 0, 0, 0, 0, 2, 0, 1, 6},
    //                                                  {8, 11, 0, 0, 0, 0, 1, 0, 7},
    //                                                  {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    //     dijkstra(graph, 0);

    //     return 0;
    // }
};
#endif