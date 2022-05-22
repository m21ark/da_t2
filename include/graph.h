#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <climits>
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include "readFiles.h"
#include "../include/minHeap.h"
#include "../include/maxHeap.h"

#define INF ( INT_MAX / 2)

using namespace std;

enum Color {
    WHITE, GREY, BLACK
};

class Graph {

    struct Edge {
        int dest, duration, cap;
    };

    struct Node {
        list<Edge> adj;
        int dist;
        int capacity;
        int pred;
        Color color;
        bool visited;
    };

    int n;
    bool hasDir;
    vector<Node> nodes;

public:

    explicit Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, int duration, int cap = 1);

    int dijkstra_distance(int a, int b);

    int maximum_capacity(int a, int b);

    int maximum_capacity_with_shortest_path(int a, int b);

    int shortest_path_with_maximum_capacity(int a, int b);

    list<int> get_path(int a, int b);

    int dfs(int v);

    void bfs(int v);

    int outDegree(int v);

    int connectedComponents();

    int giantComponent();

    list<int> topologicalSorting();

    void dfsTopSort(int v, list<int> &l);

    int distance(int a, int b);

    int diameter();

    bool hasCycle();

    bool cycleDfs(int v);

    int prim(int r);

};

Graph buildGraph(int id, bool hasDir = false);

#endif