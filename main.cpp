#include <iostream>
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Menu::start();

    Graph graph = buildGraph(92, true);
    cout << graph.edmonds_karp();

    return 0;
}
