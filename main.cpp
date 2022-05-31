#include <iostream>
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Menu::start();

    Graph graph = buildGraph(100, true);

    //cout << graph.fordFulkerson(1, 5, graph);

    cout << "Here!" << endl;
    cout << graph.solve();
    cout << "\nHere2!" << endl;

    graph.activity_readyAt();
    graph.print_readyAt();

    graph.printResidual();

    /*auto p = graph.path_flow(1, 6);

    cout << "flow : " << p.first << endl;

    for (auto e: p.second)
        cout << e << " ";*/


    getchar();
    return 0;
}
