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
    };

    int n;
    bool includeResidual;
    vector<Node> nodes;

public:

    explicit Graph(int nodes, bool includeResidual = false);

    void addEdge(int src, int dest, int duration, int cap = 1);

    int dijkstra_distance(int a, int b);

    int maximum_capacity(int a, int b);

    int maximum_capacity_with_shortest_path(int a, int b);

    int shortest_path_with_maximum_capacity(int a, int b);

    list<int> get_path(int a, int b);

    int dfs(int v);

    void bfs(int v);

    int outDegree(int v);

    bool bfs2(int s, int t);

    pair<int, list<int>> path_flow(int a, int b);

    list<int> getResidualPath();

    int connectedComponents();

    int giantComponent();

    list<int> topologicalSorting();

    void dfsTopSort(int v, list<int> &l);

    int fordFulkerson(int s, int t, Graph graph);

    int distance(int a, int b);

    int diameter();

    bool hasCycle();

    bool cycleDfs(int v);

    int prim(int r);

    int solve() {
        int flow, maxFlow = 0;
        do {
            flow = bfs5(1, n);
            cout << "Current flow = " << flow << endl;
            maxFlow += flow;
        } while (flow != 0);
        return maxFlow;
    }


    int bfs5(int s, int t) {

        for (int i = 1; i <= n; i++) {
            nodes[i].visited = false;
            nodes[i].pred = -1;
        }


        queue<int> q;
        q.push(s);
        nodes[s].visited = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            if (node == t) break;

            for (auto e: nodes[node].adj) {
                int remaining_cap = e.cap - e.flow;
                if (remaining_cap > 0 && !nodes[e.dest].visited) {
                    nodes[e.dest].pred = node;
                    nodes[e.dest].visited = true;
                    q.push(e.dest);
                }
            }
        }

        // no path to the sink
        if (!nodes[t].visited) return 0;

        // ===========================================================================


        // Find augmented path and bottle neck
        int bottleNeck = INT_MAX;
        int parent = t;
        int child;

        while (parent != s) {
            child = parent;
            parent = nodes[parent].pred;

            for (Edge e: nodes[parent].adj)
                if (e.dest == child) {
                    bottleNeck = min(bottleNeck, e.cap - e.flow);
                    break;
                }
        }

        // ===========================================================================

        parent = t;
        cout << t << " --> ";
        while (parent != s) {
            child = parent;
            parent = nodes[parent].pred;

            cout << parent << " --> ";
            for (Edge &e: nodes[parent].adj)
                if (e.dest == child) {
                    e.flow += bottleNeck;
                    e.residual -= bottleNeck;
                    // adicionar à edge contrario
                }
        }

        // Return bottleneck flow
        return bottleNeck;
    }

    void printResidual() {
        for (int i = 1; i <= n; i++)
            for (Edge e: nodes[i].adj)
                printf("src: %d\tdest: %d\tcap: %d\tflow: %d\tresidualVal: %d\tresidual? %d\n", i, e.dest, e.cap,
                       e.flow, e.residual, e.cap == 0);
    }

    void activity_readyAt();
    void print_readyAt();
};

Graph buildGraph(int id, bool includeResidual = false);

#endif