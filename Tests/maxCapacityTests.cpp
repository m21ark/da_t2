#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/graph.h"

using namespace std;

TEST(MaxCapacity, cenario_1_1) {
    cout << "\tTesting MaxCapacity - cenario_1_1\n" << endl;

    Graph graph1 = buildGraph(99, true);
    Graph graph2 = buildGraph(98, true);

    ASSERT_EQ(4 , graph1.maximum_capacity_distance(1, 6));
    ASSERT_EQ(7 , graph2.maximum_capacity_distance(1, 6));

}

TEST(MaxCapacity, cenario_1_2) {

}



