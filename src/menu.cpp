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

char askChar() {
    char c;
    cout << ">> ";
    cin >> c;
    cin.clear();
    cin.ignore(1000, '\n');
    return c;
}

int Menu::askInt(string message) {
    cout << message;
    string userInput;
    int response;
    while (true) {
        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "\nInvalid Input!\n";
                continue;
            }

            try {
                response = stoi(userInput);
                return response;
            } catch (invalid_argument ) {
                cout << "\nInvalid Input!\n";
                continue;
            } catch (out_of_range) {
                cout << "\nInvalid Input!\n";
                continue;
            }

        } else {
            cout << "\nInvalid Input!\n";
            getchar();
            continue;
        }
    }
}


void Menu::displayResults(int capacity, list<int> path) {
    cout << "  The path will be: ";
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n  The max group size of this path is: " << capacity << endl;
}


void Menu::start() {
    char userInput;
    while (true) {
        (void) system(CLEAR);

        cout << "========================" << endl;
        cout << "        Scenarios       " << endl;
        cout << "========================" << endl;
        cout << "  1)  Scenario 1        " << endl;
        cout << "  2)  Scenario 2        " << endl;
        cout << "  0)  Exit              " << endl;
        cout << "========================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                continue;
            }

            pair<string, string> files;
            switch (userInput) {
                case '0':
                    return;
                case '1':
                    scenario1();
                    break;
                case '2':
                    scenario2();
                    break;
                default:
                    cout << "Invalid Input!\n";
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!\n";
            getchar();
            continue;
        }
    }
}



void Menu::scenario1() {
    char userInput;
    (void) system(CLEAR);

    cout << "==============================================" << endl;
    cout << "                   Scenario 1                 " << endl;
    cout << "==============================================" << endl;
    cout << "   1)  Maximize Group Size                    " << endl;
    cout << "   2)  Maximize Group Size with Shortest Path " << endl;
    cout << "   3)  Minimize Path with with Max Group Size " << endl;
    cout << "   0)  Exit                                   " << endl;
    cout << "==============================================" << endl;
    cout << "\n > ";


    while (true) {
        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                continue;
            }

            switch (userInput) {
                case '0':
                    return;
                case '1':
                    scenario1_1();
                    return;
                case '2':
                    scenario1_2();
                    return;
                case '3':
                    scenario1_3();
                    return;
                default:
                    cout << "Invalid Input!\n";
                    continue;
            }
        } else {
            cout << "Invalid Input!\n";
            getchar();
            continue;
        }
    }

    getchar();
}

void Menu::scenario1_1() {
    // Check the if they exist
    int dataSetId = askInt("  Enter Data set id:  ");
    int begin = askInt("  Enter number of starting stop: ");
    int end = askInt("  Enter the number of ending stop: ");
    Graph graph = buildGraph(dataSetId, true);
    int capacity = graph.maximum_capacity(begin, end);
    list<int> path = graph.get_path(begin, end);
    displayResults(capacity, path);
}

void Menu::scenario1_2() {
    int dataSetId = askInt("  Enter Data set id:  ");
    int begin = askInt("  Enter number of starting stop: ");
    int end = askInt("  Enter the number of ending stop: ");
    Graph graph = buildGraph(dataSetId, true);
    int capacity = graph.maximum_capacity_with_shortest_path(begin, end);
    list<int> path = graph.get_path(begin, end);
    displayResults(capacity, path);
}

void Menu::scenario1_3() {
    int dataSetId = askInt("  Enter Data set id:  ");
    int begin = askInt("  Enter number of starting stop: ");
    int end = askInt("  Enter the number of ending stop: ");
    Graph graph = buildGraph(dataSetId, true);
    int capacity = graph.shortest_path_with_maximum_capacity(begin, end);
    list<int> path = graph.get_path(begin, end);
    displayResults(capacity, path);
}



void Menu::scenario2() {

    cout << " Scenario 2!\n";
    getchar();
}




