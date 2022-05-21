#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/graph.h"

using namespace std;

TEST(MaxCapacity, cenario_1_1) {
    cout << "\tTesting MaxCapacity - cenario_1_1\n" << endl;

    Graph graph1 = buildGraph(99, true);
    Graph graph2 = buildGraph(98, true);

    // Graph 1
    ASSERT_EQ(4 , graph1.maximum_capacity_distance(1, 6));
    list<int> path_result = graph1.get_path(1, 6);
    list<int> path1_1 = {1, 4, 3, 6};
    list<int> path1_2 = {1, 4, 2, 3, 6};
    ASSERT_EQ(true, path_result == path1_1 || path_result == path1_2);

    // Graph 2
    ASSERT_EQ(7 , graph2.maximum_capacity_distance(1, 6));
    path_result = graph2.get_path(1, 6);
    path1_1 = {1, 2, 4, 5, 6};
    ASSERT_EQ(path1_1, path_result);
}

TEST(MaxCapacity, cenario_1_2) {

}



