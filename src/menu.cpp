#include "../include/menu.h"

string trimStr(string str) {
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}

bool emptyStream(istream &ios) {
    string bufferContent;
    getline(ios, bufferContent);
    trimStr(bufferContent);
    if (bufferContent.empty())
        return true;
    return false;
}

int Menu::askInt(const string &message) {
    cout << message;
    string userInput;

    if ((cin >> userInput)) {
        if (!emptyStream(cin))
            goto END;
        try {
            int response = stoi(userInput);
            return response;
            //NOLINTNEXTLINE
        } catch (exception) {
            goto END;
        }
    }

    END:
    cout << "\nInvalid Input!\n";
    cin.clear();
    cin.ignore(1000, '\n');
    return -1;
}

void Menu::displayResults(int capacity, const list<int> &path) {
    cout << "\nThe path will be:\n";
    for (const int &it: path)
        cout << it << "  ";
    cout << "\n Path size: " << path.size();
    cout << "\n\nThe max group size of this path is: " << capacity << endl;
}

void Menu::start() {

    char userInput;
    while (true) {
        (void) system(CLEAR);

        cout << "===============================================" << endl;
        cout << "                   Scenarios                   " << endl;
        cout << "===============================================" << endl;
        cout << "   1)  Max Capacity Path (No Group Division)   " << endl;
        cout << "   2)  Max Flow (Group Division)               " << endl;
        cout << "   0)  Exit                                    " << endl;
        cout << "===============================================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin))
                continue;

            pair<string, string> files;
            switch (userInput) {
                case '0':
                    return;
                case '1':
                    submenu1();
                    break;
                case '2':
                    submenu2();
                    break;
                default:
                    break;
            }
            continue;

        } else
            continue;
    }
}

void Menu::submenu1() {

    char userInput;
    while (true) {
        (void) system(CLEAR);

        cout << "==============================================" << endl;
        cout << "                  Scenario 1                  " << endl;
        cout << "==============================================" << endl;
        cout << "   1)  Maximize Group Size                    " << endl;
        cout << "   2)  Maximize Group Size VS Shortest Path   " << endl;
        cout << "   0)  Go Back                                " << endl;
        cout << "==============================================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin))
                continue;

            switch (userInput) {
                case '0':
                    return;
                case '1':
                    scenario1(1);
                    return;
                case '2':
                    scenario1(2);
                    return;
                default:
                    continue;
            }
        } else
            continue;

    }
}

void Menu::scenario1(int option) {

    int dataSetId = askInt("\nEnter Data set id: ");
    if (dataSetId == -1) return;
    int begin = askInt("Enter number of starting stop: ");
    if (begin == -1) return;
    int end = askInt("Enter the number of ending stop: ");
    if (end == -1) return;

    Graph graph = buildGraph(dataSetId, false);

    int capacity;
    if (option == 1) {
        capacity = graph.maximum_capacity(begin, end);
        list<int> path = graph.get_path(begin, end);
        displayResults(capacity, path);
    } else {

        int capacity1 = graph.maximum_capacity_with_shortest_path(begin, end);
        list<int> path1 = graph.get_path(begin, end);

        int capacity2 = graph.shortest_path_with_maximum_capacity(begin, end);
        list<int> path2 = graph.get_path(begin, end);

        if (capacity1 == capacity2) {
            cout << "\nBoth algorithms reached same max capacity value. Showing shortest path.\n\n";
            displayResults(capacity2, path2);
        } else {
            cout << "\nTwo solutions were computed:\n\n(Max Capacity with shortest path)\n";
            displayResults(capacity1, path1);
            cout << "\n(Shortest path with max Capacity)\n";
            displayResults(capacity2, path2);

            cout << "\nHowever, there are solutions not represented in the scope. \n";
            cout << "Those solutions are not parameter optimal but rather balanced solutions\n";
            cout << "Here are the best balance solutions ... \n\n";

            bool morePathImprovement = true;
            bool moreCapImprovement = true;
            int newCap;
            list<int> path3;
            int newCapMinPath;
            list<int> path4;
            while (moreCapImprovement || morePathImprovement) {
                if (moreCapImprovement) {
                    newCap = graph.maximum_capacity_with_shortest_path(begin, end, capacity1);
                    path3 = graph.get_path(begin, end);
                }
                if (newCap == -1)
                    moreCapImprovement = false;
                if ((newCap > capacity2) && (path3.size() < path1.size())) {
                    displayResults(newCap, path3);
                    capacity1 = newCap;
                    path1 = path3;
                } else {
                    capacity1 = newCap;
                }
                if (morePathImprovement) {
                    newCapMinPath = graph.shortest_path_with_maximum_capacity(begin, end, (int) path2.size() - 1);
                    path4 = graph.get_path(begin, end);
                }
                if (newCapMinPath == 0)
                    morePathImprovement = false;
                else {
                    if ((path4.size() < path3.size()) && (newCapMinPath < newCap)) {
                        displayResults(newCapMinPath, path4);
                        capacity2 = newCapMinPath;
                        path2 = path4;
                    } else {
                        path2 = path4;
                    }
                }
            }
        }
    }
    getchar();
}

void Menu::scenario2(int option) {

    int dataSetId = askInt("\nEnter Data set id: ");
    if (dataSetId == -1) return;

    Graph graph = buildGraph(dataSetId, true);
    cout << endl;

    int groupSize = 0;
    if (option == 1) {
        groupSize = askInt("Group size: ");
        if (groupSize == -1) return;

        if(graph.cen_2_1(groupSize))
            goto TIMES;
    }

    int maxFlow;
    cout << "Flow Paths:\n";
    if (option != 3)
        maxFlow = graph.edmonds_karp(groupSize);
    else
        maxFlow = graph.dinic_algo();
    cout << "\nMax flow is: " << maxFlow;

    TIMES:
    cout << "\n\n=====================================\n\n";
    graph.max_path_dag();
    graph.print_readyAt();
    graph.critical_path_lf();

    graph.max_FL();
    graph.max_FT();

    getchar();
}

void Menu::submenu2() {

    char userInput;
    while (true) {
        (void) system(CLEAR);

        cout << "=====================================" << endl;
        cout << "              Scenario 2             " << endl;
        cout << "=====================================" << endl;
        cout << "   1)  User Given Group Size         " << endl;
        cout << "   2)  Max Group Size                " << endl;
        cout << "   3)  Dinic's solution              " << endl;
        cout << "   0)  Go Back                       " << endl;
        cout << "=====================================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin))
                continue;

            switch (userInput) {
                case '0':
                    return;
                case '1':
                    scenario2(1);
                    return;
                case '2':
                    scenario2(2);
                    return;
                case '3':
                    scenario2(3);
                    return;
                default:
                    continue;
            }
        } else
            continue;
    }
}




