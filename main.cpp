#include <iostream>
#include <vector>
#include "GraphGenerator.h"

using namespace std;

int main() {
    GraphGenerator gg = GraphGenerator();
    vector<vector<int>> graph = gg.generateGraph(9, 9);
    gg.printGraph(graph);
    return 0;
}