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
    /**
     * Builds a graph
     * @param nodes
     * @param includeResidual
     */
    explicit Graph(int nodes, bool includeResidual = false);

    /**
     * Builds the transpose graph
     * @return transposed graph
     */
    Graph *transpose();

    /**
     * Adds an edge to the graph that connects src and dest
     * @param src
     * @param dest
     * @param duration
     * @param cap
     */
    void addEdge(int src, int dest, int duration, int cap = 1);

    /**
     * Calculates a maximum capacity path for the graph
     * @param a
     * @param b
     * @return max capacity
     */
    int maximum_capacity(int a, int b);

    /**
     * Among the maximum capacity paths,
     * it calculates the shortest one
     * @param a
     * @param b
     * @param max
     * @return max capacity
     */
    int maximum_capacity_with_shortest_path(int a, int b, int max = INT32_MAX);

    /**
     * Among the shortest paths, it calculates
     * the path with the highest capacity
     * @param a
     * @param b
     * @param min
     * @return capacity
     */
    int shortest_path_with_maximum_capacity(int a, int b, int min = INT32_MIN);

    /**
     * Gets the path of the last used algorithm
     * @param a
     * @param b
     * @return path
     */
    list<int> get_path(int a, int b);

    /**
     * It traverses the graph using a depth-first search
     * @param v
     * @return number of nodes
     */
    int dfs(int v);


    bool bfs_sink(int u, int v);

    // stack<int> topologicalSorting();

    /**
     * Calculates de topological sorting path using dfs
     * @param v
     * @param l
     */
    void dfsTopSort(int v, stack<int> &l);

    /**
     * Checks the graph for cycles
     * @param v
     * @return
     */
    bool cycleDfs(int v);

    /**
     * Prints the earliest start of the last node
     */
    void print_readyAt();

    /**
     * Calculates the critical path of the graph using latest finish
     */
    void critical_path_lf();


    void max_FL();

    void max_FT();

    void max_path_dag();

    /**
     * Checks if there is a shortest path with the capacity higher or equal
     * than the one given. If so, then it outputs the result to the user.
     * @param groupSize
     * @return true if path found, false otherwise
     */
    bool cen_2_1(int groupSize);

    /**
     * Bfs used to calculate edmonds_karp_algorithm
     * @param s
     * @param t
     * @return 1 if node t is reached, false otherwise
     */
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