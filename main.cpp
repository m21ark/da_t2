#include <iostream>
#include "include/graph.h"

using namespace std;

int main() {
    cout << "Starting to build graph...\n";
    Graph graph = buildGraph(10);
    cout << "Graph Built!\n";

    cout << graph.dijkstra_distance(1, 5000) << endl;

    getchar();
    return 0;
}
