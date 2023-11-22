#include <iostream>
#include <limits.h>
#include <set>
#include <cmath>

using namespace std;

void dijkstra() {
    set<int> shortestPathTreeSet;
    int graph[4][4] = {
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
}

std::vector<std::vector<int> > generateGraph() {
        // Definindo x para determinar o número de vértices
    int x = 2;
    int vertices = pow(5, x);

    // Inicializando a semente para a função rand() com base no tempo atual
    srand(time(0));

    // Criando um array 2D para representar o grafo
    vector<vector<int> > graph(vertices, vector<int>(vertices, 0));

    // Definindo o intervalo total de arestas
    int minEdges = vertices - 1;
    int maxEdges = (vertices * (vertices - 1)) / 2;

    // Escolhendo valores equidistantes no intervalo para o número de arestas
    int numEdges = 5; // Por exemplo, escolhendo 5 valores equidistantes
    vector<int> edgeValues;

    // Distribuindo equidistantemente os valores no intervalo
    for (int i = 0; i < numEdges; ++i) {
        int value = minEdges + (i * (maxEdges - minEdges)) / (numEdges - 1);
        edgeValues.push_back(value);
    }

    // Adicionando arestas ao grafo
    for (int i = 0; i < numEdges; ++i) {
        for (int j = 0; j < edgeValues[i]; ++j) {
            int src = rand() % vertices;
            int dest = rand() % vertices;
            // Evitando auto-laços e arestas duplicadas
            if (src != dest && graph[src][dest] == 0 && graph[dest][src] == 0) {
                int weight = rand() % 10 + 1; // Atribuindo pesos aleatórios de 1 a 10
                graph[src][dest] = weight;
                graph[dest][src] = weight; // Considerando um grafo não direcionado
            }
        }
    }
    return graph;
}



int main() {
    std::vector<std::vector<int> > graph = generateGraph();
    
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[0].size(); j++) {
           cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}