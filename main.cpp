#include "include/menu.h"
#include "include/timer.h"

using namespace std;

int main() {

    cout << "Edmonds-Karp\n";
    double time = 0;
    Graph graph = buildGraph(403, true);
    Timer::start();
    int maxF = graph.edmonds_karp();
    time += Timer::getCurrentTime();
    cout << "Flow: " << maxF << "\tTime taken: " << (double) time << "\n";

    time = 0;
    cout << "\nDinics\n";
    graph = buildGraph(403, true);
    Timer::start();
    maxF = graph.dinic_algo();
    time += Timer::getCurrentTime();
    cout << "Flow: " << maxF << "\tTime taken: " << (double) time << "\n";

    return 0;
}

/*    for (int ex_num = 1; ex_num <= 10; ex_num++) {
        double time = 0;
        for (int i = 0; i < 20; i++) {
            Graph graph = buildGraph(1, false);
            Timer::start();
            graph.shortest_path_with_maximum_capacity(-1, -1);
            graph.get_path(-1, -1);
            time += Timer::getCurrentTime();
        }
        cout << "Ex: " << ex_num << "\t|\tTime taken: " << (double) time / (double) 20.0 << "\n";
    }
    return 0;*/


/*
    cout << "Edmonds-Karp\n\n";
    for (int ex_num = 1; ex_num <= 10; ex_num++) {
        double time = 0;

        for (int i = 0; i < 20; i++) {
            Graph graph = buildGraph(ex_num, true);
            Timer::start();
            graph.edmonds_karp();
            time += Timer::getCurrentTime();
        }
        cout << "Ex: " << ex_num << "\t|\tTime taken: " << (double) time / (double) 20.0 << "\n";
    }

    cout << "\n\nDinics\n\n";
    for (int ex_num = 1; ex_num <= 10; ex_num++) {
        double time = 0;

        for (int i = 0; i < 20; i++) {
            Graph graph = buildGraph(ex_num, true);
            Timer::start();
            graph.dinic_algo();
            time += Timer::getCurrentTime();
        }
        cout << "Ex: " << ex_num << "\t|\tTime taken: " << (double) time / (double) 20.0 << "\n";
    }
*/
