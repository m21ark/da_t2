#include <iostream>
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main() {

    Graph graph = buildGraph(1);
    cout << graph.dijkstra_distance(1, 50) << endl;

    Menu::start();

    getchar();
    return 0;
}
