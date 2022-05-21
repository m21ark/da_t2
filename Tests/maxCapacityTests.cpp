#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/graph.h"

using namespace std;

TEST(MaxCapacity, cenario_1_1) {
    cout << "\tTesting MaxCapacity - cenario_1_1\n" << endl;

    Graph graph1 = buildGraph(99, true);
    Graph graph2 = buildGraph(98, true);
    Graph graph3 = buildGraph(97, true);


    // Graph 1
    ASSERT_EQ(4 , graph1.maximum_capacity(1, 6));
    list<int> path_result = graph1.get_path(1, 6);
    list<int> path1_1 = {1, 4, 3, 6};
    list<int> path1_2 = {1, 4, 2, 3, 6};
    ASSERT_EQ(true, path_result == path1_1 || path_result == path1_2);


    // Graph 2
    ASSERT_EQ(7 , graph2.maximum_capacity(1, 6));
    path_result = graph2.get_path(1, 6);
    path1_1 = {1, 2, 4, 5, 6};
    ASSERT_EQ(path1_1, path_result);


    // Graph 3
    ASSERT_EQ(6 , graph3.maximum_capacity(1, 10));
    path_result = graph3.get_path(1, 10);
    path1_1 = {1, 2, 3, 4, 5, 10}; //escolhe este
    path1_2 = {1, 9, 5, 10};
    list<int> path1_3 = {1, 6, 7, 8, 5, 10};
    ASSERT_EQ(true, path_result == path1_1 || path_result == path1_2 || path_result == path1_3);
}



TEST(MaxCapacity, cenario_1_2_max_capacity_with_shortest_path) {
    cout << "\tTesting MaxCapacity with Shortest Path - cenario_1_2\n" << endl;

    Graph graph1 = buildGraph(99, true);
    Graph graph2 = buildGraph(98, true);
    Graph graph3 = buildGraph(97, true);
    Graph graph4 = buildGraph(96, true);


    // Graph 1
    ASSERT_EQ(4 , graph1.maximum_capacity_with_shortest_path(1, 6));
    list<int> path_result = graph1.get_path(1, 6);
    list<int> path = {1, 4, 3, 6};
    ASSERT_EQ(path, path_result);


    // Graph 2
    ASSERT_EQ(7 , graph2.maximum_capacity_with_shortest_path(1, 6));
    path_result = graph2.get_path(1, 6);
    path = {1, 2, 4, 5, 6};
    ASSERT_EQ(path, path_result);


    // Graph 3
    ASSERT_EQ(6 , graph3.maximum_capacity_with_shortest_path(1, 10));
    path_result = graph3.get_path(1, 10);
    path = {1, 9, 5, 10};
    ASSERT_EQ(path, path_result);


    // Graph 4
    ASSERT_EQ(9 , graph4.maximum_capacity_with_shortest_path(1, 16));
    path_result = graph4.get_path(1, 16);
    path = {1, 9, 10, 11, 12, 16};
    ASSERT_EQ(path, path_result);
}




TEST(MaxCapacity, cenario_1_2_max_shortest_path_with_maximum_capacity) {
    cout << "\tTesting Shortest Path with Max Capacity - cenario_1_2\n" << endl;

    Graph graph1 = buildGraph(99, true);
    Graph graph2 = buildGraph(98, true);
    Graph graph3 = buildGraph(97, true);
    Graph graph4 = buildGraph(96, true);


    // Graph 1
    ASSERT_EQ(4 , graph1.shortest_path_with_maximum_capacity(1, 6));
    list<int> path_result = graph1.get_path(1, 6);
    list<int> path = {1, 4, 3, 6};;
    ASSERT_EQ(path, path_result);

    // Graph 2
    ASSERT_EQ(6 , graph2.shortest_path_with_maximum_capacity(1, 6));
    path_result = graph2.get_path(1, 6);
    path = {1, 5, 6};
    ASSERT_EQ(path, path_result);

    // Graph 3
    ASSERT_EQ(5 , graph3.shortest_path_with_maximum_capacity(1, 10));
    path_result = graph3.get_path(1, 10);
    path = {1, 10};
    ASSERT_EQ(path, path_result);

    // Graph 4
    ASSERT_EQ(6 , graph4.shortest_path_with_maximum_capacity(1, 16));
    path_result = graph4.get_path(1, 16);
    path = {1, 5, 7, 8, 16};
    ASSERT_EQ(path, path_result);

}