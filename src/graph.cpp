#include "../include/graph.h"


Graph::Graph(int num, bool dir) : n(num), includeResidual(dir), nodes(num + 2) {}

void Graph::addEdge(int src, int dest, int duration, int cap) {

    if (src < 1 || src > n || dest < 1 || dest > n)
        return;

    nodes[src].adj.push_back({dest, duration, cap, 0, cap});

    if (includeResidual)
        nodes[dest].adj.push_back({src, duration, 0, 0, 0});
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


int Graph::maximum_capacity_with_shortest_path(int a, int b, int max) {
    a = 1;
    b = n;

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
            bool b3 = newCap < max;
            if ((b1 || b2) && b3) {
                nodes[it->dest].capacity = newCap;
                nodes[it->dest].dist = newDist;
                nodes[it->dest].pred = u;
                if (b1) maxHeap.increaseKey(it->dest, newCap);
            }
        }
    }
    return nodes[b].capacity;
}

int Graph::shortest_path_with_maximum_capacity(int a, int b, int mini) {
    a = 1;
    b = n;
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
            bool b3 = (it->dest != b || newDist > mini);

            if ((b1 || b2) && b3) {
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

    a = 1;
    b = n;

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


stack<int> Graph::topologicalSorting() {

    for (int i = 1; i <= n; i++)
        nodes[i].visited = false;

    stack<int> order;

    for (int i = 1; i <= n; i++)
        if (!nodes[i].visited)
            dfsTopSort(i, order);

    return order;
}

//NOLINTNEXTLINE
void Graph::dfsTopSort(int v, stack<int> &l) {
    nodes[v].visited = true;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfsTopSort(w, l);
    }
    l.push(v);
}

//NOLINTNEXTLINE
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


void Graph::activity_readyAt() {
    for (int i = 2; i <= n; ++i) {
        nodes[i].dist = 0;
    }
    nodes[1].dist = 0;
    auto lst = topologicalSorting();
    while (!lst.empty()) {
        int i = lst.top();
        lst.pop();
        for (auto &e: nodes[i].adj) {
            int w = e.dest;
            if (nodes[w].dist < nodes[i].dist + e.duration && e.flow > 0) { // TODO: e.flow esta correto? yup, ma friend
                nodes[w].dist = nodes[i].dist + e.duration;
            }
        }
    }
}

void Graph::print_readyAt() {
    cout << "Node: " << n << " Ready at: " << nodes[n].dist << endl;
}

void Graph::max_waited_time() {

    int max = 0;
    list<Node> nodesOfMaxWait;
    for (auto n: nodes) {
        for (auto &e: n.adj) {
            if (n.dist + e.duration < nodes[e.dest].dist && e.flow > 0 && nodes[e.dest].FT_MAX < n.dist + e.duration) {
                nodes[e.dest].FT_MAX = n.dist + e.duration;
                if (nodes[e.dest].FT_MAX > max) {
                    max = nodes[e.dest].FT_MAX;
                    nodesOfMaxWait.clear();
                    nodesOfMaxWait.push_back(nodes[e.dest]);
                } else if (nodes[e.dest].FT_MAX == max) {
                    nodesOfMaxWait.push_back(nodes[e.dest]);
                }
            }
        }
    }

    for (auto n: nodesOfMaxWait) {
        cout << "Node max Wait:  " << n.FT_MAX << " at " << "TODO::NEED:TOO KNOW THE NODE ID" << endl;
    }

    if (nodesOfMaxWait.empty())
        cout << "No Waiting breaks" << endl;
}

void Graph::max_path_dag() {
    for (int i = 1; i <= n; ++i) {
        nodes[i].pred = -1;
        nodes[i].dist = 0;
        nodes[i].degree = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (auto &e: nodes[i].adj) {
            if (e.flow > 0)
                nodes[e.dest].degree++;
        }
    }
    queue<int> S;
    for (int i = 1; i <= n; ++i) {
        if (nodes[i].degree == 0)
            S.push(i);
    }

    int durMin = -1, vf = -1;

    while (!S.empty()) {
        int v = S.front();
        S.pop();
        if (durMin < nodes[v].dist) {
            durMin = nodes[v].dist;
            vf = v;
        }
        for (auto &e: nodes[v].adj) {
            if (nodes[e.dest].dist < nodes[v].dist + e.duration && e.flow > 0) {
                nodes[e.dest].dist = nodes[v].dist + e.duration;
                nodes[e.dest].pred = v;
            }
            nodes[e.dest].degree--;
            if (nodes[e.dest].degree == 0)
                S.push(e.dest);
        }
    }
}


void Graph::cen_2_1(int groupSize) {

    int maxCapPath = maximum_capacity_with_shortest_path(1, n);

    if (maxCapPath >= groupSize) {

        cout << "\nA path was found where the group doesnt need to break apart:\n";
        list<int> path = get_path(1, n);

        cout << "\nThe path will be:\n";
        for (const int &it: path)
            cout << it << " ";
        cout << "\n\nThe max group size of this path is:\n" << maxCapPath << endl;

        return;
    }

    cout << "ADD LIMITING NODE AT START!";
}


// ======================= EDMONDS KARP ==============================

int Graph::edmonds_karp_bfs(int s, int t) {
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

        for (auto e: nodes[node].adj)
            if (e.residual > 0 && !nodes[e.dest].visited) {
                nodes[e.dest].pred = node;
                nodes[e.dest].visited = true;
                q.push(e.dest);
            }
    }

    // no path to the sink
    if (!nodes[t].visited) return 1;
    return 0;
}

int Graph::edmonds_karp() {
    int flow, maxFlow = 0;
    do {
        flow = edmonds_karp_flow_path(1, n);
/*        if (flow)
            cout << "New found flow = " << flow << endl;*/
        maxFlow += flow;
    } while (flow != 0);
    return maxFlow;
}

bool Graph::bfs_sink(int s, int v) {
    for (int i = 1; i <= n; ++i) {
        nodes[i].level = -1;
        nodes[i].visited = false;
    }

    queue<int> q; // queue of unvisited nodes
    q.push(s);

    nodes[s].visited = true;
    nodes[s].level = 0;

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // cout << u << " "; // show node order
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited && e.flow < e.cap) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].level = nodes[u].level + 1;
            }
        }
    }

    return nodes[v].visited;
}

int Graph::send_dinic_flow(int s, int flow, int t) {

    if (s == t) {
/*        cout << t << "\n";*/
        return flow;
    }
/*    cout << s << " --> ";*/

    for (auto &e: nodes[s].adj) {
        if (nodes[e.dest].level == nodes[s].level + 1 && e.flow < e.cap) {
            int cur_flow = min(flow, e.cap - e.flow);
            int temp_flow = send_dinic_flow(e.dest, cur_flow, t);

            if (temp_flow > 0) {

                e.flow += temp_flow;

                for (auto &e2: nodes[e.dest].adj) {
                    if (e2.dest == s) {
                        e2.flow -= temp_flow;
                    }
                }
                return temp_flow;
            }
        }
    }

    return 0;
}

int Graph::dinic_algo() {

    int total = 0;

    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].pred = -1;
    }

    while (bfs_sink(1, n)) {
        while (int flow = send_dinic_flow(1, INT_MAX, n))
            total += flow;
    }


    return total;
}


int Graph::edmonds_karp_flow_path(int s, int t) {

    // Get nodes distance from S
    if (edmonds_karp_bfs(s, t))
        return 0;

    // Get path flow bottleneck
    int bottleNeck = getPathBottleNeck(s, t);

    // Update the flows & residual edges values
    edmonds_karp_update(bottleNeck, s, t);

    return bottleNeck;
}

void Graph::edmonds_karp_update(int bottleNeck, int s, int t) {
    int parent = t, child;
   /* cout << t << " --> ";*/
    while (parent != s) {
        child = parent;
        parent = nodes[parent].pred;
/*        cout << parent << " --> ";*/

        for (Edge &e: nodes[parent].adj)
            if (e.dest == child) {

                if (e.cap != 0) {
                    e.residual -= bottleNeck;
                    e.flow += bottleNeck;
                    for (auto &e2: nodes[e.dest].adj)
                        if (e2.dest == parent) {
                            e2.residual += bottleNeck;
                            e2.flow -= bottleNeck;
                            break;
                        }
                } else
                    for (auto &e2: nodes[e.dest].adj)
                        if (e2.dest == parent)
                            e2.flow -= bottleNeck;
            }
    }
}

int Graph::getPathBottleNeck(int start, int end) {
    int bottleNeck = INT_MAX;
    int parent = end;
    int child;

    while (parent != start) {
        child = parent;
        parent = nodes[parent].pred;

        for (Edge &e: nodes[parent].adj)
            if (e.dest == child) {
                bottleNeck = min(bottleNeck, e.cap - e.flow);
                break;
            }
    }
    return bottleNeck;
}

void Graph::printEdges() {
    for (int i = 1; i <= n; i++)
        for (Edge e: nodes[i].adj)
            printf("src: %d\tdest: %d\tcap: %d\tflow: %d\tresidualVal: %d\tresidual? %d\n", i, e.dest, e.cap,
                   e.flow, e.residual, e.cap == 0);
}