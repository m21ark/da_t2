#include <iostream>
#include "gtest/gtest.h"
#include "include/graph.h"
#include "include/menu.h"

using namespace std;

int main(int argc, char *argv[]) {

    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

    Graph graph = buildGraph(1);
    Menu::start();


    getchar();
    return 0;
}
