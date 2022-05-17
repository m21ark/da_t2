#include <iostream>
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main() {
    Graph graph = buildGraph(1);
    //Menu::start();

    graph.dfs(2);

    getchar();
    return 0;
}
