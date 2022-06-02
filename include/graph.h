#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <climits>
#include <vector>
#include <list>
#include <iostream>
#include "set"
#include "map"
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
        int level = 0;
        int ES = 0;
        int LF = 0;
    };

    int n;
    bool includeResidual;
    vector<Node> nodes;

public:

    explicit Graph(int nodes, bool includeResidual = false);

    inline Graph* transpose() {
        auto *graph = new Graph(n, true);
        for (int i = 1; i <= n; ++i) {
            for (auto n : nodes[i].adj) {
                graph->addEdge(n.dest,i, n.duration, n.cap);
                graph->nodes[n.dest].visited = nodes[n.dest].visited;
            }
        }
        return graph;
    }

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

    void critical_path_lf();

    void max_FL();

    void max_FT();

    void max_path_dag();

    bool cen_2_1(int groupSize);

    int edmonds_karp_bfs(int s, int t);

    int dinic_algo();

    int send_dinic_flow(int s, int flow, int t);

    int edmonds_karp(int groupSize_limiter = 0);

    void edmonds_karp_update(int bottleNeck, int s, int t);

    int getPathBottleNeck(int start, int end);

    int edmonds_karp_flow_path(int s, int t);
};

Graph buildGraph(int id, bool includeResidual = false);

#endif