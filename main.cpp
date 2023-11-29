#include <iostream>
#include <vector>
#include <ctime>

#include "GraphGenerator.h"
#include "Dijkstra.h"
#include "FloydWarshaw.h"
#include "Bellman-Ford.h"

using namespace std;

int main()
{
    GraphGenerator graphGenerator = GraphGenerator();

     for (int x = 1; x <= 5; ++x) {
        int vertices = pow(5, x);

        // Gera valores equidistantes para as arestas
        vector<int> edgesValues;
        int minEdgeCount = vertices-1;
        int maxEdgeCount = (vertices * (vertices - 1)) / 2;
        edgesValues.push_back(minEdgeCount);
        edgesValues.push_back(maxEdgeCount);
        
        for (int i = 1; i < 4; ++i) {
            edgesValues.push_back(minEdgeCount + (maxEdgeCount - minEdgeCount)/4 * i);
        }
        sort(edgesValues.begin(), edgesValues.end());

        for (int edges : edgesValues) {
            vector<vector<int>> graph = graphGenerator.generateGraph(vertices, edges);

            cout << "Vertices: " << vertices << ", Arestas: " << edges << endl;

            Dijkstra dijkstra = Dijkstra(graph.size());
            clock_t start = clock();
            dijkstra.dijkstra(graph, 0);
            clock_t end = clock();
            double duration = double(end - start) / CLOCKS_PER_SEC;
            cout << "Dijkstra, "<< ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;

            BellmanFord bellmanFord = BellmanFord(graph.size());
            start = clock();
            bellmanFord.bellmanFord(graph, 0);
            end = clock();
            duration = double(end - start) / CLOCKS_PER_SEC;
            cout << "Bellman-Ford, "<< ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;

            FloydWarshaw floydWarshaw = FloydWarshaw();
            start = clock();
            floydWarshaw.floydWarshaw(graph);
            end = clock();
            duration = double(end - start) / CLOCKS_PER_SEC;
            cout << "Floyd Warshaw," << " Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;
            cout << endl;
        }
    }
    return 0;
}