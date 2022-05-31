#include <iostream>
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Menu::start();

    Graph graph = buildGraph(92, true);
    int maxFlow = graph.edmonds_karp();
    cout << "Max Flow: " << maxFlow;

    return 0;
}
