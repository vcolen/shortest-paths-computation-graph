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

bool fileExists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void graphToCSV(const std::vector<std::vector<int>> &graph, const std::string &filename)
{
    // Check if the file already exists
    if (fileExists(filename))
    {
        std::cerr << "File already exists: " << filename << std::endl;
        return;
    }

    // Create a new file
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error creating/opening file: " << filename << std::endl;
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
        file << std::endl;
    }

    file.close();
}

vector<vector<int>> ReadCSV(const string& filename) {
        vector<vector<int>> graph;
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<int> row;
                stringstream ss(line);
                string cell;

                while (getline(ss, cell, ',')) {
                    row.push_back(stoi(cell));
                }

                graph.push_back(row);
            }

            file.close();
        } else {
            cerr << "Error: Unable to open file " << filename << endl;
        }

        return graph;
    }

int main()
{
    GraphGenerator graphGenerator = GraphGenerator();

    int y = 1; // Graph Counter
    for (int x = 1; x <= 2; ++x)
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
            //vector<vector<int>> graph = graphGenerator.generateGraph(vertices, edges);
            vector<vector<int>> graph = ReadCSV("Graphs/Graph_" + to_string(y) + ".csv");
            clock_t end = clock();
            double duration = double(end - start) / CLOCKS_PER_SEC;

            // graphToCSV(graph, "Graphs/Graph_" + to_string(y) + ".csv");

            cout << "Grafo " + to_string(y) << ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;
            cout << "Vertices: " << vertices << ", Arestas: " << edges << endl
                 << endl;
            y++;

            // Dijkstra dijkstra = Dijkstra();
            // clock_t start = clock();
            // dijkstra.dijkstra(graph, 0);
            // clock_t end = clock();
            // double duration = double(end - start) / CLOCKS_PER_SEC;
            // cout << "Dijkstra, "<< ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;

            // BellmanFord bellmanFord = BellmanFord(graph.size());
            // start = clock();
            // bellmanFord.bellmanFord(graph, 0);
            // end = clock();
            // duration = double(end - start) / CLOCKS_PER_SEC;
            // cout << "Bellman-Ford, "<< ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;

            // FloydWarshaw floydWarshaw = FloydWarshaw();
            // start = clock();
            // floydWarshaw.floydWarshaw(graph);
            // end = clock();
            // duration = double(end - start) / CLOCKS_PER_SEC;
            // cout << "Floyd Warshaw," << " Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;
            // cout << endl;

            // Johnson johnson = Johnson();
            // start = clock();
            // johnson.johnson(graph);
            // end = clock();
            // duration = double(end - start) / CLOCKS_PER_SEC;
            // cout << "Johsnon, "<< ", Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;

            // OPF opf = OPF();
            // start = clock();
            // opf.opf(graph, 0);
            // end = clock();
            // duration = double(end - start) / CLOCKS_PER_SEC;
            // cout << "OPF,"
            //      << " Tempo: " << duration << " segundos ou " << double(end - start) << "ms" << endl;
            // cout << endl;
        }
    }
    return 0;
}