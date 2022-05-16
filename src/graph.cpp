#include "../include/graph.h"
#include "../include/minHeap.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

void Graph::addEdge(int src, int dest, int duration, int cap) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, duration, cap});
    if (!hasDir) nodes[dest].adj.push_back({src, cap});
}


Graph buildGraph(int id, bool hasDir) {

    string path;
    if (id >= 10)
        path = "../data/in" + to_string(id) + ".txt";
    else
        path = "../data/in0" + to_string(id) + ".txt";

    string aux;
    int numNodes;

    fstream file(path);
    getline(file, aux);
    stringstream ss(aux);
    ss >> numNodes;
    file.close();

    Graph graph = Graph(numNodes, hasDir);

    vector<FileContents> nodes = read_file(path);

    for (int i = 1; i < nodes.size(); i++) {
        FileContents item = nodes[i];
        graph.addEdge(item.pred, item.dest, item.duration, item.capacity);
    }

    return graph;
}


int Graph::dijkstra_distance(int a, int b) {

    for (int i = 1; i <= n; i++) {
        nodes[i].dist = INF;
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }
    nodes[a].dist = 0;
    nodes[a].pred = -1;

    MinHeap<int, int> heap(n, -1);
    for (int i = 1; i <= n; i++)
        heap.insert(i, nodes[i].dist);

    while (heap.getSize() > 0) {
        int u = heap.removeMin();
        nodes[u].visited = true;

        for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {

            int v = nodes[it->dest].dist;
            int cost = it->cap + nodes[u].dist;

            if (v > cost && !nodes[it->dest].visited) {
                nodes[it->dest].dist = cost;
                v = cost;
                nodes[it->dest].pred = u;
                heap.decreaseKey(it->dest, v);
            }
        }
    }

    if (nodes[b].dist != (INF))
        return nodes[b].dist;
    return -1;
}


list<int> Graph::dijkstra_path(int a, int b) {

    dijkstra_distance(a, b);
    list<int> path = {b};
    int parent = b;

    if (nodes[b].pred == -1)
        return {};

    while (parent != a) {
        parent = nodes[parent].pred;
        path.push_front(parent);
    }

    return path;
}


