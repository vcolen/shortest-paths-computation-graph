#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Graph
{
    int numberOfVertices;
    vector<vector<int>> adjacencyMatrix;

public:
    Graph(int vertices);

    // Função para adicionar uma aresta entre os dois vértices
    void addEdge(int source, int destination, int weight);

    // Algoritmo Bellman-Ford para achar o menor caminho
    void bellmanFord(int source);
};

Graph::Graph(int vertices) : numberOfVertices(vertices)
{
    // Inicializando a matriz de adjacência com todas as arestas valendo infinito
    adjacencyMatrix.resize(numberOfVertices, vector<int>(numberOfVertices, INT_MAX));
}

void Graph::addEdge(int source, int destination, int weight)
{
    // O grafo é NÃO-DIRECIONADO, portando arestas em ambas as direções
    adjacencyMatrix[source][destination] = weight;
    adjacencyMatrix[destination][source] = weight;
}

void Graph::bellmanFord(int source)
{
    // Inicializando o vetor de distâncias com todas as distâncias valendo infinito
    vector<int> distance(numberOfVertices, INT_MAX);
    distance[source] = 0;

    // Relaxando as arestas V-1 vezes
    for (int i = 1; i < numberOfVertices; ++i)
    {
        for (int u = 0; u < numberOfVertices; ++u)
        {
            for (int v = 0; v < numberOfVertices; ++v)
            {
                // Relaxação: Atualiza a distância se um caminho mais curto for encontrado
                if (adjacencyMatrix[u][v] != INT_MAX &&
                    distance[u] != INT_MAX &&
                    distance[u] + adjacencyMatrix[u][v] < distance[v])
                {
                    distance[v] = distance[u] + adjacencyMatrix[u][v];
                }
            }
        }
    }

    // Não iremos checar ciclos negativos pois estamos lidando somente
    // com arestas de peso positivo

    cout << "Distâncias mais curtas a partir do vértice de origem " << source << " são:" << endl;
    for (int i = 0; i < numberOfVertices; ++i)
    {
        cout << "Para o vértice " << i << ": " << distance[i] << endl;
    }
}

int main()
{
    Graph graph(5);

    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 7);

    graph.bellmanFord(0);

    return 0;
}
