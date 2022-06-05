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

/**
 * Possible node colors
 */
enum Color {
    WHITE, GREY, BLACK
};

/**
 * Graph class representation using adjacent lists
 */
class Graph {

    /**
     * Union between to Nodes
     */
    struct Edge {
        int dest, duration, cap, flow, residual;
    };

    /**
     * Represents a Node in the Graph
     */
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

    // Important information about Graph Object
    int n;
    bool includeResidual;
    vector<Node> nodes;

public:
    /**
     * Builds a graph
     * @param nodes number of nodes
     * @param includeResidual true if residual edges should be included, false otherwise
     */
    explicit Graph(int nodes, bool includeResidual = false);

    /**
     * Builds the transpose graph
     * @return transposed graph
     */
    Graph *transpose();

    /**
     * Adds an edge to the graph that connects src and dest
     * @param src start node
     * @param dest end node
     * @param duration time taken to go from src to dest node
     * @param cap capacity
     */
    void addEdge(int src, int dest, int duration, int cap = 1);

    /**
     * Calculates a maximum capacity path for the graph
     * @return max capacity
     */
    int maximum_capacity();

    /**
     * Among the maximum capacity paths,
     * it calculates the shortest one
     * @param max distance limiter
     * @return max capacity
     */
    int maximum_capacity_with_shortest_path(int max = INT32_MAX);

    /**
     * Among the shortest paths, it calculates
     * the path with the highest capacity
     * @param min capacity limiter
     * @return capacity of path from a to b
     */
    int shortest_path_with_maximum_capacity(int min = INT32_MIN);

    /**
     * Gets the path of the last used algorithm
     * @return path from a to b
     */
    list<int> get_path();

    /**
     * It traverses the graph using a depth-first search
     * @param v start node
     * @return number of nodes
     */
    int dfs(int v);

    /**
     * Bfs that only considers non saturated edges
     * Sets level for nodes
     * @param u start node
     * @param v end node
     * @return boolean if v was visited by the bfs
     */
    bool bfs_sink(int u, int v);

    // stack<int> topologicalSorting();

    /**
     * Calculates de topological sorting path using dfs
     * @param v start node
     * @param l stack of sorted nodes
     */
    void dfsTopSort(int v, stack<int> &l);

    /**
     * Checks the graph for cycles
     * @param v start node
     * @return true if cycle found, false otherwise
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

    /**
     * Calculates the maximum "Folga livre"
     */
    void max_FL();

    /**
     * Calculates the maximum "Folga total"
     */
    void max_FT();

    /**
     * Bfs update of the earliest start for paths containing flow
     */
    void max_path_dag();

    /**
     * Checks if there is a shortest path with the capacity higher or equal
     * than the one given. If so, then it outputs the result to the user.
     * @param groupSize group size to look for
     * @return true if path found, false otherwise
     */
    bool cen_2_1(int groupSize);

    /**
     * Bfs used to calculate edmonds_karp_algorithm
     * @param s start node
     * @param t end node
     * @return 1 if node t is reached, false otherwise
     */
    int edmonds_karp_bfs(int s, int t);

    /**
     * Calculates the maximum flow of a graph from start to finish using Dinic's algorithm
     * @return max flow
     */
    int dinic_algo();

    /**
     * Recursive part of the Dinic's algorithm that finds available path to the sink node
     * @param s start node
     * @param flow current flow along the recursive chain
     * @param t end node
     * @return flow found along the path
     */
    int send_dinic_flow(int s, int flow, int t);

    /**
     * Main edmonds karp algorithm
     * Calculates the maximum flow in a graph from s to t
     * @param groupSize_limiter max flow bottleneck
     * @return max flow of the graph
     */
    int edmonds_karp(int groupSize_limiter = 0);

    /**
     * Updates the residual and flow parameters of the path found
     * @param bottleNeck the minimum capacity
     * @param s start node
     * @param t end node
     */
    void edmonds_karp_update(int bottleNeck, int s, int t);

    /**
     * Get the minimum capacity edge along the path
     * @param start start node
     * @param end end node
     * @return minimum capacity along the path
     */
    int getPathBottleNeck(int start, int end);

    /**
     * Finds a flow path to the sink node
     * @param s start node
     * @param t end node
     * @return flow of the path found
     */
    int edmonds_karp_flow_path(int s, int t);
};

Graph buildGraph(int id, bool includeResidual = false);

#endif