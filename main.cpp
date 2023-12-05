#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "GraphGenerator.h"
#include "Dijkstra.h"
#include "FloydWarshaw.h"
#include "Bellman-Ford.h"
#include "OPF.h"
#include "Johnson.h"

using namespace std;

bool fileExists(const string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void graphToCSV(const vector<vector<int>> &graph, const string &filename)
{
    // Check if the file already exists
    if (fileExists(filename))
    {
        cerr << "File already exists: " << filename << endl;
        return;
    }

    // Create a new file
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error creating/opening file: " << filename << endl;
        return;
    }

    for (const auto &row : graph)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i];
            if (i < row.size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

vector<vector<int>> ReadCSV(const string &filename)
{
    vector<vector<int>> graph;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            vector<int> row;
            stringstream ss(line);
            string cell;

            while (getline(ss, cell, ','))
            {
                row.push_back(stoi(cell));
            }

            graph.push_back(row);
        }

        file.close();
    }
    else
    {
        cerr << "Error: Unable to open file " << filename << endl;
    }

    return graph;
}

// Generic function to measure the execution time of a graph algorithm
template <typename GraphAlgorithm>
void measureAlgorithmTime(GraphAlgorithm &algorithm, vector<vector<int>> &graph)
{
    clock_t start, end;
    double duration;

    start = clock();
    algorithm(graph);
    end = clock();

    duration = double(end - start) / CLOCKS_PER_SEC;

    cout << typeid(GraphAlgorithm).name() << ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;
}

int main()
{
    GraphGenerator graphGenerator = GraphGenerator();

    int y = 1; // Graph Counter
    for (int x = 1; x <= 5; ++x)
    {
        int vertices = pow(5, x);

        // Gera valores equidistantes para as arestas
        vector<int> edgesValues;
        int minEdgeCount = vertices - 1;
        int maxEdgeCount = (vertices * (vertices - 1)) / 2;
        edgesValues.push_back(minEdgeCount);
        edgesValues.push_back(maxEdgeCount);

        for (int i = 1; i < 4; ++i)
        {
            edgesValues.push_back(minEdgeCount + (maxEdgeCount - minEdgeCount) / 4 * i);
        }
        sort(edgesValues.begin(), edgesValues.end());

        for (int edges : edgesValues)
        {
            clock_t start = clock();
            vector<vector<int>> graph = graphGenerator.generateGraph(vertices, edges);
            graphToCSV(graph, "Graphs/Graph_" + to_string(y) + ".csv");
            // vector<vector<int>> graph = ReadCSV("Graphs/Graph_" + to_string(y) + ".csv");
            clock_t end = clock();
            double duration = double(end - start) / CLOCKS_PER_SEC;

            cout << "Grafo " + to_string(y) << ", Tempo: " << duration << " segundos ou " << end - start << "ms" << endl;
            cout << "Vertices: " << vertices << ", Arestas: " << edges << endl;
            y++;

            Dijkstra dijkstra;
            measureAlgorithmTime(dijkstra, graph);

            BellmanFord bellmanFord;
            measureAlgorithmTime(bellmanFord, graph);

            FloydWarshaw floydWarshaw;
            measureAlgorithmTime(floydWarshaw, graph);

            OPF opf;
            measureAlgorithmTime(opf, graph);

            Johnson johnson;
            measureAlgorithmTime(johnson, graph);
            cout << endl;
        }
    }
    return 0;
}