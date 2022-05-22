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

                //NOLINTNEXTLINE
            } catch (exception) {
                cout << "\nInvalid Input!\n";
                cin.clear();
                continue;
            }

        } else {
            cout << "\nInvalid Input!\n";
            getchar();
            continue;
        }
    }
}


void Menu::displayResults(int capacity, const list<int> &path) {
    cout << "The path will be:\n";
    for (const int &it: path)
        cout << it << "  ";
    cout << "\n\nThe max group size of this path is:\n" << capacity << endl;
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
                    submenu1();
                    break;
                case '2':
                    submenu2();
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


void Menu::submenu1() {
    char userInput;
    (void) system(CLEAR);

    cout << "==============================================" << endl;
    cout << "                   Scenario 1                 " << endl;
    cout << "==============================================" << endl;
    cout << "   1)  Maximize Group Size                    " << endl;
    cout << "   2)  Maximize Group Size VS Shortest Path " << endl;
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
                    scenario1(1);
                    return;
                case '2':
                    scenario1(2);
                    return;
                case '3':
                    scenario1(3);
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
}


void Menu::scenario1(int option) {
    // Check the if they exist
    int dataSetId = askInt("\nEnter Data set id:  ");
    int begin = askInt("Enter number of starting stop: ");
    int end = askInt("Enter the number of ending stop: ");
    Graph graph = buildGraph(dataSetId, true);

    int capacity;

    if (option == 1)
        capacity = graph.maximum_capacity(begin, end);
    else if (option == 2)
        capacity = graph.maximum_capacity_with_shortest_path(begin, end);
    else
        capacity = graph.shortest_path_with_maximum_capacity(begin, end);

    list<int> path = graph.get_path(begin, end);
    displayResults(capacity, path);
    getchar();
}


void Menu::submenu2() {
    char userInput;
    (void) system(CLEAR);

    cout << "==============================================" << endl;
    cout << "                   Scenario 2                 " << endl;
    cout << "==============================================" << endl;
    cout << "   1)  2.1                                    " << endl;
    cout << "   2)  2.2                                    " << endl;
    cout << "   3)  2.3                                    " << endl;
    cout << "   4)  2.4                                    " << endl;
    cout << "   5)  2.5                                    " << endl;
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
                    scenario2(1);
                    return;
                case '2':
                    scenario2(2);
                    return;
                case '3':
                    scenario2(3);
                    return;
                case '4':
                    scenario2(4);
                    return;
                case '5':
                    scenario2(5);
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
}


void Menu::scenario2(int option) {
    /*
    // Check the if they exist
    int dataSetId = askInt("\nEnter Data set id:  ");
    int begin = askInt("Enter number of starting stop: ");
    int end = askInt("Enter the number of ending stop: ");
    Graph graph = buildGraph(dataSetId, true);


    int capacity;

    if (option == 1)
        capacity = graph.maximum_capacity(begin, end);
    else if (option == 2)
        capacity = graph.maximum_capacity_with_shortest_path(begin, end);
    else
        capacity = graph.shortest_path_with_maximum_capacity(begin, end);

    list<int> path = graph.get_path(begin, end);
    displayResults(capacity, path);
    getchar();
    */
}




