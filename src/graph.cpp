#include "../include/graph.h"


Graph::Graph(int num, bool dir) : n(num), includeResidual(dir), nodes(num + 1) {}

void Graph::addEdge(int src, int dest, int duration, int cap) {

    if (src < 1 || src > n || dest < 1 || dest > n)
        return;

    nodes[src].adj.push_back({dest, duration, cap});

    if (includeResidual)
        nodes[dest].adj.push_back({src, duration, 0});
}

Graph buildGraph(int id, bool includeResidual) {

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

    Graph graph = Graph(numNodes, includeResidual);

    vector<FileContents> nodes = read_file(path);

    for (const FileContents &item: nodes)
        graph.addEdge(item.pred, item.dest, item.duration, item.capacity);

    return graph;
}


// Using BFS as a searching algorithm
bool Graph::bfs2(int s, int t) {

    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }

    nodes[s].visited = true;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto e: nodes[u].adj)
            if (!nodes[e.dest].visited && e.cap > 0) {
                q.push(e.dest);
                nodes[e.dest].pred = u;
                nodes[e.dest].visited = true;
            }
    }
    return (nodes[t].visited);
}


// Applying fordfulkerson algorithm
int Graph::fordFulkerson(int s, int t, Graph rGraph) {

    int max_flow = 0;

    // Set the residual values of edges
    while (rGraph.bfs2(s, t)) {

        int path_flow = INT_MAX;
        int currentNode = t;

        while (currentNode != s) {

            int u = nodes[currentNode].pred;

            for (auto e: nodes[currentNode].adj)
                if (e.dest == u) {
                    path_flow = min(path_flow, e.cap);
                    break;
                }

            currentNode = u;

            for (auto e: nodes[currentNode].adj)
                if (e.dest == u) {
                    e.cap -= path_flow;

                    for (auto e2: nodes[u].adj)
                        if (e2.dest == currentNode)
                            e2.cap += path_flow;

                    break;
                }


        }

        // Adding the path flows
        max_flow += path_flow;
    }

    return max_flow;
}

list<int> Graph::getResidualPath() {
    list<int> l;
    for (int i = 1; i < n; i++)
        for (Edge edge: nodes[i].adj) {
            int residualCap = edge.cap - edge.flow;
        }
    return l;
}

pair<int, list<int>> Graph::path_flow(int a, int b) {

    int max_flow = 999;
    //dijkstra_distance(a, b); call outside the function
    list<int> path = {b};
    int parent = b;

    if (nodes[b].pred == -1)
        return {};

    while (parent != a) {
        parent = nodes[parent].pred;
        max_flow = min(max_flow, nodes[parent].capacity);
        path.push_front(parent);
    }

    return {max_flow, path};

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


/*___________________________________SCENARIO 1___________________________________*/

int Graph::maximum_capacity(int a, int b) {
    for (int i = 1; i <= n; i++) {
        nodes[i].capacity = -1;
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }
    nodes[a].capacity = INF;
    nodes[a].pred = a;

    MaxHeap<int, int> maxHeap(n, -1);
    for (int i = 1; i <= n; i++)
        maxHeap.insert(i, nodes[i].capacity);

    while (maxHeap.getSize() > 0) {
        int u = maxHeap.removeMax();
        nodes[u].visited = true;

        for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {

            int newCap = min(nodes[u].capacity, it->cap);
            int currentCap = nodes[it->dest].capacity;

            if (newCap > currentCap && !nodes[it->dest].visited) {
                nodes[it->dest].capacity = newCap;
                nodes[it->dest].pred = u;
                maxHeap.increaseKey(it->dest, newCap);
            }
        }
    }
    return nodes[b].capacity;
}


int Graph::maximum_capacity_with_shortest_path(int a, int b) {
    for (int i = 1; i <= n; i++) {
        nodes[i].dist = INF;
        nodes[i].capacity = -1;
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }
    nodes[a].capacity = INF;
    nodes[a].dist = 0;
    nodes[a].pred = a;

    MaxHeap<int, int> maxHeap(n, -1);
    for (int i = 1; i <= n; i++)
        maxHeap.insert(i, nodes[i].capacity);

    while (maxHeap.getSize() > 0) {
        int u = maxHeap.removeMax();
        nodes[u].visited = true;

        for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {

            int newCap = min(nodes[u].capacity, it->cap);
            int currentCap = nodes[it->dest].capacity;
            int newDist = nodes[u].dist + 1;
            int currentDist = nodes[it->dest].dist;

            bool b1 = (newCap > currentCap && !nodes[it->dest].visited);
            bool b2 = (newCap == currentCap && newDist < currentDist && !nodes[it->dest].visited);

            if (b1 || b2) {
                nodes[it->dest].capacity = newCap;
                nodes[it->dest].dist = newDist;
                nodes[it->dest].pred = u;
                if (b1) maxHeap.increaseKey(it->dest, newCap);
            }
        }
    }
    return nodes[b].capacity;
}

int Graph::shortest_path_with_maximum_capacity(int a, int b) {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = INF;
        nodes[i].capacity = 0;
    }

    nodes[a].visited = true;
    nodes[a].dist = 0;
    nodes[a].capacity = INF;

    MinHeap<int, int> minHeap(n, -1); // queue of unvisited nodes
    for (int i = 1; i <= n; i++)
        minHeap.insert(i, nodes[i].dist);

    while (minHeap.getSize() > 0) { // while there are still unvisited nodes
        int u = minHeap.removeMin();
        nodes[u].visited = true;

        //cout << u << " "; // show node order
        for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {

            int newCap = min(nodes[u].capacity, it->cap);
            int currentCap = nodes[it->dest].capacity;
            int newDist = nodes[u].dist + 1;
            int currentDist = nodes[it->dest].dist;

            bool b1 = (currentDist > newDist && !nodes[it->dest].visited);
            bool b2 = (currentDist == newDist && newCap > currentCap && !nodes[it->dest].visited);

            if (b1 || b2) {
                nodes[it->dest].capacity = newCap;
                nodes[it->dest].dist = newDist;
                nodes[it->dest].pred = u;
                if (b1) minHeap.decreaseKey(it->dest, newDist);
            }
        }
    }
    return nodes[b].capacity;
}

/*___________________________________/SCENARIO 1___________________________________*/

list<int> Graph::get_path(int a, int b) {

    //dijkstra_distance(a, b); call outside the function
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


// Depth-First Search: example implementation
int Graph::dfs(int v) {
    cout << v << " "; // show node order
    int count = 1;
    nodes[v].visited = true;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
            count += dfs(w);
        }
    }
    return count;
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    nodes[v].dist = 0;
    for (int i = 1; i <= n; i++) nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        cout << u << " "; // show node order
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
}


int Graph::outDegree(int v) {
    if (v < 1 || v > n) return -1;
    return (int) nodes[v].adj.size();
}


int Graph::connectedComponents() {
    int count = 0;
    for (int i = 1; i <= n; i++)
        if (!nodes[i].visited) {
            count++;
            dfs(i);
        }
    return count;
}


int Graph::giantComponent() {
    int maxSize = -1;
    for (int i = 1; i <= n; i++)
        if (!nodes[i].visited)
            maxSize = max(dfs(i), maxSize);
    return maxSize;
}


stack<int> Graph::topologicalSorting() {

    for (int i = 1; i <= n; i++)
        nodes[i].visited = false;

    stack<int> order;

    for (int i = 1; i <= n; i++)
        if (!nodes[i].visited)
            dfsTopSort(i, order);

    return order;
}

void Graph::dfsTopSort(int v, stack<int> &l) {
    nodes[v].visited = true;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfsTopSort(w, l);
    }
    l.push(v);
}


int Graph::distance(int a, int b) {
    if (a == b) return 0;
    for (int i = 1; i <= n; i++)
        nodes[i].dist = -1;
    bfs(a);
    return nodes[b].dist;
}


int Graph::diameter() {
    if (connectedComponents() > 1) return -1;

    bfs(1);
    int d = 0;

    for (int i = 1; i <= n; i++)
        d = max(d, nodes[i].dist);
    return d;
}


bool Graph::hasCycle() {
    for (int i = 1; i <= n; i++)
        nodes[i].color = WHITE;
    return cycleDfs(1);
}

bool Graph::cycleDfs(int v) {
    nodes[v].color = GREY;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (nodes[w].color == GREY) return true;
        else if (nodes[w].color == WHITE)
            return cycleDfs(w);
    }
    nodes[v].color = BLACK;
    return false;
}


int Graph::prim(int r) {

    MinHeap<int, int> heap(n, -1);

    for (int i = 1; i <= n; i++) {
        nodes[i].dist = INF;
        nodes[i].pred = -1;
        heap.insert(i, nodes[i].dist);
    }

    nodes[r].dist = 0;
    heap.decreaseKey(r, 0);

    int cost = 0;
    while (heap.getSize() > 0) {

        int u = heap.removeMin();
        cost += nodes[u].dist;

        for (Edge edge: nodes[u].adj) {

            int peso = edge.duration;
            int dest = edge.dest;

            if (heap.hasKey(dest) && nodes[dest].dist > peso) {
                nodes[dest].dist = peso;
                nodes[dest].pred = u;
                heap.decreaseKey(dest, peso);
            }
        }
    }
    return cost;
}

void Graph::activity_readyAt() {
    for (int i = 2; i <= n; ++i) {
        nodes[i].dist = 0;
    }
    nodes[1].dist = 0;
    auto lst = topologicalSorting();
    while (!lst.empty()){
        int i = lst.top();
        lst.pop();
        for (auto& e : nodes[i].adj) {
            int w = e.dest;
            if (nodes[w].dist < nodes[i].dist+ e.duration && e.flow > 0) { // TODO: e.flow esta correto? yup, ma friend
                nodes[w].dist = nodes[i].dist+ e.duration;
            }
        }
    }
}
void Graph::print_readyAt() {
    cout << "Node: "<< n << " Ready at: " << nodes[n].dist << endl;
}

void Graph::max_waited_time() {

    int max = 0;
    list<Node> nodesOfMaxWait;
    for (auto n : nodes) {
        for ( auto & e : n.adj) {
            if (n.dist + e.duration < nodes[e.dest].dist && e.flow > 0 && nodes[e.dest].FT_MAX < n.dist + e.duration) {
                nodes[e.dest].FT_MAX = n.dist + e.duration;
                if (nodes[e.dest].FT_MAX > max) {
                    max = nodes[e.dest].FT_MAX;
                    nodesOfMaxWait.empty();
                    nodesOfMaxWait.push_back(nodes[e.dest]);
                } else if (nodes[e.dest].FT_MAX == max) {
                    nodesOfMaxWait.push_back(nodes[e.dest]);
                }
            }
        }
    }

    for (auto n : nodesOfMaxWait) {
        cout <<"Node max:  "<< n.FT_MAX << " at " << "TODO::NEED:TOO KNOW THE NODE ID" << endl;
    }
}

void Graph::max_path_dag() {
    for (int i = 1; i <= n; ++i) {
        nodes[i].pred = NULL;
        nodes[i].dist = 0;
        nodes[i].degree = 0;
    }
    for(int i = 1; i <= n; ++i) {
        for (auto & e : nodes[i].adj) {
            if (e.flow > 0)
                nodes[e.dest].degree++;
        }
    }
    queue<int> S;
    for (int i = 1; i <= n ; ++i) {
        if (nodes[i].degree == 0 )
            S.push(i);
    }

    int durMin = -1, vf = NULL;

    while (!S.empty()) {
        int v = S.front();
        S.pop();
        if (durMin < nodes[v].dist) {
            durMin = nodes[v].dist;
            vf = v;
        }
        for (auto &e : nodes[v].adj) {
            if  (nodes[e.dest].dist < nodes[v].dist + e.duration && e.flow > 0) {
                nodes[e.dest].dist = nodes[v].dist + e.duration;
                nodes[e.dest].pred = v;
            }
            nodes[e.dest].degree--;
            if (nodes[e.dest].degree == 0)
                S.push(e.dest);
        }
    }
}
