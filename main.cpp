#include <iostream>
#include "include/graph.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Menu::start();

    Graph graph = buildGraph(93, true);
    // int maxFlow = graph.edmonds_karp();
    // cout << "Max Flow: " << maxFlow << endl;

    // NEEDS TO HAVE ALL EDGES WITH FLOW ZERO TO EXECUTE , above can't be uncomment.
    int maxFlow = graph.dinic_algo();
    cout << "Max Flow: " << maxFlow << endl;

    graph.max_path_dag();
    graph.print_readyAt();
    graph.max_waited_time();

    return 0;
}
