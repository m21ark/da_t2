#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <climits>
#include <vector>
#include <list>
#include <iostream>
#include "set"
#include <queue>
#include "stack"
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
        int dest, duration, cap, flow, residual;
    };

    struct Node {
        list<Edge> adj;
        int dist;
        int capacity;
        int pred;
        Color color;
        bool visited;
        int degree = 0;
        int FT_MAX = 0;
        int level;
    };

    int n;
    bool includeResidual;
    vector<Node> nodes;

public:

    explicit Graph(int nodes, bool includeResidual = false);

    void addEdge(int src, int dest, int duration, int cap = 1);

    int dijkstra_distance(int a, int b);

    int maximum_capacity(int a, int b);

    int maximum_capacity_with_shortest_path(int a, int b, int max = INT32_MAX);

    int shortest_path_with_maximum_capacity(int a, int b, int min = INT32_MIN);

    list<int> get_path(int a, int b);

    int dfs(int v);

    bool bfs_sink(int u, int v);

    stack<int> topologicalSorting();

    void dfsTopSort(int v, stack<int> &l);

    bool cycleDfs(int v);

    void printEdges();

    void activity_readyAt();

    void print_readyAt();

    void max_waited_time();

    void max_path_dag();

    void cen_2_1(int groupSize);

    // ----------------------------------------------------

    int edmonds_karp_bfs(int s, int t);

    int dinic_algo();

    int send_dinic_flow(int s, int flow, int t);

    int edmonds_karp();

    void edmonds_karp_update(int bottleNeck, int s, int t);

    int getPathBottleNeck(int start, int end);

    int edmonds_karp_flow_path(int s, int t);
};

Graph buildGraph(int id, bool includeResidual = false);

#endif