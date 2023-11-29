#include <iostream>
#include <vector>
#include "GraphGenerator.h"
#include "Dijkstra.h"
#include "FloydWarshaw.h"

using namespace std;

int main() {
    GraphGenerator gg = GraphGenerator();
    vector<vector<int>> graph = gg.generateGraph(5, 10);
    gg.printGraph(graph);

    Dijkstra dijk = Dijkstra(graph.size());
    FloydWarshaw fw = FloydWarshaw();
    fw.floydWarshall(graph);
    dijk.dijkstra(graph, 0);

    return 0;
}