#include <iostream>
#include "gtest/gtest.h"
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Menu::start();

    Graph graph = buildGraph(94, true);

    // cout << graph.fordFulkerson(1, 6, graph);

    cout << "Here!" << endl;
    cout << graph.solve();
    cout << "\nHere2!" << endl;
    graph.printResidual();

    /*auto p = graph.path_flow(1, 6);

    cout << "flow : " << p.first << endl;

    for (auto e: p.second)
        cout << e << " ";*/


    //getchar();
    return 0;
}
