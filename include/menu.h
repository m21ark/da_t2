#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "graph.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#define TERMINAL_CLEAR  if(system(CLEAR)){}

using namespace std;

/**
 * Removes empty spaces from the start and end of a string
 * @param str string to be trimmed
 * @return trimmed string
 */
string trimStr(string str);

/**
 * Tests if IOstream buffer is empty
 * @param ios buffer to be tested
 * @return boolean if buffer is empty
 */
bool emptyStream(istream &ios);


/**
 * Simple Menu Terminal GUI
 * prompting user to choose one of the 3 scenarios
 */
class Menu {
public:
    /**
     * Starts the Menu Terminal GUI
     */
    static void start();

    static int askInt(const string &message);

    static void displayResults(int capacity, const list<int> &path);

private:

    static void submenu1();

    static void scenario1(int option);

    static void submenu2();

    static void scenario2(int option);

};


#endif //MENU_H