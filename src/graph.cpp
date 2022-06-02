#include "../include/graph.h"


Graph::Graph(int num, bool dir) : n(num), includeResidual(dir), nodes(num + 2) {}

void Graph::addEdge(int src, int dest, int duration, int cap) {

    if (src < 1 || src > n + 2 || dest < 1 || dest > n)
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


//NOLINTNEXTLINE
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


/* TODO Unico sitio onde é usada é noutra funcao q n e usada. @Ricardo
 * stack<int> Graph::topologicalSorting() {

    for (int i = 1; i <= n; i++)
        nodes[i].visited = false;

    stack<int> order;

    for (int i = 1; i <= n; i++)
        if (!nodes[i].visited)
            dfsTopSort(i, order);

    return order;
}*/

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

/*
 // TODO Ricardo vê se esta funcao e util ou n (n estava a ser usada)
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
*/

void Graph::print_readyAt() {
    cout << "Node: " << n << " Ready at: " << nodes[n].ES << endl;
}


void Graph::max_path_dag() {
    for (int i = 1; i <= n; ++i) {
        nodes[i].pred = -1;
        nodes[i].ES = 0;
        nodes[i].degree = 0;
    }

    for (int i = 1; i <= n; ++i)
        for (auto &e: nodes[i].adj)
            if (e.flow > 0)
                nodes[e.dest].degree++;

    queue<int> S;
    for (int i = 1; i <= n; ++i)
        if (nodes[i].degree == 0)
            S.push(i);

    int durMin = -1;

    while (!S.empty()) {

        int v = S.front();
        S.pop();
        if (durMin < nodes[v].ES)
            durMin = nodes[v].ES;

        for (auto &e: nodes[v].adj) {

            if (nodes[e.dest].ES < nodes[v].ES + e.duration && e.flow > 0) {
                nodes[e.dest].ES = nodes[v].ES + e.duration;
                nodes[e.dest].pred = v;
            }

            nodes[e.dest].degree--;
            if (nodes[e.dest].degree == 0)
                S.push(e.dest);
        }
    }
}


bool Graph::cen_2_1(int groupSize) {

    int maxCapPath = maximum_capacity_with_shortest_path(1, n);

    if (maxCapPath >= groupSize) {

        cout << "\nA path was found where the group doesnt need to break apart:\n";
        list<int> path = get_path(1, n);

        cout << "\nThe path will be:\n";
        for (const int &it: path)
            cout << it << " ";
        cout << "\n\nThe max group size of this path is: " << maxCapPath << endl;

        return true;
    }
    return false;
}

int Graph::edmonds_karp_bfs(int s, int t) {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].pred = -1;
        nodes[i].dist = -1;
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
                nodes[e.dest].dist = nodes[node].dist + 1;
                q.push(e.dest);
            }
    }

    // no path to the sink
    if (!nodes[t].visited) return 1;
    return 0;
}

int Graph::edmonds_karp(int groupSize_limiter) {

    if (groupSize_limiter)
        addEdge(n + 1, 1, 0, groupSize_limiter);

    int flow, maxFlow = 0;
    do {

        if (!groupSize_limiter)
            flow = edmonds_karp_flow_path(1, n);
        else
            flow = edmonds_karp_flow_path(n + 1, n);

        if (flow)
            if (nodes[n].dist < 20)
                cout << "New flow = " << flow << endl;

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

//NOLINTNEXTLINE
int Graph::send_dinic_flow(int s, int flow, int t) {

    if (s == t) {
        if (nodes[n].dist < 20)
            cout << t << "\n";
        return flow;
    }
    if (nodes[n].dist < 20)
        cout << s << " --> ";

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

    if (nodes[t].dist < 20)
        cout << t << " <-- ";

    while (parent != s) {
        child = parent;
        parent = nodes[parent].pred;

        if (nodes[t].dist < 20)
            cout << ((parent == n + 1) ? 0 : parent) << " <-- ";

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

// TODO: POTENTIAL PROBLEM HERE! WE'RE CREATING A NEW GRAPH WITH N SIZE WHILE THE ORIGINAL VECTOR HAS N+2!!!
Graph *Graph::transpose() {
    auto *graph = new Graph(n, true);
    for (int i = 1; i <= n; ++i) {
        for (auto e: nodes[i].adj) {
            graph->addEdge(e.dest, i, e.duration, e.cap);
            graph->nodes[e.dest].visited = nodes[e.dest].visited;
        }
    }
    return graph;
}

void Graph::critical_path_lf() {
    for (int i = 1; i <= n; ++i) {
        nodes[i].pred = -1;
        nodes[i].LF = nodes[n].ES; // needs to be called after ES
        nodes[i].degree = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (auto &e: nodes[i].adj) {
            if (e.flow > 0)
                nodes[e.dest].degree++;
        }
    }

    auto gt = transpose();

    queue<int> S;
    for (int i = 1; i <= n; ++i) {
        if (nodes[i].degree == 0)
            S.push(i);
    }

    while (!S.empty()) {
        int v = S.front();
        S.pop();
        for (auto &e: gt->nodes[v].adj) {
            if (e.flow > 0 && nodes[e.dest].LF > nodes[v].LF - e.duration) {
                nodes[e.dest].LF = nodes[v].LF - e.duration;
                nodes[e.dest].pred = v;
            }
            nodes[e.dest].degree--;
            if (nodes[e.dest].degree == 0)
                S.push(e.dest);
        }
    }
}

void Graph::max_FL() {

    cout << "If schedule does not have any delay:\n";
    int max_Fl = 0;
    set<int> lst;
    for (auto &node: nodes) {
        for (auto &e: node.adj) {
            int fl = nodes[e.dest].ES - (node.ES + e.duration);
            if (fl > max_Fl && e.flow > 0) {
                lst.clear();
                lst.insert(e.dest);
                max_Fl = fl;
            } else if (fl == max_Fl && max_Fl != 0) {
                lst.insert(e.dest);
            }
        }
    }

    for (auto i: lst) {
        cout << "Node max Wait:  " << max_Fl << " at " << i << endl;
    }

    if (lst.empty())
        cout << "No Waiting breaks" << endl;

}

void Graph::max_FT() {
    int max_FT = 0;
    for (auto &node: nodes) {
        for (auto &e: node.adj) {
            int ls = nodes[e.dest].LF - e.duration;
            int ft = ls - node.ES;
            if (ft > max_FT && e.flow > 0) {
                max_FT = ft;
            }
        }
    }

    if (max_FT == 0)
        cout << "\n\nThere is no Total 'day' off " << endl;
    else
        cout << "\nTotal MAX freedom / (day of, or FT): " << max_FT << endl;
}
